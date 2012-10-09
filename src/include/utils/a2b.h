/***************************************************************************
			   a2b.h  -  description
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

#ifndef _A2B_H
#define _A2B_H

// ---------------------------------------------------------------------------
// Includes
// ---------------------------------------------------------------------------
#include "nast/nast_code.h"
#include "nast/edge_code.h"

#include "error/bad_a2b.h"

#include "util/XMLString.hpp"

#include <string>
#include <map>

// ---------------------------------------------------------------------------
// CLASS
// ---------------------------------------------------------------------------

//! This class is used for various kinds of convertion
/*! This class is used for various kinds of convertion

  This class perform the follows convertion (and transcoding) :

  - conversion from nast_code enumeral value to the currespondent string value
  - conversion from edge_code enumeral value to the currespondent string value
  - conversion from string value to the currespondent nast_code enumeral value
  - conversion from string value to the currespondent edge_code enumeral value
  - transcoding from XMLChar string to the currespondent C++ string
  - conversion from long int to string

  \note This class ha staict attributes and static members (is a static class)

*/

class a2b {

 private:

  //**** Attributes
  
  //! Map for conversion from string to nast_code
  /*! Map for conversion from string to nast_code
    
    \sa string2nast_code
   */
  static map < string, nast_code > strg2n_c;
  
  
  //! Map for conversion from string to edge_code
  /*! Map for conversion from string to edge_code
    
    \sa string2edge_code
  */
  static map < string, edge_code > strg2e_c;
  

  //! Map for conversion from nast_code to string
  /*! Map for conversion from nast_code to string
    
    \sa nast_code2string
  */
  static map < nast_code, string > n_c2strg;

  //! Map for conversion from edge_code to string
  /*! Map for conversion from edge_code to string
    
    \sa edge_code2string
  */
  static map < edge_code, string > e_c2strg;
  
 public:
  
  //**** Members
  
  //! Constructor
  /*! Constructor */
  a2b() {

    // INIT strg2n_c  
#define  DEFnastCODE(CODE, STRING_CODE, C, P)   a2b::strg2n_c[#STRING_CODE] = CODE;
#include "nast/nast_code.def"
#undef DEFnastCODE
    
    // INIT strg2e_c  
#define  DEFedgeCODE(STRING_CODE, CODE)         a2b::strg2e_c[#STRING_CODE] = CODE;
#include "nast/edge_code.def"
#undef DEFedgeCODE
    
    // INIT n_c2strg
#define  DEFnastCODE(CODE, STRING_CODE, C, P)   a2b::n_c2strg[CODE] = #STRING_CODE;
#include "nast/nast_code.def"
#undef DEFnastCODE
    
    // INIT e_c2strg
#define  DEFedgeCODE(STRING_CODE, CODE)         a2b::e_c2strg[CODE] = #STRING_CODE;
#include "nast/edge_code.def"
#undef DEFedgeCODE

}


  //! Conversion from string to nast_code
  /*! Conversion from string to nast_code
    
    Given the string with the nast code this function return the 
    currespondent nast_code enumeration value (how defined in
    nast_code.def).
    
    For example, given the string C++ "var_decl" it return VAR_DECL.
    
    For the translation from string to enumeration 
    we use the map strg2n_c. 
    
    \param code C++ string with the nast code
    
    \return The nast_code currespondent to code, or THROW exception
    
  */
  static nast_code string2nast_code (string code) 
    throw (bad_a2b);


  //! Conversion from string to edge_code
  /*! Conversion from string to edge_code
    
    Given the string with the edge code this function return the 
    currespondent edge_code enumeration value (how defined in
    edge_code.def).
    
    For example, given the string C++ "arguments" it return ARGUMENTS_EDGE.

    For the translation from string to enumeration 
    we use the map strg2e_c. 
    
    \param code C++ string with the edge code
    
    \return The edge_code currespondent to code, or THROW exception
    
  */
  static edge_code string2edge_code(string code)
    throw (bad_a2b);


  //! Conversion from nast_code to string
  /*! Conversion from nast_code to string

    Given a nast_code this function return the 
    currespondent string
    
    For example, given the nast_code VAR_DECL it return "var_decl"
    
    For the translation from string to enumeration 
    we use the map n_c2strg. 
    
    \param code the nast_code
    
    \return The string currespondent to code, or THROW exception
    
  */
  static string nast_code2string (nast_code code)
    throw (bad_a2b);


  //! Conversion from edge_code to string
  /*! Conversion from edge_code to string

    Given an edge_code this function return the 
    currespondent string
    
    For example, given the edge_code ARGUMENTS_EDGE it return "arguments"
    
    For the translation from string to enumeration 
    we use the map e_c2strg. 
    
    \param code the edge_code
    
    \return The string currespondent to code, or THROW exception
    
  */
  static string edge_code2string (edge_code code)
    throw (bad_a2b);

  //! Convert a C++ string into a C string
  static char *cpp_string2c_string(string s);

  //! Transcoding from XMLChar * to string
  /*!    
    This is a simple function that lets us do easy (though not terribly efficient)
    trancoding of XMLCh data to local code page for display.
  */
  static string XMLChar2string(const XMLCh* const toTranscode);


  //! Conversion from long int to string
  /*! Conversion from long int to string

    Given a long int this function return the 
    currespondent string value.
    
    \param lg the long int
    
    \return The string currespondent to long int 
    
  */
  static string long2string (long int lg);

};


#endif





