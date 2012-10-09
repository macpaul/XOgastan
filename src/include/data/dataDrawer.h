/***************************************************************************
			   dataDrawer.h  -  description
			      -------------------
     begin                : Sept 1 2001
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

#ifndef _DATA_DRAWER_H
#define _DATA_DRAWER_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "data/typeDef.h"
#include "data/dataObj.h"
#include "data/fnctData.h"
#include "data/declData.h"
#include "data/exprNumData.h"
#include "data/stmtNumData.h"
#include "data/nastNumData.h"
#include "data/graphData.h"

#include "nast/nast_code.h"

#include <list>

// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

//! This class holds the entry for the datas collected during the visit
/*!
  This class can be view as a big DRAWER that contains the entry point 
  (pointer) to the datas structure (declDataList, fnctData, ...)
  associated with a function. These datas structure are
  built during the analysis of NAST by using the visitors.

  This class can be use to pass the data collected to the other module
  of XOgastan (see HTMLbuilder, ...)
  
  These data are :
  - fnctData : the declaration of the function
  - declsList : the list of declarations into the function
  - varUsedList : the list of variables used into the expressions of the function
  - exprsList : the list of the expression into the function
  - exprNumData : the statistics of the expressions into the function
  - stmtNumData : the statistics of the statements into the function
  - nastNumData : the number of the nast_node reacheable from the body
  - graphData : the graph of body
  - the name of the dot file with the graph of the body
  - the name of the gif file with the graph of the body
  - callGraphData : the call graph
  - the name of the gif file with the call graph
  - the name of the dot file with the call graph
  - cfgGraphData : the control flow graph
  - the name of the gif file with the CFG
  - the name of the dot file with the CFG
  - the name of the txt file with the CFG

  \sa dataObj DATABuilder
*/
class dataDrawer
{

 private:

  //---- Attributes

  //! The data about the function declaration
  fnctData      *fData;

  //! The list of declarations into the function
  declsList     *dList;

  //! The list of variables used into the function
  varUsedList   *vuList;

  //! The list of expression into the function
  exprsList     *eL;

  //! The number of the expressions into the function
  exprNumData   *enData;

  //! The number of the statements into the function
  stmtNumData   *snData;

  //! The number of the nast_node reacheable from the body
  nastNumData   *nnData;

  //! The body's graph
  graphData     *bodyGraph;

  //! The call graph
  callGraphData *callGraph;

  //! The control flow graph (cfg) 
  cfgGraphData  *cfgGraph;

  //! The name of gif the file with the graph of the body'statement
  string        bodyGraphGIF;

  //! The name of the gif file with the call graph
  string        callGraphGIF;

  //! The name of the gif file with the CFG
  string        cfgGIF;
  
  //! The name of the dot file with the graph of the body'statement
  string        bodyGraphDOT;

  //! The name of the dot file with the call graph
  string        callGraphDOT;

  //! The name of the dot file with the CFG
  string        cfgDOT;

  //! The name of the txt file with the CFG
  string        cfgTXT;

 public:
  //! Constructor
  dataDrawer() {
    fData = 0;
    dList = 0;
    eL = 0;
    vuList = 0;
    enData = 0;
    snData = 0;
    nnData = 0;
    bodyGraph = 0;
    callGraph = 0;
    cfgGraph = 0;
  }
  
  //! Destructor
  ~dataDrawer() { }


  //---- Members

  //---- SET

  //! Set the data about the function declaration
  void setFnctData(fnctData  *fData) 
    { this->fData = fData; }

  //! Set the list of declarations into the function
  void setDeclsList(declsList *dList) 
    { this->dList = dList; }

  //! Set the list of variables used by function
  void setVarUsedList(varUsedList *vuList) 
    { this->vuList = vuList; }

  //! Set the list of expression into function
  void setExprsList(exprsList *eL) 
    { this->eL = eL; }
  
  //! Set the number of the expressions into the function
  void setExprNumData(exprNumData *enData) 
    { this->enData = enData; }
  
  //! Set the number of the statements into the function
  void setStmtNumData(stmtNumData *snData) 
    { this->snData = snData; }
  
  //! Set the number of the nast_node reacheable from the body
  void setNastNumData(nastNumData *nnData) 
    { this->nnData = nnData; }

  //! Set body's graph
  void setBodyGraph(graphData *bodyGraph) 
    { this->bodyGraph = bodyGraph; }
  
  //! Set call graph
  void setCallGraph(callGraphData *callGraph) 
    { this->callGraph = callGraph; }

  //! Set cfg
  void setCfgGraph(cfgGraphData* cfgGraph) 
    { this->cfgGraph = cfgGraph; }
  
  //! Set the GIF graph of the body's statements
  void setBodyGraphGIF(string bodyGraphGIF) 
    { this->bodyGraphGIF = bodyGraphGIF; }

