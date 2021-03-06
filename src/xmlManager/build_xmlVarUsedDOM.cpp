/***************************************************************************
			   build_xmlVarUsedDOM.cpp  -  description
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
#include "xmlManager/build_xmlVarUsedDOM.h"


// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

void 
build_xmlVarUsedDOM::newDOM_Document(void) {
  DOM_DOMImplementation impl;

  doc = new DOMDocument;

  *doc = DOMDocument::createDocument();
  doc->appendChild(doc->createDocumentType("var_used"));
  root = doc->createElement("var_used");
  doc->appendChild(root);

  return;
}


void
build_xmlVarUsedDOM::addRow(void) 
{
  DOM_Element     row;             // <row>...</row>
  DOM_Element     fnctName;        // <fnct_name>..</fnct_name>
  DOM_Element     where;           // <where>..</where>
  DOM_Element     line;            // <line>..</line>
  DOM_Element     name;            // <name>..</name>
  DOM_Element     type;            // <type>..</type>
  DOM_Element     const_qual;      // <const_qual>..</const_qual>
  DOM_Element     volatile_qual;   // <volatile_qual>..</volatile_qual>
  DOM_Element     stars;           // <stars>..</stars>
  DOM_Element     squares;         // <squares>..</squares>

  rowNumber++;

  // create nodes
  row = doc->createElement("row"); 
  fnctName = doc->createElement("fnct_name");
  where = doc->createElement("where");
  line = doc->createElement("line");
  name = doc->createElement("name");
  type = doc->createElement("type");
  const_qual = doc->createElement("const_qual");
  volatile_qual = doc->createElement("volatile_qual");
  stars = doc->createElement("stars");
  squares = doc->createElement("squares");

  // fill information into the nodes
  row.setAttribute( "number", 
		    ("r" + a2b::long2string(rowNumber)).c_str() );
  //-- function name
  fnctName.appendChild( doc->createTextNode(fData->getName().c_str()) ); 
  //-- where
  string whereIs;
  
  if (vuData->isLocal())
    whereIs = "local";
  else
    whereIs = "global";
  
  if ( (vuData->getNodeP())->getCode() == PARM_DECL )
    whereIs += "_parm";
  else if ( (vuData->getNodeP())->getCode() == VAR_DECL )
    whereIs += "_var";
  else 
    whereIs += "_other";
  where.appendChild(doc->createTextNode(whereIs.c_str())); 
  //-- line
  line.appendChild( doc->createTextNode
		    (a2b::long2string(vuData->getLine()).c_str()) );
  //-- name
  name.appendChild( doc->createTextNode(vuData->getName().c_str()) );
  //-- type
  type.appendChild( doc->createTextNode(vuData->getType().c_str()) );
  //-- const_qual
  if ( ((vuData->getTypeExtra()).find("const")) != string::npos)
    const_qual.appendChild(doc->createTextNode("true"));
  else 
    const_qual.appendChild(doc->createTextNode("false"));
  //-- volatile_qual
  if ( (vuData->getTypeExtra().find("volatile")) != string::npos)
    volatile_qual.appendChild(doc->createTextNode("true"));
  else 
    volatile_qual.appendChild(doc->createTextNode("false"));
  //-- stars
  stars.appendChild( doc->createTextNode
		     (a2b::long2string(vuData->getStarNumber()).c_str()) );
  //-- squares
  squares.appendChild( doc->createTextNode
		       (a2b::long2string(vuData->getSquareNumber()).c_str()) );

  // append row in doc
  root.appendChild(row);

  // append elements in row
  row.appendChild(fnctName);
  row.appendChild(where);  
  row.appendChild(line);
  row.appendChild(name);
  row.appendChild(type);
  row.appendChild(const_qual);  
  row.appendChild(volatile_qual);
  row.appendChild(stars);
  row.appendChild(squares);  

  return;
}


void 
build_xmlVarUsedDOM::buildDOM(void) 
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
      
      // extract data of the function and the varUsed list
      fData = dataB->getFnctData();
      vuL = dataB->getVarUsedList();

      // write varUsed
      if (vuL != 0) {
	varUsedListIterator p2 = vuL->begin();
	while (p2 != vuL->end()) {
	  vuData = *p2;
	  p2 ++;
	  // add data into the DOMDocument
	  addRow();
	}
      }

    }
  }

  catch (const XMLException& e)
    {
      throw bad_XML("build_xmlVarUsedDOM",
		    a2b::XMLChar2string(e.getMessage()) );
    }

  catch (const DOM_DOMException& e)
    {
      XMLDOM_str_exception DOMse;
      throw bad_XML("build_xmlVarUsedDOM",
		    DOMse(e.code));
    }

  catch (...) 
    {
      throw bad_XML("build_xmlVarUsedDOM",
		    "An unknown error occured during DOM manipulation\n ");
    }
  
  return;
}
