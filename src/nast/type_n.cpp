/***************************************************************************
                          type_n.cpp  -  description
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
#include "nast/type_n.h"
  
#include "visitor/visitor.h"
  
// ---------------------------------------------------------------------------
//  MEMBERS
// ---------------------------------------------------------------------------



//------------------------
// type_n
//------------------------

void
type_n::setConstant (void) 
{
  qlf |= qual_constant;
}

void
type_n::setVolatile (void) 
{
  qlf |= qual_volatile;
}

void
type_n::setRestrict (void) 
{
  qlf |= qual_restrict;
}

bool 
type_n::isConstant (void) 
{
  return (qlf & qual_constant);
}


bool 
type_n::isVolatile (void) 
{
  return (qlf & qual_volatile);
}


bool 
type_n::isRestrict (void) 
{
  return (qlf & qual_restrict);
}


//------------------------
// void_type_n
//------------------------

void
void_type_n::accept (visitor & v) 
{
  v.visit_void_type (this);
}



//------------------------
// integer_type_n
//------------------------

void
integer_type_n::setSigned (void)
{
  sign = true;
}

void
integer_type_n::setUnsigned (void)
{
  sign = false;
}

bool 
integer_type_n::isSigned (void)
{
  return sign;
}

bool 
integer_type_n::isUnsigned (void)
{
  return !sign;
}

void
integer_type_n::accept (visitor & v) 
{
  v.visit_integer_type (this);
}




//------------------------
// enumeral_type_n
//------------------------

void
enumeral_type_n::setSigned (void)
{
  sign = true;
}

void
enumeral_type_n::setUnsigned (void)
{
  sign = false;
}

bool 
enumeral_type_n::isSigned (void)
{
  return sign;
}

bool 
enumeral_type_n::isUnsigned (void)
{
  return !sign;
}

void
enumeral_type_n::accept (visitor & v) 
{
  v.visit_enumeral_type (this);
}



//------------------------
// real_type_n
//------------------------

void
real_type_n::accept (visitor & v) 
{
  v.visit_real_type (this);
}



//------------------------
// array_type_n
//------------------------

void
array_type_n::accept (visitor & v) 
{
  v.visit_array_type (this);
}



//------------------------
// record_type_n
//------------------------

void 
record_type_n::accept (visitor & v) 
{
  v.visit_record_type (this);
}



//------------------------
// union_type_n
//------------------------

void
union_type_n::accept (visitor & v) 
{
  v.visit_union_type (this);
}



//------------------------
// pointer_type_n
//------------------------

void
pointer_type_n::accept (visitor & v) 
{
  v.visit_pointer_type (this);
}



//------------------------
// function_type_n
//------------------------

void
function_type_n::accept (visitor & v) 
{
  v.visit_function_type (this);
}



//------------------------
// othr_type_n
//------------------------

void
othr_type_n::accept (visitor & v) 
{
  v.visit_othr_type (this);
}
