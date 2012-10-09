/***************************************************************************
			   type_n.h  -  description
			      -------------------
     begin                : July 12 2001
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


#ifndef _TYPE_N_H
#define _TYPE_N_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "nast/nast_node.h"


// ---------------------------------------------------------------------------
//  Enumerations
// ---------------------------------------------------------------------------


//! The enumeration for the three C qualifiers
/*! The enumeration for the three C 
  qualifiers : constant, volatile, restrict

  we define :
    - constant = 1 		001(bits)
    - volatile = 2		010(bits)
    - restrict = 4		100(bits)
  we have also :
    - constant,volatile= 3 		011(bits)
    - constant,restrict= 5		101(bits)
    - volatile,restrict= 6		110(bits)
  
    - constant,volatile,restrict=7	111(bit) ??? improbable but
    possibile if we want
*/			

typedef enum { 
  qual_nothing  = 0,
  qual_constant = 1, 
  qual_volatile = 2, 
  qual_restrict = 4 
} qualifier;


// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

//! The base class of the types
/*! The base class of the types
  The Type classes are used to represent the type
  elements in the C/C++ grammar. They are :

  ## Standard C :

  DEFnastCODE(VOID_TYPE, void_type, 1, 0)
  DEFnastCODE(FUNCTION_TYPE, function_type, 1, 0)
  DEFnastCODE(INTEGER_TYPE, integer_type, 1, 1)
  DEFnastCODE(ENUMERAL_TYPE, enumeral_type, 1, 1)
  DEFnastCODE(REAL_TYPE, real_type, 1, 0)
  DEFnastCODE(POINTER_TYPE, pointer_type, 1, 0)
  DEFnastCODE(ARRAY_TYPE, array_type, 1, 0)
  DEFnastCODE(RECORD_TYPE, record_type, 1, 0)
  DEFnastCODE(UNION_TYPE, union_type, 1, 0)
  
  ## Standard C++ and other languages :

  DEFnastCODE(COMPLEX_TYPE, complex_type, 1, 0) 
  DEFnastCODE(LANG_TYPE, lang_type, 1, 0) 
  DEFnastCODE(BOOLEAN_TYPE, boolean_type, 1, 0) 
  DEFnastCODE(REFERENCE_TYPE, reference_type, 1, 0) 
  DEFnastCODE(METHOD_TYPE, method_type, 1, 0) 
  DEFnastCODE(CHAR_TYPE, char_type, 1, 0) 
  DEFnastCODE(FILE_TYPE, file_type, 1, 0) 
  DEFnastCODE(QUAL_UNION_TYPE, qual_union_type, 1, 0) 
  DEFnastCODE(SET_TYPE, set_type, 1, 0) 
  DEFnastCODE(VECTOR_TYPE, vector_type, 1, 0) 
  DEFnastCODE(TYPENAME_TYPE, typename_type, 1, 0) 
  DEFnastCODE(TYPEOF_TYPE, typeof_type, 1, 0) 
  

  All the types share the 1 attributes :

  - the_qualifier_of_the_type
  
  Moreover, we have the private attributes :

  - INTEGER_TYPE : 1 attribute
  -# signed_flag

  - ENUMERAL_TYPE : 1 attribute
  -# signed_flag

  \note Only the C element are good defined.
*/  
class type_n : public nast_node {

 private:

  //*** Attributes

  //! The qualifier of the type
  /*! The qualifier of the type
    
    The value is one of the enumeration qualifier.
  */
  int       qlf;	

 public:
  //! Constructor
  /*! Constructor */
  type_n() : 
    qlf(qual_nothing) { return; }
  
  //! Constructor
  /*! Constructor */
  type_n(qualifier q) : 
    qlf(q) { return; } 

  //! Destructor
  /*! Destructor */
  ~type_n() { }

  //*** Members

  //! Set the  qualifier status : it is constant
  /*! Set the  qualifier status : it is constant */
  void setConstant(void);

  //! Set the  qualifier status : it is volatile
  /*! Set the  qualifier status : it is volatile */
  void setVolatile(void);

  //! Set the  qualifier status : it is restrict
  /*! Set the  qualifier status : it is restrict */
  void setRestrict(void);


  //! Pool if the  is constant
  /*! Pool if the  is constant

    \return True if it is constant
    false otherwise.
  */
  bool isConstant(void);

  //! Pool if the  is volatile
  /*! Pool if the  is volatile

    \return True if it is volatile
    false otherwise.
  */
  bool isVolatile(void);

  //! Pool if the  is restrict
  /*! Pool if the  is restrict

    \return True if it is restrict
    false otherwise.
  */
  bool isRestrict(void);
  
};



//! The class for the void type
/*! The class for the void type 
  
  This image shows the possibile output edges.

  \image html void_type.gif

*/
class void_type_n : public type_n {
  
  // NO ATTRIBUTES
  
 public:
  //! Constructor
  /*! Constructor */
  void_type_n() : 
    type_n(qual_nothing) { return; }
  
  //! Destructor
  /*! Destructor */
  ~void_type_n() { }

  //*** Member
  
  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);
};




//! The class for the integer type
/*! The class for the integer type 
  
  The types :
 
  - int
  - signed int
  - undigned int
  - short
  - signed short
  - undigned short
  - long
  - signed long
  - undigned long
  - char
  - signed char
  - undigned char

  - long long (ANSI ??)

  are represented by this class.

  This image shows the possibile output edges.

  \image html integer_type.gif
*/
class integer_type_n : public type_n {

 private:

  //*** Attributes

  //! Flag for the signed status
  /*! Flag for the signed status 
    
    True if it is signed
    false otherwise.
  */
  bool		sign;	 

 public:
  //! Constructor
  /*! Constructor */
  integer_type_n() : 
    type_n(qual_nothing), sign(true) { return; }
  