  //! Set the call graph
  void setCallGraphGIF(string callGraphGIF) 
    { this->callGraphGIF = callGraphGIF; }

  //! Set the CFG
  void setCfgGIF(string cfgGIF) 
    { this->cfgGIF = cfgGIF; }

  //! Set the graph of the body's statements
  void setBodyGraphDOT(string bodyGraphDOT) 
    { this->bodyGraphDOT = bodyGraphDOT; }

  //! Set the call graph
  void setCallGraphDOT(string callGraphDOT) 
    { this->callGraphDOT = callGraphDOT; }

  //! Set the CFG
  void setCfgDOT(string cfgDOT) 
    { this->cfgDOT = cfgDOT; }

  //! Set the CFG
  void setCfgTXT(string cfgTXT) 
    { this->cfgTXT = cfgTXT; }

  //---- GET

  //! Get the data about the function declaration
  fnctData *getFnctData(void) 
    { return this->fData; }

  //! Get the list of declarations into the function
  declsList *getDeclsList(void) 
    { return this->dList; }
  
  //! Get the list of variables used by function
  varUsedList *getVarUsedList(void)
    { return this->vuList; }

  //! Get the list of expression into function
  exprsList *getExprsList(void)
    { return this->eL; }

  //! Get the number of the expressions into the function
  exprNumData *getExprNumData(void) 
    { return this->enData; }
  
  //! Get the number of the statements into the function
  stmtNumData *getStmtNumData(void) 
    { return this->snData; }
  
  //! Get the number of the nast_node reacheable from the body
  nastNumData *getNastNumData(void) 
    { return this->nnData; }

  //! Get body's graph
  graphData *getBodyGraph(void) 
    { return this->bodyGraph; }
  
  //! Get call graph
  callGraphData *getCallGraph(void) 
    { return this->callGraph; }

  //! Get cfg
  cfgGraphData *getCfgGraph(void) 
    { return this->cfgGraph; }

  //! Get the graph of the body's statements
  string getBodyGraphGIF(void) 
    { return this->bodyGraphGIF; }

  //! Get the call graph
  string getCallGraphGIF(void) 
    { return this->callGraphGIF; }

  //! Get the CFG
  string getCfgGIF(void) 
    { return this->cfgGIF; }

  //! Get the graph of the body's statements
  string getBodyGraphDOT(void) 
    { return this->bodyGraphDOT; }

  //! Get the call graph
  string getCallGraphDOT(void) 
    { return this->callGraphDOT; }

  //! Get the CFG
  string getCfgDOT(void) 
    { return this->cfgDOT; }
  
  //! Get the CFG
  string getCfgTXT(void) 
    { return this->cfgTXT; }

  //---- HAS ... ?

  //! Pool if there's a function declaration
  bool hasFnctData(void) 
    { return (this->fData == 0); }

  //! Pool if there's a list of declarations into the function
  bool hasDeclsList(void) 
    { return ( (this->dList != 0) &&
	       (dList->size() > 0) ); 
    }

  //! Pool if there's a list of variables used by function
  bool hasVarUsedList(void)
    { return ( (this->vuList != 0) &&
	       (vuList->size() > 0) ); 
    }

  //! Pool if there's a list of expression into function
  bool hasExprsList(void)
    { return ( (this->eL != 0) &&
	       (eL->size() > 0) ); 
    }

  //! Pool if there's a number of the expressions into the function
  bool hasExprNumData(void) 
    { return (this->enData == 0); }
  
  //!  Pool if there's a number of the statements into the function
  bool hasStmtNumData(void) 
    { return (this->snData == 0); }
  
  //!  Pool if there's a number of the nast_node reacheable from the body
  bool hasNastNumData(void) 
    { return (this->nnData == 0); }

  //! Has body's graph
  bool hasBodyGraph(void) 
    { return (this->bodyGraph == 0); }
  
  //! Has call graph
  bool hasCallGraph(void) 
    { return (this->callGraph == 0); }

  //! Has cfg
  bool hasCfgGraph(void) 
    { return (this->cfgGraph == 0); }

  //! Has the graph of the body's statements
  bool hasBodyGraphGIF(void) 
    { return (this->bodyGraphGIF == ""); }

  //! Has the call graph
  bool hasCallGraphGIF(void) 
    { return (this->callGraphGIF == ""); }

  //! Has the CFG gif
  bool hasCfgGIF(void) 
    { return (this->cfgGIF == ""); }

  //! Has the graph of the body's statements
  bool hasBodyGraphDOT(void) 
    { return (this->bodyGraphDOT == ""); }

  //! Has the call graph
  bool hasCallGraphDOT(void) 
    { return (this->callGraphDOT == ""); }

  //! Has the CFG dot
  bool hasCfgDOT(void) 
    { return (this->cfgDOT == ""); }

  //! Has the CFG txt
  bool hasCfgTXT(void) 
    { return (this->cfgTXT == ""); }

};

#endif









