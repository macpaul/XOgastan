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
#include "visitor/check_dump.h"

// ---------------------------------------------------------------------------
//  MEMBERS
// ---------------------------------------------------------------------------

void
check_dump::visitor_reset (void)
{
  return;
}

void
check_dump::visitor_dump_info (void)
{
  return;
}


void
check_dump::sniff_and_dump_edges (nast_node * np)
{

  try {
    if (np->hasEdges ())
      {
	nast_node *p;
	
	p = np->firstEdge ();
	dump_edge (np->getId (), p->getId (),
		   a2b::edge_code2string (np->currentEdgeCode ()));
	
	while (np->hasNextEdge ())
	  {
	    p = np->nextEdge ();
	    dump_edge (np->getId (), p->getId (),
		       a2b::edge_code2string (np->currentEdgeCode ()));
	  }
      }
  }
  catch (bad_XOgastan &b) {
    
  }
  catch (...) {
   
    throw bad_XOgastan ("Check_dump", "unknown event force the termination");
  
  }
}
  
void
check_dump::visit_edges (nast_node * np)
{
  try {
    if (np->hasEdges ())
      {
	nast_node *p;
	
	p = np->firstEdge ();
		
	if (visited.find(p->getId()) == visited.end()) {
	  visited[p->getId()] = p;
	  p->accept (*this);
	}
	
	while (np->hasNextEdge ())
	  {
	    p = np->nextEdge ();

	    if (visited.find(p->getId()) == visited.end()) {
	      visited[p->getId()] = p;
	      p->accept (*this);
	    }
	  }
      }
  }
  catch (bad_XOgastan &b) {
  }
  catch (...) {
    
    throw bad_XOgastan ("Check_dump", "unknown event force the termination");
    
  }
  
}

// visit declarations
void
check_dump::visit_var_decl (var_decl_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_attr ("source_file", "string", np->getSource ());
  dump_attr ("source_line", "int", np->getLine ());
  if (np->isArtificial ())
    dump_attr ("flag", "string", "artificial");

  if (np->isRegister ())
    dump_attr ("flag", "string", "register");

  dump_nodeE ();

  sniff_and_dump_edges (np);
  visit_edges (np);

  return;
}

void
check_dump::visit_parm_decl (parm_decl_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_attr ("source_file", "string", np->getSource ());
  dump_attr ("source_line", "int", np->getLine ());
  if (np->isArtificial ())
    dump_attr ("flag", "string", "artificial");

  if (np->isRegister ())
    dump_attr ("flag", "string", "register");

  dump_nodeE ();

  sniff_and_dump_edges (np);
  visit_edges (np);

  return;
}

void
check_dump::visit_result_decl (result_decl_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_attr ("source_file", "string", np->getSource ());
  dump_attr ("source_line", "int", np->getLine ());
  if (np->isArtificial ())
    dump_attr ("flag", "string", "artificial");

  sniff_and_dump_edges (np);
  visit_edges (np);

  return;
}

