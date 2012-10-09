/***************************************************************************
			   is_functions.h  -  description
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

/** \file 
 * Function used to classify the different types of nast_nodes
 * We can divide all the types of nodes in some sets 
 * (equivalency classes), so that one type of node belong to 
 * one class (and only one).
 * 
 * The policy used divide the types of nodes using a equivanlecy
 * relashonship.
 *
 * The functions in this module recognize if a node_code belong
 * to a particular class.
 *
 */

#ifndef _IS_FUNCTIONS_H
#define _IS_FUNCTIONS_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "nast/nast_code.h"


// ---------------------------------------------------------------------------
//  Functions
// ---------------------------------------------------------------------------

//! Check if the node_code is a declaration code
/*!
  \param nc the code to check

  \return True if the code is a declaration code,
  false otherwhise.
*/
extern bool isDecl(nast_code nc);

//! Check if the node_code is a type code
/*!
  \param nc the code to check

  \return True if the code is a type code,
  false otherwhise.
*/
extern bool isType(nast_code nc);

//! Check if the node_code is a constant code
/*!
  \param nc the code to check

  \return True if the code is a constant code,
  false otherwhise.
*/
extern bool isCst(nast_code nc);

//! Check if the node_code is a statement code
/*!
  \param nc the code to check

  \return True if the code is a statement code,
  false otherwhise.
*/
extern bool isStmt(nast_code nc);

//! Check if the node_code is an other code
/*!
  \param nc the code to check

  \return True if the code is an other code,
  false otherwhise.
*/
extern bool isOthr(nast_code nc);

//! Check if the node_code is a expression code
/*!
  \param nc the code to check

  \return True if the code is a expression code,
  false otherwhise.
*/
extern bool isExpr(nast_code nc);

//! Check if the node_code is a unary expression code
/*!
  \param nc the code to check

  \return True if the code is a unary expression code,
  false otherwhise.
*/
extern bool isUnaryExpr(nast_code nc);

//! Check if the node_code is a binary expression code
/*!
  \param nc the code to check

  \return True if the code is a binary expression code,
  false otherwhise.
*/
extern bool isBinaryExpr(nast_code nc);

//! Check if the node_code is a ternary expression code
/*!
  \param nc the code to check

  \return True if the code is a ternary expression code,
  false otherwhise.
*/
extern bool isTernaryExpr(nast_code nc);

//! Check if the node_code is a reference expression code
/*!
  \param nc the code to check

  \return True if the code is a reference expression code,
  false otherwhise.
*/
extern bool isRefExpr(nast_code nc);


//! Check if the node_code is an other declaration code
/*!
  \param nc the code to check

  \return True if the code is an other declaration code,
  false otherwhise.
*/
extern bool isOthrDecl(nast_code nc);

//! Check if the node_code is an other type code
/*!
  \param nc the code to check

  \return True if the code is an other type code,
  false otherwhise.
*/
extern bool isOthrType(nast_code nc);

//! Check if the node_code is an other constant code
/*!
  \param nc the code to check

  \return True if the code is a code,
  false otherwhise.
*/
extern bool isOthrCst(nast_code nc);

//! Check if the node_code is an other statement code
/*!
  \param nc the code to check

  \return True if the code is an other statement code,
  false otherwhise.
*/
extern bool isOthrStmt(nast_code nc);

//! Check if the node_code is an other other code
/*!
  \param nc the code to check

  \return True if the code is an other other code,
  false otherwhise.
*/
extern bool isOthrOthr(nast_code nc);

//! Check if the node_code is an other expression code
/*!
  \param nc the code to check

  \return True if the code is an other expression code,
  false otherwhise.
*/
extern bool isOthrExpr(nast_code nc);

#endif


