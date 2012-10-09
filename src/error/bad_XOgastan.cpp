/***************************************************************************
			   bad_XOgastan.cpp  -  description
			      -------------------
     begin                : July 20 2001
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
#include "error/bad_XOgastan.h"

// ---------------------------------------------------------------------------
//  Member
// ---------------------------------------------------------------------------
void bad_XOgastan::printMessages(void) {

  cerr << "XOgastan ERROR:\n" 
       << base_message << "\n"
       << other_message << "\n\n" << endl;
  cerr.flush();
}
  




