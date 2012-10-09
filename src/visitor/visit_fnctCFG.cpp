/***************************************************************************
			   visit_fnctCFG.cpp  -  description
			      -------------------
     begin                : Aug 28 2001
     copyright            : (C) 2001 by Gianluca Masone
     email                : lucas75it@yahoo.it
***************************************************************************/
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "visitor/visit_fnctCFG.h"

// ---------------------------------------------------------------------------
//  MEMBERS
// ---------------------------------------------------------------------------


// visit statements
void
visit_fnctCFG::visit_break_stmt (break_stmt_n * np)
{
  nast_node *child;
    
  takeIndex(np);

  // make edge to the nearest cycle or switch
  nast_node *basePoint = breakStack.top();
  nast_node *exitPoint = nextNodeMap[basePoint];
  addEdge(np, exitPoint, "U");

  // If the exit point is a DO_STMT and the lastNodeStac.top
  // is a SWITCH_STMT then we have a pending DO_STMT to complete
  if ( (exitPoint->getCode() == DO_STMT) && 
       ((lastCycleCond.top())->getCode() == SWITCH_STMT) ) {
    addEdge(nodeBeforeDo[exitPoint], firstStmtInDo[exitPoint], 
	    labelBeforeDo[exitPoint]);
    addEdge(exitPoint, firstStmtInDo[exitPoint],"T");
    addEdge(exitPoint, nextNodeMap[exitPoint], "F");
  } 

  // Visit next statement but don't make any edge
  if ((child = nextNodeMap[np]))
    child->accept(*this);
  
  return;
}

void
visit_fnctCFG::visit_continue_stmt (continue_stmt_n * np)
{
  nast_node *child;

  takeIndex(np);

  // make edge to the nearest cycle or switch
  nast_node *reiterPoint = continueStack.top();
  addEdge(np, reiterPoint, "U");

  // Visit next statement but don't make any edge
  if ((child = nextNodeMap[np]))
    child->accept(*this);

  return;
}

void
visit_fnctCFG::visit_scope_stmt (scope_stmt_n * np)
{
  // This method could not be use !
  // But it is here only for safe reason.

  nast_node *child;
  
  takeIndex(np);
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    addEdge(np, child, "U");
    child->accept(*this);
  } else makePendingFromCurrentNode(np);

  return;
}

void
visit_fnctCFG::visit_decl_stmt (decl_stmt_n * np)
{
  nast_node *child;
  
  takeIndex(np);

  // Visit next stmt if there is
  if ((child = nextNodeMap[np])) {

    //
    // Make an edge to the next stmt only
    // if itsn't a DO_STMT
    //
    if (!weAreBeforeDo(np, "U"))
      addEdge(np, child, "U");
    
    child->accept(*this);

  } else 
    // It's a last node of chain
    makePendingFromCurrentNode(np);

  return;
}

void
visit_fnctCFG::visit_expr_stmt (expr_stmt_n * np)
{
  nast_node *child;
  
  takeIndex(np);

  // Is a loop_expr ?
  if (np->hasEdgeName(EXPRESSION_EDGE)) {
    child = np->edgeName(EXPRESSION_EDGE);

    if (child->getCode() == LOOP_EXPR) {
      addEdge(np, child, "U");
      child->accept(*this);
    }

  }
  
  // Visit next stmt if there is
  if ((child = nextNodeMap[np])) {

    //
    // Make an edge to the next stmt only
    // if itsn't a DO_STMT
    //
    if (!weAreBeforeDo(np, "U"))
      addEdge(np, child, "U");

    child->accept(*this);

  } else 
    // It's a last node of chain
    makePendingFromCurrentNode(np);


  return;
}

void
visit_fnctCFG::visit_goto_stmt (goto_stmt_n * np)
{
  nast_node *child;
  
  takeIndex(np);

  if (np->hasEdgeName(DESTINATION_EDGE)) {
    //
    // Get the destination and put the pair <destination,goto>
    // into the list pendingGoto
    //
    child = np->edgeName(DESTINATION_EDGE);
    pendingGoto.push_front( make_pair(child, np));
  }

   
  // Visit next stmt if there is
  if ((child = nextNodeMap[np])) 
    // Visit next statement but don't make any edge
    child->accept(*this);
  
  
  return;
}

