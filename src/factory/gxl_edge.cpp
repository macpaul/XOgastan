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
#include "factory/gxl_edge.h"


// ---------------------------------------------------------------------------
//  CONSTRUCTOR and MEMBERS
// ---------------------------------------------------------------------------

//---- Constructor

gxl_edge::gxl_edge (string type, long from, long to)
{
  this->type = type;
  this->from = from;
  this->to = to;
}

//---- Members

void
gxl_edge::setType (string type)
{
  this->type = type;
}

void
gxl_edge::setFrom (long from)
{
  this->from = from;
}

void
gxl_edge::setTo (long to)
{
  this->to = to;
}

string
gxl_edge::getType (void)
{
  return this->type;
}

long
gxl_edge::getFrom (void)
{
  return this->from;
}

long
gxl_edge::getTo (void)
{
  return this->to;
}
