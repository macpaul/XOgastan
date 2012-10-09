/***************************************************************************
			   visit_varUsedByFnct.cpp  -  description
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

#ifndef _VISIT_VAR_USED_BY_FNCT_H
#define _VISIT_VAR_USED_BY_FNCT_H

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

#include "data/typeDef.h"
#include "data/varUsedData.h"

#include <list>
#include <string>

// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

//! This visitor build a list of the variables used by a function
/*!
  <b>Purpose</b> :<br>
  Build a list of the variables used by a function, or, in other
  word : build a list of the variables used in some expression
  into a function.

  <b>Rules</b> :<br>
  From the entry point of the body of a function_decl
  it visit the statements in the body, and the 
  expressions linked to this statements.<br>
  When an entry point of expression is
  reached the currespondent expression is visited, and a list
  of the variables used is built. An entry point of an expression 
  is expr_stmt, the condition of an if, a switch, a while, a do, a for, 
  the initialization of a for, the increment of a for, the 
  expression of a return.<br>
  When a var_decl node or a parm_decl node
  is reached we build the name of declaration, the 
  type, and the other informations.<br>
  When a type_n node is reached we build the name of the
  type, the operator of the type ( [], * ) and the qualifier.
  The only special case is the type pointer to function. This 
  case is treated by visiting : the function_type node
  for the type of the function pointed to, and the list of tree_list_n
  for the arguments of the function pointed to.<br>
  When a stmt_n node is reached we follow the link to the other 
  stmt_n, and we explore the expressions linked to the node, if 
  there are.<br>
  When a decl_stmt node is reach we push it on the list
  of nast_node *. At the end of the visit we check if 
  the variables used belong to these list. The variable 
  that doesn't belong to the list is external to the function !

  <b>Action</b> :<br> 
\code
visit_varUsedByFnct::var_decl
  get the NodeP
  get the PosName
  get the Line  
  visit the child NAME_EDGE   get the Name
  visit the child TYPE_EDGE   get the Type
  get the TypeExtra
  get the StarNumber
  get the SquareNumber
  if it doesn't belong to the list varUsedList the push it in the list
visit_varUsedByFnct::visit_parm_decl 
  get the NodeP
  get the PosName
  get the Line  
  visit the child NAME_EDGE get the Name
  visit the child TYPE_EDGE get the Type
  get the TypeExtra
  get the StarNumber
  get the SquareNumber
  push on the declsList
  if it doesn't belong to the list varUsedList the push it in the list
visit_varUsedByFnct::visit_break_stmt 
  visit the child NEXT_STMT_EDGE
visit_varUsedByFnct::visit_continue_stmt 
  visit the child NEXT_STMT_EDGE
visit_varUsedByFnct::visit_scope_stmt 
  visit the child NEXT_STMT_EDGE
visit_varUsedByFnct::visit_decl_stmt 
  visit the child NEXT_STMT_EDGE
  push the nast_node* into the list of declarations declStmtL
visit_varUsedByFnct::visit_expr_stmt 
  visit the child NEXT_STMT_EDGE
  visit the child EXPRESSION_EDGE
visit_varUsedByFnct::visit_goto_stmt 
  visit the child NEXT_STMT_EDGE
  visit the child DESTINATION_EDGE
visit_varUsedByFnct::visit_label_stmt 
  visit the child NEXT_STMT_EDGE
visit_varUsedByFnct::visit_return_stmt 
  visit the child NEXT_STMT_EDGE
  visit the child EXPRESSION_EDGE
visit_varUsedByFnct::visit_if_stmt 
  visit the child NEXT_STMT_EDGE
  visit the child THEN_EDGE
  visit the child ELSE_EDGE
  visit the child CONDITION_EDGE
visit_varUsedByFnct::visit_switch_stmt 
  visit the child NEXT_STMT_EDGE
  visit the child BODY_EDGE
  visit the child CONDITION_EDGE
visit_varUsedByFnct::visit_for_stmt 
  visit the child NEXT_STMT_EDGE
  visit the child BODY_EDGE
  visit the child CONDITION_EDGE
  visit the child EXPRESSION_EDGE
  visit the child INITIALIZATION_EDGE
visit_varUsedByFnct::visit_while_stmt 
  visit the child NEXT_STMT_EDGE
  visit the child BODY_EDGE
  visit the child CONDITION_EDGE
visit_varUsedByFnct::visit_do_stmt 
  visit the child NEXT_STMT_EDGE
  visit the child BODY_EDGE
  visit the child CONDITION_EDGE
visit_varUsedByFnct::visit_compound_stmt 
  visit the child NEXT_STMT_EDGE
  visit the child BODY_EDGE
visit_varUsedByFnct::visit_asm_stmt 
  visit the child NEXT_STMT_EDGE
visit_varUsedByFnct::visit_case_label 
  visit the child NEXT_STMT_EDGE
visit_varUsedByFnct::visit_othr_stmt 
  visit the child NEXT_STMT_EDGE
visit_varUsedByFnct::visit_unary_expr 
  visit the child OPERAND_0_EDGE
visit_varUsedByFnct::visit_binary_expr 
  visit the child OPERAND_0_EDGE
  visit the child OPERAND_1_EDGE
visit_varUsedByFnct::visit_ternary_expr 
  visit the child CONDITION_EDGE
  visit the child THEN_VALUE_EDGE
  visit the child ELSE_VALUE_EDGE
visit_varUsedByFnct::visit_ref_expr 
  visit the child OPERAND_0_EDGE
  visit the child OPERAND_1_EDGE
  visit the child OPERAND_2_EDGE
  visit the child AGGREGATE_EDGE
  visit the child FIELD_EDGE
  visit the child ARRAY_EDGE
  visit the child INDEX_EDGE
visit_varUsedByFnct::visit_othr_expr 
  if it is a LOOP_EXPR then visit the child BODY_EDGE
  if it is a CALL_EXPR then visit the child ARGUMENTS_EDGE
  if it is a CALL_EXPR then visit the child FUNCTION_EDGE
  if it is a TARGET_EXPR then visit the child INITIALIZER_EDGE
  visit the child OPERAND_0_EDGE
  visit the child OPERAND_1_EDGE
  visit the child OPERAND_2_EDGE
visit_varUsedByFnct::visit_void_type 
  build the name "void "
  set to true constantSetted if the type has constant qualifier
  set to true volatileSetted if the type has volatile qualifier
  set to true restrictSetted if the type has restrict qualifier
visit_varUsedByFnct::visit_integer_type 
  visit the child MAIN_VARIANT_EDGE or NAME_EDGE and get the name of the type	
  set to true constantSetted if the type has constant qualifier
  set to true volatileSetted if the type has volatile qualifier
  set to true restrictSetted if the type has restrict qualifier
visit_varUsedByFnct::visit_enumeral_type 
  visit the child MAIN_VARIANT_EDGE or NAME_EDGE and get the name of the type	
  set to true constantSetted if the type has constant qualifier
  set to true volatileSetted if the type has volatile qualifier
  set to true restrictSetted if the type has restrict qualifier
visit_varUsedByFnct::visit_real_type 
  visit the child MAIN_VARIANT_EDGE or NAME_EDGE and get the name of the type	
  set to true constantSetted if the type has constant qualifier
  set to true volatileSetted if the type has volatile qualifier
  set to true restrictSetted if the type has restrict qualifier
visit_varUsedByFnct::visit_array_type 
  visit the child MAIN_VARIANT_EDGE or NAME_EDGE and get the name of the type
  set to true constantSetted if the type has constant qualifier
  set to true volatileSetted if the type has volatile qualifier
  set to true restrictSetted if the type has restrict qualifier
visit_varUsedByFnct::visit_record_type 
  visit the child MAIN_VARIANT_EDGE or NAME_EDGE and get the name of the type
  set to true constantSetted if the type has constant qualifier
  set to true volatileSetted if the type has volatile qualifier
  set to true restrictSetted if the type has restrict qualifier
visit_varUsedByFnct::visit_union_type 
  visit the child MAIN_VARIANT_EDGE or NAME_EDGE and get the name of the type
  set to true constantSetted if the type has constant qualifier
  set to true volatileSetted if the type has volatile qualifier
  set to true restrictSetted if the type has restrict qualifier
visit_varUsedByFnct::visit_pointer_type 
  visit the child POINTED_TO_EDGE and get the type of the elements
  set to true constantSetted if the type has constant qualifier
  set to true volatileSetted if the type has volatile qualifier
  set to true restrictSetted if the type has restrict qualifier
visit_varUsedByFnct::visit_function_type 
  visit the child TYPE_RETURNED_EDGE and build the type returned
  visit the child ARGUMENTS_EDGE and build the list (string) of arguments
visit_varUsedByFnct::visit_othr_type 
  visit the child MAIN_VARIANT_EDGE or NAME_EDGE and get the name of the type
  set to true constantSetted if the type has constant qualifier
  set to true volatileSetted if the type has volatile qualifier
  set to true restrictSetted if the type has restrict qualifier
visit_varUsedByFnct::visit_identifier 
  get the name of the identifier
visit_varUsedByFnct::visit_tree_list 
  visit the child VALUE_EDGE  and build it
  visit the child NEXT_EDGE 
\endcode

  <b>dataObj</b> used :<br>
  varUsedData and the typedef varUsedList to build the list of variables used.
  
  The caller of this visitor must use it to visit
  the body of function. So, the caller browse the 
  declarations into the global namespace, one node for time, 
  and for each function_decl_n it visit the body.
  The protocol must be like :
  
  \code
  visit_varUsedByFnct   v;
  nast_node             *node;
  nast_node             *body;
  varUsedList           *list;
  
  if (node is a function_decl_n) {
    v.setVarUsedList(list);
    v.setFnctName(fnctName);
    v.init();
    body = get the body of function_decl;
    body->accept(v);
    v.finish();
  }
  \endcode
*/
class visit_varUsedByFnct : public visitor 
{

