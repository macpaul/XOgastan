/***************************************************************************
			   HTMLFregister.cpp  -  description
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

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "htmlWriter/HTMLfilesRegister.h"

#include "utils/a2b.h"

#include <string>

// ---------------------------------------------------------------------------
//  Static Constants Attributes
// ---------------------------------------------------------------------------

// Home page
const char *HTMLfilesRegister::homePage = "index.htm";

// Indexes of the functions
const char* HTMLfilesRegister::fnctIndex  = "function_index.htm";
const char* HTMLfilesRegister::fnctWithBodyIndex = "function_with_body_index.htm";
const char* HTMLfilesRegister::fnctWithParmIndex = "function_with_parm_index.htm";
const char* HTMLfilesRegister::fnctIsStdCIndex  = "function_is_std_c_index.htm";

// NAST statistics
const char* HTMLfilesRegister::nastStatistics = "nast_statistics.htm";

// ---------------------------------------------------------------------------
//  Members
// ---------------------------------------------------------------------------


string 
HTMLfilesRegister::htmlFile(fnctData &fd) {
  string fileName;
  
  fileName = fd.getName() + "_" + 
    a2b::long2string( (fd.getNodeP())->getId()) + ".htm";
  
  return fileName;
}


