/***************************************************************************
			   exprData.cpp  -  description
			      -------------------
     begin                : Aug 31 2001
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
#include "data/exprData.h"


// ---------------------------------------------------------------------------
//  Members of exprData_Cmp
// ---------------------------------------------------------------------------

bool exprData_Cmp::operator()(exprData& ed1, 
			      exprData& ed2) {
  return (ed1.getLine() < ed2.getLine());
}

bool exprData_Cmp::operator()(exprData* ed1, 
			      exprData* ed2) {
  return (ed1->getLine() < ed2->getLine());
}