 private:
  
  //! The list of the variables used
  /*!
    In this list are placed the informations about the
    variable used (it's a declaration node var_decl, or
    a parm_decl).

    When we find a variable used then :
    - the type, if there's, is built
    - the name, if there's, is built
    - the extra informations are collected
    - All the informations are placed into an object varUsedData
    - The object varUsedData is placed into this list
   */    
  varUsedList *vuL;

  //! Temporary string
  /*!    
    This string is used to build the different informations.

    A typical use is when we visit an identifier_n :
    - the identifier_n set tempS whit its stringValue.
    - the caller of identifier_n::accept(visitor &) use the value
    of tempS to build its own information. (see the name 
    of var_decl_n)
  */
  string tempS;

  //! The name of the function 
  string fnctName;

  //! The name of the variable used
  string name;

  //! The type of the variable used
  string type;

  //! The extra information about the type of the variable used
  string typeExtra;

  //! Flag for the constant qualifier
  /*!
    Values :

    true, if the type has a constant qualifier
    false, if the type hasn't a constnt qualifier
  */
  bool  constantSetted;

  //! Flag for the volatile qualifier
  /*!
    Values :

    true, if the type has a volatile qualifier
    false, if the type hasn't a volatile qualifier
  */
  bool  volatileSetted;

  //! Flag for the restrict qualifier
  /*!
    Values :

    true, if the type has a restrict qualifier
    false, if the type hasn't a restrict qualifier
  */
  bool  restrictSetted;

