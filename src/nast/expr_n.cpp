/***************************************************************************
                          expr_n.cpp  -  description
                             -------------------
    begin                : July 13 2001
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
#include "nast/expr_n.h"
  
#include "visitor/visitor.h"
  
// ---------------------------------------------------------------------------
//  MEMBERS
// ---------------------------------------------------------------------------



//------------------------
// unary_expr_n
//------------------------

void
unary_expr_n::accept (visitor & v)
{
  v.visit_unary_expr (this);
}



//------------------------
// binary_expr_n
//------------------------

void
binary_expr_n::accept (visitor & v)
{
  v.visit_binary_expr (this);
}



//------------------------
// ternary_expr_n
//------------------------

void
ternary_expr_n::accept (visitor & v)
{
  v.visit_ternary_expr (this);
}


//------------------------
// ref_expr_n
//------------------------

void
ref_expr_n::accept (visitor & v)
{
  v.visit_ref_expr (this);
}



//------------------------
// othr_expr_n
//------------------------

void
othr_expr_n::accept (visitor & v)
{
  v.visit_othr_expr (this);
}


