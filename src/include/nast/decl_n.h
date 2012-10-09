/***************************************************************************
			   decl_n.h  -  description
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


/*! \file
   \brief The sub class hierarcy for the declarations

   The sub class hierarcy for the declarations.
   
   In this file we define the classes for the declaration.
   The base class is decl_n (child of the class nast_node).
   The derived classes are the classes for the declarations :
   const_decl_n, field_decl_n, function_decl_n, label_decl_n,
   othr_decl_n, parm_decl_n, result_decl_n, type_decl_n,
   var_decl_n.
*/


#ifndef _DECL_N_H
#define _DECL_N_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "nast/nast_node.h"

#include <string>

// ---------------------------------------------------------------------------
//  ENUMERATION
// ---------------------------------------------------------------------------

//! The enumeration for the two C memory class : static, extern 
/*! The enumeration for the two C memory class : static, extern  

  These enumeral value are used by the class function_decl_n to 
  keep track if the function declaration has static or extern
  memory class.
 */
typedef enum { mc_static, mc_extern } memory_class;


// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

//! The base class of the declarations
/*! The base class of the declarations

  The Declaration classes are used to represent the declaration
  element in the C/C++ grammar. They are :

  ## Standard C :

  DEFnastCODE(TYPE_DECL, type_decl, 3, 0)
  DEFnastCODE(FUNCTION_DECL, function_decl, 3, 2)
  DEFnastCODE(PARM_DECL, parm_decl, 3, 1)
  DEFnastCODE(VAR_DECL, var_decl, 3, 1)
  DEFnastCODE(FIELD_DECL, field_decl, 3, 1)
  DEFnastCODE(CONST_DECL, const_decl, 3, 0)
  DEFnastCODE(LABEL_DECL, label_decl, 3, 0)
  DEFnastCODE(RESULT_DECL, result_decl, 3, 0)

  ## Special C++ :

  DEFnastCODE(NAMESPACE_DECL, namespace_decl, 3, 0) 
  DEFnastCODE(TEMPLATE_DECL, template_decl, 3, 0) 
  DEFnastCODE(USING_DECL, using_decl, 3, 0) 


  All the declarations share the 3 attributes :
  
  - artificial_flag (holds if the element is compiler generated)
  - line_in_the_source_file 
  - name_of_the_source_file
  
  Moreover, we have the private attributes :
  
  - FUNCTION_DECL : 2 attributes
    -# the_memory_class : static or extern
    -# the_linkage_definition : definde or undefined
  
  - PARM_DECL : 1 attribute
    -# register_flag : is register defined ?
  
  - VAR_DECL : 1 attribute
    -# register_flag : is register defined ?
  
  - FIELD_DECL : 1 attribute
    -# bitfield_flag : is the field a bit field ?

  \note In this implementation only the C element are good defined.
*/  
class decl_n : public nast_node {

 private:

  //**** Attributes

  //! The name of the source file
  /*! The name of the source file */
  string 	sourceF;	

  //! The position in the source file
  /*! The position in the source file */
  long		lineF;		
  
  //! Flag for the artificial status
  /*! Flag for the artificial status 
    
    True if it is compiler generated
    false otherwise.

    During the compiltaion process the compiler may
    add some declarations. These declarations are added
    to improve the translation and the performance of the
    final object (assembler) code.
  */
  bool		artificial;	

public:	
  //! Constructor
  /*! Constructor */
  decl_n () :
    sourceF(""), lineF(0), artificial(false) { return; }

  //! Constructor
  /*! Constructor */
  decl_n (string s, long l, bool a) :
    sourceF(s), lineF(l), artificial(a) { return; }
 
  //! Destructor
  /*! Destructor */
  ~decl_n () { }

  //**** Members
  
  //! Set the declaration artificial status : it is artificial
  /*! Set the declaration artificial status : it is artificial */
  void setArtificial(void); 

  //! Set the declaration artificial status : it isn't artificial
  /*! Set the declaration artificial status : it isn't artificial */
  void unsetArtificial(void);

  //! Pool if the declaration is artificial
  /*! Pool if the declaration is artificial

    \return True if it is compiler generated
    false otherwise.
  */
  bool isArtificial(void);
  
  //! Set the number of line
  /*! Set the number of line
    
    \param l the number of the line in the source file
  */
  void setLine(long l);

