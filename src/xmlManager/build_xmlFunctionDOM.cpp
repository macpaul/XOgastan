/***************************************************************************
			   build_xmlFunctionDOM.cpp  -  description
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
#include "xmlManager/build_xmlFunctionDOM.h"


// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

void 
build_xmlFunctionDOM::newDOM_Document(void) {
  
  doc = new DOMDocument;

  *doc = DOMDocument::createDocument();
  doc->appendChild(doc->createDocumentType("function"));
  root = doc->createElement("function");
  doc->appendChild(root);

  return;
}


void
build_xmlFunctionDOM::addRow(void) 
{
  DOM_Element     row;             // <row>...</row>
  DOM_Element     name;            // <name>..</name>
  DOM_Element     typeReturned;    // <type_returned>...</type_returned>
  DOM_Element     source;          // <source>...</source>

  rowNumber++;

  // create nodes
  row = doc->createElement("row");
  name = doc->createElement("name");
  typeReturned = doc->createElement("type_returned");
  source = doc->createElement("source");

  // fill information into the nodes
  row.setAttribute( "number", 
		    ("r" + a2b::long2string(rowNumber)).c_str() );
  name.appendChild( doc->createTextNode(fData->getName().c_str()) );
  typeReturned.appendChild( doc->createTextNode(fData->getType().c_str()) );
  source.appendChild( doc->createTextNode(fData->getSource().c_str()) );

  // append row in doc
  root.appendChild(row);

  // append elements in row
  row.appendChild(name);
  row.appendChild(typeReturned);  
  row.appendChild(source);

  return;
}


void 
build_xmlFunctionDOM::buildDOM(void) 
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
      // extract data of the function
      fData = dataB->getFnctData();
      // add data into the DOMDocument
      addRow();
    }
  }

  catch (const XMLException& e)
    {
      throw bad_XML("build_xmlFunctionDOM",
		    a2b::XMLChar2string(e.getMessage()) );
    }

  catch (const DOM_DOMException& e)
    {
      XMLDOM_str_exception DOMse;
      throw bad_XML("build_xmlFunctionDOM",
		    DOMse(e.code));
    }

  catch (...) 
    {
      throw bad_XML("build_xmlFunctionDOM",
		    "An unknown error occured during DOM manipulation\n ");
    }
  
  return;
}



