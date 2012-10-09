/***************************************************************************
			   write_htmlFnctFilter.h  -  description
			      -------------------
     begin                : Aug 29 2001
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

#ifndef _WRITE_HTML_FNCT_FILTER_H
#define _WRITE_HTML_FNCT_FILTER_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "htmlWriter/HTMLwriter.h"
#include "htmlWriter/HTMLofstream.h"
#include "htmlWriter/HTMLfilesRegister.h"

#include "data/typeDef.h"
#include "data/fnctData.h"
#include "data/parmData.h"
#include "data/dataDrawer.h"
#include "data/dataFilter.h"

// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

//! This class write index of the functions
/*! 
  This class use a dataFilter to decide 
  wich function we must include into the index.

  The idea is represented by the follow code :

  \code
  while (have functions in dataDrawerList to examine) {
    get the dataDrawer dataB;
    get the function description fData;

    if (dFilter->isGood(*fData)) 
      include function into the index, write it;
   
  }
  \endcode

*/
class write_htmlFnctFilter : public HTMLwriter
{
 private:

  //! List of dataDrawer
  /*!
    All the infomartion about the function
    are here
  */
  dataDrawerList   *dataBL;
  
  //! The filter used to select the functions
  dataFilter    *dFilter;

 public:
  //! Constructor
  write_htmlFnctFilter() { }

  //! Destructor
  ~write_htmlFnctFilter() { }

  //! Set the pointer to the dataDrawer list
  void setDataDrawerList(dataDrawerList *dataBL)
    { this->dataBL = dataBL; }

  //! Set the pointer to the filter
  void setDataFilter(dataFilter *dFilter) 
    { this->dFilter = dFilter; }

  //! Write the page
  /*!
    The dataDrawerList is browsed from the start to the end.
    For each element we checks if the fnctData pass
    the test's filter. If it pass the test then the function
    is included into the index (see example code below).
  */
  void writePage(void);
  
};


#endif