  //! Get the number of line
  /*! Get the number of line
    
    \return The number of line
  */
  long getLine(void);

  //! Set the source
  /*! Set the source
    
    \param l the name of the source file
  */
  void setSource(string s);

  //! Get the source
  /*! Get the source
    
    \return l the name of the source file
  */
  string getSource(void);
  
};




//! The class for the variable declaration
/*! The class for the variable declaration
  
  The variable's declarations like :

  int i;
  register float f;
  tree *t;
  double d[10];

  are represented by this class.
  
  This image shows the possibile output edges.

  \image html var_decl.gif
*/
class var_decl_n : public decl_n {

 private:
  //**** Attributes

  //! Flag for the register status
  /*! Flag for the register status 
    
    True if it is register qualified
    false otherwise.
  */
  bool      reg;   

 public:
  //! Constructor
  /*! Constructor */
  var_decl_n() : 
    decl_n("", 0, false), reg(false) { return; }

  //! Destructor
  /*! Destructor */
  ~var_decl_n() { } 
  
  //**** Members
  
  //! Set the declaration register status : it is register qualified
  /*! Set the declaration register status : it is register qualified*/
  void setRegister(void);

  //! Set the declaration register status : it isn't register qualified
  /*! Set the declaration register status : it isn't register qualified*/
  void unsetRegister(void);

  //! Pool if the declaration is register
  /*! Pool if the declaration is register

    \return True if it is register qualified
    false otherwise.
  */
  bool isRegister(void);

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);

};




//! The class for the function's parameter declaration
/*! The class for the function's parameter declaration
  
  The  function's parameter declaration like :

  void foo(int i, register float f, tree *t, double d[10])
  
  are represented by this class.

  This image shows the possibile output edges.

  \image html parm_decl.gif
*/
class parm_decl_n : public decl_n {

 private:

  //**** Attributes 

  //! Flag for the register status
  /*! Flag for the register status 
    
    True if it is register qualified
    false otherwise.
  */
  bool      reg;   

 public:
  //! Constructor
  /*! Constructor */
  parm_decl_n() :
    decl_n("", 0, false), reg(false) { return; }

  //! Destructor
  /*! Destructor */
  ~parm_decl_n() { }

  //**** Members
  
  //! Set the declaration register status : it is register qualified
  /*! Set the declaration register status : it is register qualified*/
  void setRegister(void);

  //! Set the declaration register status : it isn't register qualified
  /*! Set the declaration register status : it isn't register qualified*/
  void unsetRegister(void);

  //! Pool if the declaration is register
  /*! Pool if the declaration is register

    \return True if it is register qualified
    false otherwise.
  */
  bool isRegister(void);

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);

};




//! The class for the constant declaration of function's parameter or variable
/*! The class for the constant declaration of function's parameter or variable

  These nodes are used to represent enumeration constants.

  This image shows the possibile output edges.

  \image html const_decl.gif
*/
class const_decl_n : public decl_n {

  // NO ATTRIBUTES
 
 public:
  //! Constructor
  /*! Constructor */
  const_decl_n() :
    decl_n("", 0, false) { return; }

  //! Destructor
  /*! Destructor */
  ~const_decl_n() { }
  
  //**** Member
 
  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);

};





//! The class for the value returned by a function
/*! The class for the value returned by a function

  This image shows the possibile output edges.

  \image html result_decl.gif
 */
class result_decl_n : public decl_n {
 
  // NO ATTRIBUTES
  
 public:
  //! Constructor
  /*! Constructor */
  result_decl_n() :
    decl_n("", 0, false) { return; }

  //! Destructor
  /*! Destructor */
  ~result_decl_n() { }
  
  //**** Member
 
  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);

};





//! The class for the fields of a C struct or C union (in C++ it is extened...)
/*! The class for the fields of a C struct or C union (in C++ it is extened...)

  The field's declrations like :

  struct S {
     int i;
     register float f;
     tree *t;
     double d[10];
  }

  are represented by this class.

  This image shows the possibile output edges.

  \image html field_decl.gif

  \note In the C++ the meaning is diferrent. This declaration can be used 
  also for the methods.

 */
class field_decl_n : public decl_n {

 private:

  //**** Attributes
 
