/***************************************************************************
			   write_htmlFnctFilter.cpp  -  description
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
#include "htmlWriter/write_htmlFnctFilter.h"

// ---------------------------------------------------------------------------
//  Members
// ---------------------------------------------------------------------------

void 
write_htmlFnctFilter::writePage(void) 
{
  fnctData                 *fData;    // information about the function
  dataDrawer               *dataB;    // elment of the list
  dataDrawerListIterator   p;         // browse the list
  bool                 
    almostOne = false;                // True if almost one fnctData
                                      // is filtered, false otherwise
  
  htmlpage.open (pageName.c_str());
  writeHead();
  writeIndex();

  htmlpage << "<b>functions with body click "
	   << "<a href=\"" << HTMLfilesRegister::fnctWithBodyIndex
	   << "\">here</a></b><br>\n\n";
  htmlpage << "<b>functions with parameters click "
	   << "<a href=\"" << HTMLfilesRegister::fnctWithParmIndex
	   << "\">here</a></b><br>\n\n";
  htmlpage << "<b>C standard functions click "
	   << "<a href=\"" << HTMLfilesRegister::fnctIsStdCIndex
	   << "\">here</a></b><br>\n\n";

  htmlpage << "<br><br>\n"
	   << "List of the functions.<br>\n"
	   << "We have a short description of each function : <br>\n"
	   << "<ol>\n"
	   << "\t<li>The name of the function\n"
	   << "\t<li>The type returned by the function\n"
	   << "\t<li>Has the function a body ?\n"
	   << "\t<li>The number of parameters\n"
	   << "\t<li>Does the function belong to the C standard library\n"
	   << "\t<li>The index of the nast_node function_decl\n"
	   << "</ol>\n"
	   << "<br>Follow the link of the function for more informations !"
	   << "<br><br>\n\n";


  p = dataBL->begin();
  while (p != dataBL->end()) {
    dataB = *p;
    p++;
    
    fData = dataB->getFnctData();

    if (dFilter->isGood(*fData)) {

      // is the first fnctData that pass the filter ?
      if (!almostOne) {

	htmlpage << "<table width=\"100%\" cellspacing=\"2\">\n\n";
	htmlpage << "\t<tr>\n";
	htmlpage << "\t<td width=\"30%\">"
		 << "<b>Function's name</b>"
		 << "</td>\n\n";
	htmlpage << "\t<td width=\"30%\">"
		 << "<b>Type returned</b>"
		 << "</td>\n\n";
	htmlpage << "\t<td width=\"10%\">"
		 << "<b>body ?</b>"
		 << "</td>\n\n";
	htmlpage << "\t<td width=\"10%\">"
		 << "<b>Parm ?</b>"
		 << "</td>\n\n";
	htmlpage << "\t<td width=\"10%\">"
		 << "<b>Cstd ?</b>"
		 << "</td>\n\n";
	htmlpage << "\t<td width=\"10%\">"
		 << "\t<b>index</b>"
		 << "\t</td>\n";
	htmlpage << "\t</tr>\n";

      }
      almostOne = true;
      
      htmlpage << "\t<tr>\n";

      htmlpage << "\t<tr>\n";
      
      // write the link to the html file of the function
      htmlpage << "\t<td bgcolor=\"#AFF7ED\" width=\"30%\">\n"
	       << "\t<a href=\"" 
	       << HTMLfilesRegister::htmlFile(*fData) 
	       << "\">"
	       << fData->getName()
	       << "</a>\n"
	       << "\t</td>\n";
      
      // write the type returned
      htmlpage << "\t<td bgcolor=\"#AFF7ED\" width=\"30%\">"
	       << fData->getType()
	       << "</td>\n";
      
      // write the body flag
      htmlpage << "\t<td bgcolor=\"#AFF7ED\" width=\"10%\">";
      if (fData->hasBody())
	htmlpage << "<font color=\"red\">yes</font>";
      else
	htmlpage << "no";
      htmlpage << "</td>\n";
      
      // write the number of parameters
      htmlpage << "\t<td bgcolor=\"#AFF7ED\" width=\"10%\">";
      if (fData->numParm())
	htmlpage << "<font color=\"red\">" << fData->numParm() << "</font>";
      else 
	htmlpage << fData->numParm();
      htmlpage << "</td>\n";
      
      // write the Cstandard flag 
      htmlpage << "\t<td bgcolor=\"#AFF7ED\" width=\"10%\">";
      if (fData->isStdC())
	htmlpage << "<font color=\"red\">yes</font>";
      else
	htmlpage << "no";
      htmlpage << "</td>\n";
      
      // write the index of the function_decl
      htmlpage << "\t<td bgcolor=\"#AFF7ED\" width=\"10%\">"
	       << (fData->getNodeP())->getId()
	       << "</td>\n";
      
      htmlpage << "\t</tr>\n\n";
      
    }
    
  }
  
  // Almost one fnctData has passed the test ?
  if (!almostOne)
    htmlpage << "<br><font color=\"red\">No function in this list</font><br>\n";
  else 
    htmlpage << "</table>\n\n";

  writeIndex();
  writeFoot();
  htmlpage.close();

  return;
};







