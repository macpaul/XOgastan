/***************************************************************************
			   nast_code.h  -  description
			      -------------------
     begin                : July 10 2001
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

#ifndef _NAST_CODE_H
#define _NAST_CODE_H


#define  DEFnastCODE(CODE, STRING_CODE, C_ATTR, P_ATTR) 	CODE,

//! The nast_code enumeration
/*! The nast_code enumeration.
  
  The elements of this enumeration are used to refer the 
  different types of nast_node.
  They are the same used in gcc, but the order (the value in the 
  enumeration) is different

  \note Each enumeration element has a currespondent string value.
  The class a2b translate an nast_string_code into an nast_enumeral_code
  and viceversa. The string code are used in the gxl document, and the
  enumeral code are used into the internal representation of a NAST
  structure.
*/
typedef enum {
	FIRST_NAST_CODE = 0,
	#include "nast/nast_code.def"
	LAST_NAST_CODE,
	NO_NAST_CODE
} nast_code;

#undef DEFnastCODE

#endif