void
visit_fnctCFG::visit_label_stmt (label_stmt_n * np)
{
  nast_node *child;

  takeIndex(np);
  
  // insert the entry labelFound[label_decl] = label_stmt
  labelFound[np->edgeName(LABEL_NAME_EDGE)] = np;

  // Visit next stmt if there is
  if ((child = nextNodeMap[np])) {

    //
    // Make an edge to the next stmt only
    // if itsn't a DO_STMT
    //
    if (!weAreBeforeDo(np, "U")) 
      addEdge(np, child, "U");

    child->accept(*this);

  } else 
    // It's a last node of chain
    makePendingFromCurrentNode(np);

  return;
}

void
visit_fnctCFG::visit_return_stmt (return_stmt_n * np)
{
  nast_node *child;

  takeIndex(np);

  if ((child = nextNodeMap[np]))
    // Visit next statement but don't make any edge
    child->accept(*this);

  return;
}

void
visit_fnctCFG::visit_if_stmt (if_stmt_n * np)
{
  nast_node *child;

  takeIndex(np);

  // If the next stmt is NULL then in the previous
  // exploreChain(np) we didn't get it.
  //
  // Now, try again !
  // Maybe the next stmt is a previous for, do, or while!
  //
  if (!nextNodeMap[np])
    nextNodeMap[np] = nextExitPoint(np);

  // Push into stacks (the children will link to this IF)
  lastCycleCond.push(np);

  //---- Explore Branches

  //
  // Explore the THEN branch
  //
  if (np->hasEdgeName(THEN_EDGE)) {
    child = np->edgeName(THEN_EDGE);

    // Prolog of the body :
    //
    //   zero or one  COMPOUND_STMT
    //   zero or many SCOPE_STMT
    //   zero or one  COMPOUND_STMT
    // 
    // The body without instructions ahave only SCOPE_STMT.
    // Jump these nodes !
    //
    if (child->getCode() == COMPOUND_STMT)
      child = child->edgeName(BODY_EDGE);
    child = canJumpScopeStmt(child);
    if (child->getCode() == COMPOUND_STMT)
      child = child->edgeName(BODY_EDGE);

    exploreChain(child);

    //
    // Make an edge to the next stmt only
    // if itsn't a DO_STMT
    //
    if (child->getCode() == DO_STMT) {
      labelBeforeDo[child] = "T";
      nodeBeforeDo[child] = np;
    }
    else 
      addEdge(np, child, "T");
    
    child->accept(*this);

  }

  //
  // Explore the ELSE branch
  //
  // If the else branch doesn't exsist make the edge from this if
  // to the next node (if the next node exsist).
  //
  if (np->hasEdgeName(ELSE_EDGE)) {
    child = np->edgeName(ELSE_EDGE);

    // Prolog of the body :
    //
    //   zero or one  COMPOUND_STMT
    //   zero or many SCOPE_STMT
    //   zero or one  COMPOUND_STMT
    // 
    // The body without instructions have only SCOPE_STMT.
    // Jump these nodes !
    //
    if (child->getCode() == COMPOUND_STMT)
      child = child->edgeName(BODY_EDGE);
    child = canJumpScopeStmt(child);
    if (child->getCode() == COMPOUND_STMT)
      child = child->edgeName(BODY_EDGE);

    exploreChain(child);

    //
    // Make an edge to the next stmt only
    // if itsn't a DO_STMT
    //
    if (child->getCode() == DO_STMT) {
      labelBeforeDo[child] = "F";
      nodeBeforeDo[child] = np;
    }
    else
      addEdge(np, child, "F");

    child->accept(*this);

  } else if (nextNodeMap[np])
    addEdge(np, nextNodeMap[np], "F");

  //---- End Exploring Branches

  // Pop from stacks
  lastCycleCond.pop();

  // We use canJumpScopeStmt to avoid the entering
  // into an infinite loop
  //
  // If nextNodeMap[np] point to A and some branch of A point
  // to np, the we have an infinite loop !
  if ((child = canJumpScopeStmt(np)))
    // Visit next statement but don't make any edge
    child->accept(*this);
  else 
    // If the lastCycleCond.top()
    // is a DO_STMT then we have a pending DO_STMT to complete
    if ( (!lastCycleCond.empty()) && 
	 ((lastCycleCond.top())->getCode() == DO_STMT) ) {
      nast_node *doNode = lastCycleCond.top();

      addEdge(nodeBeforeDo[doNode],firstStmtInDo[doNode],labelBeforeDo[doNode]);
      addEdge(doNode, firstStmtInDo[doNode],"T");
      addEdge(doNode, nextNodeMap[doNode], "F");

    }
  
  return;
}

