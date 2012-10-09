/***************************************************************************
			   visit_exprNumber.h  -  description
			      -------------------
     begin                : Sept 1 2001
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

#ifndef _VISIT_EXPR_NUMBER_H
#define _VISIT_EXPR_NUMBER_H

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

#include "data/exprNumData.h"

#include <map>
#include <string>

// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

//! This visitor counts the number expressions
/*! 
  <b>Purpose</b> :<br>
  Count the number of expression into the body of the function.

  <b>Rules</b> :<br>
  From the entry point of the body of a function_decl
  it visit the statements in the body, and the 
  expressions linked to this statements.<br>
  When an entry point of expression is
  reached the number of the expression is incremented. 
  An entry point of an expression 
  is expr_stmt, the condition of an if, a switch, a while, a do, a for, 
  the initialization of a for, the increment of a for, the 
  expression of a return.<br>
  When a stmt_n node is reached we follow the link to the other 
  stmt_n, and we explore the expressions linked to the node, if 
  there are.<br>

  <b>Action</b> :<br> 
\code
visit_exprNumber::visit_break_stmt 
  visit the child NEXT_STMT_EDGE
visit_exprNumber::visit_continue_stmt 
  visit the child NEXT_STMT_EDGE
visit_exprNumber::visit_scope_stmt 
  visit the child NEXT_STMT_EDGE
visit_exprNumber::visit_decl_stmt 
  visit the child NEXT_STMT_EDGE
visit_exprNumber::visit_expr_stmt 
  visit the child NEXT_STMT_EDGE
  visit the child EXPRESSION_EDGE
visit_exprNumber::visit_goto_stmt 
  visit the child NEXT_STMT_EDGE
  visit the child DESTINATION_EDGE
visit_exprNumber::visit_label_stmt 
  visit the child NEXT_STMT_EDGE
visit_exprNumber::visit_return_stmt 
  visit the child NEXT_STMT_EDGE
  visit the child EXPRESSION_EDGE
visit_exprNumber::visit_if_stmt 
  visit the child NEXT_STMT_EDGE
  visit the child THEN_EDGE
  visit the child ELSE_EDGE
  visit the child CONDITION_EDGE
visit_exprNumber::visit_switch_stmt 
  visit the child NEXT_STMT_EDGE
  visit the child BODY_EDGE
  visit the child CONDITION_EDGE
visit_exprNumber::visit_for_stmt 
  visit the child NEXT_STMT_EDGE
  visit the child BODY_EDGE
  visit the child CONDITION_EDGE
  visit the child EXPRESSION_EDGE
  visit the child INITIALIZATION_EDGE
visit_exprNumber::visit_while_stmt 
  visit the child NEXT_STMT_EDGE
  visit the child BODY_EDGE
  visit the child CONDITION_EDGE
visit_exprNumber::visit_do_stmt 
  visit the child NEXT_STMT_EDGE
  visit the child BODY_EDGE
  visit the child CONDITION_EDGE
visit_exprNumber::visit_compound_stmt 
  visit the child NEXT_STMT_EDGE
  visit the child BODY_EDGE
visit_exprNumber::visit_asm_stmt 
  visit the child NEXT_STMT_EDGE
visit_exprNumber::visit_case_label 
  visit the child NEXT_STMT_EDGE
visit_exprNumber::visit_othr_stmt 
  visit the child NEXT_STMT_EDGE
visit_exprNumber::visit_unary_expr 
  add on other unary np->getCode() expression 
  visit the child OPERAND_0_EDGE
visit_exprNumber::visit_binary_expr 
  add on other binary np->getCode() expression 
  visit the child OPERAND_0_EDGE
  visit the child OPERAND_1_EDGE
visit_exprNumber::visit_ternary_expr 
  add on other ternary np->getCode() expression 
  visit the child CONDITION_EDGE
  visit the child THEN_VALUE_EDGE
  visit the child ELSE_VALUE_EDGE
visit_exprNumber::visit_ref_expr 
  add on other reference np->getCode() expression 
  visit the child OPERAND_0_EDGE
  visit the child OPERAND_1_EDGE
  visit the child OPERAND_2_EDGE
  visit the child AGGREGATE_EDGE
  visit the child FIELD_EDGE
  visit the child ARRAY_EDGE
  visit the child INDEX_EDGE
visit_exprNumber::visit_othr_expr 
  add on other np->getCode() expression 
  if it is a LOOP_EXPR then visit the child BODY_EDGE
  if it is a CALL_EXPR then visit the child ARGUMENTS_EDGE
  if it is a CALL_EXPR then visit the child FUNCTION_EDGE
  if it is a TARGET_EXPR then visit the child INITIALIZER_EDGE
  visit the child OPERAND_0_EDGE
  visit the child OPERAND_1_EDGE
  visit the child OPERAND_2_EDGE
visit_exprNumber::visit_tree_list 
  visit the child VALUE_EDGE
  visit the child NEXT_EDGE 
\endcode

  <b>dataObj</b> used :<br>
  exprNumData

  The caller of this visitor must use it to visit
  the body of function. So, the caller browse the 
  declarations into the global namespace, one node for time, 
  and for each function_decl_n it visit the body.
  The protocol must be like :
 
  \code
  visit_exprNumber v;
  nast_node        *node;
  nast_node        *body;
  exprNumData      eData;
  
  if (node is a function_decl_n) {
    v.setExprNumData(&eData);
    body = get the body of node;
    body->accept(v);
  }
  \endcode

*/
class visit_exprNumber : public visitor 
{

 private:
  
  //! The object exprNumData
  /*!
    It holds the expressions counted during the visit.
  */
  exprNumData *enData;

 public:
  //! Constructor
  visit_exprNumber() { }
  
  //! Destructor
  ~visit_exprNumber() { }

  //---- Members

  //! Set the pointer to the object stmtNumData
  void setExprNumData(exprNumData *enData) 
    { this->enData = enData;  }

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
  virtual void visit_case_label(case_label_n *);
  virtual void visit_tree_list(tree_list_n *);

};

#endif




