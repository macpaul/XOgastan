/***************************************************************************
			   stmt_n.h  -  description
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



#ifndef _STMT_N_H
#define _STMT_N_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "nast/nast_node.h"


// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

//! The base class of the statements
/*! The base class of the declartions
  The Statement classes are used to represent the statement
  element in the C/C++ grammar. They are :

  ## Standard C :

  DEFnastCODE(BREAK_STMT, break_stmt, 1, 0)
  DEFnastCODE(CONTINUE_STMT, continue_stmt, 1, 0)
  DEFnastCODE(COMPOUND_STMT, compound_stmt, 1, 0)
  DEFnastCODE(DECL_STMT, decl_stmt, 1, 0)
  DEFnastCODE(EXPR_STMT, expr_stmt, 1, 0)
  DEFnastCODE(DO_STMT, do_stmt, 1, 0)
  DEFnastCODE(WHILE_STMT, while_stmt, 1, 0)
  DEFnastCODE(FOR_STMT, for_stmt, 1, 0)
  DEFnastCODE(GOTO_STMT, goto_stmt, 1, 0)
  DEFnastCODE(LABEL_STMT, label_stmt, 1, 0)
  DEFnastCODE(IF_STMT, if_stmt, 1, 0)
  DEFnastCODE(SWITCH_STMT, switch_stmt, 1, 0)
  DEFnastCODE(SCOPE_STMT, scope_stmt, 1, 2)
  DEFnastCODE(RETURN_STMT, return_stmt, 1, 0)
  DEFnastCODE(ASM_STMT, asm_stmt, 1, 0)

  ## Special C++ :
  
  DEFnastCODE(START_CATCH_STMT, start_catch_stmt, 1, 0) 
  DEFnastCODE(USING_STMT, using_stmt, 1, 0) 
  DEFnastCODE(OVERLOAD, overload, 1, 0) 
  DEFnastCODE(TRY_BLOCK, try_block, 1, 0) 
  DEFnastCODE(EH_SPEC_BLOCK, eh_spec_block, 1, 0)  
  DEFnastCODE(CLEANUP_STMT, cleanup_stmt, 1, 0) 
  DEFnastCODE(CTOR_STMT, ctor_stmt, 1, 0) 
  DEFnastCODE(HANDLER, handler, 1, 0) 
  DEFnastCODE(MUST_NOT_THROW_EXPR, must_not_throw_expr, 0, 0) 
  DEFnastCODE(SUBOBJECT, subobject, 1, 0) 
  
  All the statements share the 1 attributes :
 
  - line_in_the_source_file
  
  Moreover, we have the private attributes :
  
  - SCOPE_STMT : 2 attributes 
    -# point_flag
    -# variables_flag
  
*/
class stmt_n : public nast_node {

 private:

  //*** Attributes

  //! The line in the source file
  /*! The line in the source file */
  long 	lineF;	    

 public:
  //! Constructor
  /*! Constructor */
  stmt_n() : 
    lineF(0) { return; }

  //! Constructor
  /*! Constructor */
  stmt_n(long l) :
    lineF(l) { return; }
	
  //! Destructor
  /*! Destructor */
  ~stmt_n() { }

  //*** Members

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

};



//! The class for the compound statement
/*! The class for the compound statement 

  Used to represent a brace-enclosed block.
  
  This image shows the possibile output edges.
  
  \image html compound_stmt.gif
*/
class compound_stmt_n : public stmt_n {

  // NO ATTRIBUTES

 public:
  //! Constructor
  /*! Constructor */
  compound_stmt_n() : 
    stmt_n(0){ return; }

  //! Destructor
  /*! Destructor */
  ~compound_stmt_n() { }
  
  //*** Member

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);

};


//! The class for the break statement
/*! The class for the break statement 

  Used to represent the statement :
      break;
  
  This image shows the possibile output edges.
  
  \image html break_stmt.gif

*/
class break_stmt_n : public stmt_n {

  // NO ATTRIBUTES

 public:
  //! Constructor
  /*! Constructor */
  break_stmt_n() : 
    stmt_n(0){ return; }

  //! Destructor
  /*! Destructor */
  ~break_stmt_n() { }
  
  //*** Member

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);

};



