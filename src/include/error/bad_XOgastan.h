/***************************************************************************
			   bad_XOgastan.h  -  description
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

#ifndef _BAD_XOGASTAN_H
#define _BAD_XOGASTAN_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <string>
#include <iostream>


// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

//! The base class error for the exception
/*! The base class error for the exception
 */
class bad_XOgastan
{

 protected:
  //! The string message for error
  /*! The string message for error
    
    In this string we can store the base information about
    the error.
    This string is printed on the stderr
  */
  string base_message;

  //! Additional string message for error
  /*! Additional string message for error

     In this string we can store other information about
     the error.
     This string is printed on the stderr
   */
  string other_message;

 public:
  //! The constructor : whitout any message
  /*! The constructor : whitout any message
   */
  bad_XOgastan ():base_message ("") { }

  //! The constructor : set only the fundamental string message 
  /*! The constructor : set only the fundamental string message 
   */
  bad_XOgastan (string base):base_message (base)
    {
    }
  
  //! The constructor : set all the string message
  /*! The constructor : set all the string message */
  bad_XOgastan (string base, string other):base_message (base),
    other_message (other)
    {
    }

  //! Set the base message
  /*! Set the base message */
  void setBaseMessage (string base)
    {
      base_message = base;
    }

  //! Set the other message
  /*! Set the other message */
  void setOtherMessage (string other)
    {
      other_message = other;
    }

  //! Get the base message
  /*! Get the base message */
  string getBaseMessage (void)
    {
      return base_message;
    }
  
  //! Get the other message
  /*! Get the other message */
  string getOtherMessage (void)
    {
      return other_message;
    }
  
  //! Print the error messages on cerr
  /*! Print the error messages on cerr */
  virtual void printMessages (void);
  
};

#endif
