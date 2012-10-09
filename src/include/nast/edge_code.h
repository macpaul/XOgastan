/***************************************************************************
			   edge_code.h  -  description
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

#ifndef _EDGE_CODE_H
#define _EDGE_CODE_H

#define  DEFedgeCODE(STRING_CODE, CODE) 	CODE,

//! The edge_code enumeration
/*! The edge_code enumeration.
  
  The elements of this enumeration are used to refer the 
  edges of a nast_node.

  \note Each enumeration element has a currespondent string value.
  The class a2b translate an edge_string_code into an edge_enumeral_code
  and viceversa.The string code are used in the gxl document, and the
  enumeral code are used into the internal representation of a NAST
  structure.
*/
typedef enum {
	FIRST_EDGE_CODE = 0,
	#include "nast/edge_code.def"
	LAST_EDGE_CODE
} edge_code;


#undef DEFedgeCODE

#endif