//! The class for the continue statement
/*! The class for the continue statement 

  Used to represent the statement :
      continue;
  
  This image shows the possibile output edges.
  
  \image html continue_stmt.gif
*/
class continue_stmt_n : public stmt_n {

  // NO ATTRIBUTES

 public:
  //! Constructor
  /*! Constructor */
  continue_stmt_n() : 
    stmt_n(0){ return; }

  //! Destructor
  /*! Destructor */
  ~continue_stmt_n() { }
  
  //*** Member

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);

};



//! The class for the scope statement
/*! The class for the scope statement 

  Used to represent the the beginning or end of a scope.

  This image shows the possibile output edges.
  
  \image html scope_stmt.gif
*/
class scope_stmt_n : public stmt_n {

 private:

  //*** Attributes
  
  //! Flag for the begin/end status
  /*! Flag for the begin/end status 
    
    True if it is begin point of a scope
    false otherwise.
  */
  bool 	begin_point;  

  //! Flag for the variables status
  /*! Flag for the variables status 
    
    True if it has variables in the scope
    false otherwise.
  */
  bool	with_variables;    // has its variables ?


 public:
  //! Constructor
  /*! Constructor */
  scope_stmt_n() : 
    stmt_n(0), begin_point(true), with_variables(false) { return; }

  //! Destructor
  /*! Destructor */
  ~scope_stmt_n() { }

	
  //*** Members

  //! Set the variable status : it has variable
  /*! Set the variable status : it has variable */
  void setVariables(void); 

  //! Set the variable status : it hasn't variable
  /*! Set the variable status : it hasn't variable */
  void unsetVariables(void);

  //! Pool if the  has variables
  /*! Pool if the  has variables

    \return True if it has variables in the scope
     false otherwise.
  */
  bool hasVariables(void);

  //! Set the begin/end status : it is begin point
  /*! Set the begin/end status : it is begin point */
  void setBegin(void); 

  //! Set the begin/end status : it isn't end point
  /*! Set the begin/end status : it isn't end point */
  void setEnd(void);

  //! Pool if the  is begin point
  /*! Pool if the  is begin point 

    \return    True if it is the begin point of a scope
     false otherwise.
  */
  bool isBegin(void);

  //! Pool if the  is begin point
  /*! Pool if the  is begin point 

    \return    True if it is the begin point of a scope
     false otherwise.
  */
  bool isEnd(void);
	
  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);

};



//! The class for the decl statement
/*! The class for the decl statement 

  Used to represent a local declaration like :
        int i;

  This image shows the possibile output edges.
  
  \image html decl_stmt.gif
*/
class decl_stmt_n : public stmt_n {

  // NO ATTRIBUTES

 public:
  //! Constructor
  /*! Constructor */
  decl_stmt_n() : 
    stmt_n(0){ return; }

  //! Destructor
  /*! Destructor */
  ~decl_stmt_n() { }
  
  //*** Member

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);

};


//! The class for the expr statement
/*! The class for the expr statement 

  Used to represent an expression statement like :
        i = v[j++] * h;

  This image shows the possibile output edges.
  
  \image html expr_stmt.gif
*/
class expr_stmt_n : public stmt_n {

  // NO ATTRIBUTES

 public:
  //! Constructor
  /*! Constructor */
  expr_stmt_n() : 
    stmt_n(0){ return; }

  //! Destructor
  /*! Destructor */
  ~expr_stmt_n() { }
  
  //*** Member

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);

};



//! The class for the goto statement
/*! The class for the goto statement 

  Used to represent a goto statement like :
        goto label;

  This image shows the possibile output edges.
  
  \image html goto_stmt.gif
*/
class goto_stmt_n : public stmt_n {

  // NO ATTRIBUTES

 public:
  //! Constructor
  /*! Constructor */
  goto_stmt_n() : 
    stmt_n(0){ return; }

  //! Destructor
  /*! Destructor */
  ~goto_stmt_n() { }
  
  //*** Member

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);

};



//! The class for the label statement
/*! The class for the label statement 

  Used to represent a label like :
        foo i++;
	    v[i]++;

  This image shows the possibile output edges.
  
  \image html label_stmt.gif
*/
class label_stmt_n : public stmt_n {

  // NO ATTRIBUTES

 public:
  //! Constructor
  /*! Constructor */
  label_stmt_n() : 
    stmt_n(0){ return; }

  //! Destructor
  /*! Destructor */
  ~label_stmt_n() { }
  
