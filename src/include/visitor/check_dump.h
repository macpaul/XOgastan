/***************************************************************************
			   check_dump.cpp  -  description
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

#ifndef _CHECK_DUMP_H
#define _CHECK_DUMP_H

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

#include "utils/a2b.h"

#include "error/bad_nast.h"

#include <map>
#include <string>

// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

//! Visit the NAST structure, check the dangling reference and dumps the nodes
/*! Visit the NAST structure, check the dangling reference and dumps the nodes */
class check_dump : public visitor 
{

 private:
  // S stay for start
  // E stay for end
  void dump_nodeS(long id, string type);
  void dump_nodeE(void);
  void dump_attr(char* name, char* type, string value);
  void dump_attr(char* name, char* type, char* value);
  void dump_attr(char* name, char* type, long value);
  void dump_edge(long from, long to, string type);

  void sniff_and_dump_edges(nast_node *np);
  void visit_edges(nast_node *np);

  // nodes just visited 
  map<long, nast_node *> visited;

 public:
  check_dump() { }
  
  check_dump(ofstream *out) : visitor(out) { }
  
  ~check_dump() { }

  void begin_visit() { 
    (*output) << "<?xml version=\"1.0\"?>\n\n" 
	      << "<!DOCTYPE gxl SYSTEM \"gxl.dtd\">\n\n"
	      << "<gxl><graph id=\"GCC_AST\">\n\n";
  }
  
  void end_visit() {
    (*output) << "\n\n</graph></gxl>\n";
  }

  virtual void visitor_reset(void);
  virtual void visitor_dump_info(void);

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

};

#endif