  //! The number of * (for pointer type)
  int starNumber;

  //! The number of [] (for array type)
  int squareNumber;

  //! The list of arguments of function
  /*!   
    This attribute is used when we found a declaration
    which type is pointer to function. In this case :
    - the type returned by the function is built
    - the arguments list is built. The type of the arguments of the function 
    are built, one for time, and are concatenate in this string.
  */
  string                            argumentsList;

  //! The list of declaration nodes (child of decl_stmt node)
  /*!
    At the end of the visit we call the method
    finish(). This method check if the variables used 
    found belong to the current function or have global
    scope.
    
    If the variable used belong to these list (has 
    a pointer in this list) then it has local
    scope, otherwise it has global scope.
  */
  list<nast_node *>                 declStmtL;

 public:
  //! Constructor
  visit_varUsedByFnct() { }
  
  //! Destructor
  ~visit_varUsedByFnct() { }


  //---- Members

  //! Set the pointer to the declaration list
  void setVarUsedList(varUsedList *vuL) 
    { this->vuL = vuL; }

  //! Set the function name
  void setFnctName(string fnctName) 
    { this->fnctName = fnctName; }

  //! The initialization operation
  virtual void init(void);

  //! The finalization operation
  virtual void finish(void);

  // visit declarations
  virtual void visit_var_decl(var_decl_n *);
  virtual void visit_parm_decl(parm_decl_n *);

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

  //! Clear the data of the previous declaration built
  void clearData(void);

};

#endif