void
visit_fnctCFG::visit_switch_stmt (switch_stmt_n * np)
{
  nast_node *child;
  
  takeIndex(np);

  // If the next stmt is NULL then in the previous
  // exploreChain(np) we didn't get it.
  //
  // Now, try again !
  // Maybe the next stmt is a previous for, do, or while!
  //
  if (!nextNodeMap[np])
    nextNodeMap[np] = nextExitPoint(np);

  // Push into stacks (the children will link to this SWITCH)
  lastCycleCond.push(np);
  breakStack.push(np);
  lastSwitch.push(np);

  //
  // BODY branch
  if (np->hasEdgeName(BODY_EDGE)) {
    child = np->edgeName(BODY_EDGE);
    
    // Prolog of the body :
    //
    //   zero or one  COMPOUND_STMT
    //   zero or many SCOPE_STMT
    //   zero or one  COMPOUND_STMT
    // 
    // The body without instructions have only SCOPE_STMT.
    // Jump these nodes !
    //
    if (child->getCode() == COMPOUND_STMT)
      child = child->edgeName(BODY_EDGE);
    child = canJumpScopeStmt(child);
    if (child->getCode() == COMPOUND_STMT)
      child = child->edgeName(BODY_EDGE);

    // Reach the first case_label
    while ( (child->getCode() != CASE_LABEL) && 
	    (child->hasEdgeName(NEXT_STMT_EDGE)) )
      child = child->edgeName(NEXT_STMT_EDGE);

    exploreChain(child);

    child->accept(*this);
  }

  // Pop from stacks
  lastCycleCond.pop();
  breakStack.pop();
  lastSwitch.pop();
  
  // We use canJumpScopeStmt to avoid the entering
  // into an infinite loop
  //
  // If nextNodeMap[np] point to A and some branch of A point
  // to np, the we have an infinite loop !
  if ((child = canJumpScopeStmt(np)))
    // Visit next statement but don't make any edge
    child->accept(*this);

  return;
}

void
visit_fnctCFG::visit_for_stmt (for_stmt_n * np)
{
  nast_node *child;
  
  takeIndex(np);

  // If the next stmt is NULL then in the previous
  // exploreChain(np) we didn't get it.
  //
  // Now, try again !
  // Maybe the next stmt is a previous for, do, or while!
  //
  if (!nextNodeMap[np])
    nextNodeMap[np] = nextExitPoint(np);

  // Push into stacks (the children will link to this FOR)
  lastCycleCond.push(np);
  breakStack.push(np);
  continueStack.push(np);

  //
  // BODY branch
  if (np->hasEdgeName(BODY_EDGE)) {
    child = np->edgeName(BODY_EDGE);

    // Prolog of the body :
    //
    //   zero or one  COMPOUND_STMT
    //   zero or many SCOPE_STMT
    //   zero or one  COMPOUND_STMT
    // 
    // The body without instructions have only SCOPE_STMT.
    // Jump these nodes !
    // Note the if when we check the chain of scope_stmt ?!
    //
    if (child->getCode() == COMPOUND_STMT)
      child = child->edgeName(BODY_EDGE);
    if ((child = canJumpScopeStmt(child))) {
      if (child->getCode() == COMPOUND_STMT)
	child = child->edgeName(BODY_EDGE);
      
      exploreChain(child);
      
      //
      // Make an edge to the next stmt only
      // if itsn't a DO_STMT
      //
      if (child->getCode() == DO_STMT) {
	labelBeforeDo[child] = "T";
	nodeBeforeDo[child] = np;
      }
      else 
	addEdge(np, child, "T");

      child->accept(*this);

    } else addEdge(np,np,"T");

  } else addEdge(np,np,"T");

  // Pop from stacks
  lastCycleCond.pop();
  breakStack.pop();
  continueStack.pop();


  // We use canJumpScopeStmt to avoid the entering
  // into an infinite loop
  //
  // If nextNodeMap[np] point to A and some branch of A point
  // to np, the we have an infinite loop !
  if ((child = canJumpScopeStmt(np))) {

    //
    // Make an edge to the next stmt only
    // if itsn't a DO_STMT
    //
    if (!weAreBeforeDo(np, "F"))
      addEdge(np, child, "F");

    child->accept(*this);

  } else 
    // It's a last node of chain
    makePendingFromCurrentNode(np);

  return;
}

