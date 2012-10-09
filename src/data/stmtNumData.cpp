/***************************************************************************
			   stmtNumData.cpp  -  description
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
#include "data/stmtNumData.h"

// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------
void 
stmtNumData::addStmt(nast_code code)
  throw (bad_data)
{ 
  if ( (isStmt(code)) || (isOthrStmt(code)) || (code == CASE_LABEL) )
    counted[code]++; 
  else 
    throw bad_data("stmtNumData",
		   "Impossibile add a new stmt_n");
  return;
}


long 
stmtNumData::numStmt(nast_code code)
  throw (bad_data)
{ 
  if ( (isStmt(code)) || (isOthrStmt(code)) || (code == CASE_LABEL) )
    return counted[code]; 
  else 
    throw bad_data("stmtNumData",
		   "Impossibile get the number of a stmt_n");
}


long 
stmtNumData::totalStmt(void) 
{ 
  long total;
  long i;
  
  for (i=BREAK_STMT, total=0; i <= ASM_STMT; i++)
	total += counted[(nast_code) i];
  
  return total;
}










