/***************************************************************************
			   visit_fnctBodyGraph.cpp  -  description
			      -------------------
     begin                : AUG 28 2001
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

#ifndef _VISIT_FNCT_BODY_GRAPH_H
#define _VISIT_FNCT_BODY_GRAPH_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "nast/nast_node.h"
#include "nast/type_n.h"
#include "nast/decl_n.h"
#include "nast/stmt_n.h"
#include "nast/expr_n.h"
#include "nast/othr_n.h"
#include "nast/cst_n.h"

#include "visitor/visitor.h"

#include "data/graphData.h"

#include "error/bad_nast.h"

#include <map>
#include <string>

// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

//! This visitor builds a graphs of body's statement of a function
/*!
  <b>Purpose</b> :<br>
  Build the graph of the body of the function.

  <b>Rules</b> :<br>
  From the entry point of the body of a function_decl
  it visit the statements in the body.<br>
  When a stmt_n node is reached we insert int into the graph (tree) of the
  body.
  After we insert the edges to the children nodes and we visit them.<br>

  <b>Action</b> :<br> 

\code
visit_fnctBodyGraph::label_decl
  add the node to the graph with the name label_decl and the color yellow
visit_fnctBodyGraph::visit_break_stmt a
  add the node to the graph with the name break_stmt and the color red
  visit the child NEXT_STMT_EDGE and make an edge to this child node
visit_fnctBodyGraph::visit_continue_stmt 
  add the node to the graph with the name continue_stmt and the color red
  visit the child NEXT_STMT_EDGE and make an edge to this child node
visit_fnctBodyGraph::visit_scope_stmt 
  add the node to the graph with the name scope_stmt and the color yellow
  visit the child NEXT_STMT_EDGE and make an edge to this child node
visit_fnctBodyGraph::visit_decl_stmt 
  add the node to the graph with the name decl_stmt and the color yellow
  visit the child NEXT_STMT_EDGE and make an edge to this child node
  push the nast_node* into the list of declarations declStmtL
visit_fnctBodyGraph::visit_expr_stmt 
  add the node to the graph with the name expr_stmt and the color yellow
  visit the child NEXT_STMT_EDGE and make an edge to this child node
  visit the child EXPRESSION_EDGE and make an edge to this child node
visit_fnctBodyGraph::visit_goto_stmt 
  add the node to the graph with the name goto_stmt and the color red
  visit the child NEXT_STMT_EDGE and make an edge to this child node
  visit the child DESTINATION_EDGE and make an edge to this child node
visit_fnctBodyGraph::visit_label_stmt 
  add the node to the graph with the name label_stmt and the color yellow
  visit the child NEXT_STMT_EDGE and make an edge to this child node
visit_fnctBodyGraph::visit_return_stmt 
  add the node to the graph with the name return_stmt and the color red
  visit the child NEXT_STMT_EDGE and make an edge to this child node
  visit the child EXPRESSION_EDGE and make an edge to this child node
visit_fnctBodyGraph::visit_if_stmt 
  add the node to the graph with the name if_stmt and the color green
  visit the child NEXT_STMT_EDGE and make an edge to this child node
  visit the child THEN_EDGE and make an edge to this child node
  visit the child ELSE_EDGE and make an edge to this child node
visit_fnctBodyGraph::visit_switch_stmt 
  add the node to the graph with the name switch_stmt and the color green
  visit the child NEXT_STMT_EDGE and make an edge to this child node
  visit the child BODY_EDGE and make an edge to this child node
visit_fnctBodyGraph::visit_for_stmt 
  add the node to the graph with the name for_stmt and the color cyan
  visit the child NEXT_STMT_EDGE and make an edge to this child node
  visit the child BODY_EDGE and make an edge to this child node
visit_fnctBodyGraph::visit_while_stmt 
  add the node to the graph with the name while_stmt and the color cyan
  visit the child NEXT_STMT_EDGE and make an edge to this child node
  visit the child BODY_EDGE and make an edge to this child node
visit_fnctBodyGraph::visit_do_stmt 
  add the node to the graph with the name do_stmt and the color cyan
  visit the child NEXT_STMT_EDGE and make an edge to this child node
  visit the child BODY_EDGE and make an edge to this child node
visit_fnctBodyGraph::visit_compound_stmt 
  add the node to the graph with the name compound_stmt and the color yellow
  visit the child NEXT_STMT_EDGE and make an edge to this child node
  visit the child BODY_EDGE and make an edge to this child node
visit_fnctBodyGraph::visit_asm_stmt 
  add the node to the graph with the name asm_stmt and the color yellow
  visit the child NEXT_STMT_EDGE and make an edge to this child node
visit_fnctBodyGraph::visit_case_label 
  add the node to the graph with the name case_label and the color yellow
  visit the child NEXT_STMT_EDGE and make an edge to this child node
visit_fnctBodyGraph::visit_othr_stmt 
  add the node to the graph with the name othr_stmt and the color yellow
  visit the child NEXT_STMT_EDGE and make an edge to this child node
visit_fnctBodyGraph::visit_othr_expr 
  if it is a LOOP_EXPR 
	then visit the child BODY_EDGE and make an edge to this child node
\endcode

  <b>dataObj</b> used :<br>
  graphData 
  
  The caller of this visitor must use it to visit
  the body of function. So, the caller browse the 
  declarations into the global namespace, one node for time, 
  and for each function_decl_n it visit the body.
  The protocol must be like :

  \code
  visit_fnctBodyGraph  v;
  nast_node            *node;
  nast_node            *body;
  graphData            *g;
  
  if (node is a function_decl_n) {
    v.setGraphData(g);
    body = get the body of function_decl;
    v.init();
    body->accept(v);
  }
  \endcode


  The node have different color.
  The convention is :

  - cyan : cycle node (for, do, while)
  - green : conditional node (if, switch)
  - red : node that modify the flow (break, continue, return, goto)
  - yellow : others node
*/
class visit_fnctBodyGraph : public visitor 
{