void
visit_fnctCFG::visit_while_stmt (while_stmt_n * np)
{
  nast_node *child;
  
  takeIndex(np);

  // If the next stmt is NULL then in the previous
  // exploreChain(np) we didn't get it.
  //
  // Now, try again !
  // Maybe the next stmt is a previous for, do, or while!
  //
  if (!nextNodeMap[np])
    nextNodeMap[np] = nextExitPoint(np);

  // Push into stacks (the children will link to this WHILE)
  lastCycleCond.push(np);
  breakStack.push(np);
  continueStack.push(np);

  //
  // BODY branch
  if (np->hasEdgeName(BODY_EDGE)) {
    child = np->edgeName(BODY_EDGE);

    // Prolog of the body :
    //
    //   zero or one  COMPOUND_STMT
    //   zero or many SCOPE_STMT
    //   zero or one  COMPOUND_STMT
    // 
    // The body without instructions have only SCOPE_STMT.
    // Jump these nodes !
    // Note the IF when we check the chain of scope_stmt ?!
    //
    if (child->getCode() == COMPOUND_STMT)
      child = child->edgeName(BODY_EDGE);
    if ((child = canJumpScopeStmt(child))) {
      if (child->getCode() == COMPOUND_STMT)
	child = child->edgeName(BODY_EDGE);
      
      exploreChain(child);
      
      //
      // Make an edge to the next stmt only
      // if itsn't a DO_STMT
      //
      if (child->getCode() == DO_STMT) {
	labelBeforeDo[child] = "T";
	nodeBeforeDo[child] = np;
      }
      else
	addEdge(np, child, "T");

      child->accept(*this);
      
    } else addEdge(np,np,"T");
 
  } else addEdge(np,np,"T");
  
  // Pop from stacks
  lastCycleCond.pop();
  breakStack.pop();
  continueStack.pop();

  // We use canJumpScopeStmt to avoid the entering
  // into an infinite loop
  //
  // If nextNodeMap[np] point to A and some branch of A point
  // to np, the we have an infinite loop !
  if ((child = canJumpScopeStmt(np))) {

    //
    // Make an edge to the next stmt only
    // if itsn't a DO_STMT
    //
    if (!weAreBeforeDo(np, "F"))
      addEdge(np, child, "F");

    child->accept(*this);

  } else 
    // It's a last node of chain
    makePendingFromCurrentNode(np);
    
  return;
}

