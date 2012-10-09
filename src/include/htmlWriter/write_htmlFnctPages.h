/***************************************************************************
			   write_htmlFnctPages.h  -  description
			      -------------------
     begin                : Aug 30 2001
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

#ifndef _WRITE_HTML_FNCT_PAGES_H
#define _WRITE_HTML_FNCT_PAGES_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "htmlWriter/HTMLwriter.h"
#include "htmlWriter/HTMLofstream.h"
#include "htmlWriter/HTMLfilesRegister.h"

#include "data/typeDef.h"
#include "data/fnctData.h"
#include "data/parmData.h"
#include "data/declData.h"
#include "data/exprData.h"
#include "data/varUsedData.h"
#include "data/stmtNumData.h"
#include "data/exprNumData.h"
#include "data/dataDrawer.h"

#include "utils/flags.h"

#include <string>
// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

//! This class writes the pages of alls the functions
/*!
  For each function into the dataDrawerList
  it writes the html page of the function
  
  The html page include :
  - body graph of the statement
  - cfg graph of the statement
  - call graph
  - declrations list
  - var used list
  - stmt statistics
  - expr statistics
  - nast statistics

  Some parts of the page can be excluded if 
  the command line include some of the flags :
  - nocfg
  - nobodygraph
  - nocallgraph
  - nodecllist
  - novarused
  - nostmtstat
  - noexprstat
  - nonaststat

*/
class write_htmlFnctPages : public HTMLwriter
{
 private:

  //! List of dataDrawer
  /*!
    All the infomartion about the function
    are here
  */
  dataDrawerList *dataBL;

  //! The current dataDrawer of the page that we are writing
  dataDrawer *dataB;   

  //! The current fnctData of the page that we are writing
  fnctData *fData;   

 public:
  //! Constructor
  write_htmlFnctPages() { }

  //! Destructor
  ~write_htmlFnctPages() { }

  //! Set the pointer to the dataDrawer list
  void setDataDrawerList(dataDrawerList *dataBL)
    { this->dataBL = dataBL; }

  //! Write the page
  void writePage(void);

  //! Write the index of this page
  void writePageIndex(void);

  //! Write the graph of the body
  void writeBodyGraph(void);

  //! Write the CFG
  void writeCFG(void);

  //! Write the graph of the function calleds
  void writeCallGraph(void);

};


#endif








