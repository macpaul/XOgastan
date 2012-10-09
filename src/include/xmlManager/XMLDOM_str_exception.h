/***************************************************************************
			   XMLDOM_Str_Exception.h  -  description
			      -------------------
     begin                : Sept 6 2001
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

#ifndef _XML_DOM_STR_EXCEPTION_H
#define _XML_DOM_STR_EXCEPTION_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "dom/DOM_DOMException.hpp"

// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

//! This class translate a DOM_exception code into a string error
class XMLDOM_str_exception
{

 public:
  //! Constructor
  XMLDOM_str_exception() { }

  //! Destructor
  ~XMLDOM_str_exception() { }

  //---- Members

  //! Overload the () operator
  /*!
    \param code the dom exception code
    
    \return The char * string currespondent to the error of code.
  */
  char *operator()(const enum DOM_DOMException::ExceptionCode &code);

};


#endif
