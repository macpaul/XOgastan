/***************************************************************************
			   build_xmlReachStatDOM.h  -  description
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

#ifndef _BUILD_XML_REACH_STAT_DOM_H
#define _BUILD_XML_REACH_STAT_DOM_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "xmlManager/build_xmlStatisticDOM.h"
#include "xmlManager/XMLDOM_str_exception.h"

#include "data/typeDef.h"
#include "data/fnctData.h"
#include "data/nastNumData.h"
#include "data/dataDrawer.h"

#include "nast/nast_code.h"

#include "utils/a2b.h"

#include "error/bad_XML.h"

#include <xercesc/dom/DOM.hpp>
// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

//! This class build a reach statistic DOM
/*!
  This class build a xml file with the list
  of the reach statistics of the functions.
  See reach_statistic.dtd for more info.
*/

class build_xmlReachStatDOM : public build_xmlStatisticDOM
{
 private:
  
  //---- Attributes

  //! The dataDrawer with the information data that we are computing
  dataDrawerList     *dataBL;

  //! The fnctData with the info that we are computing
  fnctData        *fData;

  //! The reachNumData with the info that we are computing
  nastNumData     *nnData;

  //---- Members

  //! Create a new DOMDocument
  void newDOM_Document(void);
  
 public:
  //! Constructor
  build_xmlReachStatDOM() { }

  //! Destructor
  ~build_xmlReachStatDOM() { }

  //---- Members


  //! Set the pointer to the dataDrawer list
  void setDataBagList(dataDrawerList *dataBL)
    { this->dataBL = dataBL; }
  
  //! Build an XML DOM document
  void buildDOM(void) throw (bad_XML);

};


#endif



