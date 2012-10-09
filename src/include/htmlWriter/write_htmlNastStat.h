/***************************************************************************
			   write_htmlNastStat.h  -  description
			      -------------------
     begin                : Sept 1 2001
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

#ifndef _WRITE_HTML_NAST_STAT_H
#define _WRITE_HTML_NAST_STAT_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "htmlWriter/HTMLwriter.h"
#include "htmlWriter/HTMLofstream.h"
#include "htmlWriter/HTMLfilesRegister.h"

#include "visitor/visit_nastNumber.h"

#include "data/typeDef.h"
#include "data/nastNumData.h"
#include "data/fnctData.h"
#include "data/dataFilter.h"
#include "data/dataDrawer.h"

#include "utils/get_functions.h"

#include <list>
#include <string>
// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

//! This class write the statistics about the NAST
/*!
  The statistics writed are :
  - the statistics about the nast_node into NAST
  - the reacheables nast_nodes of each functions
  
  This page is not dumped if the flag nonaststat is raised
  on the command line.
*/
class write_htmlNastStat : public HTMLwriter
{
 private:

  //! List of dataDrawer
  /*!
    All the infomartion about the function
    are here
  */
  dataDrawerList *dataBL;

  //! The statistics about NAST
  nastNumData *nastStat;
  
  //! Total nodes counted in NAST
  long totals;

 public:
  //! Constructor
  write_htmlNastStat() { }

  //! Destructor
  ~write_htmlNastStat() { }

  //! Set the statistcs about nast
  void setNastStat(nastNumData *nastStat) 
    { this->nastStat = nastStat; }

  //! Set the dataDrawer list
  void setDataDrawerList(dataDrawerList *dataBL) 
    { this->dataBL = dataBL; }

  //! Write the statistics about all the NAST
  void writeGlobalStatistics(void);

  //! Write the statistics about each function
  void writePartialStatistics(void);

  //! Write a table cell for the statitcs information about the functions
  void writeCell(string value);
  //! Write a table cell for the statitcs information about the functions
  void writeCell(long value, double valueX100);

  //! Write the page
  void writePage(void);
  
};


#endif