  //*** Member

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);

};


//! The class for the return statement
/*! The class for the return statement 

  Used to represent a return statement like :
	    return i;

  This image shows the possibile output edges.
  
  \image html return_stmt.gif
*/
class return_stmt_n : public stmt_n {

  // NO ATTRIBUTES

 public:
  //! Constructor
  /*! Constructor */
  return_stmt_n() : 
    stmt_n(0){ return; }

  //! Destructor
  /*! Destructor */
  ~return_stmt_n() { }
  
  //*** Member

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);

};



//! The class for the if statement
/*! The class for the if statement 

  Used to represent an if statement like :
	    if (i) {
	       i--
	    } else i++;

  This image shows the possibile output edges.
  
  \image html if_stmt.gif

*/
class if_stmt_n : public stmt_n {

  // NO ATTRIBUTES

 public:
  //! Constructor
  /*! Constructor */
  if_stmt_n() : 
    stmt_n(0){ return; }

  //! Destructor
  /*! Destructor */
  ~if_stmt_n() { }
  
  //*** Member

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);

};




//! The class for the switch statement
/*! The class for the switch statement 

  Used to represent a switch statement like :
	    switch (i) {
	       case 10:
	         ....
		 ....
	         break;
	       ........
	       ........
	       default:
	         ....
	    } 

  This image shows the possibile output edges.
  
  \image html switch_stmt.gif
*/
class switch_stmt_n : public stmt_n {

  // NO ATTRIBUTES

 public:
  //! Constructor
  /*! Constructor */
  switch_stmt_n() : 
    stmt_n(0){ return; }

  //! Destructor
  /*! Destructor */
  ~switch_stmt_n() { }
  
  //*** Member

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);

};


//! The class for the for statement
/*! The class for the for statement 

 Used to represent a for statement like :
	    for(i = 0; i < 10; i++) {
	       ........
	       ........
	    } 

  This image shows the possibile output edges.
  
  \image html for_stmt.gif
*/
class for_stmt_n : public stmt_n {

  // NO ATTRIBUTES

 public:
  //! Constructor
  /*! Constructor */
  for_stmt_n() : 
    stmt_n(0){ return; }

  //! Destructor
  /*! Destructor */
  ~for_stmt_n() { }
  
  //*** Member

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);

};



//! The class for the do statement
/*! The class for the do statement 

  Used to represent a for statement like :
	    do {
	       ........
	       ........
	    } while (i < 10);

  This image shows the possibile output edges.
  
  \image html do_stmt.gif
*/
class do_stmt_n : public stmt_n {

  // NO ATTRIBUTES

 public:
  //! Constructor
  /*! Constructor */
  do_stmt_n() : 
    stmt_n(0){ return; }

  //! Destructor
  /*! Destructor */
  ~do_stmt_n() { }
  
  //*** Member

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);

};



//! The class for the while statement
/*! The class for the while statement 

  Used to represent a for statement like :
	    while (i < 10) {
	       ........
	       ........
	    }

  This image shows the possibile output edges.
  
  \image html while_stmt.gif

*/
class while_stmt_n : public stmt_n {

  // NO ATTRIBUTES

 public:
  //! Constructor
  /*! Constructor */
  while_stmt_n() : 
    stmt_n(0){ return; }

  //! Destructor
  /*! Destructor */
  ~while_stmt_n() { }
  
  //*** Member

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);

};


//! The class for the asm statement
/*! The class for the asm statement 

  Used to represent a statement block of assembler code.

  This image shows the possibile output edges.
  
  \image html asm_stmt.gif

*/
class asm_stmt_n : public stmt_n {

  // NO ATTRIBUTES

 public:
  //! Constructor
  /*! Constructor */
  asm_stmt_n() : 
    stmt_n(0){ return; }

  //! Destructor
  /*! Destructor */
  ~asm_stmt_n() { }
  
  //*** Member

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);

};



//! The class for the othr statement
/*! The class for the othr statement */
class othr_stmt_n : public stmt_n {

  // NO ATTRIBUTES

 public:
  //! Constructor
  /*! Constructor */
  othr_stmt_n() : 
    stmt_n(0){ return; }

  //! Destructor
  /*! Destructor */
  ~othr_stmt_n() { }
  
  //*** Member

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);

};

#endif






  