void
visit_fnctCFG::visit_do_stmt (do_stmt_n * np)
{
  nast_node *child;
  
  takeIndex(np);
    

  // If the next stmt is NULL then in the previous
  // exploreChain(np) we didn't get it.
  //
  // Now, try again !
  // Maybe the next stmt is a previous for, do, or while!
  //
  if (!nextNodeMap[np])
    nextNodeMap[np] = nextExitPoint(np);

  // Push into stacks (the children will link to this DO)
  lastCycleCond.push(np);
  breakStack.push(np);
  continueStack.push(np);
  
  //
  // BODY branch
  if (np->hasEdgeName(BODY_EDGE)) {

    child = np->edgeName(BODY_EDGE);

    // Prolog of the body :
    //
    //   zero or one  COMPOUND_STMT
    //   zero or many SCOPE_STMT
    //   zero or one  COMPOUND_STMT
    // 
    // The body without instructions ahave only SCOPE_STMT.
    // Jump these nodes !
    // Note the IF when we check the chain of scope_stmt ?!
    //
    if (child->getCode() == COMPOUND_STMT)
      child = child->edgeName(BODY_EDGE);
    if ((child = canJumpScopeStmt(child))) {
      if (child->getCode() == COMPOUND_STMT)
	child = child->edgeName(BODY_EDGE);

      exploreChain(child);

      // 
      // We can have many nested do_stmt.
      // We search the first stmt of the DO different 
      // from a nested DO.
      // 
      nast_node *temp = child;    // browse the chain of neste do_stmt
      bool nodeInChain = true;    // False if the do_stmt hasn't body
      while ((temp->getCode() == DO_STMT ) && nodeInChain) {
	nast_node *child;
	
	// get the body of the DO
	if (temp->hasEdgeName(BODY_EDGE)) {
	  child = temp->edgeName(BODY_EDGE);
	  // Jump the Prolog !! (see above)
	  if (child->getCode() == COMPOUND_STMT)
	    child = child->edgeName(BODY_EDGE);
	  if ((child = canJumpScopeStmt(child))) {
	    if (child->getCode() == COMPOUND_STMT)
	      child = child->edgeName(BODY_EDGE);
	    temp = child;
	  } else 
	    nodeInChain = false;

	} else 
	  nodeInChain = false;
      }
      // Set the first stmt of the do body
      firstStmtInDo[np] = (nodeInChain && (temp->getCode() != DO_STMT)) ?
	temp : 0;

      // The Do has a body ?
      if (firstStmtInDo[np]) {
	// We are here if there's a stmt different from 
	// another DO_STMT in the do_body. We must
	// mark this first stmt of the first stmt of
	// the nested do_stmt
	
	// If there's another DO_STMT then
	// propgate the reiter point !
	if (child->getCode() == DO_STMT) {
	  labelBeforeDo[child] = labelBeforeDo[np];
	  nodeBeforeDo[child] = nodeBeforeDo[np];
	  upperNestedDo[child] = np;
	}

      } else {
	// We are here if there's only DO_STMT in the do_body
	// or there's no stmt in the do_body
	
	addEdge(np,np,"T");
	addEdge(np,nextNodeMap[np],"F");
      }

      child->accept(*this);
      
    } else {
      // We are here if there's no stmt in the do_body

      addEdge(np,np,"T");
      addEdge(np,nextNodeMap[np],"F");
    }

  } else {
    // We are here if there's no do_body
    
    addEdge(np,np,"T");
    addEdge(np,nextNodeMap[np],"F");
  }
    

  // Pop from stacks
  lastCycleCond.pop();
  breakStack.pop();
  continueStack.pop();


  // We use canJumpScopeStmt to avoid the entering
  // into an infinite loop
  //
  // If nextNodeMap[np] point to A and some branch of A point
  // to np, the we have an infinite loop !
  if ((child = canJumpScopeStmt(np)))
    // Visit next statement but don't make any edge
    child->accept(*this);
    
  return;
}

void
visit_fnctCFG::visit_compound_stmt (compound_stmt_n * np)
{
  nast_node *child;
  
  takeIndex(np);

  //
  // BODY branch
  if (np->hasEdgeName(BODY_EDGE)) {
    child = np->edgeName(BODY_EDGE);

    // Jump the scope_stmt at the begin of the body
    if (child->getCode() == SCOPE_STMT) {
      if ((child = canJumpScopeStmt(child))) {
    
	exploreChain(child);
	
	//
	// Make an edge to the next stmt only
	// if itsn't a DO_STMT
	//
	if (child->getCode() == DO_STMT) {
	  labelBeforeDo[child] = "U";
	  nodeBeforeDo[child] = np;
	}
	else
	  addEdge(np, child, "U");
	
	child->accept(*this);
	
      }
    }
  }


  // We use canJumpScopeStmt to avoid the entering
  // into an infinite loop
  //
  // If nextNodeMap[np] point to A and some branch of A point
  // to np, the we have an infinite loop !
  if ((child = canJumpScopeStmt(np))) {
    child->accept(*this);
    addEdge(np, child, "U");
  }

  return;
}

void
visit_fnctCFG::visit_asm_stmt (asm_stmt_n * np)
{
  nast_node *child;
  
  takeIndex(np);
  
  // Visit next stmt if there is
  if ((child = nextNodeMap[np])) {

    //
    // Make an edge to the next stmt only
    // if itsn't a DO_STMT
    //
    if (!weAreBeforeDo(np, "U"))
      addEdge(np, child, "U");
    
    child->accept(*this);

  } else 
    // It's a last node of chain
    makePendingFromCurrentNode(np);

  return;
}

