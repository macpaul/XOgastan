/***************************************************************************
			   fnctData.cpp  -  description
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

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "data/fnctData.h"

// ---------------------------------------------------------------------------
//  STATIC Members
// ---------------------------------------------------------------------------

map<string, int> fnctData::cStdFnct;


// ---------------------------------------------------------------------------
//  Members of fnctData
// ---------------------------------------------------------------------------

// constructor
fnctData::fnctData() { 
  nodep = 0;
  // Init the static member : the map of C function of the standard library
#define DEFcStdLibraryFnct(std_name)    fnctData::cStdFnct[#std_name]=1;
#include "data/stdClib.def"
#undef DEFcStdLibraryFnct
  return;
}


void 
fnctData::addParm(parmData *parm) { 
  parameters.push_front(parm); 
}

parmData *
fnctData::firstParm(void) {

  // is the list empty ?
  if ( parameters.size() ) {
    p_pos = 1;
    p_parameters = parameters.begin();
    
    return *p_parameters;
  } 

  return 0;
}

    
parmData *
fnctData::nextParm(void) {

  // is there a next parameters ?
  if ( fnctData::hasNextParm()) {
    p_pos++;
    p_parameters++;

    return *p_parameters;
  } 

  return 0;
}

bool 
fnctData::isStdC(void) {
  return (cStdFnct.find(name) != cStdFnct.end());
}


// ---------------------------------------------------------------------------
//  Members of fnctData_Cmp
// ---------------------------------------------------------------------------

bool fnctData_Cmp::operator()(fnctData& fd1, 
			      fnctData& fd2) {
  return (fd1.getName() < fd2.getName());
}

bool fnctData_Cmp::operator()(fnctData* fd1, 
			      fnctData* fd2) {
  return (fd1->getName() < fd2->getName());
}
