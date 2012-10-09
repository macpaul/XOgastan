/***************************************************************************
			   stmtNumData.h  -  description
			      -------------------
     begin                : Aug 31 2001
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

#ifndef _STMT_NUM_DATA_H
#define _STMT_NUM_DATA_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "data/dataObj.h"

#include "error/bad_data.h"

#include "nast/nast_code.h"

#include "utils/is_functions.h"

#include <map>
#include <string>
// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

//! This class holds informations about the number of statements
/*!
  This class can be used to hold the number of statement present 
  in a function, in all the nast, in sub-block of function.

  The implementation of this class depend of the file
  nast_code.def If we change this file something will go wrong.
*/
class stmtNumData : public dataObj
{

 private:

  //---- Attributes

  //! The map of the counted statements
  /*!
    Each element of this map is associated count the number of element 
    of a class derived from the class stmt_n.
  */
  map<nast_code, long>        counted;

 public:
  //! Constructor
  stmtNumData() { }
  
  //! Destructor
  ~stmtNumData() { }

  //---- Members

  //---- ADD
  
  //! Add an other stmt_n
  /*!
    \param code The code of the statement

    \note Throw an execption if code isn't a statement code
  */
  void addStmt(nast_code code)
    throw (bad_data);

  //---- GET

  //! Get total number of asm_stmt
  /*!
    \param code The code of the statement
    
    \return The number of presence of the statement
    
    \note Throw an execption if code isn't a statement code
  */
  long numStmt(nast_code code)
    throw (bad_data);

  //---- TOTAL

  //! Get total number of SelectStmt statements
  /*!
    \return The number of IF and SWITCH
  */
  long totalSelectStmt(void) 
    { return (this->counted[IF_STMT] +
	      this->counted[SWITCH_STMT]); }

  //! Get total number of IterStmt statements
  /*!
    \return The number of FOR, DO, WHILE
  */
  long totalIterStmt(void) 
    { return (this->counted[FOR_STMT] +
	      this->counted[DO_STMT] +
	      this->counted[WHILE_STMT]); }

  //! Get total number of FlowModifierStmt statements
  /*!
    \return The number of BREAK, CONTINUE, RETURN, GOTO
  */
  long totalFlowModifierStmt(void) 
    { return (this->counted[BREAK_STMT] +
	      this->counted[CONTINUE_STMT] +
	      this->counted[RETURN_STMT] +
	      this->counted[GOTO_STMT]); }

  //! Get total number of statements
  long totalStmt(void);

};

#endif









