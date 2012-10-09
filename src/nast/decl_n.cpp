/***************************************************************************
                          decl_n.cpp  -  description
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
#include "nast/decl_n.h"
  
#include "visitor/visitor.h"
  

// ---------------------------------------------------------------------------
//  MEMBERS
// ---------------------------------------------------------------------------



//------------------------
// decl_n
//------------------------

bool decl_n::isArtificial (void) 
{
  return artificial;
}
	
void
decl_n::setArtificial (void) 
{
  artificial = true;
}

void
decl_n::unsetArtificial (void)
{
  artificial = false;
}

long
decl_n::getLine (void) 
{
  return lineF;
}

void 
decl_n::setLine (long l) 
{  
  lineF = l;  
}

string 
decl_n::getSource (void)  
{
  return sourceF;
}

void
decl_n::setSource (string s) 
{
  sourceF = s;
}



//------------------------
// var_decl_n
//------------------------

void
var_decl_n::accept (visitor & v) 
{
  v.visit_var_decl (this);
}

void 
var_decl_n::setRegister(void) {
  reg = true;
}

void 
var_decl_n::unsetRegister(void) {
  reg = false;
}

bool 
var_decl_n::isRegister(void) {
  return reg;
}



//------------------------
// parm_decl_n
//------------------------

void
parm_decl_n::accept (visitor & v) 
{
  v.visit_parm_decl (this);
}

void 
parm_decl_n::setRegister(void) {
  reg = true;
}

void 
parm_decl_n::unsetRegister(void) {
  reg = false;
}

bool 
parm_decl_n::isRegister(void) {
  return reg;
}



//------------------------
// const_decl_n
//------------------------

void
const_decl_n::accept (visitor & v) 
{
  v.visit_const_decl (this);
}



//------------------------
// result_decl_n
//------------------------

void
result_decl_n::accept (visitor & v) 
{
  v.visit_result_decl (this);
}



//------------------------
// field_decl_n
//------------------------

void
field_decl_n::accept (visitor & v) 
{
  v.visit_field_decl (this);
}


void 
field_decl_n::setBitfield(void) {
  bitfield = true;
}

void 
field_decl_n::unsetBitfield(void) {
  bitfield = false;
}

bool 
field_decl_n::isBitfield(void) {
  return bitfield;
}



//------------------------
// type_decl_n
//------------------------

void
type_decl_n::accept (visitor & v) 
{
  v.visit_type_decl (this);
}



//------------------------
// label_decl_n
//------------------------

void
label_decl_n::accept (visitor & v) 
{
  v.visit_label_decl (this);
}



//------------------------
// function_decl
//------------------------

bool function_decl_n::isExtern (void)
{
  return (mclass == mc_extern);
}

bool function_decl_n::isStatic (void)
{
  return (mclass == mc_static);
}

void
function_decl_n::setExtern (void)
{
  mclass = mc_extern;
}

void
function_decl_n::setStatic (void)
{
  mclass = mc_static;
}

void 
function_decl_n::setUndefined(void) {
  undefined = true;
}


void 
function_decl_n::unsetUndefined(void) {
  undefined = false;
}

bool 
function_decl_n::isUndefined(void) {
  return undefined;
}

void
function_decl_n::accept (visitor & v) 
{
  v.visit_function_decl (this);
}



//------------------------
// othr_decl_n
//------------------------

void
othr_decl_n::accept (visitor & v) 
{
  v.visit_othr_decl (this);
}



