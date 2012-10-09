/***************************************************************************
			   visit_nastNumber.h  -  description
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

#ifndef _VISIT_NAST_NUMBER_H
#define _VISIT_NAST_NUMBER_H

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

#include "data/nastNumData.h"

#include "visitor/visitor.h"

#include <map>
#include <string>
// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

//! This visitor count the nast_node
/*!
  <b>Purpose</b> :<br>
  Count the number of nast_node.

  <b>Rules</b> :<br>
  When an entry point of expression is
  reached the currespondent expression is visited, and a list
  of the variables used is built. An entry point of an expression 
  is expr_stmt, the condition of an if, a switch, a while, a do, a for, 
  the initialization of a for, the increment of a for, the 
  expression of a return.<br>
  When a decl_n node is reached we visit the node linked to it.<br>
  When a type_n node is reached we visit the node linked to it.<br>
  When a stmt_n node is reached we follow the link to the other 
  stmt_n, and we explore the expressions linked to the node, if 
  there are.<br>
  When an expr_n node is reached we explore the linked espression 
  and the type of the expression.<br>
  When an cst_n node is reached we visit the type.<br>

  <b>Action</b> :<br> 
  see the file visit_nastNumber.cpp

  <b>dataObj</b> used :<br>
  nastNumData

  If it visits the entire NAST then it will 
  count the number nast_node.
  When it visits the body of a function 
  then it will count the
  number of nast_node that we can reach
  from the body.
  The protocol must be like :
  
  \code
  visit_nastNumber v;
  nast_node        *node;
  nastNumData      nnData;
  
  v.setNastNumData(&nnData);
  node->accept(v);
  \endcode

  If we use this visitor in a cycle the it may be necessary 
  to use the alternative protocol :

  \code
  v.setNastNumData(&nnData);
  
  for(...;...;...){
    v.init();
    nnData.reset();
    node->accept(v);
    find new node to visit;
  }
  \endcode

  \note We can use this also to visitor a generic node (nor the
  entry point of the NAST and the function body). The result of
  the counting operation is the number of nast_node of the NAST 
  that can be reached from this generic node.
*/
class visit_nastNumber : public visitor 
{

 private:
  
  //! The map of the nodes just visited 
  /*!
    This map is used to trace the nodes just visited.
    It is necessary to avoid the entering into an 
    inifite loop during the visit.
  */
  map<long, nast_node *> justVisited;
  
  //! The object nastNumData
  /*!
    It holds the nast_node counteds during the visit
  */
  nastNumData *nnData;
  
 public:
  //! Constructor
  visit_nastNumber() { }
  
  //! Destructor
  ~visit_nastNumber() { }

  //! Set the pointer to the object nastNumData
  void setNastNumData(nastNumData *nnData) 
    { this->nnData = nnData; }

  // visit declarations
  virtual void visit_var_decl(var_decl_n *);
  virtual void visit_parm_decl(parm_decl_n *);
  virtual void visit_result_decl(result_decl_n *);
  virtual void visit_const_decl(const_decl_n *);
  virtual void visit_field_decl(field_decl_n *);
  virtual void visit_type_decl(type_decl_n *);
  virtual void visit_function_decl(function_decl_n *);
  virtual void visit_label_decl(label_decl_n *);
  virtual void visit_othr_decl(othr_decl_n *);

  // visit types
  virtual void visit_void_type(void_type_n *);
  virtual void visit_integer_type(integer_type_n *);
  virtual void visit_enumeral_type(enumeral_type_n *);
  virtual void visit_real_type(real_type_n *);
  virtual void visit_array_type(array_type_n *);
  virtual void visit_record_type(record_type_n *);
  virtual void visit_union_type(union_type_n *);
  virtual void visit_pointer_type(pointer_type_n *);
  virtual void visit_function_type(function_type_n *);
  virtual void visit_othr_type(othr_type_n *);
  
  // visit constants
  virtual void visit_integer_cst(integer_cst_n *);
  virtual void visit_real_cst(real_cst_n *);
  virtual void visit_string_cst(string_cst_n *);
  virtual void visit_othr_cst(othr_cst_n *);
  
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
  virtual void visit_identifier(identifier_n *);
  virtual void visit_tree_list(tree_list_n *);
  virtual void visit_case_label(case_label_n *);
  virtual void visit_special(special_n *);

  //! The initialization operation
  /*!    
    Dump the head of the dot file
  */
  void init(void);

  //! Checks is the nodes has just visited
  /*! 
    \param np the pointer to nast_node that we will check

    \return True if the nast_node *np has visited,
    false otherwise.
  */
  bool haveVisited (nast_node *np);

};

#endif