  //! Flag for the bitfield status
  /*! Flag for the bitfield status 
    
    True if it is bitfield
    false otherwise.
  */
  bool     bitfield; 
  
 public:

  //! Constructor
  /*! Constructor */
  field_decl_n() :
    decl_n("", 0, false), bitfield(false) { return; }

  //! Destructor
  /*! Destructor */
  ~field_decl_n() { }
  
  //**** Members

  //! Set the declaration bitfield status : it is bitfield
  /*! Set the declaration bitfield status : it is bitfield */
  void setBitfield(void);

  //! Set the declaration bitfield status : it isn't bitfield
  /*! Set the declaration bitfield status : it isn't bitfield */
  void unsetBitfield(void);

  //! Pool if the is bitfield
  /*! Pool if the is bitfield

    \return True if it is bitfield
    false otherwise.
  */
  bool isBitfield(void);

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);
};



//! The class for the C typedef
/*! The class for the C typedef

  The typedef's declarations like :

  <b>
  typedef long index;
  typedef struct tree_node *tree;
  </b>

  are represented by this class.
  
  This image shows the possibile output edges.

  \image html type_decl.gif
 */
class type_decl_n : public decl_n {
 
  // NO ATTRIBUTES
  
 public:
  //! Constructor
  /*! Constructor */
  type_decl_n() :
    decl_n("", 0, false) { return; }

  //! Destructor
  /*! Destructor */
  ~type_decl_n() { }

  //**** Member
  
  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);
};



//! The class for the label declaration in function bodies
/*! The class for the label declaration in function bodies

  The label's declarations like :

  <b>foo</b> i++;
      j *= i;
      goto foo;
  
  are represented by this class.
  
  This image shows the possibile output edges.

  \image html label_decl.gif
 
  \note  this declaration class doesn't have next edge
*/
class label_decl_n : public decl_n {
  
  // NO ATTRIBUTES

 public:	
  //! Constructor
  /*! Constructor */
  label_decl_n() :
    decl_n("", 0, false) { return; }

  //! Destructor
  /*! Destructor */
  ~label_decl_n() { }
  
  //**** Member

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);
};




//! The class for the function declaration
/*! The class for the fubction declaration

  The function declaration like :

  long foo(int i, register float f, tree *t, double d[10])
  
  This image shows the possibile output edges.

  \image html function_decl.gif
*/
class function_decl_n : public decl_n {

 private:

  //**** Attributes

  //! The memory class : static or extern
  /*! The memory class : static or extern */
  memory_class	mclass;


  //! Flag for the undefined status
  /*! Flag for the undefined status 
    
    True if it is undefined (no definition in the translation unit)
    false otherwise.
  */
  bool          undefined;
                          
 public:	
  //! Constructor
  /*! Constructor */
  function_decl_n() :
    decl_n("", 0, false), mclass(mc_static), undefined(false) { return; }

  //! Destructor
  /*! Destructor */
  ~function_decl_n() { }
  
  //**** Members

  //! Set the memory class : is extern
  //! Set the memory class : is extern
  void setExtern(void);

  //! Set the memory class : is static
  //! Set the memory class : is static
  void setStatic(void);

  //! Pool if the declaration is extern
  /*! Pool if the declaration is extern

    \return True if it is extern 
    false otherwise.
  */
  bool isExtern(void);

  //! Pool if the declaration is static
  /*! Pool if the declaration is static

    \return True if it is static 
    false otherwise.
  */
  bool isStatic(void);


  //! Set the declaration undefined status : it is undefined 
  /*! Set the declaration undefined status : it is undefined */
  void setUndefined(void);

  //! Set the declaration undefined status : it isn't undefined 
  /*! Set the declaration undefined status : it isn't undefined */
  void unsetUndefined(void);

  //! Pool if the declaration is undefined
  /*! Pool if the declaration is undefined

    \return True if it is undefined 
    false otherwise.
  */
  bool isUndefined(void);

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);
};



//! The class for the other declarations
/*! The class for the other declarations
 */
class othr_decl_n : public decl_n {
  
  // NO ATTRIBUTES

 public:	
  //! Constructor
  /*! Constructor */
  othr_decl_n() :
    decl_n("", 0, false) { return; }
  
  //! Destructor
  /*! Destructor */
  ~othr_decl_n() { }

  //**** Member

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);

};


#endif







