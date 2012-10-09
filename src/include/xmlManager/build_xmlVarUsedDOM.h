/***************************************************************************
			   build_xmlVarUsedDOM.h  -  description
			      -------------------
     begin                : Sept 7 2001
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

#ifndef _BUILD_XML_VAR_USED_DOM_H
#define _BUILD_XML_VAR_USED_DOM_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "xmlManager/XMLBuilder.h"
#include "xmlManager/XMLDOM_str_exception.h"

#include "data/typeDef.h"
#include "data/fnctData.h"
#include "data/varUsedData.h"
#include "data/dataDrawer.h"

#include "utils/a2b.h"

#include "error/bad_XML.h"

#include "dom/DOM.hpp"
// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

//! This class build a var_used DOM
/*!
  This class build a xml file with the list
  of the var_used in the functions.
  See var_used.dtd for more info.
*/

class build_xmlVarUsedDOM : public XMLBuilder
{
 private:
  
  //---- Attributes

  //! The dataDrawer with the information data that we are computing
  dataDrawerList     *dataBL;

  //! The fnctData with the info that we are computing
  fnctData        *fData;

  //! The varUsedData list with the declartions that we are computing
  varUsedList     *vuL;

  //! The varUsedData with the info that we are computing
  varUsedData     *vuData;

  //! The current number of row
  long            rowNumber;

  //---- Members

  //! Create a new DOMDocument
  void newDOM_Document(void);
  
  //! Add a row into the DOM 
  /*!
    See var_used.dtd for the specific of the <row>...</row> 
    element.
  */
  void addRow(void);

 public:
  //! Constructor
  build_xmlVarUsedDOM() 
    { rowNumber = 0; }

  //! Destructor
  ~build_xmlVarUsedDOM() { }

  //---- Members

  //! Set the pointer to the dataDrawer list
  void setDataBagList(dataDrawerList *dataBL)
    { this->dataBL = dataBL; }
  
  //! Build an XML DOM document
  void buildDOM(void) throw (bad_XML);

};


#endif
