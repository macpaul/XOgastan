/***************************************************************************
			   typeDef.h  -  description
			      -------------------
     begin                : Aug 28 2001
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

/*! \file
  
  This file contains some C typedef to define
  the different alias name of structure used.
  We define :
  - list of fnctData
  - list of declData
  - list of parmData
  - list of varUsedData
  - list of dataDrawer
  Moreover, we define :
  - iterator to the list of fnctData
  - iterator to the list of declData
  - iterator to the list of parmData
  - iterator to the list of varUsedData
  - iterator to the list of dataDrawer
*/

#ifndef _TYPE_DEF_H
#define _TYPE_DEF_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "nast/nast_node.h"

#include <list>
#include <string>

// ---------------------------------------------------------------------------
//  Typedef
// ---------------------------------------------------------------------------
class fnctData;
class declData;
class exprData;
class varUsedData;
class parmData;
class dataDrawer;

//! The list of functions 
typedef list<fnctData *> fnctsList;

//! The iterator of the list of functions
typedef list<fnctData *>::iterator fnctsListIterator;

//! The list of declarations
typedef list<declData *> declsList;

//! The iterator of the list of declarations
typedef list<declData *>::iterator declsListIterator;

//! The list of parameters
typedef list<parmData *> parmList;

//! The iterator of the list of parameters
typedef list<parmData *>::iterator parmListIterator;

//! The list of variables used
typedef list<varUsedData *> varUsedList;

//! The iterator of the list of variables used
typedef list<varUsedData *>::iterator varUsedListIterator;

//! The list of expressions
typedef list<exprData *> exprsList;

//! The iterator of the list of expressions
typedef list<exprData *>::iterator exprsListIterator;

//! The list of dataDrawer
typedef list<dataDrawer *> dataDrawerList;

//! The iterator of the list of dataDrawer
typedef list<dataDrawer *>::iterator dataDrawerListIterator;

#endif



