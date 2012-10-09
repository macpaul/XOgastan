/***************************************************************************
			   DATAfilesRegister.h  -  description
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

#ifndef _DATA_FILES_REGISTER_H
#define _DATA_FILES_REGISTER_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "data/fnctData.h"

#include "utils/a2b.h"

#include <string>
// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

//! The class for the information about the name of the data files
/*!
  This static class help the construction of the names of the 
  data files.
  
  It maps data object (see include/data/ ) on the
  currespondents (and unique) file name.

  For example :
  
  a function_decl with the name foo can have aasociated the 
  folloing files :

  foo.gif       The gif file
  foo.dot       The dot file

  each name of these files is got by calling
  an appropriate static method.
*/
class DATAfilesRegister
{
 private:
  
 public:
  //! Constructor
  /*! Constructor */
  DATAfilesRegister() { }

  //! Destructor
  /*! Destructor */
  ~DATAfilesRegister() { }

  //---- Members

  //---- GET link

  //@{
  /** Get a file name for an object fnctData 

    The output file name must be unique. 
    
    It is built using :
    
    - the name of the function 
    - the node_index of the currespondent function_decl_n
    - a qualifier of the file : gif, dot, ...

    A possibile file name can be : 

    - foo_123.gif : gif only
    - foo_123.dot : dot only

    where :

    - foo : is the function name
    - 123 : is the index of the currespondent function_decl_n
    - .gif : is the qualifier for the gif file
    - .dot : is the qualifier for the dot file

    \param fd the fnctData for the file's name generation

    \note The mapping is made on the fly. We don't use any map.
  */
  static string gifBodyGraphFile(fnctData &fd);
  static string dotBodyGraphFile(fnctData &fd);
  static string dotCallGraphFile(fnctData &fd);
  static string gifCallGraphFile(fnctData &fd);
  static string dotCFGraphFile(fnctData &fd);
  static string txtCFGraphFile(fnctData &fd);
  static string gifCFGraphFile(fnctData &fd);
  //@}

};

#endif



