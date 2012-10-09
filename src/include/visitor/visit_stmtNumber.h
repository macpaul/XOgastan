/***************************************************************************
			   visit_stmtNumber.h  -  description
			      -------------------
     begin                : AUG 31 2001
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

#ifndef _VISIT_STMT_NUMBER_H
#define _VISIT_STMT_NUMBER_H

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

#include "data/stmtNumData.h"

#include "visitor/visitor.h"

#include <map>
#include <string>

// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

//! This visitor count the statements
/*! 
  <b>Purpose</b> :<br>
  Count the number of statement into the body of the function.

  <b>Rules</b> :<br>
  From the entry point of the body of a function_decl
  it visit the statements in the body.<br>
  When a stmt_n node is reached we increment it presence into the 
  body

  <b>Action</b> :<br> 

\code
visit_stmtNumber::visit_break_stmt a
  add an other break_stmt
  visit the child NEXT_STMT_EDGE and make an edge to this child node
visit_stmtNumber::visit_continue_stmt 
  add an other continue_stmt
  visit the child NEXT_STMT_EDGE and make an edge to this child node
visit_stmtNumber::visit_scope_stmt 
  add an other scope_stmt
  visit the child NEXT_STMT_EDGE and make an edge to this child node
visit_stmtNumber::visit_decl_stmt 
  add an other decl_stmt
  visit the child NEXT_STMT_EDGE and make an edge to this child node
  push the nast_node* into the list of declarations declStmtL
visit_stmtNumber::visit_expr_stmt 
  add an other expr_stmt
  visit the child NEXT_STMT_EDGE and make an edge to this child node
  visit the child EXPRESSION_EDGE and make an edge to this child node
visit_stmtNumber::visit_goto_stmt 
  add an other goto_stmt
  visit the child NEXT_STMT_EDGE and make an edge to this child node
  visit the child DESTINATION_EDGE and make an edge to this child node
visit_stmtNumber::visit_label_stmt 
  add an other label_stmt
  visit the child NEXT_STMT_EDGE and make an edge to this child node
visit_stmtNumber::visit_return_stmt 
  add an other return_stmt
  visit the child NEXT_STMT_EDGE and make an edge to this child node
  visit the child EXPRESSION_EDGE and make an edge to this child node
visit_stmtNumber::visit_if_stmt 
  add an other if_stmt
  visit the child NEXT_STMT_EDGE and make an edge to this child node
  visit the child THEN_EDGE and make an edge to this child node
  visit the child ELSE_EDGE and make an edge to this child node
visit_stmtNumber::visit_switch_stmt 
  add an other switch_stmt
  visit the child NEXT_STMT_EDGE and make an edge to this child node
  visit the child BODY_EDGE and make an edge to this child node
visit_stmtNumber::visit_for_stmt 
  add an other for_stmt
  visit the child NEXT_STMT_EDGE and make an edge to this child node
  visit the child BODY_EDGE and make an edge to this child node
visit_stmtNumber::visit_while_stmt 
  add an other while_stmt
  visit the child NEXT_STMT_EDGE and make an edge to this child node
  visit the child BODY_EDGE and make an edge to this child node
visit_stmtNumber::visit_do_stmt 
  add an other do_stmt
  visit the child NEXT_STMT_EDGE and make an edge to this child node
  visit the child BODY_EDGE and make an edge to this child node
visit_stmtNumber::visit_compound_stmt 
  add an other compound_stmt
  visit the child NEXT_STMT_EDGE and make an edge to this child node
  visit the child BODY_EDGE and make an edge to this child node
visit_stmtNumber::visit_asm_stmt 
  add an other asm_stmt
  visit the child NEXT_STMT_EDGE and make an edge to this child node
visit_stmtNumber::visit_case_label 
  add an other case_label
  visit the child NEXT_STMT_EDGE and make an edge to this child node
visit_stmtNumber::visit_othr_stmt 
  add an other othr_stmt
  visit the child NEXT_STMT_EDGE and make an edge to this child node
visit_stmtNumber::visit_othr_expr 
  if it is a LOOP_EXPR 
	then visit the child BODY_EDGE and make an edge to this child node
\endcode

  <b>dataObj</b> used :<br>
  stmtNumData
  
  The caller of this visitor must use it to visit
  the body of a function. So, the caller browse the 
  declarations into the global namespace, one node for time, 
  and for each function_decl_n it visit the body.
  The protocol must be like :
  
  \code
  visit_stmtNumber  v;
  nast_node         *node;
  nast_node         *body;
  stmtNumData       snData;
  
  if (node is a function_decl_n) {
    v.setStmtNumData(&snData);
    body = get the body of the function_decl;
    body->accept(v);
  }
  \endcode

*/
class visit_stmtNumber : public visitor 
{

 private:
  
  //! The object stmtNumData
  /*!
    It holds the statements counted during the visit
  */
  stmtNumData *snData;
  
 public:
  //! Constructor
  visit_stmtNumber() { }
  
  //! Destructor
  ~visit_stmtNumber() { }

  //! Set the pointer to the object stmtNumData
  void setStmtNumData(stmtNumData *snData) 
    { this->snData = snData; }

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

};

#endif

