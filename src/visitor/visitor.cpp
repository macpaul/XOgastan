/***************************************************************************
			   visitor.cpp  -  description
			      -------------------
     begin                : Aug 9 2001
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

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "visitor/visitor.h"

// ---------------------------------------------------------------------------
//  MEMBERS
// ---------------------------------------------------------------------------

// visit declarations
void
visitor::init(void)
{
  return;
}

void
visitor::finish (void)
{
  return;
}


// visit declarations
void
visitor::visit_var_decl (var_decl_n *)
{
  return;
}

void
visitor::visit_parm_decl (parm_decl_n *)
{
  return;
}

void
visitor::visit_result_decl (result_decl_n *)
{
  return;
}

void
visitor::visit_const_decl (const_decl_n *)
{
  return;
}

void
visitor::visit_field_decl (field_decl_n *)
{
  return;
}

void
visitor::visit_type_decl (type_decl_n *)
{
  return;
}

void
visitor::visit_function_decl (function_decl_n *)
{
  return;
}

void
visitor::visit_label_decl (label_decl_n *)
{
  return;
}

void
visitor::visit_othr_decl (othr_decl_n *)
{
  return;
}

  // visit types
void
visitor::visit_void_type (void_type_n *)
{
  return;
}

void
visitor::visit_integer_type (integer_type_n *)
{
  return;
}

void
visitor::visit_enumeral_type (enumeral_type_n *)
{
  return;
}

void
visitor::visit_real_type (real_type_n *)
{
  return;
}

void
visitor::visit_array_type (array_type_n *)
{
  return;
}

void
visitor::visit_record_type (record_type_n *)
{
  return;
}

void
visitor::visit_union_type (union_type_n *)
{
  return;
}

void
visitor::visit_pointer_type (pointer_type_n *)
{
  return;
}

void
visitor::visit_function_type (function_type_n *)
{
  return;
}

void
visitor::visit_othr_type (othr_type_n *)
{
  return;
}

  // visit constants
void
visitor::visit_integer_cst (integer_cst_n *)
{
  return;
}

void
visitor::visit_real_cst (real_cst_n *)
{
  return;
}

void
visitor::visit_string_cst (string_cst_n *)
{
  return;
}

void
visitor::visit_othr_cst (othr_cst_n *)
{
  return;
}

  // visit statements
void
visitor::visit_break_stmt (break_stmt_n *)
{
  return;
}

void
visitor::visit_continue_stmt (continue_stmt_n *)
{
  return;
}

void
visitor::visit_scope_stmt (scope_stmt_n *)
{
  return;
}

void
visitor::visit_decl_stmt (decl_stmt_n *)
{
  return;
}

void
visitor::visit_expr_stmt (expr_stmt_n *)
{
  return;
}

void
visitor::visit_goto_stmt (goto_stmt_n *)
{
  return;
}

void
visitor::visit_label_stmt (label_stmt_n *)
{
  return;
}

void
visitor::visit_return_stmt (return_stmt_n *)
{
  return;
}

void
visitor::visit_if_stmt (if_stmt_n *)
{
  return;
}

void
visitor::visit_switch_stmt (switch_stmt_n *)
{
  return;
}

void
visitor::visit_for_stmt (for_stmt_n *)
{
  return;
}

void
visitor::visit_while_stmt (while_stmt_n *)
{
  return;
}

void
visitor::visit_do_stmt (do_stmt_n *)
{
  return;
}

void
visitor::visit_compound_stmt (compound_stmt_n *)
{
  return;
}

void
visitor::visit_asm_stmt (asm_stmt_n *)
{
  return;
}

void
visitor::visit_othr_stmt (othr_stmt_n *)
{
  return;
}

  // visit expressions
void
visitor::visit_unary_expr (unary_expr_n *)
{
  return;
}

void
visitor::visit_binary_expr (binary_expr_n *)
{
  return;
}

void
visitor::visit_ternary_expr (ternary_expr_n *)
{
  return;
}

void
visitor::visit_ref_expr (ref_expr_n *)
{
  return;
}

void
visitor::visit_othr_expr (othr_expr_n *)
{
  return;
}

  // visit other nodes
void
visitor::visit_identifier (identifier_n *)
{
  return;
}

void
visitor::visit_tree_list (tree_list_n *)
{
  return;
}

void
visitor::visit_case_label (case_label_n *)
{
  return;
}

void
visitor::visit_special (special_n *)
{
  return;
}
