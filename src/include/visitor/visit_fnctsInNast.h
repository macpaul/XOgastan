/***************************************************************************
			   visit_fnctsInNast.cpp  -  description
			      -------------------
     begin                : Aug 29 2001
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

#ifndef _VISIT_FNCTS_IN_NAST_H
#define _VISIT_FNCTS_IN_NAST_H

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
#include "data/fnctData.h"
#include "data/parmData.h"

#include "utils/a2b.h"

#include <list>
#include <string>

// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

//! This visitor build a list of the function's declaration 
/*!
  <b>Purpose</b> :<br>
  Build a list of function's declarations

  <b>Rules</b> :<br>
  From the entry point of NAST (a namespace_decl)
  we visit all the nodes declarations that are chained 
  togheter (to form the main chain of the translation unit)
  In other word, we follows the edges NEXT_DECL_EDGE.<br>
  When a function_decl_n is reached then we visit the 
  identifier_n (the function name) and the *_TYPE nodes
  that represent the type of the function.<br>
  When a parm_decl_n is reached then we visit the 
  identifier_n (the parameter name) and the *_TYPE nodes
  that represent the type of the parameter.<br>
  When a *_TYPE node is reached we build the name of 
  type, the operator of the type ( [], * ) and the qualifier.<br>
  The only special case is the type pointer to function. This 
  case is treated by visiting : the function_type node
  for the type of function pointed to, and the list of tree_list_n
  for the argument of the function pointed to.

  <b>Action</b> :<br> 
\code
visit_fnctsInNast::visit_var_decl
  visit the child NEXT_DECL_EDGE
visit_fnctsInNast::visit_parm_decl
  get the NodeP
  visit the child NAME_EDGE and get the name
  visit the child TYPE_EDGE and get the type, 
  get the typeExtra
  get the * number
  get the [] number
  push on the fnctData::parmList
  visit the child NEXT_DECL_EDGE
visit_fnctsInNast::visit_result_decl
  visit the child NEXT_DECL_EDGE
visit_fnctsInNast::visit_const_decl
  visit the child NEXT_DECL_EDGE
visit_fnctsInNast::visit_field_decl
  visit the child NEXT_DECL_EDGE
visit_fnctsInNast::visit_type_decl
  visit the child NEXT_DECL_EDGE
visit_fnctsInNast::visit_function_decl
  get the NodeP
  visit the child NAME_EDGE and get the name
  visit the child TYPE_EDGE and get the type
  visit the child ARGUMENTS_EDGE and get the parameters list
  push on the fnctsList
  visit the child NEXT_DECL_EDGE
visit_fnctsInNast::visit_label_decl
  visit the child NEXT_DECL_EDGE
visit_fnctsInNast::visit_othr_decl
  visit the child NEXT_DECL_EDGE
  if it is a NAMESPACE_DECL visit the child DECLARATIONS_EDGE
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
visit_declsInFnct::visit_identifier 
  get the name of the identifier
visit_declsInFnct::visit_tree_list 
  visit the child VALUE_EDGE (the name of the argument) and build it
  visit the child NEXT_EDGE (the next argument)
\endcode
  
  <b>dataObj</b> used :<br>
  fnctData, parmData and the typedef fnctsList.

  \image html visit_fnctsInNast.jpg

  The caller of this visitor must use it by calling the
  accept method on the entry point (the first node) of the NAST 
  structure.
  The protocol must be like :
  
  \code
  visit_fnctsInNast v;
  nast_node         *nast;
  fnctsList         *list;
  
  v.setFnctsList(list);
  nast->accept(v);
  \endcode
*/
class visit_fnctsInNast : public visitor 
{

 private:
  
  //! The list of the function's declarations that we find
  /*!
    In this list are placed the informations about the
    function's declarations found during the analysis.

    When we find a function_decl_n then :
    - the type is built
    - the name is built
    - the list of parameters is built
    - the extra informations are collected
    - All the informations are placed into an object fnctData
    - The object fnctData is placed into the fnctsList
   */    
  fnctsList *fL;

  //! The fnctData of the currrent function that we are building
  fnctData  *fData;

  //! Temporary string
  /*!    
    This string is used to build different informations.

    A typical use is when we visit an identifier_n :
    - the identifier_n set tempS with its stringValue.
    - the caller of identifier_n::accept(visitor &) use the value
    of tempS to build its own information. (see the name 
    of var_decl_n)
  */
  string tempS;

  //! The name of the function 
  string fnctName;

  //! The type returned by the function
  string fnctType; 

  //! The name of a parameter of the function 
  string parmName;

  //! The type of a parameter of the function 
  string parmType; 

  //! The extra information about the type of a parameter
  string parmTypeExtra;

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

  //! The number of * (for pointer), is a parameter information
  int parmStarNumber;

  //! The number of [] (for array), is a parameter information
  int parmSquareNumber;

  //! The list of arguments of function
  /*!   
    This attribute is used when we found a declaration 
    (of function or of parameter)
    which type is pointer to function. In this case :
    - the type returned by the function is built
    - the arguments list is built, one argument for time.
    The type of the arguments are concatenate in this string.
  */
  string argumentsList;

  //! Flag for the building status of the type
  /*!
    Its value is :
    - true if we are building the type of the function
    - false if we are building the type of a parameter

    When we visit a type_node we build a type. But, the 
    type that we are building, is a type of parameter or a
    type of a function ? This flag helps to tracks if we
    are building the type of function, or the type of a parameter.
  */
  bool buildingFnctType;

  //! The number of the functions without name
  /*!
    Some function_decl has no name. So XOgastan 
    assign them a conventional name.
    The syntax of this name is :<br>
    XOgastan_NOname<noNameNumber>
  */
  long noNameNumber;

 public:
  //! Constructor
  visit_fnctsInNast() 
    { noNameNumber = 0; }
  
  //! Destructor
  ~visit_fnctsInNast() { }

  //! Set the pointer to the functions list
  void setFnctsList(fnctsList *fL) { this->fL = fL; }

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
  
  // visit other nodes
  virtual void visit_identifier(identifier_n *);
  virtual void visit_tree_list(tree_list_n *);

  //! Clear the data of the previous declaration built
  void clearData(void);

};

#endif
