/***************************************************************************
			   visitor.h  -  description
			      -------------------
     begin                : JULY 20 2001
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

#ifndef _VISITOR_H
#define _VISITOR_H


// ---------------------------------------------------------------------------
//  MACRO DEF
// ---------------------------------------------------------------------------

#ifndef _NAST_NODE_H
class nast_n;
#endif


#ifndef _DECL_N_H
class var_decl_n;
class parm_decl_n;
class const_decl_n;
class result_decl_n;
class field_decl_n;
class type_decl_n;
class label_decl_n;
class function_decl_n;
class othr_decl_n;
#endif


#ifndef _TYPE_N_H
class type_n;
class void_type_n;
class integer_type_n;
class enumeral_type_n;
class real_type_n;
class array_type_n;
class record_type_n;
class union_type_n;
class pointer_type_n;
class function_type_n;
class othr_type_n;
#endif


#ifndef _CONSTANT_N_H
class integer_cst_n;
class real_cst_n;
class string_cst_n;
class othr_cst_n;
#endif


#ifndef _STMT_N_H
class compound_stmt_n;
class break_stmt_n;
class continue_stmt_n;
class scope_stmt_n;
class decl_stmt_n;
class expr_stmt_n;
class goto_stmt_n;
class label_stmt_n;
class return_stmt_n;
class if_stmt_n;
class switch_stmt_n;
class for_stmt_n;
class do_stmt_n;
class while_stmt_n;
class asm_stmt_n;
class othr_stmt_n;
#endif


#ifndef _TREE_LIST_H
class tree_list_n;
class case_label_n;
class identifier_n;
class special_n;
#endif


#ifndef _EXPR_N_H
class unary_expr_n;
class binary_expr_n;
class ternary_expr_n;
class ref_expr_n;
class othr_expr_n;
#endif


// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

//! Represent an onperation to be perfomed on the element of the NAST
/*!
  In the visitor is packaged the operation to be performed. Each class
  of the NAST hierarcy has a virtul function member void accept(visitor &v);
  the body is formed by an invocation to a visitor function member with 
  the argument *this (a reference to the nast class). The function 
  member of the visitor is called, and the operation is performed.

  So, the base elements for a visit's operation are :
  
  - a hierarcy of visitors class (each visitor perform a different operation)
  - a hierarcy to explore (with a function member that accept the
  visit operation)
  
  \image html visitorStructure.png

  The collaboration diagram is :

  \image html collaborationVisitors.png

  In the XOgastan implementation of the visitor pattern we define
  also a hierarcy of class that hold the data collected by the
  differents visitors. So, we have :
  - a hierarcy of visitors class (each visitor perform a different operation)
  - a hierarcy to explore (with a function member that accept the
  visit operation)
  - a hierarcy of dataObj that hold the information collected by the visitor.

  The protocol for the use of the visitor may be like :
  
  \code;
  visitor v;
  
  v.init();
  node->accept(v);
  v.finish();
  \endcode

  \note For some deriveds visitors this protocol may be
  ignored. See the specific documentation.

  \sa nast_node decl_n type_n stmt_n cst_n expr_n othr_n
*/
class visitor {

 public:
  //! Constructor
  visitor () { }

  //! Destructor 
  ~visitor() { }

  //! The initialization operation
  virtual void init(void);

  //! The finalization operation
  virtual void finish(void);

  /* These functions member are used to visit the declarations node.*/
  virtual void visit_var_decl(var_decl_n *);
  virtual void visit_parm_decl(parm_decl_n *);
  virtual void visit_result_decl(result_decl_n *);
  virtual void visit_const_decl(const_decl_n *);
  virtual void visit_field_decl(field_decl_n *);
  virtual void visit_type_decl(type_decl_n *);
  virtual void visit_function_decl(function_decl_n *);
  virtual void visit_label_decl(label_decl_n *);
  virtual void visit_othr_decl(othr_decl_n *);

  /* These functions member are used to visit the types node.*/
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

  /* These functions member are used to visit the constants node.*/
  virtual void visit_integer_cst(integer_cst_n *);
  virtual void visit_real_cst(real_cst_n *);
  virtual void visit_string_cst(string_cst_n *);
  virtual void visit_othr_cst(othr_cst_n *);

  /* These functions member are used to visit the statements node.*/
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
		
  /* These functions member are used to visit the expressions node.*/
  virtual void visit_unary_expr(unary_expr_n *);
  virtual void visit_binary_expr(binary_expr_n *);
  virtual void visit_ternary_expr(ternary_expr_n *);
  virtual void visit_ref_expr(ref_expr_n *);
  virtual void visit_othr_expr(othr_expr_n *);

  /* These functions member are used to visit the others node.*/
  virtual void visit_identifier(identifier_n *);
  virtual void visit_tree_list(tree_list_n *);
  virtual void visit_case_label(case_label_n *);
  virtual void visit_special(special_n *);
 
};

#endif

