/***************************************************************************
			   dataFilter.h  -  description
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

#ifndef _DATA_FILTER_H
#define _DATA_FILTER_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "data/dataObj.h"

#include "data/fnctData.h"
// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

//---- BASE CLASS

//! This is the base class of the hierarcy of the filters
/*! 
  A filter is a class with a virtual method<br>
  bool isGood(dataObj &dO);.<br>
  This method is a predicate that define
  a semantic test. It return :
  - true, if the dataObj dO pass the test
  - false, if the dataObj dO doesn't pass the test

  The filter can be used in the follow context :
  we have a set of dataObj,<br>
  we must elaborate only the dataObj that satisfy a criterion,<br>
  THEN we define a filter for the criterion,<br>
  we apply the filter to the dataObj using the protocol :

  \code
  dataFilter    dFilter;
  set<dataObj>  setDO;
  
  for each dO in setDO
     if dFilter.isGood(dO)
        make something with dO;
  \endcode
*/
class dataFilter
{
 public:
  //! Destructor
  ~dataFilter() { }

  //---- Members

  //! The function used to filter the objects dataObj
  /*! 
    This function checks if the dataObj pass or not the
    test of the filter.

    \param d the dataObj to test
   
    \return True if the dataObj d pass the test,
    false if the dataObj d doesn't pass the test
  */
  virtual bool isGood(dataObj& d) = 0;
};


//---- fnctData FILTERS

//! This class filter alls the objects fnctData 
class filter_fnctDataAlls : public dataFilter
{
 public:

  //! The function used to filter the objects dataObj
  /*! 
    This function checks if the dataObj pass or not the
    test of the filter.

    Criterion : <b>all the fnctData pass the test</b>

    \param d the dataObj to test
   
    \return Alway true.
  */
  virtual bool isGood(dataObj& d);
};

//! This class filter the object fnctData with (fnctData::hasBody() == true)
class filter_fnctDataWithBody : public dataFilter
{
 public:

  //! The function used to filter the objects dataObj
  /*! 
    This function checks if the dataObj pass or not the
    test of the filter.

    Criterion : </b>fnctData::hasBody() == true</b>

    \param d the dataObj to test
   
    \return True if the dataObj d pass the test,
    false if the dataObj d doesn't pass the test
  */
  virtual bool isGood(dataObj& d);
};

//! This class filter the object fnctData with (fnctData::hasParm() == true)
class filter_fnctDataWithParm : public dataFilter
{
 public:

  //! The function used to filter the objects dataObj
  /*! 
    This function checks if the dataObj pass or not the
    test of the filter.

    Criterion : <b>fnctData::hasParm() == true</b>

    \param d the dataObj to test
   
    \return True if the dataObj d pass the test,
    false if the dataObj d doesn't pass the test
  */
  virtual bool isGood(dataObj& d);
};

//! This class filter the object fnctData with (fnctData::isStdC() == true)
class filter_fnctDataIsStdC : public dataFilter
{
 public:

  //! The function used to filter the objects dataObj
  /*! 
    This function checks if the dataObj pass or not the
    test of the filter.

    Criterion : <b>fnctData::isStdC() == true</b>

    \param d the dataObj to test
   
    \return True if the dataObj d pass the test,
    false if the dataObj d doesn't pass the test
  */
  virtual bool isGood(dataObj& d);
};



#endif

