/***************************************************************************
			   HTMLwriter.h  -  description
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

#ifndef _HTML_WRITER_H
#define _HTML_WRITER_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "htmlWriter/HTMLfilesRegister.h"
#include "htmlWriter/HTMLofstream.h"

#include "utils/flags.h"

#include <string>
// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

//! The base for the html pages generation
/*!
  The deriveds class of this class are used to 
  write the html pages with the datas of the C
  program and of the NAST.
  
  This class write the head and the foot of an html page.
  In this way the look and feel is the always the same.
*/

class HTMLwriter
{
 protected:
  
  //---- Attributes
  
  //! Title of the page
  string       pageTitle;

  //! Html file
  HTMLofstream htmlpage;

  //! Name of the html file
  string       pageName;
  
 public:
  //! Constructor
  HTMLwriter() { }

  //! Destructor
  ~HTMLwriter() { }

  //---- Members
  
  //! Set the title of the html page
  void setPageTitle(string pageTitle) 
    { this->pageTitle = pageTitle; }

  //! Set the name of the html page
  void setPageName(string pageName) 
    { this->pageName = pageName; }

  //! Write the head of the html page
  void writeHead(void);

  //! Write the horizontal index
  void writeIndex(void);

  //! Write section title bar
  void writeSectionTitle(string sectionTitle);

  //! Write the page
  virtual void writePage(void) { }

  //! Write the index of this page
  virtual void writePageIndex(void) { }
  
  //! Write the foot of the html page
  void writeFoot(void);
};


#endif



