/***************************************************************************
			   bad_a2b.h  -  description
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

#ifndef _BAD_A2B_H
#define _BAD_A2B_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "error/bad_XOgastan.h"

// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

//! The classes for handle errors during a2b conversion
/*! The classes for handle errors during a2b conversion
  
  We can raise this exception only when :

  an error occured during string2nast_code conversion  
  OR
  an error occured during string2edge_code conversion  
  OR
  an error occured during nast_code2string conversion  
  OR
  an error occured during edge_code2string conversion  

*/
class bad_a2b:public bad_XOgastan
{
public:
  //! The constructor : whitout any message
  /*! The constructor : whitout any message
   */
  bad_a2b():bad_XOgastan () { }

  //! The constructor : set only the fundamental string message 
  /*! The constructor : set only the fundamental string message 
   */
  bad_a2b (string base):bad_XOgastan (base)
  {
  }

  //! The constructor : set all the string message
  /*! The constructor : set all the string message */
  bad_a2b (string base, string other):bad_XOgastan (base,other)
  {
  }
};


#endif
