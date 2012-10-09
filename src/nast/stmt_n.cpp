/***************************************************************************
                          stmt_n.cpp  -  description
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
#include "nast/stmt_n.h"
  
#include "visitor/visitor.h"
  
// ---------------------------------------------------------------------------
//  MEMBERS
// ---------------------------------------------------------------------------



//------------------------
// stmt_n
//------------------------

void
stmt_n::setLine (long l)
{
  lineF = l;
}

long
stmt_n::getLine (void)
{
  return lineF;
}


//------------------------
// compound_stmt_n
//------------------------

void
compound_stmt_n::accept (visitor & v) 
{
  v.visit_compound_stmt (this);
}


//------------------------
// break_stmt_n
//------------------------

void
break_stmt_n::accept (visitor & v) 
{
  v.visit_break_stmt (this);
}


//------------------------
// continue_stmt_n
//------------------------

void
continue_stmt_n::accept (visitor & v) 
{
  v.visit_continue_stmt (this);
}


//------------------------
// scope_stmt_n
//------------------------

void
scope_stmt_n::setVariables (void)
{
  with_variables = true;
}

void
scope_stmt_n::unsetVariables (void)
{
  with_variables = false;
}

bool 
scope_stmt_n::hasVariables (void)
{
  return with_variables;
}

void
scope_stmt_n::setBegin (void)
{
  begin_point = true;
}

void
scope_stmt_n::setEnd (void)
{
  begin_point = false;
}

bool scope_stmt_n::isBegin (void)
{
  return begin_point;
}


bool scope_stmt_n::isEnd (void)
{
  return !begin_point;
}

void
scope_stmt_n::accept (visitor & v) 
{
  v.visit_scope_stmt (this);
}


//------------------------
// decl_stmt_n
//------------------------

void
decl_stmt_n::accept (visitor & v) 
{
  v.visit_decl_stmt (this);
}


//------------------------
// expr_stmt_n
//------------------------

void
expr_stmt_n::accept (visitor & v) 
{
  v.visit_expr_stmt (this);
}



//------------------------
// goto_stmt_n
//------------------------

void
goto_stmt_n::accept (visitor & v) 
{
  v.visit_goto_stmt (this);
}


//------------------------
// label_stmt_n
//------------------------

void
label_stmt_n::accept (visitor & v) 
{
  v.visit_label_stmt (this);
}


//------------------------
// return_stmt_n
//------------------------

void
return_stmt_n::accept (visitor & v) 
{
  v.visit_return_stmt (this);
}



//------------------------
// if_stmt_n
//------------------------

void
if_stmt_n::accept (visitor & v) 
{
  v.visit_if_stmt (this);
}

//------------------------
// switch_stmt_n
//------------------------

void
switch_stmt_n::accept (visitor & v) 
{
  v.visit_switch_stmt (this);
}


//------------------------
// for_stmt_n
//------------------------

void
for_stmt_n::accept (visitor & v) 
{
  v.visit_for_stmt (this);
}


//------------------------
// do_stmt_n
//------------------------

void
do_stmt_n::accept (visitor & v) 
{
  v.visit_do_stmt (this);
}


//------------------------
// while_stmt_n
//------------------------

void
while_stmt_n::accept (visitor & v) 
{
  v.visit_while_stmt (this);
}


//------------------------
// asm_stmt_n
//------------------------

void
asm_stmt_n::accept (visitor & v) 
{
  v.visit_asm_stmt (this);
}


//------------------------
// othr_stmt_n
//------------------------

void
othr_stmt_n::accept (visitor & v) 
{
  v.visit_othr_stmt (this);
}




