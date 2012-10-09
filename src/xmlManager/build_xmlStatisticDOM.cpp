/***************************************************************************
			   build_xmlStatisticDOM.cpp  -  description
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
#include "xmlManager/build_xmlStatisticDOM.h"


// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

void
build_xmlStatisticDOM::addRow(string pos, string c, long v) 
{
  DOM_Element     row;             // <row>...</row>
  DOM_Element     fnct_name;       // <fnct_name>..</fnct_name>
  DOM_Element     code;            // <code>..</code>
  DOM_Element     value;           // <value>..</value>
  
  rowNumber++;
  
  // create nodes
  row = doc->createElement("row"); 
  fnct_name = doc->createElement("fnct_name"); 
  code = doc->createElement("code");
  value = doc->createElement("value");
  
  // fill information into the nodes
  row.setAttribute( "number", 
		    ("r" + a2b::long2string(rowNumber)).c_str() );
  //-- function name
  fnct_name.appendChild( doc->createTextNode(pos.c_str()) ); 
  //-- code 
  code.appendChild( doc->createTextNode(c.c_str()) );
  //-- value
  value.appendChild( doc->createTextNode(a2b::long2string(v).c_str()) );
  
  // append row in doc
  root.appendChild(row);
  
  // append elements in row
  row.appendChild(fnct_name);
  row.appendChild(code);
  row.appendChild(value);
  
}
  

