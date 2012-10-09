/***************************************************************************
			   print_warning.h  -  description
			      -------------------
     begin                : Aug 6 2001
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
// Include
// ---------------------------------------------------------------------------
#include "utils/print_warning.h"

// ---------------------------------------------------------------------------
// Function
// ---------------------------------------------------------------------------

//! Print a warning message on stdout
void printWarning(string base_message, string other_message) {
  if (astWarning) {
    cout << "\nXOgastan WARNING:\n" 
	 << base_message << "\n"
	 << other_message << "\n\n";
    cout.flush();
  }
  return;
}









