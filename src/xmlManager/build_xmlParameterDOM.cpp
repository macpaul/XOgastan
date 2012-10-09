/***************************************************************************
			   build_xmlParameterDOM.cpp  -  description
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
#include "xmlManager/build_xmlParameterDOM.h"


// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

void 
build_xmlParameterDOM::newDOM_Document(void) {
  
  doc = new DOM_Document;

  *doc = DOM_Document::createDocument();
  doc->appendChild(doc->createDocumentType("parameter"));
  root = doc->createElement("parameter");
  doc->appendChild(root);

  return;
}


void
build_xmlParameterDOM::addRow(void) 
{
  DOM_Element     row;             // <row>...</row>
  DOM_Element     fnctName;        // <fnct_name>..</fnct_name>
  DOM_Element     name;            // <name>..</name>
  DOM_Element     type;            // <type>..</type>
  DOM_Element     const_qual;      // <const_qual>..</const_qual>
  DOM_Element     volatile_qual;   // <volatile_qual>..</volatile_qual>

  rowNumber++;

  // create nodes
  row = doc->createElement("row"); 
  fnctName = doc->createElement("fnct_name");
  name = doc->createElement("name");
  type = doc->createElement("type");
  const_qual = doc->createElement("const_qual");
  volatile_qual = doc->createElement("volatile_qual");

  // fill information into the nodes
  row.setAttribute( "number", 
		    ("r" + a2b::long2string(rowNumber)).c_str() );
  //-- function name
  fnctName.appendChild( doc->createTextNode(fData->getName().c_str()) ); 
  //-- name
  name.appendChild( doc->createTextNode(pData->getName().c_str()) );
  //-- type
  type.appendChild( doc->createTextNode(pData->getType().c_str()) );
  //-- const_qual
  if ( ((pData->getTypeExtra()).find("const")) != string::npos)
    const_qual.appendChild(doc->createTextNode("true"));
  else 
    const_qual.appendChild(doc->createTextNode("false"));
  //-- volatile_qual
  if ( (pData->getTypeExtra().find("volatile")) != string::npos)
    volatile_qual.appendChild(doc->createTextNode("true"));
  else 
    volatile_qual.appendChild(doc->createTextNode("false"));

  // append row in doc
  root.appendChild(row);

  // append elements in row
  row.appendChild(fnctName);
  row.appendChild(name);
  row.appendChild(type);
  row.appendChild(const_qual);  
  row.appendChild(volatile_qual);

  return;
}


void 
build_xmlParameterDOM::buildDOM(void) 
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

      if (fData->hasParm()) {
	pData = fData->firstParm();
	// add data into the DOM_Document
	addRow();
	
	while (fData->hasNextParm()) {
	  pData = fData->nextParm();
	  // add data into the DOM_Document
	  addRow();
	}
      }
      
    }
  
  }

  catch (const XMLException& e)
    {
      throw bad_XML("build_xmlParameterDOM",
		    a2b::XMLChar2string(e.getMessage()) );
    }

  catch (const DOM_DOMException& e)
    {
      XMLDOM_str_exception DOMse;
      throw bad_XML("build_xmlParameterDOM",
		    DOMse(e.code));
    }

  catch (...) 
    {
      throw bad_XML("build_xmlParameterDOM",
		    "An unknown error occured during DOM manipulation\n ");
    }
  
  return;
}



