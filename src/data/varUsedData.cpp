/***************************************************************************
			   varUsedData.cpp  -  description
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
#include "data/varUsedData.h"


// ---------------------------------------------------------------------------
//  Members of varUsedData_Cmp
// ---------------------------------------------------------------------------

bool varUsedData_Cmp::operator()(varUsedData& vud1, 
				 varUsedData& vud2) {
  return (vud1.getName() < vud2.getName());
}

bool varUsedData_Cmp::operator()(varUsedData* vud1, 
				 varUsedData* vud2) {
  return (vud1->getName() < vud2->getName());
}