 private:
  
  //! The graph of the body
  graphData *graph;


  //! Index of the nodes
  int index;

  //! Map the nast_node * on the index
  map<nast_node *, int> indexMap;

 public:
  //! Constructor
  visit_fnctBodyGraph() { index = 0; }
  
  //! Destructor
  ~visit_fnctBodyGraph() { }

  //---- Members
  
  void setGraphData(graphData *graph) 
    { this->graph = graph; }
  
  // visit label_decl (goto_stmt)
  virtual void visit_label_decl(label_decl_n *);

  // visit statements
  virtual void visit_break_stmt(break_stmt_n *);
  virtual void visit_continue_stmt(continue_stmt_n *);
  virtual void visit_scope_stmt(scope_stmt_n *);
  virtual void visit_decl_stmt(decl_stmt_n *);
  virtual void visit_expr_stmt(expr_stmt_n *);
  virtual void visit_goto_stmt(goto_stmt_n *);
  virtual void visit_label_stmt(label_stmt_n *);
  virtual void visit_return_stmt(return_stmt_n *);
  virtual void visit_if_stmt(if_stmt_n *);
  virtual void visit_switch_stmt(switch_stmt_n *);
  virtual void visit_for_stmt(for_stmt_n *);
  virtual void visit_while_stmt(while_stmt_n *);
  virtual void visit_do_stmt(do_stmt_n *);
  virtual void visit_compound_stmt(compound_stmt_n *);
  virtual void visit_asm_stmt(asm_stmt_n *);
  virtual void visit_othr_stmt(othr_stmt_n *);

  // visit other nodes
  virtual void visit_case_label(case_label_n *);

  // visit expressions
  virtual void visit_othr_expr(othr_expr_n *);

  //! The initialization operation
  /*!    
    Dump the head of the dot file
  */
  void init(void);

};

#endif
