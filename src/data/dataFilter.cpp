/***************************************************************************
			   dataFilter.cpp  -  description
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

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "data/dataFilter.h"

// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------


//---- fnctData FILTERS

bool 
filter_fnctDataAlls::isGood(dataObj& d) {
  fnctData  fData;
  
  fData = dynamic_cast<fnctData &>(d);

  return true;
};


bool 
filter_fnctDataWithBody::isGood(dataObj& d) {
  fnctData  fData;
  
  fData = dynamic_cast<fnctData &>(d);

  return fData.hasBody();
};


bool 
filter_fnctDataWithParm::isGood(dataObj& d) {
  fnctData  fData;
  
  fData = dynamic_cast<fnctData &>(d);

  return fData.hasParm();
};


bool 
filter_fnctDataIsStdC::isGood(dataObj& d) {
  fnctData  fData;
  
  fData = dynamic_cast<fnctData &>(d);

  return fData.isStdC();
};


