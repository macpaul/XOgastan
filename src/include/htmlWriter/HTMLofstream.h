/***************************************************************************
			   HTMLofstream.h  -  description
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


#ifndef _HTML_OFSTREAM_H
#define _HTML_OFSTREAM_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "data/typeDef.h"
#include "data/declData.h"
#include "data/exprData.h"
#include "data/varUsedData.h"
#include "data/fnctData.h"
#include "data/parmData.h"
#include "data/stmtNumData.h"
#include "data/exprNumData.h"
#include "data/nastNumData.h"

#include "nast/nast_code.h"

#include "utils/a2b.h"
#include "utils/get_functions.h"

#include <fstream>

// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

//! The class for the html output on the file
/*!
  This class represent an html page (file).
  The page can be opened and closed.
  We can write on the page the C++ type like int,
  string, ... and we can also write the dataObj.
  The operator << are overloaded.

  The data are formatted using the html tag.
  
  In this way each dataObj has always the same look & feel
  style.
*/
class HTMLofstream {
 private:

  //! The html page for the output
  ofstream   page;

 public:
  //! Constructor
  HTMLofstream() { }
  
  //! Destructor
  ~HTMLofstream() { }
  
  //---- Members

  //! Open a file for the output
  /*!
    \param pageName the name of the file
  */
  void open(const char *pageName);

  //! Close the page opened
  void close();

  //! Write on the ostream& a statitic row 
  /*! 
    A statitic row is composed by a couple of <td>...</td> :
    - name of the data (string)
    - value of the data (long)
    
    \param name the name
    \param value the value
    \param bold the flag for the bold modifier for the name
  */
  void statisticRow(string name, long value, bool bold);
  
  //! Write on the ostream& a statitic row 
  /*! 
    A statitic row is composed by a couple of <td>...</td> :
    - name of the data (string)
    - value of the data (long)
    
    \param name the name
    \param value the value
    \parm  x100 the percentual value of value
    \param bold the flag for the bold modifier for the name
  */
  void statisticRowX100(string name, long value, double x100, bool bold);

  //! Write a char*
  friend 
    HTMLofstream& operator<<(HTMLofstream& HTMLos, char *c);

  //! Write a string
  friend 
    HTMLofstream& operator<<(HTMLofstream& HTMLos, string s);

  //! Write a long
  friend 
    HTMLofstream& operator<<(HTMLofstream& HTMLos, long l);

  //! Write a long
  friend 
    HTMLofstream& operator<<(HTMLofstream& HTMLos, double d);

  //! Write a fnctData object on the output
  friend 
    HTMLofstream& operator<<(HTMLofstream& HTMLos, fnctData& fd);
  
  //! Write a parmData object on the output
  friend 
    HTMLofstream& operator<<(HTMLofstream& HTMLos, parmData& pd);
  
  //! Write an object declsList on the output
  friend 
    HTMLofstream& operator<<(HTMLofstream& HTMLos, declsList& dL);

  //! Write an object declsList on the output
  friend 
    HTMLofstream& operator<<(HTMLofstream& HTMLos, varUsedList& vuL);

  //! Write an object exprsList on the output
  friend 
    HTMLofstream& operator<<(HTMLofstream& HTMLos, exprsList& eL);
  
  //! Write an object parmList on the output
  friend 
    HTMLofstream& operator<<(HTMLofstream& HTMLos, parmList& pL);
  
  //! Write an object stmtNumData on the output
  friend 
    HTMLofstream& operator<<(HTMLofstream& HTMLos, stmtNumData& snd);
  
  //! Write an object exprNumData on the output
  friend 
    HTMLofstream& operator<<(HTMLofstream& HTMLos, exprNumData& end);
  
  //! Write an object nastNumData on the output
  friend 
    HTMLofstream& operator<<(HTMLofstream& HTMLos, nastNumData& nnd);

};
  
#endif

