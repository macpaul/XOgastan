/***************************************************************************
                          cst_n.cpp  -  description
                             -------------------
    begin                : July 12 2001
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
#include "nast/cst_n.h"
  
#include "visitor/visitor.h"
  
// ---------------------------------------------------------------------------
//  MEMBERS
// ---------------------------------------------------------------------------



//------------------------
// integer_cst_n
//------------------------

void
integer_cst_n::accept (visitor & v) 
{
  v.visit_integer_cst (this);
}


//------------------------
// real_cst_n
//------------------------

void
real_cst_n::accept (visitor & v) 
{
  v.visit_real_cst (this);
}


//------------------------
// string_cst_n
//------------------------

void
string_cst_n::accept (visitor & v) 
{
  v.visit_string_cst (this);
}


//------------------------
// othr_cst_n
//------------------------

void
othr_cst_n::accept (visitor & v) 
{
  v.visit_othr_cst (this);
}
