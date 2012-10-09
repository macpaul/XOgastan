/***************************************************************************
			   bad_get.h  -  description
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

#ifndef _BAD_GET_H
#define _BAD_GET_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "error/bad_XOgastan.h"


// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

//! The classes for handle errors during get operations
/*!  
  This exception is raised by the get_functions defined in
  get_functions.h
 */
class bad_get: public bad_XOgastan
{
public:
  //! The constructor : whitout any message
  /*! The constructor : whitout any message
   */
  bad_get ():bad_XOgastan() { }

  //! The constructor : set only the fundamental string message 
  /*! The constructor : set only the fundamental string message 
   */
  bad_get (string base):bad_XOgastan(base)
  {
  }

  //! The constructor : set all the string message
  /*! The constructor : set all the string message */
  bad_get (string base, string other):bad_XOgastan(base,other)
  {
  }
};

#endif
