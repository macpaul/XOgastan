/***************************************************************************
			   flags.h  -  description
			      -------------------
     begin                : Aug 6 2001
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


#ifndef _FLAGS_H
#define _FLAGS_H

// ---------------------------------------------------------------------------
// FLAGS
// ---------------------------------------------------------------------------

//! The verbosity level of the output
/*!
  The value are :
  
  true  : print messages during ast building process
  false : don't print messages during ast building process
*/
extern bool astVerbosity;

//! Flag for the warning ability
/*!
  The value are :
  
  true  : print warning messages during ast building process
  false : don't print warning messages during ast building process
*/
extern bool astWarning;

//! Flag for the cfg graphs generation
/*!
  The value are :
  
  true  : don't generate cfg graphs
  false : generate cfg graphs
*/
extern bool noCFG;

//! Flag for the body graphs generation
/*!
  The value are :
  
  true  : don't generate body graphs
  false : generate body graphs
*/
extern bool noBodyGraph;

//! Flag for the call graphs generation
/*!
  The value are :
  
  true  : don't generate call graphs
  false : generate call graphs
*/
extern bool noCallGraph;

//! Flag for the declarations list generation
/*!
  The value are :
  
  true  : don't generate declarations list
  false : generate declarations list
*/
extern bool noDeclsList;

//! Flag for the var used list generation
/*!
  The value are :
  
  true  : don't generate var used list
  false : generate var used list
*/
extern bool noVarUsed;

//! Flag for the expressions list generation
/*!
  The value are :
  
  true  : don't generate expressions list
  false : generate expressions list
*/
extern bool noExprsList;

//! Flag for the stmt Number Statistics generation
/*!
  The value are :
  
  true  : don't generate stmt statistics
  false : generate stmt statistics
*/
extern bool noStmtStat;

//! Flag for the expr Number Statistics generation
/*!
  The value are :
  
  true  : don't generate expr statistics
  false : generate expr statistics
*/
extern bool noExprStat;

//! Flag for the nast Number Statistics generation
/*!
  The value are :
  
  true  : don't generate nast statistics
  false : generate nast statistics
*/
extern bool noNastStat;

//! Flag for the html generation
/*!
  The value are :
  
  true  : don't generate html
  false : generate html
*/
extern bool noHtml;

//! Flag for the xml generation
/*!
  The value are :
  
  true  : don't generate xml
  false : generate xml
*/
extern bool noXml;

#endif

