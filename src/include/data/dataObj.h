/***************************************************************************
			   dataObj.h  -  description
			      -------------------
     begin                : Aug 28 2001
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

#ifndef _DATA_OBJ_H
#define _DATA_OBJ_H

// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

//! This is the base class of the data objects hierarcy
/*!
  All the class that hold the result of a visit
  operation are child of this class.

  This class is necsary to define a hirerarcy of data.
  
  \note We have only virtual one function member. This
  virtual member is necessary to use the parameter
  dataObj * or dataObj & in functions and methods. So
  we can access to only  dataObj from the base class.
*/
class dataObj
{
 public:
  //! Constructor
  dataObj() { }
  
  //! Destructor
  ~dataObj() { }
  
  //! Virtual member 
  /*!
    It is UNUSED.
    It is DEFINED only to allow the access
    to the derived class from a reference or a
    pointer to the base class.
  */
  virtual void unused(void) { }

};

#endif
