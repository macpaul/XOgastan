/***************************************************************************
			   write_htmlHomePage.cpp  -  description
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

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "htmlWriter/write_htmlHomePage.h"

// ---------------------------------------------------------------------------
//  Members
// ---------------------------------------------------------------------------
extern char *xmlFile;

void 
write_htmlHomePage::writePage(void) 
{
  htmlpage.open (HTMLfilesRegister::homePage);
  pageTitle = "Home Page";
  writeHead();
  writeIndex();

  htmlpage << "In these pages we show the results of the analisys of "
	   << "the NAST (New Abstract Syntax Tree) built by the "
	   << "application XOgastan from the xml file " << xmlFile 
	   << ".<br><br>\n";

  htmlpage << "<ol>";
 
  htmlpage << "\t<li>"
	   << "<a href=\""
	   << HTMLfilesRegister::fnctIndex
	   << "\">Index of the functions</a><br><br>\n\n";
  htmlpage << "\t<ol>";
  htmlpage << "\t\t<li>"
	   << "<a href=\""
	   << HTMLfilesRegister::fnctWithBodyIndex
	   << "\">Functions with body</a><br><br>\n\n";
  htmlpage << "\t\t<li>"
	   << "<a href=\""
	   << HTMLfilesRegister::fnctWithParmIndex
	   << "\">Functions with parameters</a><br><br>\n\n";
  htmlpage << "\t\t<li>"
	   << "<a href=\""
	   << HTMLfilesRegister::fnctIsStdCIndex
	   << "\">List of functions of the C standard library</a><br><br>\n\n";
  htmlpage << "\t</ol>\n\n";

  htmlpage << "\t<li>"
	   << "<a href=\""
	   << HTMLfilesRegister::nastStatistics
	   << "\">Statistics information of the NAST</a><br><br>\n\n";

  htmlpage << "</ol>\n\n";

  writeIndex();
  writeFoot();
  htmlpage.close();

  return;
}






