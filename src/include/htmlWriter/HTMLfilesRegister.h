/***************************************************************************
			   HTMLfilesRegister.h  -  description
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

#ifndef _HTML_FILES_REGISTER_H
#define _HTML_FILES_REGISTER_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------

#include "data/fnctData.h"


// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

//! The class for the information about the name of the html files
/*!
  When we write more html pages there are a lots
  of pages to link togheter. 
  This static class help this linking process.
  
  It maps data object (see include/data/ ) on the
  currespondents (and unique) html file name.

  When a link to a data object is required, then the 
  link is mapped into a hmtl file name.

  An object can have more links associated with it.
  These name of the currespondets file names are built
  when the object is added for the first time.

  For example :
  
  a function_decl with the name foo can have aasociated the 
  folloing files :

  foo.htm       The index of the function

  each name of these files is obteined by calling
  an appropriate method of HTMLregister.

  \note The mapping is done on the fly.
*/
class HTMLfilesRegister
{
 private:
  
 public:
  //! Constructor
  HTMLfilesRegister() { }

  //! Destructor
  ~HTMLfilesRegister() { }

  //---- Members

  //---- GET link

  //! Get an html file name for an object fnctData 
  /*!      
    The output file name must be unique. 
    
    It is built using :
    
    - the name of the function 
    - the node_index of the currespondent function_decl_n
    - a qualifier of the file : html,

    A possibile file name can be : 

    - foo_123.htm : html only

    where :

    - foo : is the function name
    - 123 : is the index of the currespondent function_decl_n
    - .htm : is the qualifier for the html page

    \param fd the fnctData for the file's name generation

  */
  static string htmlFile(fnctData &fd);


  //! The Home Page
  static const char *homePage;

  //! The html page with the index of all functions
  static const char *fnctIndex;

  //! The html page with the index of functions with body
  static const char* fnctWithBodyIndex;

  //! The html page with the index of functions with parameters
  static const char* fnctWithParmIndex;

  //! The html page with the index of C standard functions
  static const char* fnctIsStdCIndex;

  //! The html page with the NAST statistics
  static const char* nastStatistics;
  
};

#endif



