/***************************************************************************
			   visit_exprsInFnct.cpp  -  description
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

#ifndef _VISIT_EXPRS_IN_FNCT_H
#define _VISIT_EXPRS_IN_FNCT_H

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
#include "data/exprData.h"
#include "data/exprNumData.h"
#include "data/varUsedData.h"

#include <list>
#include <string>

// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

//! This visitor build a list of the variables used by a function
/*!
  <b>Purpose</b> :<br>

  <b>Rules</b> :<br>

  <b>Action</b> :<br> 

  <b>dataObj</b> used :<br>
  
*/
class visit_exprsInFnct : public visitor 
{

 private:
  
  //! The list of the variables used
  /*!
    In this list are placed the information about the
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

  //! The statistic information about the operator of an expression
  exprNumData   *exprStat;

  //! The list of expression
  exprsList     *exprL;

  //! The information about an expression
  exprData      *eData;

 public:
  //! Constructor
  visit_exprsInFnct() { }
  
  //! Destructor
  ~visit_exprsInFnct() { }


  //---- Members

  //! Set the pointer to the declaration list
  void setExprsList(exprsList *exprL) 
    { this->exprL = exprL; }

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




