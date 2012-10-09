/***************************************************************************
			   exprData.h  -  description
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

#ifndef _EXPR_DATA_H
#define _EXPR_DATA_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "data/dataObj.h"
#include "data/exprNumData.h"
#include "data/varUsedData.h"
#include "data/typeDef.h"

#include "nast/nast_node.h"

#include <string>

// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

//! This class holds information about a generic expression
/*! 
  Each expression has :
  
  - a base statement : statement expression, condition of do ...
  - a number of line in the source file 
  - statistic about the operators used 
  - a list of variables used

*/
class exprData : public dataObj
{

 private:

  //---- Attributes

  //! The base statement
  nast_code  baseStmt;

  //! The number of line in the source file 
  long line;

  //! The statistic about the operators
  exprNumData  *exprStat;

  //! The list of variables used
  varUsedList  *vuL;

 public:
  //! Constructor
  exprData() { }
  
  //! Destructor
  ~exprData() { }


  //---- Members

  //---- SET

  //! Set the base statement
  /*!
    \param baseStmt The nast code of the base statement
  */
  void setPosName(nast_code baseStmt)
    { this->baseStmt = baseStmt; }

  //! Set the line
  /*!
    \param line The line in the source file
  */
  void setLine(long line) 
    { this->line = line; }

  //! Set the expr statistic
  /*!
    \param exprStat Pointer to the object exprNumData
  */
  void setExprStat(exprNumData *exprStat)
    { this->exprStat = exprStat; }

  //! Set the list of variables used
  /*!
    \param vuL Pointer to the object varUsedList
  */
  void setVarUsed(varUsedList *vuL)
    { this->vuL = vuL; }


  //---- GET

  //! Get the base statement
  /*!
    \return The nast code of the base statement
  */
  nast_code getPosName(void)
    { return this->baseStmt; }

  //! Get the line
  /*!
    \return The line in the source file
  */
  long getLine(void) 
    { return this->line; }

  //! Get the expr statistic
  /*!
    \return Pointer to the object exprNumData
  */
  exprNumData *getExprStat(void)
    { return this->exprStat; }

  //! Get the list of variables used
  /*!
    \return vuL Pointer to the object varUsedList
  */
  varUsedList *getVarUsed(void)
    { return this->vuL; }


};


// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

//! The Class for the comparison between 2 objects exprData
/*! 
  This class is used to compare 2 objects exprData.
  
  The comparation between 2 exprData is made used the attribute 
  line.
  Given the 2 object exprData ed1 and ed2 then :

  - ed1 <  ed2 if only if ed1::line <  ed2::line
  - ed1 == ed2 if only if ed1::line == ed2::line
  - ed1 >  ed2 if only if ed1::line >  ed2::line
  
  Remember : the type of the attribute exprData::line 
  is long.

  \note This class overload the operator ().
*/
class exprData_Cmp {

 public:

  //! The member for the comparison
  /*!
    Overload the operator ().

    \param ed1 the first exprData
    \param ed2 the second exprData

    \return True if ed1::line < ed2::line,
    false otherwise.
  */
  bool operator()(exprData& ed1, exprData& ed2);

  //! The member for the comparison
  /*!
    Overload the operator ().

    \param ed1 the first exprData
    \param ed2 the second exprData

    \return True if ed1::line < ed2::line,
    false otherwise.
    
    \note This method differs from the previous in the type 
    of the parameters. Now we have pointer, in the previous
    method we have reference.
  */
  bool operator()(exprData* ed1, exprData* ed2);

};

#endif
