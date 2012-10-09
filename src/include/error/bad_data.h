/***************************************************************************
			   bad_data.h  -  description
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

#ifndef _BAD_DATA_H
#define _BAD_DATA_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "error/bad_XOgastan.h"

// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

//! The classes for handle errors during data collection (visitor)
/*!   
  During the visiting operation an error can occur
  when we manage some data structure.

  This class hanlde these errors
*/
class bad_data:public bad_XOgastan
{
public:
  //! The constructor : whitout any message
  /*! The constructor : whitout any message
   */
  bad_data():bad_XOgastan () { }

  //! The constructor : set only the fundamental string message 
  /*! The constructor : set only the fundamental string message 
   */
  bad_data (string base):bad_XOgastan (base)
  {
  }

  //! The constructor : set all the string message
  /*! The constructor : set all the string message */
  bad_data (string base, string other):bad_XOgastan (base,other)
  {
  }
};


#endif
