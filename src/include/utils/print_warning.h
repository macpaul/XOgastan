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


#ifndef _PRINT_WARNING_H
#define _PRINT_WARNING_H

// ---------------------------------------------------------------------------
// Includes
// ---------------------------------------------------------------------------
#include "utils/flags.h"

#include <string>
#include <iostream>

using namespace std;

// ---------------------------------------------------------------------------
// Function
// ---------------------------------------------------------------------------

//! Print a warning message on stdout
extern void printWarning(string base, string other);

#endif








