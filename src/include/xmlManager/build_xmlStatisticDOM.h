/***************************************************************************
			   build_xmlStatisticDOM.h  -  description
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

#ifndef _BUILD_STATISTIC_DOM_H
#define _BUILD_STATISTIC_DOM_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "xmlManager/XMLBuilder.h"
#include "xmlManager/XMLDOM_str_exception.h"

#include "data/typeDef.h"
#include "data/fnctData.h"
#include "data/stmtNumData.h"
#include "data/dataDrawer.h"

#include "nast/nast_code.h"

#include "utils/a2b.h"

#include "error/bad_XML.h"

#include <xercesc/dom/DOM.hpp>
// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

//! This is the base class for the statistic DOM builder
class build_xmlStatisticDOM : public XMLBuilder
{
 protected:
  
  //---- Attributes

  //! The current number of row
  long            rowNumber;

  //---- Members

  //! Add a row into the DOM 
  /*! 
    A statistic row is added into the DOM.
    The structure of this row is :
    
    \code
    <row>
      <fnct_name>foo</fnct_name>
      <code>boh</code>
      <value>12357</code>
    </row>
    \endcode

    \param f the function name
    \param c the code
    \param v the value
  */
  void addRow(string f, string c,long v);

 public:
  //! Constructor
  build_xmlStatisticDOM() 
    { rowNumber = 0; }

  //! Destructor
  ~build_xmlStatisticDOM() { }


};


#endif



