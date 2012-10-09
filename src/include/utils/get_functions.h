/***************************************************************************
			   get_functions.h  -  description
			      -------------------
     begin                : Aug 6 2001
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

/*! \file
   \brief Functions for extract value from C/C++ 
   string.

   All the functions in this file are used to extract some 
   part of a C/C++ string.

*/

#ifndef _GET_FUNCTIONS_H
#define _GET_FUNCTIONS_H


// ---------------------------------------------------------------------------
// Includes
// ---------------------------------------------------------------------------
#include "nast/nast_code.h"
#include "nast/edge_code.h"

#include "error/bad_get.h"

#include <cstdlib>
#include <string>
#include <ctype.h>

// ---------------------------------------------------------------------------
// Functions
// ---------------------------------------------------------------------------

//! Extract the index of a gxl node 
/*!
  The GXL index has the syntax : nd<number>
  This function checks if the syntax is rigth an then return
  the long value of the index.

  For example, given the C++ string "nd123" it
  return the long value 123.

  \param s C++ string with the index
  
  \return The index in s, or TRHOW exception
*/
extern long getGXLindex (string s)
     throw (bad_get);


//! Extract the type of a gxl node or edge 
/*!
  The GXL type has the syntax : gccast.xml#<string_type>
  This function checks if the syntax is rigth an then return
  the C++ string with the <string_type>.

  For example, given the C string "gccast.xml#var_decl" it
  return the C string "var_decl"

  \param cpps C++ string with the type
  
  \return The type in cs, or TRHOW exception

*/
extern string getGXLtype (string s) 
     throw (bad_get);


//! Calculate the percentual value
/*! 
  \param d the data
  \param t the total

  \return The percentual value of d on the total t

*/
extern double getX100(double d, double t);

#endif








