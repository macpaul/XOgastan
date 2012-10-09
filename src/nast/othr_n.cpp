/***************************************************************************
                          othr_n.cpp  -  description
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
#include "nast/othr_n.h"
  
#include "visitor/visitor.h"
  
// ---------------------------------------------------------------------------
//  MEMBERS
// ---------------------------------------------------------------------------



//------------------------
// indentifier_n
//------------------------

void
identifier_n::setString (string s) 
{
  node_string = s;
}

string
identifier_n::getString (void) 
{
  return node_string;
}

void
identifier_n::accept (visitor & v) 
{
  v.visit_identifier (this);
}



//------------------------
// case_label
//------------------------

void
case_label_n::setCase (void) 
{
  case_lb = true;
}

void
case_label_n::setDefault (void) 
{
  case_lb = false;
}

bool case_label_n::isCase (void) 
{
  return case_lb;
}


bool case_label_n::isDefault (void) 
{
  return !case_lb;
}

void
case_label_n::accept (visitor & v) 
{
  v.visit_case_label (this);
}


//------------------------
// tree_list_n
//------------------------

void
tree_list_n::accept (visitor & v) 
{
  v.visit_tree_list (this);
}


//------------------------
// special
//------------------------

void
special_n::accept (visitor & v) 
{
  v.visit_special (this);
}

