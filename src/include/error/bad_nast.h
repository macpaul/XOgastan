/***************************************************************************
			   bad_nast.h  -  description
			      -------------------
     begin                : July 22 2001
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

#ifndef _BAD_NAST_H
#define _BAD_NAST_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "error/bad_XOgastan.h"


// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

//! The classes for handlig errors during nast manipulation
/*! The classes for handlig errors during nast manipulation
  
  When we throug, read, build a NewAbastractSyntaxTree it could
  happens some unattend events ... These errors events are
  signaled using this class, and its childs classes.
 */
class bad_nast:public bad_XOgastan
{
public:
  //! The constructor : whitout any message
  /*! The constructor : whitout any message
   */
  bad_nast (): bad_XOgastan() { }

  //! The constructor : set only the fundamental string message 
  /*! The constructor : set only the fundamental string message 
   */
  bad_nast (string base): bad_XOgastan(base)
  {
  }

  //! The constructor : set all the string message
  /*! The constructor : set all the string message */
  bad_nast (string base, string other): bad_XOgastan(base,other)
  {
  }

};


//! The classes for handlig errors during edge manipulation of a nast_node
/*! The classes for handlig errors during edge manipulation of a nast_node
  
  When we search, add, delete, browse the edges of a nast_node it could
  happens some unattend events ... These errors events are
  signaled using this class, and its childs classes.
 */
class bad_edge:public bad_nast
{
public:
  //! The constructor : whitout any message
  /*! The constructor : whitout any message
   */
  bad_edge (): bad_nast () { }

  //! The constructor : set only the fundamental string message 
  /*! The constructor : set only the fundamental string message 
   */
  bad_edge (string base): bad_nast (base)
  {
  }

  //! The constructor : set all the string message
  /*! The constructor : set all the string message */
  bad_edge (string base, string other):bad_nast (base, other)
  {
  }

};


#endif
