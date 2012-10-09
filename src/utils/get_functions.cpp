/***************************************************************************
			   get_functions.cpp  -  description
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

// ---------------------------------------------------------------------------
// Includes
// ---------------------------------------------------------------------------
#include "utils/get_functions.h"


// ---------------------------------------------------------------------------
// Functions
// ---------------------------------------------------------------------------


long
getGXLindex (string s)
  throw (bad_get)
{
  // Warning : the memory allocate for p must be free by the caller

  char     *p;             // C string for the index
  int      i;              // counter
  bool     good_syntax;    // flag for good syntax
  int      len;            // length of s
  long     indexValue;     // value of the index

  // check first and second characters : they must be nd
  good_syntax = ( (len = s.length()) >= 3)
    && (s[0] == 'n') && (s[1] == 'd');

  if (good_syntax) {
    // allocate memory for C string 
    p = new char[len];
    
    // Check if the characters after the second are digits
    // Build the node id
    for (i = 0; (i+2 < len) && good_syntax; i++) 
      good_syntax = isdigit (p[i] = s[i+2]);
    
    p[i] = '\0';
  }

  if (!good_syntax)
    throw bad_get("getGXLIndex",
		  "Syntax error in the format of the node index");
  
  // Computhe the index
  indexValue = atol(p);
  delete p;

  return indexValue;
}



string
getGXLtype (string s)
  throw (bad_get)
{
  // flag for good syntax
  bool good_syntax;

  // checks if the string contains "gccastxml#" and there
  // is other characters
  // remember : the length of "gccast.xml#" is 11
  good_syntax = (s.length () > 11) && (s.find ("gccast.xml#") == 0);
  
  if (!good_syntax)
    throw bad_get ("getGXLtype",
		   "Syntax error in the type of a node or edge");

  // return the <string> substring
  return s.substr (11, s.length() - 1);
}


double 
getX100(double d, double t) {
  return (100*d)/t;
}
