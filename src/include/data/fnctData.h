/***************************************************************************
			   fnctData.h  -  description
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

#ifndef _FNCT_DATA_H
#define _FNCT_DATA_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "data/typeDef.h"
#include "data/dataObj.h"
#include "data/parmData.h"

#include "nast/nast_node.h"


#include <list>
#include <string>
#include <algorithm>

// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

//! This class holds informations about the function's declarations
/*! 
  Each function declaration has :

  - a name 
  - a type returned
  - a list of parameters
  - the name of the source where the function is declarated
  - a pointer to the body, if there's one

  This class define also the function for the acces to
  the parameters list. This access can happen by
  visiting the element one for time, from the first
  to the last. The protocol for the visit is :
  
  \code
  fnctData    fData;
  parmData    *pData;
  
  if (fData.hasParm()) {
    pData = fData.firstParm();
    use pData;
    while (fData.hasNextParm()) {
      pData = fData.nextParm;
      use pData;
    }
  }
  \endcode

  \note  This class can recognize if the function stored 
  belong to the C standard library.
*/
class fnctData : public dataObj
{

 private:
  
  //---- Attributes
  
  //! The pointer to the function_decl node into the NAST
  nast_node *nodep;
  
  //! The name of the source where the function is declarated
  /*!
    The value can be :
    - <internal> for the function added by the compiler
    - a name of source file like foo.c
  */
  string source;

  //! The name of the function 
  string name;

  //! The type returned by the function
  string type;

  //! The parameters list
  parmList parameters;
  
  //! The map of the c standard function
  /*!    
    The second value is unused !
    We use a map because the acces is faster than in the list !!

    \note It's a static member
  */
  static map<string, int> cStdFnct;

  //---- Access to the parameters list

  //! The parameters list iterator
  parmListIterator p_parameters;

  //! The ordinal position of p_parameters in the list 
  int p_pos;

 public:
  //! Constructor
  fnctData();
  
  //! Destructor
  ~fnctData() { }

  //---- Members


  //---- SET

  //! Set the pointer to the function_decl nast_node
  /*!
    \param nodep The pointer to nast_node
  */
  void setNodeP(nast_node *nodep) 
    { this->nodep = nodep; }

  //! Set the name of the source file (can have the value <internal>)
  /*!
    \param source The name of the source
  */
  void setSource(string source) 
    { this->source = source; }

  //! Set the name of the function
  /*!
    \param name The name of the function
  */
  void setName(string name) 
    { this->name = name; }

  //! Set the type returned by the function
  /*!
    \param type The type returned by the function
  */
  void setType(string type) 
    { this->type = type; }

  //! Add a parameter
  /*!
    \param parm The pointer to the parmData object that represent the parameter
  */
  void addParm(parmData *parm);


  //---- GET

  //! Get the pointer to the function_decl nast_node
  /*!
    \return The pointer to the nast node
  */
  nast_node* getNodeP(void) 
    { return this->nodep; }

  //! Get the name of the source
  /*!
    \return The name of the source file
  */
  string getSource(void) 
    { return this->source; }

  //! Get the name of the function
  /*!
    \return  The name of the function
  */
  string getName(void) 
    { return this->name; }

  //! Get the type
  /*!
    \return The type returned by the function
  */
  string getType(void) 
    { return this->type; }

  //! Get the body's pointer
  /*!
    \return The pointer to the body of the function
  */
  nast_node* getBody(void)
    { 
      if ( (nodep) && (nodep->hasEdgeName(BODY_EDGE)) )
	return nodep->edgeName(BODY_EDGE); 
      else
	return 0;
    }
  
  //---- PARAMETERS list access ...

  //! Get the first parameter
  /*!
    Before to use this method it is necessary to check if the
    function has parameters (almost one)

    \return The pointer to the first parameter,
    or 0 if it doesn't
  */
  parmData *firstParm(void);

  //! Get the next parameter
  /*!
    Before to use this method it is necessary to check if the
    function has next parameters (after the last got)

    \return The pointer to the next parameter in the list
    or 0 if it doesn't
  */
  parmData *nextParm(void);

  //! Get the parameters list
  /*!
    \return The reference to the parameters list
  */
  parmList &getParmList(void) {
    return this->parameters;
  }

  //--- HAS ... ?

  //! Ask if the function has a body
  /*!
    \return True if the function has a body,
    false otherwise.
  */
  bool hasBody(void) {
    return ( (nodep) && (nodep->hasEdgeName(BODY_EDGE)) );
  }

  //! Ask if the function has parameters
  /*!
    \return True if the function has parameters,
    false otherwise.
  */
  bool hasParm(void) {
    return (parameters.size() > 0);
  }

  //! Ask if the function has next parameters
  /*!
    Used during the access to the list of parameters.

    \return True if the function has next parameters,
    false otherwise.
   */
  bool hasNextParm(void) {
    int num_parm;
    return ( ((num_parm = parameters.size()) > 0) 
	     && (p_pos < num_parm));
  }

  //--- IS ... ?

  //! Ask if the function is in the C standard library
  /*!
    \return True if the function  is in the C standard library,
    false otherwise.
   */
  bool isStdC(void);


  //--- Other 
  
  //! Get the number of parameters
  long numParm(void) {
    return (parameters.size());
  }
    
};


// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------


//! The Class for the comparison between 2 objects fnctData
/*! 
  This class is used to compare 2 objects fnctData.
  
  The comparation between 2 fnctData is made used the attribute 
  fnctName.
  Given the 2 object fnctData fd1 nad fd2 then :

  - fd1 <  fd2 if only if fd1::fnctName <  fd2::fnctName
  - fd1 == fd2 if only if fd1::fnctName == fd2::fnctName
  - fd1 >  fd2 if only if fd1::fnctName >  fd2::fnctName
  
  Rembember : the type of the attribute fnctData::fnctName 
  is string.

  \note The follow class overload the operator ().
*/
class fnctData_Cmp {

 public:

  //! The member for the comparison
  /*!
    Overload the operator ().

    \param fd1 the first fnctData
    \param fd2 the second fnctData

    \return True if fd1::fnctName < fd2::fnctName,
    false otherwise.
  */
  bool operator()(fnctData& fd1, fnctData& fd2);

  //! The member for the comparison
  /*!
    Overload the operator ().

    \param fd1 the first fnctData
    \param fd2 the second fnctData

    \return True if fd1::fnctName < fd2::fnctName,
    false otherwise.
    
    \note This method differs from the previous in the type 
    of the parameters. Now we have pointer, in the previous
    method we have reference.
  */
  bool operator()(fnctData* fd1, fnctData* fd2);

};

#endif

