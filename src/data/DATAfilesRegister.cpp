/***************************************************************************
			   DATAfilesRegister.cpp  -  description
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
#include "data/DATAfilesRegister.h"

// ---------------------------------------------------------------------------
//  Members
// ---------------------------------------------------------------------------


string 
DATAfilesRegister::gifBodyGraphFile(fnctData &fd) {
  return (fd.getName() + "_" + 
	  a2b::long2string( (fd.getNodeP())->getId()) + "_bodyGraph.gif" );
}


string 
DATAfilesRegister::dotBodyGraphFile(fnctData &fd) {
  return (fd.getName() + "_" + 
	  a2b::long2string( (fd.getNodeP())->getId()) + "_bodyGraph.dot" );
}


string 
DATAfilesRegister::dotCallGraphFile(fnctData &fd) {
  return (fd.getName() + "_" + 
	  a2b::long2string( (fd.getNodeP())->getId()) + "_callGraph.dot" );
}


string 
DATAfilesRegister::gifCallGraphFile(fnctData &fd) {
  return (fd.getName() + "_" + 
	  a2b::long2string( (fd.getNodeP())->getId()) + "_callGraph.gif" );
}


string 
DATAfilesRegister::dotCFGraphFile(fnctData &fd) {
  return (fd.getName() + "_" + 
	  a2b::long2string( (fd.getNodeP())->getId()) + "_CFG.dot" );
}


string 
DATAfilesRegister::txtCFGraphFile(fnctData &fd) {
  return (fd.getName() + "_" + 
	  a2b::long2string( (fd.getNodeP())->getId()) + "_CFG.txt" );
}


string 
DATAfilesRegister::gifCFGraphFile(fnctData &fd) {
  return (fd.getName() + "_" + 
	  a2b::long2string( (fd.getNodeP())->getId()) + "_CFG.gif" );
}

