/***************************************************************************
			   varUsedData.h  -  description
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

#ifndef _VAR_USED_DATA_H
#define _VAR_USED_DATA_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "data/declData.h"

#include <string>

// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

//! This class holds informations about a variable used by a function
/*!
  It is derived from declData. 
  In the NAST when an expression use a variable then a 
  pointer to a var_decl node is made; so, this class hold the 
  information about the var_decl pointed
  into an expression.
*/
class varUsedData: public declData {
 private:

  //! Hold if the variable is local to the function, or has global scope
  /*!
    Value :

    true, the variable is local to the function
    false, the variable isn't local to the function

    A variable is local to the function if it is declared in one
    of the block (delimeted by {}) into the function.
  */
  bool local;

 public:
  //! Constructor
  varUsedData() { local = true; }
  
  //! Destructor
  ~varUsedData() { }

  //--- Members

  //! Set the variable as a local variable
  void setLocal(void) 
    { this->local = true; }

  //! Set the variable as a not local variable
  void unsetLocal(void) 
    { this->local = false; }

  //--- IS ... ?
  
  //! Ask if the variable is local or not
  /*!
    \return True if the variable is local,
    false otherwise
  */
  bool isLocal(void)
    { return this->local; }
    
};


// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

//! The Class for the comparison between 2 objects varUsedData
/*! 
  This class is used to compare 2 objects varUsedData.
  
  The comparation between 2 varUsedData is made used the attribute 
  name.
  Given the 2 object varUsedData vud1 nad vud2 then :

  - vud1 <  vud2 if only if vud1::name <  vud2::name
  - vud1 == vud2 if only if vud1::name == vud2::name
  - vud1 >  vud2 if only if vud1::name >  vud2::name
  
  Remember : the type of the attribute varUsedData::name 
  is string.

  \note This class overload the operator ().
*/
class varUsedData_Cmp {

 public:

  //! The member for the comparison
  /*!
    Overload the operator ().

    \param vud1 the first varUsedData
    \param vud2 the second varUsedData

    \return True if vud1::name < vud2::name,
    false otherwise.
  */
  bool operator()(varUsedData& vud1, varUsedData& vud2);

  //! The member for the comparison
  /*!
    Overload the operator ().

    \param vud1 the first varUsedData
    \param vud2 the second varUsedData

    \return True if vud1::name < vud2::name,
    false otherwise.
    
    \note This method differs from the previous in the type 
    of the parameters. Now we have pointer, in the previous
    method we have reference.
  */
  bool operator()(varUsedData* vud1, varUsedData* vud2);

};

#endif

