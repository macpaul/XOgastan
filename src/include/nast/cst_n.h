/***************************************************************************
			   cst_n.h  -  description
			      -------------------
     begin                : July 13 2001
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


#ifndef _CST_N_H
#define _CST_N_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "nast/nast_node.h"

#include <string>



// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

//! The base class of the constants
/*! The base class of the constants
  The constants classes are used to represent the statement
  element in the C/C++ grammar. They are :

  ## Standard C :

  DEFnastCODE(INTEGER_CST, integer_cst, 0, 0)
  DEFnastCODE(REAL_CST, real_cst, 0, 0)
  DEFnastCODE(STRING_CST, string_cst, 0, 0)
  
  ## Special C++ :

  DEFnastCODE(COMPLEX_CST, complex_cst, 0, 0) 
  DEFnastCODE(PTRMEM_CST, ptrmem_cst, 0, 0)
  
  
  All the constants haven't any attributes.

  \note Only the C element are good defined.
*/
class cst_n : public nast_node {

  // NO ATTRIBUTES

 public:
  //! Constructor
  /*! Constructor */
  cst_n() { return; }

  //! Destructor
  /*! Destructor */
  ~cst_n() { }
  
};



//! The class for the integer constant
/*! The class for the integer constant 

  Used to represent an integer constant like :
      100
      'c'

  This image shows the possibile output edges.
  
  \image html integer_cst.gif

*/
class integer_cst_n : public cst_n {

  // NO ATTRIBUTES

 public:
  //! Constructor
  /*! Constructor */
  integer_cst_n() { return; }

  //! Destructor
  /*! Destructor */
  ~integer_cst_n() { }
  
  //*** Member

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);

};



//! The class for the real constant
/*! The class for the real constant 

  Used to represent an real constant like :
      10.5f

  This image shows the possibile output edges.
  
  \image html real_cst.gif
*/
class real_cst_n : public cst_n {

  // NO ATTRIBUTES

 public:
  //! Constructor
  /*! Constructor */
  real_cst_n() { return; }

  //! Destructor
  /*! Destructor */
  ~real_cst_n() { }
  
  //*** Member

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);

};


//! The class for the string constant
/*! The class for the string constant 

  Used to represent an string constant like :
      "Hello World !\n"

  This image shows the possibile output edges.
  
  \image html string_cst.gif
*/
class string_cst_n : public cst_n {

  // NO ATTRIBUTES

 public:
  //! Constructor
  /*! Constructor */
  string_cst_n() { return; }

  //! Destructor
  /*! Destructor */
  ~string_cst_n() { }
  
  //*** Member

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);

};


//! The class for the othr constant
/*! The class for the othr constant */
class othr_cst_n : public cst_n {

  // NO ATTRIBUTES

 public:
  //! Constructor
  /*! Constructor */
  othr_cst_n() { return; }

  //! Destructor
  /*! Destructor */
  ~othr_cst_n() { }
  
  //*** Member

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);

};

#endif









