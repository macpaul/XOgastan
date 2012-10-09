/***************************************************************************
			   visit_fnctCallGraph.h  -  description
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

#ifndef _VISIT_FNCT_CALL_GRAPH_H
#define _VISIT_FNCT_CALL_GRAPH_H

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

#include "utils/a2b.h"

#include <map>
#include <string>
#include <fstream>
// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

//! This visitor count build a dor graph of a fnct call
/*!
  <b>Purpose</b> :<br>
  Build the call graph of the functions called.

  <b>Rules</b> :<br>
  From the entry point of the body of a function_decl
  it visit the statements in the body, and the 
  expressions linked to this statements.<br>
  When an entry point of expression is
  reached the currespondent expression is visited.
  The most important expression is the call_expr; it is
  the entry point for the call operation.<br>
  When a function_decl node  is reached we build the name of 
  the function, we insert the function into the graph, we insert
  the refresh the numbre of called ...<br>
  When a var_decl node  is reached, if the declaration
  has an initial value then the expression is visited.<br>
  When a stmt_n node is reached we follow the link to the other 
  stmt_n, and we explore the expressions linked to the node, if 
  there are.<br>

  <b>Action</b> :<br> 
\code
visit_fnctCallGraph::visit_function_decl
  get the name of the function
  if the function hasn't inserted into the graph then
     insert the node into the function
     make an edge to the base funcion
  if is a recursive call to the base function then add the loop edge
  increment the number of the call to this function
visit_fnctCallGraph::visit_break_stmt 
  visit the child NEXT_STMT_EDGE
visit_fnctCallGraph::visit_continue_stmt 
  visit the child NEXT_STMT_EDGE
visit_fnctCallGraph::visit_scope_stmt 
  visit the child NEXT_STMT_EDGE
visit_fnctCallGraph::visit_decl_stmt 
  visit the child NEXT_STMT_EDGE
  if is a var_decl then if it has an initial expession then visit it
visit_fnctCallGraph::visit_expr_stmt 
  visit the child NEXT_STMT_EDGE
  visit the child EXPRESSION_EDGE
visit_fnctCallGraph::visit_goto_stmt 
  visit the child NEXT_STMT_EDGE
  visit the child DESTINATION_EDGE
visit_fnctCallGraph::visit_label_stmt 
  visit the child NEXT_STMT_EDGE
visit_fnctCallGraph::visit_return_stmt 
  visit the child NEXT_STMT_EDGE
  visit the child EXPRESSION_EDGE
visit_fnctCallGraph::visit_if_stmt 
  visit the child NEXT_STMT_EDGE
  visit the child THEN_EDGE
  visit the child ELSE_EDGE
  visit the child CONDITION_EDGE
visit_fnctCallGraph::visit_switch_stmt 
  visit the child NEXT_STMT_EDGE
  visit the child BODY_EDGE
  visit the child CONDITION_EDGE
visit_fnctCallGraph::visit_for_stmt 
  visit the child NEXT_STMT_EDGE
  visit the child BODY_EDGE
  visit the child CONDITION_EDGE
  visit the child EXPRESSION_EDGE
  visit the child INITIALIZATION_EDGE
visit_fnctCallGraph::visit_while_stmt 
  visit the child NEXT_STMT_EDGE
  visit the child BODY_EDGE
  visit the child CONDITION_EDGE
visit_fnctCallGraph::visit_do_stmt 
  visit the child NEXT_STMT_EDGE
  visit the child BODY_EDGE
  visit the child CONDITION_EDGE
visit_fnctCallGraph::visit_compound_stmt 
  visit the child NEXT_STMT_EDGE
  visit the child BODY_EDGE
visit_fnctCallGraph::visit_asm_stmt 
  visit the child NEXT_STMT_EDGE
visit_fnctCallGraph::visit_case_label 
  visit the child NEXT_STMT_EDGE
visit_fnctCallGraph::visit_othr_stmt 
  visit the child NEXT_STMT_EDGE
visit_fnctCallGraph::visit_unary_expr 
  visit the child OPERAND_0_EDGE
visit_fnctCallGraph::visit_binary_expr 
  visit the child OPERAND_0_EDGE
  visit the child OPERAND_1_EDGE
visit_fnctCallGraph::visit_ternary_expr 
  visit the child CONDITION_EDGE
  visit the child THEN_VALUE_EDGE
  visit the child ELSE_VALUE_EDGE
visit_fnctCallGraph::visit_ref_expr 
  visit the child OPERAND_0_EDGE
  visit the child OPERAND_1_EDGE
  visit the child OPERAND_2_EDGE
  visit the child AGGREGATE_EDGE
  visit the child FIELD_EDGE
  visit the child ARRAY_EDGE
  visit the child INDEX_EDGE
visit_fnctCallGraph::visit_othr_expr 
  if it is a LOOP_EXPR then visit the child BODY_EDGE
  if it is a CALL_EXPR then visit the child ARGUMENTS_EDGE
  if it is a CALL_EXPR then visit the child FUNCTION_EDGE
  if it is a TARGET_EXPR then visit the child INITIALIZER_EDGE
  visit the child OPERAND_0_EDGE
  visit the child OPERAND_1_EDGE
  visit the child OPERAND_2_EDGE
visit_fnctCallGraph::visit_tree_list 
  visit the child VALUE_EDGE
\endcode

  <b>dataObj</b> used :<br>
  callGraphData 

  It visits the body of a function and builds a graphs of
  the function called. This graphs is a .dot file. 
  
  The caller of this visitor must use it to visit
  the body of function. So, the caller browse the 
  declarations into the global namespace, one node for time, 
  and for each function_decl_n it visit the body.
  The protocol must be like :

  \code
  visit_fnctCallGraph   v;
  nast_node             *node;
  nast_node             *body;
  callGraphData         *g;
  
  if (node is a function_decl_n) {
    g = new callGraphData;
    v.setGraphData(g);
    v.setFnctName(fnctName);
    v.setFnctId(fnctId);
    body = get the body of function_decl;
    v.init();
    body->accept(v);
    v.finish();
  }
  \endcode 

*/
class visit_fnctCallGraph : public visitor 
{

 private:

  //! The graph of the functions called
  callGraphData *graph;

  //! The name of the base function (that call) that we are visiting
  string fnctName;

  //! The id of the base function (that call) that we are visiting
  int fnctId;

 public:
  //! Constructor
  visit_fnctCallGraph() { }
  
  //! Destructor
  ~visit_fnctCallGraph() { }

  //---- Members

  void setCallGraphData(callGraphData *graph) 
    { this->graph = graph; }

  //! Set the function's name
  void setFnctName(string fnctName) 
    { this->fnctName = fnctName; }

  //! Set the function's id
  void setFnctId(int fnctId) 
    { this->fnctId = fnctId; }

  // visit declarations
  virtual void visit_function_decl(function_decl_n *);

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
		
  // visit expressions
  virtual void visit_unary_expr(unary_expr_n *);
  virtual void visit_binary_expr(binary_expr_n *);
  virtual void visit_ternary_expr(ternary_expr_n *);
  virtual void visit_ref_expr(ref_expr_n *);
  virtual void visit_othr_expr(othr_expr_n *);

  // visit other nodes
  virtual void visit_tree_list(tree_list_n *);
  virtual void visit_case_label(case_label_n *);

  //! The initialization operation
  virtual void init(void);
};

#endif

