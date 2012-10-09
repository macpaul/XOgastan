/***************************************************************************
			   write_htmlHomePage.h  -  description
			      -------------------
     begin                : Aug 31 2001
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

#ifndef _WRITE_HTML_HOME_PAGE_H
#define _WRITE_HTML_HOME_PAGE_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "htmlWriter/HTMLwriter.h"
#include "htmlWriter/HTMLfilesRegister.h"
#include "htmlWriter/HTMLofstream.h"

// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

//! This class write the home page
/*!
  The home page contains the links
  to the index pages.
*/
class write_htmlHomePage : public HTMLwriter
{
 public:
  //! Constructor
  write_htmlHomePage() { }

  //! Destructor
  ~write_htmlHomePage() { }

  //! Write the page
  void writePage(void);
  
};


#endif