void
visit_fnctCFG::visit_othr_stmt (othr_stmt_n * np)
{
  nast_node *child;

  takeIndex(np);

  // Visit next stmt if there is
  if ((child = nextNodeMap[np])) {

    //
    // Make an edge to the next stmt only
    // if itsn't a DO_STMT
    //
    if (!weAreBeforeDo(np, "U"))
      addEdge(np, child, "U");
    
    child->accept(*this);

  } else 
    // It's a last node of chain
    makePendingFromCurrentNode(np);

  return;
}

void 
visit_fnctCFG::visit_case_label(case_label_n *np) 
{
  nast_node *child;
  nast_node *firstChild;

  takeIndex(np);

  // edge from the nearest switch to the case
  addEdge(lastSwitch.top(), np, "U");

  if ((child = nextNodeMap[np])) {

    firstChild = child;

    // jump chain of (sequential) case_label
    while ( child->getCode() == CASE_LABEL )
      child = child->edgeName(NEXT_STMT_EDGE);

    // The body begin with a compound !
    if ( (child->getCode() == COMPOUND_STMT) && canJumpScopeStmt(child))
      addEdge(child, canJumpScopeStmt(child), "T");

    addEdge(np, child, "T");
    firstChild->accept(*this);
  }
  
  return;
}

void
visit_fnctCFG::visit_othr_expr (othr_expr_n *np)
{
  nast_node *child;

  if (np->getCode() == LOOP_EXPR) {
    
    takeIndex(np);
    
    lastCycleCond.push(np);

    // We don't push the loop_expr into the
    // stacks. 
    // The infinite loop is executed until
    // an exit_expr is reached !!
    if (np->hasEdgeName(BODY_EDGE)) {
      child = np->edgeName(BODY_EDGE);
      addEdge(np, child, "U");;
      child->accept(*this);
    }
  
    lastCycleCond.pop();

  }
  
  return;
}

nast_node *
visit_fnctCFG::canJumpScopeStmt(nast_node *np) {
  nast_node *child;

  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    
    // Jump sequential SCOPE_STMT
    child = np->edgeName(NEXT_STMT_EDGE);
    while ( (child->getCode() == SCOPE_STMT) && 
	    (child->hasEdgeName(NEXT_STMT_EDGE)) )
      child = child->edgeName(NEXT_STMT_EDGE);

    // We can exit from the while loop :
    // - when there is no NEXT_STMT_EDGE
    // - or when there is no SCOPE_STMT
    if (child->getCode() == SCOPE_STMT)
      // we can't jump the scope_stmt
      return 0;
    else
      // we can jump the scope_stmt
      return child;
    
  }
  else return 0;

}
  
nast_node *
visit_fnctCFG::nextExitPoint(nast_node *np) {
  stack<nast_node *> tempStack;
  nast_node  *exitPoint;

  if (!lastCycleCond.empty()) {
    nast_code code;
    
    // The exit point is a previou do, while or for
    code = (lastCycleCond.top())->getCode();
    if ( (code == WHILE_STMT) || (code == FOR_STMT) || (code == DO_STMT) )
      exitPoint = lastCycleCond.top();
    else {
      // The exit point is the first not NULL nast_node *
      // from the top of the stack
      
      // We use a temporary stack

      // Search first not NULL exit point
      while (! (exitPoint = nextNodeMap[lastCycleCond.top()]) ) {
	tempStack.push(lastCycleCond.top());
	lastCycleCond.pop();
      }
      
      
      while (! tempStack.empty()) {
	lastCycleCond.push(tempStack.top());
	tempStack.pop();
      }
      
    }
  }
  else { 
    // There is not ufficial exit point 
    // Make the next SCOPE_STMT of np how exit point;
    exitPoint = np->edgeName(NEXT_STMT_EDGE);
    takeIndex(exitPoint);
  }
    
  return exitPoint;
}
  

  

void 
visit_fnctCFG::addEdge(nast_node *from,nast_node *to, char *label) {
  toPoint  *tp = new toPoint;
  tp->to = to;
  tp->label = label;
  edges.insert( make_pair(from, tp) );
}


