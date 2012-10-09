/***************************************************************************
			   build_xmlReachStatDOM.cpp  -  description
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
#include "xmlManager/build_xmlReachStatDOM.h"


// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

void 
build_xmlReachStatDOM::newDOM_Document(void) {
  
  doc = new DOM_Document;

  *doc = DOM_Document::createDocument();
  doc->appendChild(doc->createDocumentType("reach_statistic"));
  root = doc->createElement("reach_statistic");
  doc->appendChild(root);

  return;
}


void 
build_xmlReachStatDOM::buildDOM(void) 
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
      if ((nnData = dataB->getNastNumData())) {
	string fnctName = fData->getName();
	
	addRow(fnctName, "type_nodes",
	       nnData->totalTypeNastNode() );
	addRow(fnctName, "decl_nodes",
	       nnData->totalDeclNastNode() );
	addRow(fnctName, "stmt_nodes",
	       nnData->totalStmtNastNode() );
	addRow(fnctName, "cst_nodes",
	       nnData->totalCstNastNode() );
	addRow(fnctName, "othr_nodes",
	       nnData->totalOthrNastNode() );
	addRow(fnctName, "total_nodes",
	       nnData->totalNastNode() );
	
      }

    }
  
  }

  catch (const XMLException& e)
    {
      throw bad_XML("build_xmlReachStatDOM",
		    a2b::XMLChar2string(e.getMessage()) );
    }

  catch (const DOM_DOMException& e)
    {
      XMLDOM_str_exception DOMse;
      throw bad_XML("build_xmlReachStatDOM",
		    DOMse(e.code));
    }

  catch (...) 
    {
      throw bad_XML("build_xmlReachStatDOM",
		    "An unknown error occured during DOM manipulation\n ");
    }
  
  return;
}