  //! Destructor
  /*! Destructor */
  ~integer_type_n() { }
  
  //*** Members

  //! Set the  signed status : it is signed
  /*! Set the  signed status : it is signed */
  void setSigned(void);

  //! Set the  signed status : it is unsigned
  /*! Set the  signed status : it is unsigned */
  void setUnsigned(void);

  //! Pool if the  is signed
  /*! Pool if the  is signed

    \return True if it is signed
    false otherwise.
  */
  bool isSigned(void);

  //! Pool if the  is unsigned
  /*! Pool if the  is unsigned

    \return True if it is unsigned
    false otherwise.
  */
  bool isUnsigned(void);

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);
};



//! The class for the enumeral type
/*! The class for the enumeral type 

  The enumeral type definition like :

  <b>weekday<b> { monday, tuesday, wednsday, thursday, freday, saturday, sunday }
  
  are represented by this class.

  This image shows the possibile output edges.

  \image html enumeral_type.gif

*/
class enumeral_type_n : public type_n {

 private:

  //*** Attributes

  //! Flag for the signed status
  /*! Flag for the signed status 
    
    True if it is signed
    false otherwise.
  */
  bool		sign;	 

 public:
  //! Constructor
  /*! Constructor */
  enumeral_type_n() : 
    type_n(qual_nothing), sign(true) { return; }
  
  //! Destructor
  /*! Destructor */
  ~enumeral_type_n() { }
  
  //*** Members

  //! Set the  signed status : it is signed
  /*! Set the  signed status : it is signed */
  void setSigned(void);

  //! Set the  signed status : it is unsigned
  /*! Set the  signed status : it is unsigned */
  void setUnsigned(void);

  //! Pool if the  is signed
  /*! Pool if the  is signed

    \return True if it is signed
    false otherwise.
  */
  bool isSigned(void);

  //! Pool if the  is unsigned
  /*! Pool if the  is unsigned

    \return True if it is unsigned
    false otherwise.
  */
  bool isUnsigned(void);

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);
};





//! The class for the real type
/*! The class for the real type 

  The types :
 
  - float
  - double
  - long double

  are represented by this class.

  This image shows the possibile output edges.

  \image html real_type.gif
*/
class real_type_n : public type_n {
  
  // NO ATTRIBUTES
  
 public:
  //! Constructor
  /*! Constructor */
  real_type_n() : 
    type_n(qual_nothing) { return; }
  
  //! Destructor
  /*! Destructor */
  ~real_type_n() { }

  //*** Member
  
  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);
};



//! The class for the array type
/*! The class for the array type 

  The array types like :
 
  int v[10];

  are represented by this class.

  This image shows the possibile output edges.

  \image html array_type.gif

*/
class array_type_n : public type_n {
  
  // NO ATTRIBUTES
  
 public:
  //! Constructor
  /*! Constructor */
  array_type_n() : 
    type_n(qual_nothing) { return; }
  
  //! Destructor
  /*! Destructor */
  ~array_type_n() { }

  //*** Member
  
  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);
};



//! The class for the record type
/*! The class for the record type 

  The struct types like :
 
  struct S {
     int i;
     register float f;
     tree *t;
     double d[10];
  }

  are represented by this class.

  This image shows the possibile output edges.

  \image html record_type.gif

  \note In C++ this class also is used to represent a class type.

*/
class record_type_n : public type_n {
  
  // NO ATTRIBUTES
  
 public:
  //! Constructor
  /*! Constructor */
  record_type_n() : 
    type_n(qual_nothing) { return; }
  
  //! Destructor
  /*! Destructor */
  ~record_type_n() { }
  
  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);
};



//! The class for the union type
/*! The class for the union type 

  The union's types like :
 
  union U {
     int i;
     register float f;
     tree *t;
     double d[10];
  }

  are represented by this class.

  This image shows the possibile output edges.

  \image html union_type.gif

*/
class union_type_n : public type_n {
  
  // NO ATTRIBUTES
  
 public:
  //! Constructor
  /*! Constructor */
  union_type_n() : 
    type_n(qual_nothing) { return; }
  
  //! Destructor
  /*! Destructor */
  ~union_type_n() { }

  //*** Member
  
  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);
};


//! The class for the pointer type
/*! The class for the pointer type 

  The pointer's types like :

  tree *t;

  are represented by this class.

  This image shows the possibile output edges.

  \image html pointer_type.gif

*/
class pointer_type_n : public type_n {
  
  // NO ATTRIBUTES
  
 public:
  //! Constructor
  /*! Constructor */
  pointer_type_n() : 
    type_n(qual_nothing) { return; }
  
  //! Destructor
  /*! Destructor */
  ~pointer_type_n() { }

  //*** Member
  
  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);
};



//! The class for the function's type
/*! The class for the function's type 

  The types of the function like :

  long foo(int i, register float f, tree *t, double d[10])
 
  are represented by this class.

  This image shows the possibile output edges.

  \image html function_type.gif

  \note the function node type doesn't have qualifiers !
 */
class function_type_n : public type_n {
  
  // NO ATTRIBUTES
  
 public:
  //! Constructor
  /*! Constructor */
  function_type_n() : 
    type_n(qual_nothing) { return; }
  
  //! Destructor
  /*! Destructor */
  ~function_type_n() { }

  //*** Member
  
  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);
};



//! The class for the other type
/*! The class for the other type */
class othr_type_n : public type_n {
  
  // NO ATTRIBUTES
  
 public:
  //! Constructor
  /*! Constructor */
  othr_type_n() : 
    type_n(qual_nothing) { return; }
  
  //! Destructor
  /*! Destructor */
  ~othr_type_n() { }

  //*** Member
  
  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);
};


#endif