void 
visit_fnctCFG::makePendingFromCurrentNode(nast_node *np) 
{
  // If there's a previou cycle or condition node the link
  // np to this node.
  if (!lastCycleCond.empty()) {
    nast_node *last = lastCycleCond.top();      // the last cycle or condition
    nast_node *exitPoint = nextNodeMap[last];   // the next node of the last
                                                // this is the exit point of
                                                // np
    char *label;                                // the label of the edge between
                                                // np and last
    
    // set the label
    switch (np->getCode()) {
    case FOR_STMT:
    case WHILE_STMT:
    case IF_STMT:
      label = "F";
      break;
    default:
      label = "U";
      break;
    }

    // Make edges from np to last (or more ...)
    switch (last->getCode()) {
    case DO_STMT:

      addEdge(nodeBeforeDo[last], firstStmtInDo[last], labelBeforeDo[last]);
      addEdge(np, last, label);
      addEdge(last, firstStmtInDo[last],"T");
      addEdge(last, exitPoint, "F");
      
      // Follow the chain of many nested do_stmt
      if (last->getCode() == DO_STMT) {
	nast_node *upperDo;

	// make edges
	while ((upperDo = upperNestedDo[last])) {
	  addEdge(upperDo, firstStmtInDo[upperDo],"T");
	  addEdge(upperDo, nextNodeMap[upperDo], "F");
	  last = upperDo;
	}
      }

      break;
    case FOR_STMT:
    case WHILE_STMT:
      addEdge(np, last, label);
    break;
    case IF_STMT:
      addEdge(np, exitPoint, label);
      break;
    }
  }
  
  return;
}


void
visit_fnctCFG::takeIndex(nast_node *np) {
  indexMap[np] = ++lastIndex;
  nodesMap[lastIndex] = np;
  return;
}

void 
visit_fnctCFG::init(void) { 
  // First Index
  lastIndex = 1;
  // Clear the stacks and the maps
  while (!lastCycleCond.empty())
    lastCycleCond.pop();
  while (!breakStack.empty())
    breakStack.pop();
  while (!continueStack.empty())
    continueStack.pop();
  while (!lastSwitch.empty())
    lastSwitch.pop();
  labelFound.clear();
  pendingGoto.clear();
  indexMap.clear();
  nodesMap.clear();
  labelBeforeDo.clear();
  nodeBeforeDo.clear();
  firstStmtInDo.clear();
  upperNestedDo.clear();
}


bool
visit_fnctCFG::weAreBeforeDo(nast_node *np, char *label) {
  nast_node *child;

  // The next child is a DO_STMT ?
  if ( ((child = nextNodeMap[np])) && (child->getCode() == DO_STMT) ) {
    // save the special point for the do_stmt
    labelBeforeDo[child] = label;
    nodeBeforeDo[child] = np;
    return true;
  } else 
    return false;
}

void
visit_fnctCFG::exploreChain(nast_node *np) {
  nast_node *child;

  while (np->hasEdgeName(NEXT_STMT_EDGE)) {

    // if np isn't a scope stmt the search its next node
    if (np->getCode() != SCOPE_STMT) {
      
      // jump scope_stmt and search the next node
      child = np->edgeName(NEXT_STMT_EDGE);
      while ( child->hasEdgeName(NEXT_STMT_EDGE) &&
	      (child->getCode() == SCOPE_STMT) )
	child = child->edgeName(NEXT_STMT_EDGE);

      // mark the next node of np
      nextNodeMap[np] = (child->getCode() != SCOPE_STMT) ? child : 0;
      
    }
    
    // go to the next node
    np = np->edgeName(NEXT_STMT_EDGE);

  }

  return;
}

	     

