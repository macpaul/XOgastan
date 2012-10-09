/***************************************************************************
			   bad_xml.h  -  description
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

#ifndef _BAD_XML_H
#define _BAD_XML_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "error/bad_XOgastan.h"

// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

//! The classes for handle errors during xml management
class bad_XML:public bad_XOgastan
{
public:
  //! The constructor : whitout any message
  bad_XML():bad_XOgastan () { }

  //! The constructor : set only the fundamental string message 
  bad_XML (string base):bad_XOgastan (base)
  {
  }

  //! The constructor : set all the string message
  bad_XML (string base, string other):bad_XOgastan (base,other)
  {
  }
};


#endif
