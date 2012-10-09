/***************************************************************************
			   declData.h  -  description
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

#ifndef _DECL_DATA_H
#define _DECL_DATA_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "data/dataObj.h"

#include "nast/nast_node.h"

#include <string>

// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

//! This class holds informations about a generic declarations
/*! 
  Each declaration has :
  
  - a nast_code : is variable ? is typedef ? is enumeral constant ? ...
  - a name : variable's name, typedef's alias, enumeral constant's name, ...
  - a type : variable's type, typedef's type, enumeral constant's type, ...
  - a extra type : is constant ? is volatile ? is restrict ?
  - a number of line in the source file !
  - a number of * associated with the type
  - a number of [] associated with the type

  The name, the type, the extra type datas are string... so
  we can use it for aoutput, or pattern matching (in C++ ?).

  \note This class is used to hold information 
  about var_decl, type_decl, const_decl, parm_decl, ... but
  it isn't  used to hold information about the
  function declaration !
*/
class declData : public dataObj
{

 private:

  //---- Attributes

  //! The pointer to the declaration node into the NAST
  nast_node* nodep;

  //! The name of the position : function or file
  /*!
    A declaration can be placed into a function (one of the
    block delimited by { }) or in global scope of the 
    translation unit.
  */
  string posName;

  //! The name of the declaration 
  /*!
    In var_decl the name is the name of the variable.
    In type_decl the name is the name of the new alias type.
    In const_decl the name is the name of the enumeral constant.
  */
  string name;

  //! The type of the declaration 
  string type;

  //! The extra information about the type : qualifiers, ...
  string typeExtra;

  //! The number of line in the source file 
  long line;

  //! The number of * (for pointer)
  int starNumber;

  //! The number of [] (for array)
  int squareNumber;

 public:
  //! Constructor
  declData() { nodep = 0;}
  
  //! Destructor
  ~declData() { nodep = 0; }


  //---- Members

  //---- SET

  //! Set the node to the nast_node
  /*!
    \param nodep The pointer to the nast_node
  */
  void setNodeP(nast_node *nodep) 
    { this->nodep = nodep; }

  //! Set the position name
  /*!
    \param posName The position of the declaration in the translation unit
  */
  void setPosName(string posName) 
    { this->posName = posName; }

  //! Set the name
  /*!
    \param name The name of the declaration
  */
  void setName(string name) 
    { this->name = name; }

  //! Set the type
  /*!
    \param type The type of the declaration
  */
  void setType(string type) 
    { this->type = type; }

  //! Set the extra type
  /*!
    \param typeExtra Th extra type information
  */
  void setTypeExtra(string typeExtra) 
    { this->typeExtra = typeExtra; }

  //! Set the line
  /*!
    \param line The line in the source file
  */
  void setLine(long line) 
    { this->line = line; }

  //! Set the star number
  /*!
    \param starNumebr The number of star present in the type
  */
  void setStarNumber(int starNumber) 
    { this->starNumber = starNumber; }

  //! Set the square number
  /*!
    \param squareNumebr The number of square present in the type
  */
  void setSquareNumber(int squareNumber) 
    { this->squareNumber = squareNumber; }

  //---- GET

  //! Get the pointer to node
  /*!
    \return The pointer to the nast_node
  */
  nast_node* getNodeP(void) 
    { return this->nodep; }

  //! Get the code of the declration
  /*!
    \return The code of the declaration : var_decl, type_decl, const_decl, ...
  */
  nast_code getCode(void)
    { 
      if (nodep)
	return this->nodep->getCode(); 
      else 
	return FIRST_NAST_CODE;
    }

  //! Get the position name
  /*!
    \return The position in the translation unit
  */
  string getPosName(void)
    { return this->posName; }

  //! Get the name
  /*!
    \return The name of the declaration
  */
  string getName(void)
    { return this->name; }

  //! Get the type
  /*!
    \return The type of the declaration
  */
  string getType(void)
    { return this->type; }

  //! Get the extra type
  /*!
    \return The extra type information
  */
  string getTypeExtra(void)
    { return this->typeExtra; }

  //! Get the line in the source
  /*!
    \return The line in the source file
  */
  long getLine(void)
    { return this->line; }

  //! Get the star number
  /*!
    \return The number of star of the type
  */
  int getStarNumber(void)
    { return this->starNumber; }

  //! Get the square number
  /*!
    \return The number of square of the type
  */
  int getSquareNumber(void)
    { return this->squareNumber; }

};


// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

//! The Class for the comparison between 2 objects declData
/*! 
  This class is used to compare 2 objects declData.
  
  The comparation between 2 declData is made used the attribute 
  name.
  Given the 2 object declData dd1 and dd2 then :

  - dd1 <  dd2 if only if dd1::name <  dd2::name
  - dd1 == dd2 if only if dd1::name == dd2::name
  - dd1 >  dd2 if only if dd1::name >  dd2::name
  
  Remember : the type of the attribute declData::name 
  is string.

  \note This class overload the operator ().
*/
class declData_Cmp {

 public:

  //! The member for the comparison
  /*!
    Overload the operator ().

    \param dd1 the first declData
    \param dd2 the second declData

    \return True if dd1::name < dd2::name,
    false otherwise.
  */
  bool operator()(declData& dd1, declData& dd2);

  //! The member for the comparison
  /*!
    Overload the operator ().

    \param dd1 the first declData
    \param dd2 the second declData

    \return True if dd1::name < dd2::name,
    false otherwise.
    
    \note This method differs from the previous in the type 
    of the parameters. Now we have pointer, in the previous
    method we have reference.
  */
  bool operator()(declData* dd1, declData* dd2);

};

#endif