void 
visit_fnctCFG::finish(void) {
  typedef multimap<nast_node *, toPoint *>::iterator MI;
  long                  i;          // counter
  nast_node             *np;        // the node
  MI                    g;          // Multimap iterator
  pair<MI,MI>           p;          // datas into the multimap
  bool                  hasOutEdge; // true if a node has almost one 
                                    // output edge, false otherwhise
  bool                  hasInEdge;  // true if a node has almost one 
                                    // input edge, false otherwhise
  map<long, bool>       danglNode;  // map[i] == true if the node 
                                    // with index i is dangling
                                    // map[i] == false otherwise
  map<long, long>       newIndex;   // map[i] is the new index of
                                    // the node with index i
  long                  lastNewIndex; // Use to remap the indexes
  

  // Adjust the pending goto
  list< pair<nast_node*, nast_node*> >::iterator p2;
  for (p2 = pendingGoto.begin(); p2 != pendingGoto.end(); p2++) { 
    pair<nast_node *, nast_node *>  gotoInfo = *p2;
    nast_node *                     dest = labelFound[gotoInfo.first];
    addEdge(gotoInfo.second, dest, "U");
  }

  lastNewIndex = 1;

  // Search a dangling node
  // Assign a new index to the non dangling node
  for (i = 1; i <= lastIndex; i++) 
    if ((np = nodesMap[i])) {    

      // Check for output edge
      p = edges.equal_range(np);
      hasOutEdge = (p.first != p.second);
      if (!hasOutEdge) {
	int  j;  // counter;

	// check for input edge
	for (j = 1, hasInEdge = false; (j <= lastIndex) && (!hasInEdge) ; j++) 
	  if (j != i) {
	    nast_node       *from = nodesMap[j];
	    p = edges.equal_range(from);
	    for (g = p.first; g != p.second; ++g) {
	      toPoint      *to = g->second;
	      hasInEdge |= (to->to == np);
	    }
	  }
      }

      danglNode[i] = !(hasOutEdge || hasInEdge);
      if (!danglNode[i])
	newIndex[i] = ++lastNewIndex;
    }

  // Build the graphData

  for (i = 1; i <= lastIndex; i++) 
    if ((np = nodesMap[i])) {    
      // Is a dangling node ?
      // If the node is dangling don't add to the graph.
      if (!danglNode[i]) 
	
	// Insert the node
	switch (np->getCode()) {
	case ASM_STMT:
	case SCOPE_STMT: 
	  graph->addNode(newIndex[i], "generic", graphData::yellow);
	  break;
	case LABEL_STMT: 
	  graph->addNode(newIndex[i], "label", graphData::yellow);
	  break;
	case COMPOUND_STMT: 
	  graph->addNode(newIndex[i], "block", graphData::yellow);
	  break;
	case DECL_STMT: 
	  graph->addNode(newIndex[i], "declaration", graphData::yellow);
	  break;
	case EXPR_STMT: 
	  graph->addNode(newIndex[i], "expression", graphData::yellow);
	  break;
	case SWITCH_STMT: 
	  graph->addNode(newIndex[i], "switch", graphData::green);
	  break;
	case BREAK_STMT: 
	  graph->addNode(newIndex[i], "break", graphData::red);
	  break;
	case CONTINUE_STMT: 
	  graph->addNode(newIndex[i], "continue", graphData::red);
	  break;
	case DO_STMT: 
	  graph->addNode(newIndex[i], "do", graphData::cyan);
	  break;
	case FOR_STMT: 
	  graph->addNode(newIndex[i], "for", graphData::cyan);
	  break;
	case GOTO_STMT: 
	  graph->addNode(newIndex[i], "goto", graphData::red);
	  break;
	case IF_STMT: 
	  graph->addNode(newIndex[i], "if", graphData::green);
	  break;
	case RETURN_STMT: 
	  graph->addNode(newIndex[i], "return", graphData::red);
	  break;
	case WHILE_STMT: 
	  graph->addNode(newIndex[i], "while", graphData::cyan);
	  break;
	case CASE_LABEL: 
	  if ( ((case_label_n *)np)->isCase())
	    graph->addNode(newIndex[i], "case", graphData::yellow);
	  else
	    graph->addNode(newIndex[i], "default", graphData::yellow);
	  break;
	defalut:
	  graph->addNode(newIndex[i], "generic", graphData::yellow);
	  break;
	}

      // Insert the edges
      p = edges.equal_range(np);
      for (g = p.first; g != p.second; ++g) {
	toPoint      *to = g->second;
	long         toIndex = indexMap[to->to];
	graph->addEdge(newIndex[i], newIndex[toIndex], to->label);
      }
      
    }  
  
  //---- End build graph
  
  // Free memory
  for(g = edges.begin();g != edges.end(); g++) {
    toPoint      *to = g->second;
    delete to;
  }
  edges.clear();

  return;
}
  
      



