/***************************************************************************
			   visit_stmtFnct2dot.cpp  -  description
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
#include "visitor/visit_fnctBodyGraph.h"

// ---------------------------------------------------------------------------
//  MEMBERS
// ---------------------------------------------------------------------------

void 
visit_fnctBodyGraph::visit_label_decl(label_decl_n *np) 
{
  graph->addNode(++index, "label_decl", graphData::yellow);
  indexMap[np] = index;
  return;
}

// visit statements
void
visit_fnctBodyGraph::visit_break_stmt (break_stmt_n * np)
{
  nast_node *child;
    
  graph->addNode(++index, "break_stmt", graphData::red);
  int safeIndex = index; indexMap[np] = index;

  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
    graph->addEdge(safeIndex,indexMap[child], "next_stmt");
  }
  
  return;
}

void
visit_fnctBodyGraph::visit_continue_stmt (continue_stmt_n * np)
{
  nast_node *child;

  graph->addNode(++index, "continue_stmt", graphData::red);
  int safeIndex = index; indexMap[np] = index;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
    graph->addEdge(safeIndex,indexMap[child], "next_stmt");
  }

  return;
}

void
visit_fnctBodyGraph::visit_scope_stmt (scope_stmt_n * np)
{
  nast_node *child;
  
  graph->addNode(++index, "scope_stmt", graphData::yellow);
  int safeIndex = index; indexMap[np] = index;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
    graph->addEdge(safeIndex,indexMap[child], "next_stmt");
  }
  
  return;
}

void
visit_fnctBodyGraph::visit_decl_stmt (decl_stmt_n * np)
{
  nast_node *child;
  
  graph->addNode(++index, "decl_stmt", graphData::yellow);
  int safeIndex = index; indexMap[np] = index;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
    graph->addEdge(safeIndex,indexMap[child], "next_stmt");
  }

  return;
}

void
visit_fnctBodyGraph::visit_expr_stmt (expr_stmt_n * np)
{
  nast_node *child;
  
  graph->addNode(++index, "expr_stmt", graphData::yellow);
  int safeIndex = index; indexMap[np] = index;
  
  // Loop expr ?
  if (np->hasEdgeName(EXPRESSION_EDGE)) {
    child = np->edgeName(EXPRESSION_EDGE);
    if (child->getCode() == LOOP_EXPR) {
      child->accept(*this);
      graph->addEdge(safeIndex,indexMap[child], "next_stmt");
    }
  }
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
    graph->addEdge(safeIndex,indexMap[child], "next_stmt");
  }
  
  return;
}

void
visit_fnctBodyGraph::visit_goto_stmt (goto_stmt_n * np)
{
  nast_node *child;
  
  graph->addNode(++index, "goto_stmt", graphData::red);
  int safeIndex = index; indexMap[np] = index;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
    graph->addEdge(safeIndex,indexMap[child], "next_stmt");
  }
	
  if (np->hasEdgeName(DESTINATION_EDGE)) {
    child = np->edgeName(DESTINATION_EDGE);
    child->accept(*this);
    graph->addEdge(safeIndex,indexMap[child], "destination");
  }
  
  return;
}

void
visit_fnctBodyGraph::visit_label_stmt (label_stmt_n * np)
{
  nast_node *child;
  
  graph->addNode(++index, "label_stmt", graphData::yellow);
  int safeIndex = index; indexMap[np] = index;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
    graph->addEdge(safeIndex,indexMap[child], "next_stmt");
  }
  
  return;
}

void
visit_fnctBodyGraph::visit_return_stmt (return_stmt_n * np)
{
  nast_node *child;
  
  graph->addNode(++index, "return_stmt", graphData::red);
  int safeIndex = index; indexMap[np] = index;
    
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
    graph->addEdge(safeIndex,indexMap[child], "next_stmt");
  }
  
  return;
}

void
visit_fnctBodyGraph::visit_if_stmt (if_stmt_n * np)
{
  nast_node *child;
  
  graph->addNode(++index, "if_stmt", graphData::green);
  int safeIndex = index; indexMap[np] = index;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
    graph->addEdge(safeIndex,indexMap[child], "next_stmt");
  }
  
  if (np->hasEdgeName(THEN_EDGE)) {
    child = np->edgeName(THEN_EDGE);
    child->accept(*this);
    graph->addEdge(safeIndex,indexMap[child], "then");
  }
  
  if (np->hasEdgeName(ELSE_EDGE)) {
    child = np->edgeName(ELSE_EDGE);
    child->accept(*this);
    graph->addEdge(safeIndex,indexMap[child], "else");
  }
  
  return;
}

void
visit_fnctBodyGraph::visit_switch_stmt (switch_stmt_n * np)
{
  nast_node *child;
  
  graph->addNode(++index, "switch_stmt", graphData::green);
  int safeIndex = index; indexMap[np] = index;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
    graph->addEdge(safeIndex,indexMap[child], "next_stmt");
  }
  
  if (np->hasEdgeName(BODY_EDGE)) {
    child = np->edgeName(BODY_EDGE);
    child->accept(*this);
    graph->addEdge(safeIndex,indexMap[child], "body");
  }
  
  return;
}

void
visit_fnctBodyGraph::visit_for_stmt (for_stmt_n * np)
{
  nast_node *child;
  
  graph->addNode(++index, "for_stmt", graphData::cyan);
  int safeIndex = index; indexMap[np] = index;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
    graph->addEdge(safeIndex,indexMap[child], "next_stmt");
  }
    
  if (np->hasEdgeName(BODY_EDGE)) {
    child = np->edgeName(BODY_EDGE);
    child->accept(*this);
    graph->addEdge(safeIndex,indexMap[child], "body");
  }

  return;
}

void
visit_fnctBodyGraph::visit_while_stmt (while_stmt_n * np)
{
  nast_node *child;
  
  graph->addNode(++index, "while_stmt", graphData::cyan);
  int safeIndex = index; indexMap[np] = index;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
    graph->addEdge(safeIndex,indexMap[child], "next_stmt");
  }

  if (np->hasEdgeName(BODY_EDGE)) {
    child = np->edgeName(BODY_EDGE);
    child->accept(*this);
    graph->addEdge(safeIndex,indexMap[child], "body");
  }
  
  return;
}

void
visit_fnctBodyGraph::visit_do_stmt (do_stmt_n * np)
{
  nast_node *child;
  
  graph->addNode(++index, "do_stmt", graphData::cyan);
  int safeIndex = index; indexMap[np] = index;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
    graph->addEdge(safeIndex,indexMap[child], "next_stmt");
  }
  
  if (np->hasEdgeName(BODY_EDGE)) {
    child = np->edgeName(BODY_EDGE);
    child->accept(*this);
    graph->addEdge(safeIndex,indexMap[child], "body");
  }
  
  return;
}

void
visit_fnctBodyGraph::visit_compound_stmt (compound_stmt_n * np)
{
  nast_node *child;
  
  graph->addNode(++index, "compound_stmt", graphData::yellow);
  int safeIndex = index; indexMap[np] = index;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
    graph->addEdge(safeIndex,indexMap[child], "next_stmt");
  }
  
  if (np->hasEdgeName(BODY_EDGE)) {
    child = np->edgeName(BODY_EDGE);
    child->accept(*this);
    graph->addEdge(safeIndex,indexMap[child], "body");
  }

  return;
}

void
visit_fnctBodyGraph::visit_asm_stmt (asm_stmt_n * np)
{
  nast_node *child;
  
  graph->addNode(++index, "asm_stmt", graphData::yellow);
  int safeIndex = index; indexMap[np] = index;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
    graph->addEdge(safeIndex,indexMap[child], "next_stmt");
  }
  
  return;
}

void
visit_fnctBodyGraph::visit_othr_stmt (othr_stmt_n * np)
{
  nast_node *child;
  
  graph->addNode(++index, "othr_stmt", graphData::yellow);
  int safeIndex = index; indexMap[np] = index;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
    graph->addEdge(safeIndex,indexMap[child], "next_stmt");
  }
  
  return;
}

void 
visit_fnctBodyGraph::visit_case_label(case_label_n *np) 
{
  nast_node *child;
  
  graph->addNode(++index, "case_label", graphData::yellow);
  int safeIndex = index; indexMap[np] = index;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
    graph->addEdge(safeIndex,indexMap[child], "next_stmt");
  }
  
  return;
}

void
visit_fnctBodyGraph::visit_othr_expr (othr_expr_n *np)
{
  nast_node *child;
  
  if (np->getCode() == LOOP_EXPR) {
      
    graph->addNode(++index, "loop_expr", graphData::yellow);
    int safeIndex = index; indexMap[np] = index;
    
    if (np->hasEdgeName(BODY_EDGE)) {
      child = np->edgeName(BODY_EDGE);
      child->accept(*this);
      graph->addEdge(safeIndex,indexMap[child], "body");
    }

  }
  return;
}




void
visit_fnctBodyGraph::init(void)
{
  index = 1;
}