void
check_dump::visit_const_decl (const_decl_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_attr ("source_file", "string", np->getSource ());
  dump_attr ("source_line", "int", np->getLine ());
  if (np->isArtificial ())
    dump_attr ("flag", "string", "artificial");

  dump_nodeE ();

  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_field_decl (field_decl_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_attr ("source_file", "string", np->getSource ());
  dump_attr ("source_line", "int", np->getLine ());
  if (np->isArtificial ())
    dump_attr ("flag", "string", "artificial");

  if (np->isBitfield ())
    dump_attr ("flag", "string", "bitfield");

  dump_nodeE ();

  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_type_decl (type_decl_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_attr ("source_file", "string", np->getSource ());
  dump_attr ("source_line", "int", np->getLine ());
  if (np->isArtificial ())
    dump_attr ("flag", "string", "artificial");

  dump_nodeE ();


  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_function_decl (function_decl_n * np)
{

  cout << "Visit function_decl\n\n";

  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));
  
  dump_attr ("source_file", "string", np->getSource ());
  dump_attr ("source_line", "int", np->getLine ());
  
  if (np->isArtificial ())
    dump_attr ("flag", "string", "artificial");
  
  if (np->isStatic ())
    dump_attr ("flag", "string", "static");
  else
    dump_attr ("flag", "string", "extern");

  if (np->isUndefined ())
    dump_attr ("flag", "string", "undefined");

  cout.flush();

  dump_nodeE ();

  sniff_and_dump_edges (np);

  visit_edges (np);

  return;
}

void
check_dump::visit_label_decl (label_decl_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_attr ("source_file", "string", np->getSource ());
  dump_attr ("source_line", "int", np->getLine ());
  if (np->isArtificial ())
    dump_attr ("flag", "string", "artificial");

  dump_nodeE ();


  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_othr_decl (othr_decl_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_attr ("source_file", "string", np->getSource ());
  dump_attr ("source_line", "int", np->getLine ());

  if (np->isArtificial ())
    dump_attr ("flag", "string", "artificial");

  dump_nodeE ();


  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

  // visit types
void
check_dump::visit_void_type (void_type_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  if (np->isConstant ())
    dump_attr ("qualifier", "string", "constant");
  if (np->isVolatile ())
    dump_attr ("qualifier", "string", "volatile");
  if (np->isRestrict ())
    dump_attr ("qualifier", "string", "restrict");


  dump_nodeE ();


  sniff_and_dump_edges (np);
  visit_edges (np);

  return;
}

void
check_dump::visit_integer_type (integer_type_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  if (np->isConstant ())
    dump_attr ("qualifier", "string", "constant");
  if (np->isVolatile ())
    dump_attr ("qualifier", "string", "volatile");
  if (np->isRestrict ())
    dump_attr ("qualifier", "string", "restrict");

  if (np->isUnsigned ())
    dump_attr ("flag", "string", "unsigned");

  dump_nodeE ();


  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_enumeral_type (enumeral_type_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  if (np->isConstant ())
    dump_attr ("qualifier", "string", "constant");
  if (np->isVolatile ())
    dump_attr ("qualifier", "string", "volatile");
  if (np->isRestrict ())
    dump_attr ("qualifier", "string", "restrict");

  if (np->isUnsigned ())
    dump_attr ("flag", "string", "unsigned");

  dump_nodeE ();


  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_real_type (real_type_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  if (np->isConstant ())
    dump_attr ("qualifier", "string", "constant");
  if (np->isVolatile ())
    dump_attr ("qualifier", "string", "volatile");
  if (np->isRestrict ())
    dump_attr ("qualifier", "string", "restrict");

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_array_type (array_type_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  if (np->isConstant ())
    dump_attr ("qualifier", "string", "constant");
  if (np->isVolatile ())
    dump_attr ("qualifier", "string", "volatile");
  if (np->isRestrict ())
    dump_attr ("qualifier", "string", "restrict");

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_record_type (record_type_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  if (np->isConstant ())
    dump_attr ("qualifier", "string", "constant");
  if (np->isVolatile ())
    dump_attr ("qualifier", "string", "volatile");
  if (np->isRestrict ())
    dump_attr ("qualifier", "string", "restrict");

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_union_type (union_type_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  if (np->isConstant ())
    dump_attr ("qualifier", "string", "constant");
  if (np->isVolatile ())
    dump_attr ("qualifier", "string", "volatile");
  if (np->isRestrict ())
    dump_attr ("qualifier", "string", "restrict");

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_pointer_type (pointer_type_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  if (np->isConstant ())
    dump_attr ("qualifier", "string", "constant");
  if (np->isVolatile ())
    dump_attr ("qualifier", "string", "volatile");
  if (np->isRestrict ())
    dump_attr ("qualifier", "string", "restrict");

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_function_type (function_type_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  if (np->isConstant ())
    dump_attr ("qualifier", "string", "constant");
  if (np->isVolatile ())
    dump_attr ("qualifier", "string", "volatile");
  if (np->isRestrict ())
    dump_attr ("qualifier", "string", "restrict");

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_othr_type (othr_type_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  if (np->isConstant ())
    dump_attr ("qualifier", "string", "constant");
  if (np->isVolatile ())
    dump_attr ("qualifier", "string", "volatile");
  if (np->isRestrict ())
    dump_attr ("qualifier", "string", "restrict");

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

  // visit constants
void
check_dump::visit_integer_cst (integer_cst_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  return;
}

void
check_dump::visit_real_cst (real_cst_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_nodeE ();
  return;
}

void
check_dump::visit_string_cst (string_cst_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_nodeE ();
  return;
}

void
check_dump::visit_othr_cst (othr_cst_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_nodeE ();
  return;
}

  // visit statements
void
check_dump::visit_break_stmt (break_stmt_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_attr ("line", "int", np->getLine ());

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_continue_stmt (continue_stmt_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_attr ("line", "int", np->getLine ());

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_scope_stmt (scope_stmt_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_attr ("line", "int", np->getLine ());
  if (np->hasVariables ())
    dump_attr ("flag", "string", "no_variable");
  if (np->isBegin ())
    dump_attr ("flag", "string", "begin");
  else
    dump_attr ("flag", "string", "end");


  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_decl_stmt (decl_stmt_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_attr ("line", "int", np->getLine ());

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_expr_stmt (expr_stmt_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_attr ("line", "int", np->getLine ());

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_goto_stmt (goto_stmt_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_attr ("line", "int", np->getLine ());

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_label_stmt (label_stmt_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_attr ("line", "int", np->getLine ());

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_return_stmt (return_stmt_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_attr ("line", "int", np->getLine ());

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_if_stmt (if_stmt_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_attr ("line", "int", np->getLine ());

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_switch_stmt (switch_stmt_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_attr ("line", "int", np->getLine ());

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_for_stmt (for_stmt_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_attr ("line", "int", np->getLine ());

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_while_stmt (while_stmt_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_attr ("line", "int", np->getLine ());

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_do_stmt (do_stmt_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_attr ("line", "int", np->getLine ());

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_compound_stmt (compound_stmt_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_attr ("line", "int", np->getLine ());

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_asm_stmt (asm_stmt_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_attr ("line", "int", np->getLine ());

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_othr_stmt (othr_stmt_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_attr ("line", "int", np->getLine ());

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

  // visit expressions
void
check_dump::visit_unary_expr (unary_expr_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_binary_expr (binary_expr_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_ternary_expr (ternary_expr_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_ref_expr (ref_expr_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_othr_expr (othr_expr_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

  // visit other nodes
void
check_dump::visit_identifier (identifier_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_attr ("string", "string", np->getString ());

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_tree_list (tree_list_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_case_label (case_label_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::visit_special (special_n * np)
{
  dump_nodeS (np->getId (), a2b::nast_code2string (np->getCode ()));

  dump_nodeE ();
  sniff_and_dump_edges (np);
  visit_edges (np);
  return;
}

void
check_dump::dump_nodeS (long id, string type)
{
  (*output) << "\n<node id=\"nd" << id << "\">\n"
	    << "\t<type xlink:href=\"gccast.xml#" << type << "\"/>\n";
}


void
check_dump::dump_nodeE (void)
{
  (*output) << "</node>\n\n";
}


void
check_dump::dump_attr (char* name,char* type, string value)
{ 
  int pos;
  
  if ( (pos = value.find("<")) != string::npos )
    value.replace (pos, 1, "&lt");
  if ( (pos = value.find(">")) != string::npos )
    value.replace (pos, 1, "&gt");
  
  (*output) << "\t<attr name=\"" << name
	    << "\"><" << type << ">" << value << "</" << type << "></attr>\n";
}

void
check_dump::dump_attr (char* name,char* type,char* value)
{
  int pos;
  string s(value);

  if ( (pos = s.find("<")) != string::npos )
    s.replace (pos, 1, "&lt");
  if ( (pos = s.find(">")) != string::npos )
    s.replace (pos, 1, "&gt");

  (*output) << "\t<attr name=\"" << name
	    << "\"><" << type << ">" << s << "</" << type << "></attr>\n";
}

void
check_dump::dump_attr (char* name,char* type, long value)
{

  (*output) << "\t<attr name=\"" << name
	    << "\"><" << type << ">" << value << "</" << type << "></attr>\n";
}


void
check_dump::dump_edge (long from, long to, string type)
{
  (*output) << "<edge from=\"nd" << from
	    << "\" to=\"nd" << to << "\">"
	    << "<type xlink:href=\"gccast.xml#" << type << "\"/>" << "</edge>\n";
}
