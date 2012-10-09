/***************************************************************************
			   build_xmlStmtStatDOM.cpp  -  description
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

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "xmlManager/build_xmlStmtStatDOM.h"


// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

void 
build_xmlStmtStatDOM::newDOM_Document(void) {
  
  doc = new DOMDocument;

  *doc = DOMDocument::createDocument();
  doc->appendChild(doc->createDocumentType("stmt_statistic"));
  root = doc->createElement("stmt_statistic");
  doc->appendChild(root);

  return;
}


void 
build_xmlStmtStatDOM::buildDOM(void) 
  throw (bad_XML) 
{
  dataDrawerListIterator   p;         // browse the list
  dataDrawer               *dataB;    // current dataDrawer

  try {
    newDOM_Document();
    
    rowNumber = 0;
    p = dataBL->begin();
    while (p != dataBL->end()) {
      dataB = *p;
      p++;
      
      // extract data of the function and the declaration list
      fData = dataB->getFnctData();
      if ((snData = dataB->getStmtNumData())) {
	int i;
	string fnctName = fData->getName();
	
	for (i=BREAK_STMT; i <= ASM_STMT; i++)
	  addRow(fnctName, 
		 a2b::nast_code2string((nast_code)i),
		 snData->numStmt((nast_code)i) );
	
      }

    }
  
  }

  catch (const XMLException& e)
    {
      throw bad_XML("build_xmlStmtStatDOM",
		    a2b::XMLChar2string(e.getMessage()) );
    }

  catch (const DOM_DOMException& e)
    {
      XMLDOM_str_exception DOMse;
      throw bad_XML("build_xmlStmtStatDOM",
		    DOMse(e.code));
    }

  catch (...) 
    {
      throw bad_XML("build_xmlStmtStatDOM",
		    "An unknown error occured during DOM manipulation\n ");
    }
  
  return;
}




