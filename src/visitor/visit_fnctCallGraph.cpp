/***************************************************************************
			   visit_fnctCallGraph.cpp  -  description
			      -------------------
     begin                : Sept 3 2001
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
#include "visitor/visit_fnctCallGraph.h"

// ---------------------------------------------------------------------------
//  MEMBERS
// ---------------------------------------------------------------------------

void 
visit_fnctCallGraph::visit_function_decl(function_decl_n *np) 
{
  identifier_n *identifier; 
      
  // Get the identifier node for the name of the function
  identifier = dynamic_cast<identifier_n *> (np->edgeName(NAME_EDGE));
	    
  int id;
  // We insert the function into the graph only
  // if the node doesn't exsist
  if (!graph->hasNode(id = np->getId()) ) {
    // Insert node
    graph->addNode(id, 
		   a2b::cpp_string2c_string(identifier->getString()),
		   graphData::cyan);
    // Insert edge
    graph->addEdge(fnctId, id, "call");
  } 
  
  // recursive call
  if (id == fnctId) 
    graph->addEdge(fnctId, fnctId, "call");
  
  
  // Increment number of calls
  graph->addCall(id);

}

// visit statements
void
visit_fnctCallGraph::visit_break_stmt (break_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  return;
}

void
visit_fnctCallGraph::visit_continue_stmt (continue_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }

  return;
}

void
visit_fnctCallGraph::visit_scope_stmt (scope_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  return;
}

void
visit_fnctCallGraph::visit_decl_stmt (decl_stmt_n * np)
{
  nast_node *child;

  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }

  if (np->hasEdgeName(DECLARATIONS_EDGE)) {
    child = np->edgeName(DECLARATIONS_EDGE);
    if (child->getCode() == VAR_DECL) {
        if (child->hasEdgeName(INITIAL_VALUE_EDGE)) {
	  child = child->edgeName(INITIAL_VALUE_EDGE);
	  child->accept(*this);
	}
    }
  }
  
  return;
}

void
visit_fnctCallGraph::visit_expr_stmt (expr_stmt_n * np)
{
  nast_node *child;

  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(EXPRESSION_EDGE)) {
    child = np->edgeName(EXPRESSION_EDGE);
    child->accept(*this);
  }

  return;
}

void
visit_fnctCallGraph::visit_goto_stmt (goto_stmt_n * np)
{
  nast_node *child;

  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(DESTINATION_EDGE)) {
    child = np->edgeName(DESTINATION_EDGE);
    child->accept(*this);
  }
  
}

void
visit_fnctCallGraph::visit_label_stmt (label_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  return;
}

void
visit_fnctCallGraph::visit_return_stmt (return_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(EXPRESSION_EDGE)) {
    child = np->edgeName(EXPRESSION_EDGE);
    child->accept(*this);
  }
  
  return;
}

void
visit_fnctCallGraph::visit_if_stmt (if_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(THEN_EDGE)) {
    child = np->edgeName(THEN_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(ELSE_EDGE)) {
    child = np->edgeName(ELSE_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(CONDITION_EDGE)) {
    child = np->edgeName(CONDITION_EDGE);
    child->accept(*this);
  }

  return;
}

void
visit_fnctCallGraph::visit_switch_stmt (switch_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(BODY_EDGE)) {
    child = np->edgeName(BODY_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(CONDITION_EDGE)) {
    child = np->edgeName(CONDITION_EDGE);
    child->accept(*this);
  }

  return;
}

void
visit_fnctCallGraph::visit_for_stmt (for_stmt_n * np)
{
  nast_node *child;

  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(BODY_EDGE)) {
    child = np->edgeName(BODY_EDGE);
    child->accept(*this);
  }

  if (np->hasEdgeName(CONDITION_EDGE)) {
    child = np->edgeName(CONDITION_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(EXPRESSION_EDGE)) {
    child = np->edgeName(EXPRESSION_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(INITIALIZATION_EDGE)) {
    child = np->edgeName(INITIALIZATION_EDGE);
    child->accept(*this);
  }

  return;
}

void
visit_fnctCallGraph::visit_while_stmt (while_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(BODY_EDGE)) {
    child = np->edgeName(BODY_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(CONDITION_EDGE)) {
    child = np->edgeName(CONDITION_EDGE);
    child->accept(*this);
  }
  
  return;
}

void
visit_fnctCallGraph::visit_do_stmt (do_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(BODY_EDGE)) {
    child = np->edgeName(BODY_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(CONDITION_EDGE)) {
    child = np->edgeName(CONDITION_EDGE);
    child->accept(*this);
  }
  
  return;
}

void
visit_fnctCallGraph::visit_compound_stmt (compound_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(BODY_EDGE)) {
    child = np->edgeName(BODY_EDGE);
    child->accept(*this);
  }

  return;
}

void
visit_fnctCallGraph::visit_asm_stmt (asm_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }

  return;
}

void
visit_fnctCallGraph::visit_othr_stmt (othr_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  return;
}


void 
visit_fnctCallGraph::visit_case_label(case_label_n *np) 
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }

  return;
}


// visit expressions
void
visit_fnctCallGraph::visit_unary_expr (unary_expr_n *np)
{
  nast_node *child;
  
  if (np->hasEdgeName(OPERAND_0_EDGE)) {
    child = np->edgeName(OPERAND_0_EDGE);
    child->accept(*this);
  }

  return;
}

void
visit_fnctCallGraph::visit_binary_expr (binary_expr_n *np)
{
  nast_node *child;

  if (np->hasEdgeName(OPERAND_0_EDGE)) {
    child = np->edgeName(OPERAND_0_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(OPERAND_1_EDGE)) {
    child = np->edgeName(OPERAND_1_EDGE);
    child->accept(*this);
  }

  return;
}

void
visit_fnctCallGraph::visit_ternary_expr (ternary_expr_n *np)
{
  nast_node *child;
  
  if (np->hasEdgeName(CONDITION_EDGE)) {
    child = np->edgeName(CONDITION_EDGE);
    child->accept(*this);
  }

  if (np->hasEdgeName(THEN_VALUE_EDGE)) {
    child = np->edgeName(THEN_VALUE_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(ELSE_VALUE_EDGE)) {
    child = np->edgeName(ELSE_VALUE_EDGE);
    child->accept(*this);
  }
  
  return;
}

void
visit_fnctCallGraph::visit_ref_expr (ref_expr_n *np)
{
  nast_node *child;

  if (np->hasEdgeName(OPERAND_0_EDGE)) {
    child = np->edgeName(OPERAND_0_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(OPERAND_1_EDGE)) {
    child = np->edgeName(OPERAND_1_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(OPERAND_2_EDGE)) {
    child = np->edgeName(OPERAND_2_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(AGGREGATE_EDGE)) {
    child = np->edgeName(AGGREGATE_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(FIELD_EDGE)) {
    child = np->edgeName(FIELD_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(ARRAY_EDGE)) {
    child = np->edgeName(ARRAY_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(INDEX_EDGE)) {
    child = np->edgeName(INDEX_EDGE);
    child->accept(*this);
  }
  
  return;
}

void
visit_fnctCallGraph::visit_othr_expr (othr_expr_n *np)
{
  nast_node *child;
  
  if (np->getCode() == LOOP_EXPR) {
    if (np->hasEdgeName(BODY_EDGE)) {
      child = np->edgeName(BODY_EDGE);
      child->accept(*this);
    }
  }
  
  if (np->getCode() == CALL_EXPR) {
    // visit argument to build the expression
    if (np->hasEdgeName(ARGUMENTS_EDGE)) {
      child = np->edgeName(ARGUMENTS_EDGE);
      child->accept(*this);
    }
    // visit the function 
    if (np->hasEdgeName(FUNCTION_EDGE)) {
      child = np->edgeName(FUNCTION_EDGE);
      // get the function_decl
      if (child->hasEdgeName(OPERAND_0_EDGE))
	child = child->edgeName(OPERAND_0_EDGE);
      child->accept(*this);
    }   
  }

  // used for the temporary object like the var V in function call foo(V,10)
  if (np->getCode() == TARGET_EXPR) {
    
    if (np->hasEdgeName(INITIALIZER_EDGE)) {
      child = np->edgeName(INITIALIZER_EDGE);
      child->accept(*this);
    }

  }

  if (np->hasEdgeName(OPERAND_0_EDGE)) {
    child = np->edgeName(OPERAND_0_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(OPERAND_1_EDGE)) {
    child = np->edgeName(OPERAND_1_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(OPERAND_2_EDGE)) {
    child = np->edgeName(OPERAND_2_EDGE);
    child->accept(*this);
  }

  return;
}



void
visit_fnctCallGraph::visit_tree_list (tree_list_n *np)
{
  nast_node *child;
  
  // get the type of the current type_n
  if (np->hasEdgeName(VALUE_EDGE)) {
    child = np->edgeName(VALUE_EDGE);
    child->accept(*this);
  }
  
  // visit next tree_list
  if (np->hasEdgeName(NEXT_EDGE)) {
    child = np->edgeName(NEXT_EDGE);
    child->accept(*this);
  }
  
  return;
}



void 
visit_fnctCallGraph::init(void) {
  
  // add the base function
  graph->addNode(fnctId, 
		 a2b::cpp_string2c_string(fnctName),
		 graphData::yellow);
 
  return;
}


