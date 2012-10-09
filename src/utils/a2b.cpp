/***************************************************************************
			   a2b.cpp  -  description
			      -------------------
     begin                : Aug 9 2001
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
// INCLUDES
// ---------------------------------------------------------------------------
#include "utils/a2b.h"

// ---------------------------------------------------------------------------
// MAD Definitions
// ---------------------------------------------------------------------------

map < string, nast_code > a2b::strg2n_c;
map < string, edge_code > a2b::strg2e_c;
map < nast_code, string > a2b::n_c2strg;
map < edge_code, string > a2b::e_c2strg;


// ---------------------------------------------------------------------------
// MEMBERS
// ---------------------------------------------------------------------------

nast_code 
a2b::string2nast_code (string code)     
  throw (bad_a2b)
{

  if (strg2n_c.find(code) != strg2n_c.end())
    return strg2n_c[code];
  else
    throw bad_a2b("A2B error conversion",
		  "Found an inexistent nast_code");
  
}


edge_code 
a2b::string2edge_code (string code) 
  throw (bad_a2b)
{
  if (strg2e_c.find(code) != strg2e_c.end())
    return strg2e_c[code];
  else 
    throw bad_a2b("A2B error conversion",
		  "Found an inexistent edge_code");
}


string 
a2b::nast_code2string (nast_code code) 
  throw (bad_a2b)
{

  if (n_c2strg.find(code) != n_c2strg.end())
    return n_c2strg[code];
  else
    throw bad_a2b("A2B error conversion",
		  "Nast code is illegal");

}


string 
a2b::edge_code2string (edge_code code) 
  throw (bad_a2b)
{

  if (e_c2strg.find(code) != e_c2strg.end())
    return e_c2strg[code];
  else
    throw bad_a2b("A2B error conversion",
		  "Edge code is illegal");
}


char *
a2b::cpp_string2c_string(string s) {
  char *p = new char[s.length() + 1];
  s.copy(p,string::npos);
  p[s.length()] = 0;
  return p;
}


string 
a2b::XMLChar2string(const XMLCh* const toTranscode) {

  string target_string;
  char *char_string;

  // Call the private transcoding method
  char_string = XMLString::transcode(toTranscode);
  // save in string 
  target_string = char_string;

  // free memory
  delete char_string;

  // return the string saved
  return target_string;

}

string 
a2b::long2string (long int lg) {

  char *value;
  long number, digit;
  long i;
  string s;

  if (lg != 0) {
    
    // count number of digits
    number = (lg > 0) ? lg : -lg;
    i = (lg > 0) ? 0 : 1;
    while (number > 0) {
      number /= 10;
      i++;
    }

    // create the vector of chars
    value = new char[i+1];
    value[i--] = '\0';
    if (lg < 0) value[i] = '-';

    // build C string
    number = (lg > 0) ? lg : -lg;
    while (number > 0) {
      digit = number % 10;
      number /= 10;
      value[i] = '0' + digit;
      i--;
    }
    
    // save C string in s
    s = value;
    // free memory (no garbage)
    delete value;

  } else s = "0";

  return s;
}
