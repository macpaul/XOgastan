/***************************************************************************
			   build_xmlExprStatDOM.h  -  description
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

#ifndef _BUILD_XML_EXPR_STAT_DOM_H
#define _BUILD_XML_EXPR_STAT_DOM_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "xmlManager/build_xmlStatisticDOM.h"
#include "xmlManager/XMLDOM_str_exception.h"

#include "data/typeDef.h"
#include "data/fnctData.h"
#include "data/exprNumData.h"
#include "data/dataDrawer.h"

#include "nast/nast_code.h"

#include "utils/a2b.h"

#include "error/bad_XML.h"

#include <xercesc/dom/DOM.hpp>
// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

//! This class build a expr statistic DOM
/*!
  This class build a xml file with the list
  of the expr statistics of the functions.
  See expr_statistic.dtd for more info.
*/
class build_xmlExprStatDOM : public build_xmlStatisticDOM
{
 private:
  
  //---- Attributes

  //! The dataDrawer with the information data that we are computing
  dataDrawerList     *dataBL;

  //! The fnctData with the info that we are computing
  fnctData        *fData;

  //---- Members

  //! Create a new DOMDocument
  void newDOM_Document(void);
  
 public:
  //! Constructor
  build_xmlExprStatDOM() { }

  //! Destructor
  ~build_xmlExprStatDOM() { }

  //---- Members


  //! Set the pointer to the dataDrawer list
  void setDataBagList(dataDrawerList *dataBL)
    { this->dataBL = dataBL; }
  
  //! Build an XML DOM document
  void buildDOM(void) throw (bad_XML);

};


#endif



