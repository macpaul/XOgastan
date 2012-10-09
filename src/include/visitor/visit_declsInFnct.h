/***************************************************************************
			   visit_declsInFnct.cpp  -  description
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

#ifndef _VISIT_DECLS_IN_FNCT_H
#define _VISIT_DECLS_IN_FNCT_H

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
#include "data/declData.h"

#include <list>
#include <string>

// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

//! This visitor build a list of the declarations in a function's body
/*!
  <b>Purpose</b> :<br>
  Build a list of declarations into a function

  <b>Rules</b> :<br>
  From the entry point of the body of a function_decl
  it visit the statements in the body.<br>
  When a decl_stmt node is reached then we build
  the currespondent declaration by visiting the
  declaration node.<br>
  When a declaration node (var_decl, type_decl, const_decl, ...)
  is reached we build the name of declaration, the 
  type, and the other informations.<br>
  When a type_n node is reached we build the name of the
  type, the operator of the type ( [], * ) and the qualifier.
  The only special case is the type pointer to function. This 
  case is treated by visiting : the function_type node
  for the type of the function pointed to, and the list of tree_list_n
  for the arguments of the function pointed to.
  When a stmt_n node is reached we follow the link to the other 
  stmt_n.

  <b>Action</b> :<br> 
\code
visit_declsInFnct::var_decl
  get the NodeP
  get the PosName
  get the Line  
  visit the child NAME_EDGE   get the Name
  visit the child TYPE_EDGE   get the Type
  get the TypeExtra
  get the StarNumber
  get the SquareNumber
  push on the declsList
visit_declsInFnct::visit_type_decl 
  get the NodeP
  get the PosName
  get the Line  
  visit the child NAME_EDGE get the Name
    visit the child TYPE_EDGE get the Type
  get the TypeExtra
  get the StarNumber
  get the SquareNumber
  push on the declsList
visit_declsInFnct::visit_void_type 
  build the name "void "
  set to true constantSetted if the type has constant qualifier
  set to true volatileSetted if the type has volatile qualifier
  set to true restrictSetted if the type has restrict qualifier
visit_declsInFnct::visit_integer_type 
  visit the child MAIN_VARIANT_EDGE or NAME_EDGE and get the name of the type	
  set to true constantSetted if the type has constant qualifier
  set to true volatileSetted if the type has volatile qualifier
  set to true restrictSetted if the type has restrict qualifier
visit_declsInFnct::visit_enumeral_type 
  visit the child MAIN_VARIANT_EDGE or NAME_EDGE and get the name of the type	
  set to true constantSetted if the type has constant qualifier
  set to true volatileSetted if the type has volatile qualifier
  set to true restrictSetted if the type has restrict qualifier
visit_declsInFnct::visit_real_type 
  visit the child MAIN_VARIANT_EDGE or NAME_EDGE and get the name of the type	
  set to true constantSetted if the type has constant qualifier
  set to true volatileSetted if the type has volatile qualifier
  set to true restrictSetted if the type has restrict qualifier
visit_declsInFnct::visit_array_type 
  visit the child MAIN_VARIANT_EDGE or NAME_EDGE and get the name of the type
  set to true constantSetted if the type has constant qualifier
  set to true volatileSetted if the type has volatile qualifier
  set to true restrictSetted if the type has restrict qualifier
visit_declsInFnct::visit_record_type 
  visit the child MAIN_VARIANT_EDGE or NAME_EDGE and get the name of the type
  set to true constantSetted if the type has constant qualifier
  set to true volatileSetted if the type has volatile qualifier
  set to true restrictSetted if the type has restrict qualifier
visit_declsInFnct::visit_union_type 
  visit the child MAIN_VARIANT_EDGE or NAME_EDGE and get the name of the type
  set to true constantSetted if the type has constant qualifier
  set to true volatileSetted if the type has volatile qualifier
  set to true restrictSetted if the type has restrict qualifier
visit_declsInFnct::visit_pointer_type 
  visit the child POINTED_TO_EDGE and get the type of the elements
  set to true constantSetted if the type has constant qualifier
  set to true volatileSetted if the type has volatile qualifier
  set to true restrictSetted if the type has restrict qualifier
visit_declsInFnct::visit_function_type 
  visit the child TYPE_RETURNED_EDGE and build the type returned
  visit the child ARGUMENTS_EDGE and build the list (string) of arguments
visit_declsInFnct::visit_othr_type 
  visit the child MAIN_VARIANT_EDGE or NAME_EDGE and get the name of the type
  set to true constantSetted if the type has constant qualifier
  set to true volatileSetted if the type has volatile qualifier
  set to true restrictSetted if the type has restrict qualifier
visit_declsInFnct::visit_break_stmt 
  visit the child NEXT_STMT_EDGE
visit_declsInFnct::visit_continue_stmt 
  visit the child NEXT_STMT_EDGE
visit_declsInFnct::visit_scope_stmt 
  visit the child NEXT_STMT_EDGE
visit_declsInFnct::visit_decl_stmt 
  visit the child DECLARATIONS_EDGE
  visit the child NEXT_STMT_EDGE
visit_declsInFnct::visit_expr_stmt 
  visit the child NEXT_STMT_EDGE
  visit the child EXPRESSION_EDGE (we can have an infinite loop)
visit_declsInFnct::visit_goto_stmt 
  visit the child NEXT_STMT_EDGE
visit_declsInFnct::visit_label_stmt 
  visit the child NEXT_STMT_EDGE
visit_declsInFnct::visit_return_stmt 
  visit the child NEXT_STMT_EDGE
visit_declsInFnct::visit_if_stmt 
  visit the child THEN_EDGE
  visit the child ELSE_EDGE
  visit the child NEXT_STMT_EDGE
visit_declsInFnct::visit_switch_stmt 
  visit the child BODY_EDGE
  visit the child NEXT_STMT_EDGE
visit_declsInFnct::visit_for_stmt 
  visit the child BODY_EDGE
  visit the child NEXT_STMT_EDGE
visit_declsInFnct::visit_while_stmt 
  visit the child BODY_EDGE
  visit the child NEXT_STMT_EDGE
visit_declsInFnct::visit_do_stmt 
  visit the child BODY_EDGE
  visit the child NEXT_STMT_EDGE
visit_declsInFnct::visit_compound_stmt 
  visit the child NEXT_STMT_EDGE
  visit the child BODY_EDGE
  visit the child NEXT_STMT_EDGE
  visit the child NEXT_STMT_EDGE
visit_declsInFnct::visit_othr_expr 
  if it's a LOOP_EXPR the visit the child BODY_EDGE
visit_declsInFnct::visit_identifier 
  get the name of the identifier
visit_declsInFnct::visit_tree_list 
  visit the child VALUE_EDGE (the name of the argument) and build it
  visit the child NEXT_EDGE (the next argument)
visit_declsInFnct::visit_case_label 
  visit the child NEXT_STMT_EDGE
\endcode


  <b>dataObj</b> used :<br>
  declData and the typedef declsList.

  The caller of this visitor must use it to visit
  the body of function. So, the caller browse the 
  declarations into the global namespace, one node for time, 
  and for each function_decl_n it visit the body.
  The protocol must be like :
  
  \code
  visit_declsInFnct   v;
  nast_node           *node;
  nast_node           *body;
  declsList           *list;
  
  if (node is a function_decl_n) {
    v.setDeclsList(list);
    v.setFnctName(fnctName);
    body = get the body of the function_decl;
    body->accept(v);
  }
  \endcode
*/
class visit_declsInFnct : public visitor 
{

