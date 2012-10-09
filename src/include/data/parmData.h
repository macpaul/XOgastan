/***************************************************************************
			   parmData.h  -  description
			      -------------------
     begin                : Aug 29 2001
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

#ifndef _PARM_DATA_H
#define _PARM_DATA_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "data/declData.h"

#include <string>

// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

//! This class holds informations about the parameter of function
/*!
  It is a derived class of the class declData !
  It don't introduce any other attribute or method, but it is
  used only to dinstinguish it from an object declData.
*/
class parmData: public declData {

 public:
  //! Constructor
  parmData() { }
  
  //! Destructor
  ~parmData() { }

};

#endif

