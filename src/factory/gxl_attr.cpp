/***************************************************************************
                          gxl_attr.cpp  -  description
                             -------------------
    begin                : Aug 2 2001
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
#include "factory/gxl_attr.h"


// ---------------------------------------------------------------------------
//  CONSTRUCTOR and MEMBERS
// ---------------------------------------------------------------------------

//*** Members

void
gxl_attr::setName (string name)
{
  this->name = name;
}

void
gxl_attr::setType (enum attributeType type)
{
  this->is_int = (type == intType);
}

void
gxl_attr::setValue (string value)
{
  this->value = value;
}

void 
gxl_attr::reset(void) {
  this->name = "";
  this->is_int = false;
  this->value = "";
}

string
gxl_attr::getName (void)
{
  return name;
}

bool
gxl_attr::isString (void)
{
  return !is_int;
}

bool
gxl_attr::isInt (void)
{
  return is_int;
}

string
gxl_attr::getStringValue (void)
{
  return value;
}

long
gxl_attr::getIntValue (void)
{
  return atol (value.c_str ());
}