 private:

  //! The list of the declarations that we find
  /*!
    In this list are placed the informations about the
    declaration found.

    When we find a decl_n then :
    - the type, if there's, is built
    - the name, if there's, is built
    - the extra informations are collected
    - All the informations are placed into an object declData
    - The object declData is placed into this list
   */    
  declsList *dL;

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
  /*!
    This function's name is registered into the object delcData
  */
  string fnctName;

  //! The name of the declaration 
  string name;

  //! The type of the declaration 
  string type;

  //! The extra information about the type of the declaration 
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
  string argumentsList;

 public:
  //! Constructor
  visit_declsInFnct() { }
  
  //! Destructor
  ~visit_declsInFnct() { }

  //---- Members

  //! Set the pointer to the declaration list
  void setDeclsList(declsList *dL) 
    { this->dL = dL; }

  //! Set the function name
  void setFnctName(string fnctName) 
    { this->fnctName = fnctName; }

  // visit declarations
  virtual void visit_var_decl(var_decl_n *);
  virtual void visit_type_decl(type_decl_n *);

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
  virtual void visit_othr_expr(othr_expr_n *);

  // visit other nodes
  virtual void visit_identifier(identifier_n *);
  virtual void visit_tree_list(tree_list_n *);
  virtual void visit_case_label(case_label_n *);

  //! Clear the data of the previous declaration built
  void clearData(void);

};

#endif




