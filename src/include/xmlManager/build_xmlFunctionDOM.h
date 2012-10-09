/***************************************************************************
			   build_xmlFunctionDOM.h  -  description
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

#ifndef _BUILD_XML_FUNCTION_DOM_H
#define _BUILD_XML_FUNCTION_DOM_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "xmlManager/XMLBuilder.h"
#include "xmlManager/XMLDOM_str_exception.h"

#include "data/typeDef.h"
#include "data/fnctData.h"
#include "data/dataDrawer.h"

#include "utils/a2b.h"

#include "error/bad_XML.h"

#include "dom/DOM.hpp"
// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

//! This class build a function DOM
/*!
  This class build a xml file with the list
  of the functions.
  See function.dtd for more info.
*/

class build_xmlFunctionDOM : public XMLBuilder
{
 private:
  
  //---- Attributes
  
  //! The dataDrawer with the information data that we are computing
  dataDrawerList *dataBL;

  //! The fnctData with the info that we are computing
  fnctData    *fData;

  //! The current number of row
  long rowNumber;

  //---- Members

  //! Create a new DOMDocument
  void newDOM_Document(void);
  
  //! Add a row into the DOM 
  /*!
    See function.dtd for the specific of the <row>...</row> 
    element.
  */
  void addRow(void);

 public:
  //! Constructor
  build_xmlFunctionDOM() 
    { rowNumber = 0; }

  //! Destructor
  ~build_xmlFunctionDOM() { }

  //---- Members

  //! Set the pointer to the dataDrawer list
  void setDataDrawerList(dataDrawerList *dataBL)
    { this->dataBL = dataBL; }
  
  //! Build an XML DOM document
  void buildDOM(void) throw (bad_XML);

};


#endif



