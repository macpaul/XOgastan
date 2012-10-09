/***************************************************************************
			   declData.cpp  -  description
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
#include "data/declData.h"


// ---------------------------------------------------------------------------
//  Members of declData_Cmp
// ---------------------------------------------------------------------------

bool declData_Cmp::operator()(declData& dd1, 
			      declData& dd2) {
  return (dd1.getName() < dd2.getName());
}

bool declData_Cmp::operator()(declData* dd1, 
			      declData* dd2) {
  return (dd1->getName() < dd2->getName());
}
