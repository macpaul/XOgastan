/***************************************************************************
			   main.cpp  -  description
			      -------------------
     begin                : Aug 7 2001
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

// ---  NAST
#include "nast/nast_node.h"

// ---  SAX Handler
#include "factory/operativeMachine.h"

// --- Includes for buildHTMLpages
#include "htmlWriter/HTMLwriter.h"
#include "htmlWriter/HTMLfilesRegister.h"
#include "htmlWriter/write_htmlHomePage.h"
#include "htmlWriter/write_htmlFnctFilter.h"
#include "htmlWriter/write_htmlFnctPages.h"
#include "htmlWriter/write_htmlNastStat.h"

// --- Includes for buildDOM_Document
#include "xmlManager/XMLWriter.h"
#include "xmlManager/build_xmlFunctionDOM.h"
#include "xmlManager/build_xmlDeclarationDOM.h"
#include "xmlManager/build_xmlVarUsedDOM.h"
#include "xmlManager/build_xmlParameterDOM.h"
#include "xmlManager/build_xmlStmtStatDOM.h"
#include "xmlManager/build_xmlExprStatDOM.h"
#include "xmlManager/build_xmlReachStatDOM.h"
#include "xmlManager/build_xmlNastStatDOM.h"

// --- Includes for buildDataOfNast
#include "data/DATAfilesRegister.h"
#include "data/typeDef.h"
#include "data/dataObj.h"
#include "data/fnctData.h"
#include "data/declData.h"
#include "data/exprData.h"
#include "data/exprNumData.h"
#include "data/stmtNumData.h"
#include "data/nastNumData.h"
#include "data/graphData.h"
#include "data/dataDrawer.h"
#include "data/dataFilter.h"

#include "visitor/visit_fnctsInNast.h"
#include "visitor/visit_declsInFnct.h"
#include "visitor/visit_exprsInFnct.h"
#include "visitor/visit_varUsedByFnct.h"
#include "visitor/visit_fnctBodyGraph.h"
#include "visitor/visit_fnctCFG.h"
#include "visitor/visit_fnctCallGraph.h"
#include "visitor/visit_exprNumber.h"
#include "visitor/visit_stmtNumber.h"
#include "visitor/visit_nastNumber.h"

#include "utils/dot2gif.h"

// --- General files
#include "utils/a2b.h"
#include "error/bad_XOgastan.h"

// Include files not written by XOgastan programmer
#include <dom/DOM.hpp>
#include <util/PlatformUtils.hpp>
#include <util/TransService.hpp>
#include <parsers/SAXParser.hpp>

#include <iostream>
#include <cstdlib>

#define _POSIX_SOURCE 1

#include <sys/types.h>
#include <sys/stat.h>

#include <list>

// ---------------------------------------------------------------------------
// VARIABLES
// ---------------------------------------------------------------------------


//      The path to the file to parser. Set via command line.
char                              *xmlFile  = 0;
//      Indicates what validation scheme to use.
static SAXParser::ValSchemes      valScheme = SAXParser::Val_Auto;


// Flag setted from the command line
bool  astVerbosity    =  false;
bool  astWarning      =  false;
bool  noCFG           =  false;
bool  noBodyGraph     =  false;
bool  noCallGraph     =  false;
bool  noDeclsList     =  false;
bool  noExprsList     =  false;
bool  noVarUsed       =  false;
bool  noStmtStat      =  false;
bool  noExprStat      =  false;
bool  noNastStat      =  false;
bool  noHtml          =  false;
bool  noXml           =  false;

// Nast
static nast_node                   *NAST;              
static list<nast_node *>           *NASTlist;

// Datas about NAST
static dataDrawerList              *dataDL;
static nastNumData                 *nastStat;

// DOM Documents
static DOM_Document                *functionDOM;
static DOM_Document                *declarationDOM;
static DOM_Document                *var_usedDOM;
static DOM_Document                *parameterDOM;
static DOM_Document                *stmt_statisticDOM;
static DOM_Document                *expr_statisticDOM;
static DOM_Document                *reach_statisticDOM;
static DOM_Document                *nast_statisticDOM;

// ---------------------------------------------------------------------------
//  Local helper methods
// ---------------------------------------------------------------------------
static void
usage ()
{
  cout << "This program analize the Gcc Abstract Syntax Tree generated\n"
       << "by the gcc compiler.\n\n"
       << "Usage:\n\tXOgastan [options] file\n"
       << "Options:\n"
       << "    -vast           Print messages during the\n"
       << "                    AST building process.\n"
       << "    -wast           Print warning messages during the.\n"
       << "                    AST building process.\n\n"
       << "    -nocfg          Don't generate the cfg.\n"
       << "    -nocallgraph    Don't generate the call graph.\n"
       << "    -nobodygraph    Don't generate the body graph.\n"
       << "    -nodecllist     Don't list declarations in functions.\n"
       << "    -noexprlist     Don't list expressions in functions.\n"
       << "    -novarused      Don't list variables used by functions.\n"
       << "    -nostmtstat     Don't generate statistics of stmt.\n"
       << "    -noexprstat     Don't generate statistics of expr.\n"
       << "    -nonaststat     Don't generate statistics of nodes.\n"
       << "    -nohtml         Don't generate html report.\n"
       << "    -noxml          Don't generate xml files.\n\n"
       << "    -?              Show this help.\n\n"
       << "Default is :\tXOgastan file\n" 
       << "Options are case sensitive." << endl;
}

// ---------------------------------------------------------------------------
//  BUILD DATA
// ---------------------------------------------------------------------------

static void 
buildDataOfNast(void) {

  // 1.
  // Build list of functions in NAST
  // --------------------------------------
  visit_fnctsInNast      v;              // the visitor
  fnctsList              fnctsL;         // The list of the functions

  cout << "Building list of the functions in NAST...\n";
  // visit NAST and create the list
  v.setFnctsList(&fnctsL);
  NAST->accept(v);
  // sort the list 
  fnctsL.sort(fnctData_Cmp());


  // 2.
  // Build datas of functions
  // --------------------------------------
  fnctsListIterator      p;              // browse the list of fnctData
  fnctData               *fData;         // current fnctData
  string                 fnctName;       // name of the function
  nast_node              *body;          // body of the function

  visit_stmtNumber       v_stmtNum;      // build statements statistics
  visit_exprNumber       v_exprNum;      // build expressions statistics
  visit_declsInFnct      v_declsF;       // build list of declarations
  visit_exprsInFnct      v_exprsF;       // build list of expressions
  visit_varUsedByFnct    v_vusedF;       // build list of variables used
  visit_nastNumber       v_nastNum;      // build nast_node statistics
  visit_fnctBodyGraph    v_fnctBody;     // build a graph of the body
  visit_fnctCFG          v_fnctCFG;      // build a CFG
  visit_fnctCallGraph    v_fnctCall;     // build a call graph
  
  // Datas about function
  stmtNumData            *snData;        // statements statistics
  exprNumData            *enData;        // expressions statistics
  declsList              *dL;            // the list of declarations
  exprsList              *eL;            // the list of expressions 
  varUsedList            *vuL;           // the list of variables used by fnct
  nastNumData            *nnData;        // number of reacheable nat_node
  graphData              *graph;         // a body graph 
  cfgGraphData           *cfgGraph;      // a CFG graph 
  callGraphData          *callGraph;     // a call graph 
  
  ofstream               dotFile;        
  ofstream               txtFile;
  string                 dotName;                 
  string                 gifName;
  string                 txtName;

  dataDrawer             *dataB;         // The dataDrawer 

  /*
    In the follow algorithm is important :
    - the direction of the visit of fnctsL (from the
    begin to the end)
    - the direction of the push operation into dataDL
    (at the end of the list)
    We must preserve the alphabetical order of the function
    analized
  */


  // dataDL is a static variable local to translationUnit of main.cpp
  //
  dataDL = new dataDrawerList;

  p = fnctsL.begin();
  while (p != fnctsL.end()) {
    fData = *p;
    p++;

    dataB = new dataDrawer;
    
    dataB->setFnctData(fData);

    if (fData->hasBody()) {
      
      fnctName = fData->getName();
      body = fData->getBody();
    

      //---- Create the CFG
      if (!noCFG) {

	cout << "Generating CFG of function " 
	     << fnctName << "...\n";

	// Get the files name 
	dotName = "dot/" + DATAfilesRegister::dotCFGraphFile(*fData);
	gifName = "img/" + DATAfilesRegister::gifCFGraphFile(*fData);
	txtName = "txt/" + DATAfilesRegister::txtCFGraphFile(*fData);
	
	// build the graph
	cfgGraph = new cfgGraphData;
	cfgGraph->setFnctName(fnctName);
	v_fnctCFG.setCfgGraphData(cfgGraph);
	v_fnctCFG.init();
	body->accept(v_fnctCFG);
	v_fnctCFG.finish();

	// Dump dot, txt and gif file 
	cfgGraph->dumpDotFile(dotName.c_str(), "box");
	cfgGraph->dumpCfgFile(txtName.c_str());
	dot2gif(dotName,gifName);

	// Set pointer in DataDrawer
	dataB->setCfgGraph(cfgGraph);
	dataB->setCfgDOT(DATAfilesRegister::dotCFGraphFile(*fData));
	dataB->setCfgTXT(DATAfilesRegister::txtCFGraphFile(*fData));
	dataB->setCfgGIF(DATAfilesRegister::gifCFGraphFile(*fData));
      }
	

      //---- Create the bodyGraph
      if (!noBodyGraph) {

	cout << "Generating body's graph of function " 
	     << fnctName << "...\n";

	// Get the files name 
	dotName = "dot/" + DATAfilesRegister::dotBodyGraphFile(*fData);
	gifName = "img/" + DATAfilesRegister::gifBodyGraphFile(*fData);
	
	// build the dot file
	graph = new graphData;
	v_fnctBody.setGraphData(graph);
	v_fnctBody.init();
	body->accept(v_fnctBody);
	v_fnctBody.finish();
	
	// Dump dot and gif files
	graph->dumpDotFile(dotName.c_str(), "box");
	dot2gif(dotName,gifName);

	// Set pointer in DataDrawer
	dataB->setBodyGraph(graph);
	dataB->setBodyGraphGIF(DATAfilesRegister::gifBodyGraphFile(*fData));
	dataB->setBodyGraphDOT(DATAfilesRegister::dotBodyGraphFile(*fData));
      }
	
      //---- Create the call Graph
      if (!noCallGraph) {
	
	cout << "Generating call graph of function " 
	     << fnctName << "...\n";
	
	// Get the files name 
	dotName = "dot/" + DATAfilesRegister::dotCallGraphFile(*fData);
	gifName = "img/" + DATAfilesRegister::gifCallGraphFile(*fData);
	
	// build the dot file
	callGraph = new callGraphData;
	callGraph->setFnctName(fnctName);
	v_fnctCall.setCallGraphData(callGraph);
	v_fnctCall.setFnctName(fnctName);
	v_fnctCall.setFnctId( (fData->getNodeP())->getId() );
	v_fnctCall.init();
	body->accept(v_fnctCall);

	// Dump dot and gif files
	callGraph->dumpDotFile(dotName.c_str(), "ellipse");
	dot2gif(dotName,gifName);

	// Set pointer in DataDrawer
	dataB->setCallGraph(callGraph);
	dataB->setCallGraphGIF(DATAfilesRegister::gifCallGraphFile(*fData));
	dataB->setCallGraphDOT(DATAfilesRegister::dotCallGraphFile(*fData));
      }
     
      //---- build the list of declarations
      if (!noDeclsList) {

	cout << "Building declarations list of function " 
	     << fnctName << "...\n";
	
	// build the declsList
	dL = new declsList; 
	v_declsF.setDeclsList(dL);
	v_declsF.setFnctName(fnctName);
	body->accept(v_declsF);

	// Sort by name 
	dL->sort(declData_Cmp());
	
	// set declsList in datadrawer
	dataB->setDeclsList(dL);
      }

      //---- build the list of variables used by the function
      if (!noVarUsed) {

	cout << "Building list of variables used by function " 
	     << fnctName << "...\n";
	
	// build the varUsed list
	vuL = new varUsedList; 
	v_vusedF.setVarUsedList(vuL);
	v_vusedF.setFnctName(fnctName);
	v_vusedF.init();
	body->accept(v_vusedF);
	v_vusedF.finish();

	// sort by name
	vuL->sort(varUsedData_Cmp());
	
	// set varUsed list in datadrawer
	dataB->setVarUsedList(vuL);
      }

      //---- make analysis of expression
      if (!noExprsList) {

	cout << "Building list of expression of function " 
	     << fnctName << "...\n";
	
	// build the varUsed list
	eL = new exprsList;
	v_exprsF.setExprsList(eL);
	v_exprsF.setFnctName(fnctName);
	v_exprsF.init();
	body->accept(v_exprsF);
	v_exprsF.finish();

	// sort by name
	eL->sort(exprData_Cmp());
	
	cout << "HERE ==> eL size " << eL->size() << "\n";

	// set varUsed list in datadrawer
	dataB->setExprsList(eL);
      }

      //---- count the number of statements
      if (!noStmtStat) {
	cout << "Counting statements number of function " 
	     << fnctName << "...\n";
	
	// build the statements statistics
	snData = new stmtNumData;
	v_stmtNum.setStmtNumData(snData);
	body->accept(v_stmtNum);
      
	// set stmt statistics in datadrawer
	dataB->setStmtNumData(snData);
      }
      
      //---- count the number of expressions
      if (!noExprStat) {

	cout << "Counting expressions number of function " 
	     << fnctName << "...\n";
	
	// build the statements statistics
	enData = new exprNumData;
	v_exprNum.setExprNumData(enData);
	body->accept(v_exprNum);
	
	// set expr statistics in datadrawer
	dataB->setExprNumData(enData);
      }

      //---- Count the number of reacheable nast_node
      if (!noNastStat) { 

	cout << "Counting reacheable nast_node from function " 
	     << fnctName << "...\n";
	
	// build the nast_node statistics
	nnData = new nastNumData;
	v_nastNum.setNastNumData(nnData);
	v_nastNum.init();
	body->accept(v_nastNum);
	
	// set nast_node number in datadrawer
	dataB->setNastNumData(nnData);
      }

    }
    
    // PUSH dataB
    dataDL->push_back(dataB);
  }

  
  // 3.
  // Build statistcs about nast
  // --------------------------------------
   
  // build the nast_node statistics of NAST
  if (!noNastStat) {
    cout << "Generating statistics about nodes in NAST...\n";
    nastStat = new nastNumData;
    v_nastNum.init();
    v_nastNum.setNastNumData(nastStat);
    NAST->accept(v_nastNum);
  }

  return;
}

// ---------------------------------------------------------------------------
//  Build HTML pages
// ---------------------------------------------------------------------------
static void
writeHTMLpages(void) {
  
  // The writers
  write_htmlHomePage       wHpage;    // write the home page
  write_htmlFnctFilter     wFfilter;  // write functions index filtereds
  write_htmlFnctPages      wFpages;   // write functions pages
  write_htmlNastStat       wNstat;    // write NAST statistic

  // The filters
  filter_fnctDataAlls      ffDataA;
  filter_fnctDataWithBody  ffDataWB;
  filter_fnctDataWithParm  ffDataWP;
  filter_fnctDataIsStdC    ffDataIC;

  cout << "Generating html home page...\n";
  // write the home page
  wHpage.writePage();
  
  cout << "Generating html index of the functions...\n";
  // write functions index filtereds
  wFfilter.setPageTitle("Index of the functions");
  wFfilter.setPageName(HTMLfilesRegister::fnctIndex);
  wFfilter.setDataFilter(&ffDataA);
  wFfilter.setDataDrawerList(dataDL);
  wFfilter.writePage();
  
  cout << "Generating html index of the functions with body...\n";
  // write functions index filtereds
  wFfilter.setPageTitle("Index of the functions with body");
  wFfilter.setPageName(HTMLfilesRegister::fnctWithBodyIndex);
  wFfilter.setDataFilter(&ffDataWB);
  wFfilter.writePage();

  cout << "Generating html index of the functions with parameters...\n";
  // write functions index filtereds
  wFfilter.setPageTitle("Index of the functions with parm");
  wFfilter.setPageName(HTMLfilesRegister::fnctWithParmIndex);
  wFfilter.setDataFilter(&ffDataWP);
  wFfilter.writePage();

  cout << "Generating html index of the the C standard functions used...\n";
  // write functions index filtereds
  wFfilter.setPageTitle("Index of the C standard functions");
  wFfilter.setPageName(HTMLfilesRegister::fnctIsStdCIndex);
  wFfilter.setDataFilter(&ffDataIC);
  wFfilter.writePage();

  cout << "Generating html pages of the functions...\n";
  // write functions pages
  wFpages.setDataDrawerList(dataDL);
  wFpages.writePage();

  if (!noNastStat) {
    cout << "Generating html page of the NAST statistics...\n";
    // write Nast statistics
    wNstat.setNastStat(nastStat);
    wNstat.setDataDrawerList(dataDL);
    wNstat.writePage();
  }

  return;
}

// ---------------------------------------------------------------------------
//  Build DOM documents
// ---------------------------------------------------------------------------
static void
buildDOM_Document(void) {

  // DOM classes
  build_xmlFunctionDOM        buildFnctDOM;
  build_xmlDeclarationDOM     buildDeclDOM;
  build_xmlVarUsedDOM         buildVarUsedDOM;
  build_xmlParameterDOM       buildParmDOM;
  build_xmlStmtStatDOM        buildStmtStatDOM;
  build_xmlExprStatDOM        buildExprStatDOM;
  build_xmlReachStatDOM       buildReachStatDOM;
  build_xmlNastStatDOM        buildNastStatDOM;

  // Build the DOM trees
  //
  //--- functionDOM
  cout << "Building DOM for function declarations...\n";
  buildFnctDOM.setDataDrawerList(dataDL);
  buildFnctDOM.buildDOM();
  functionDOM = buildFnctDOM.getDOMDocument();

  //--- declarationDOM
  if (!noDeclsList) {
    cout << "Building DOM for declarations into functions...\n";
    buildDeclDOM.setDataBagList(dataDL);
    buildDeclDOM.buildDOM();
    declarationDOM = buildDeclDOM.getDOMDocument();
  }

  //--- var_usedDOM
  if (!noVarUsed) {
    cout << "Building DOM for variables used by functions...\n";
    buildVarUsedDOM.setDataBagList(dataDL);
    buildVarUsedDOM.buildDOM();
    var_usedDOM = buildVarUsedDOM.getDOMDocument();
  }

  //--- parameterDOM
  cout << "Building DOM for paramters of functions...\n";
  buildParmDOM.setDataBagList(dataDL);
  buildParmDOM.buildDOM();
  parameterDOM = buildParmDOM.getDOMDocument();

  //--- stmt_statisticDOM
  if (!noStmtStat) {
    cout << "Building DOM for stmt statistics of functions...\n";
    buildStmtStatDOM.setDataBagList(dataDL);
    buildStmtStatDOM.buildDOM();
    stmt_statisticDOM = buildStmtStatDOM.getDOMDocument();
  }
  
  //--- expr_statisticDOM
  if (!noExprStat) {
    cout << "Building DOM for expr statistics of functions...\n";
    buildExprStatDOM.setDataBagList(dataDL);
    buildExprStatDOM.buildDOM();
    expr_statisticDOM = buildExprStatDOM.getDOMDocument();
  }

  //--- reach_statisticDOM
  if (!noNastStat) {
    cout << "Building DOM for reach statistics of functions...\n";
    buildReachStatDOM.setDataBagList(dataDL);
    buildReachStatDOM.buildDOM();
    reach_statisticDOM = buildReachStatDOM.getDOMDocument();
    
    //--- nast_statisticDOM
    cout << "Building DOM for nast statistics...\n";
    buildNastStatDOM.setNastStat(nastStat);
    buildNastStatDOM.buildDOM();
    nast_statisticDOM = buildNastStatDOM.getDOMDocument();
  }

  return;
}

// ---------------------------------------------------------------------------
//  Free Memory for Data
// ---------------------------------------------------------------------------
static void 
deleteData(void) {
  dataDrawerListIterator     p;        // Browse the declarations list
  dataDrawer                 *dataD;   // a ne element of dataDL to free

  p = dataDL->begin();
  while (p != dataDL->end()) {
    dataD = *p;
    p++;

    delete dataD->getFnctData();               // delete function information

    if (dataD->hasDeclsList())                 // delete declarations list
      delete dataD->getDeclsList();

    if (dataD->hasVarUsedList())               // delete var used list
      delete dataD->getVarUsedList();

    if (dataD->hasExprsList())                 // delete var used list
      delete dataD->getExprsList();

    if (dataD->hasStmtNumData())               // delete stmt statististics
      delete dataD->getStmtNumData();

    if (dataD->hasExprNumData())               // delete expr statististics
      delete dataD->getExprNumData();

    if (dataD->hasNastNumData())               // delete nast statististics
      delete dataD->getNastNumData();

    if (dataD->hasBodyGraph())                 // delete nast statististics
      delete dataD->getBodyGraph();

    if (dataD->hasBodyGraph())                 // delete body graph
      delete dataD->getBodyGraph();

    if (dataD->hasCfgGraph())                  // delete cfg graph
      delete dataD->getCfgGraph();

    if (dataD->hasCallGraph())                 // delete call graph
      delete dataD->getCallGraph();
    
    delete dataD;                              // delete data drawer
    
  }
  dataDL->clear;
  delete dataDL;                               // delete list
  
  delete nastStat;                             // delete nast statistic
  
  return;
} 

// ---------------------------------------------------------------------------
//  Free Memory for the NAST structure
// ---------------------------------------------------------------------------
static void 
deleteNAST(void) {
  list<nast_node *>::iterator      p;   // browse the nast list
  
  for (p = NASTlist->begin(); p != NASTlist->end(); p++)
    delete (*p);
  
  NASTlist->clear();

  return;
}
// ---------------------------------------------------------------------------
//  Program entry point
// ---------------------------------------------------------------------------
int
main (int argC, char *argV[])
{

  // Initialize class for conversion
  a2b ();

  // Initialize the XML4C2 system
  try
  {
    XMLPlatformUtils::Initialize ();
  }

  catch (const XMLException & toCatch)
  {
    cerr << "Error during initialization! :\n"
      << a2b::XMLChar2string (toCatch.getMessage ()) << endl;
    exit (EXIT_FAILURE);
  }

  cout << "XMLPlatformUtils initialized...\n";

  // Check command line and extract arguments.
  if (argC < 2)
    {
      usage ();
      XMLPlatformUtils::Terminate ();
      exit (EXIT_FAILURE);
    }

  // Watch for special case help request
  if ((argC == 2) && !strcmp (argV[1], "-?"))
    {
      usage ();
      XMLPlatformUtils::Terminate ();
      exit (EXIT_FAILURE);
    }

  // Parse the parameter
  int
    parmInd;
  for (parmInd = 1; parmInd < argC; parmInd++)
    {
      // Break out on first parm not starting with a dash
      if (argV[parmInd][0] != '-')
	break;

      // Show help
      if (!strcmp (argV[parmInd], "-?")) {
	usage();
	exit (EXIT_SUCCESS);
      }
      // Set verbosity ability during the ast building
      else if (!strcmp (argV[parmInd], "-vast"))
	astVerbosity = true;
      // Set warning ability during the ast building
      else if (!strcmp (argV[parmInd], "-wast"))
	astWarning  = true;
      // Set no cfg graph generation
      else if (!strcmp (argV[parmInd], "-nocfg"))
	noCFG = true;
      // Set no body graph generation
      else if (!strcmp (argV[parmInd], "-nobodygraph"))
	noBodyGraph = true;
      // Set no call graph generation
      else if (!strcmp (argV[parmInd], "-nocallgraph"))
	noCallGraph = true;
      // Set no decl list generation
      else if (!strcmp (argV[parmInd], "-nodecllist"))
	noDeclsList = true;
      // Set no var used list generation
      else if (!strcmp (argV[parmInd], "-novarused"))
	noVarUsed = true;
      // Set no expression list generation
      else if (!strcmp (argV[parmInd], "-noexprlist"))
	noExprsList = true;
      // Set no stmt statistics generation
      else if (!strcmp (argV[parmInd], "-nostmtstat"))
	noStmtStat = true;
      // Set no expr statistics generation
      else if (!strcmp (argV[parmInd], "-noexprstat"))
	noExprStat = true;
      // Set no nast statistics generation
      else if (!strcmp (argV[parmInd], "-nonaststat"))
	noNastStat = true;
      // Set html generation
      else if (!strcmp (argV[parmInd], "-nohtml"))
	noHtml = true;
      // Set no xml generation
      else if (!strcmp (argV[parmInd], "-noxml"))
	noXml = true;
      else {
	cerr << "\nERROR :"
	     << "Unknown option '" << argV[parmInd]
	     << "\n";
	usage();
	exit (EXIT_FAILURE);

      }
    }

  //
  //  And now we have to have only one parameter left and it must be
  //  the file name.
  //
  if (parmInd + 1 != argC)
    {
      cerr << "\nError : No input file\n";
      usage ();
      exit (EXIT_FAILURE);
    }
  xmlFile = argV[parmInd];

  cout << "xml file name : " << xmlFile << "\n";

  //
  //  Create a SAX parser object. Then, according to what we were told on
  //  the command line, set it to validate or not.
  //
  SAXParser    parser;
  parser.setValidationScheme (valScheme);
  parser.setDoNamespaces (false);
  parser.setDoSchema (false);

  //
  //  Create the handler object and install it as the document and error
  //  handler for the parser. Then parse the file and catch any exceptions
  //  that propogate out
  //
  try
  {

    // Parse Xml File and Build NAST
    operativeMachine           om;
    parser.setDocumentHandler (&om);
    parser.setErrorHandler    (&om);
    cout << "Setted GXL Handler\n\n" << "Starting parsing ...\n";
    // Parse
    parser.parse (xmlFile);
    cout << "... parsing xml file done \n";
    //
    // ---->
    // Get pointer to first node of NAST and list of nodes
    // <----
    NAST = om.getNast();
    NASTlist = om.getNastList();
    NASTlist->sort(nast_node_Cmp());
    cout << "First node - "
	 << "  index:" << NAST->getId()
	 << "  code:" << a2b::nast_code2string(NAST->getCode())
	 << "\n\n";
    

    // makeDirectory for graphs
    if (!(noCFG && noBodyGraph && noCallGraph)) {
      mkdir("dot", S_IRWXU | S_IRWXG | S_IRWXO);
      mkdir("img", S_IRWXU | S_IRWXG | S_IRWXO);
      if (!noCFG)
	mkdir("txt", S_IRWXU | S_IRWXG | S_IRWXO);
    }
    
    // Build the data : use visitors
    cout << "Visiting NAST and collecting datas...\n";
    buildDataOfNast();

    // Write the html pages
    if (!noHtml) {
      cout << "Writing html pages...\n";
      mkdir("html", S_IRWXU | S_IRWXG | S_IRWXO);
      writeHTMLpages();
    }

    // build dom Document and write them
    if (!noXml) {
      mkdir("xml", S_IRWXU | S_IRWXG | S_IRWXO);
      buildDOM_Document();
      cout << "Writing xml file function.xml...\n";
      XMLWriter::write_XMLonFile(functionDOM, "xml/function.xml");
      cout << "Writing xml file declaration.xml...\n";
      XMLWriter::write_XMLonFile(declarationDOM, "xml/declaration.xml");
      cout << "Writing xml file var_used.xml...\n";
      XMLWriter::write_XMLonFile(var_usedDOM, "xml/var_used.xml");
      cout << "Writing xml file parameter.xml...\n";
      XMLWriter::write_XMLonFile(parameterDOM, "xml/parameter.xml");
      cout << "Writing xml file stmt_statistic.xml...\n";
      XMLWriter::write_XMLonFile(stmt_statisticDOM, "xml/stmt_statistic.xml");
      cout << "Writing xml file expr_statistic.xml...\n";
      XMLWriter::write_XMLonFile(expr_statisticDOM, "xml/expr_statistic.xml");
      cout << "Writing xml file reach_statistic.xml...\n";
      XMLWriter::write_XMLonFile(reach_statisticDOM, "xml/reach_statistic.xml");
      cout << "Writing xml file nast_statistic.xml...\n";
      XMLWriter::write_XMLonFile(nast_statisticDOM, "xml/nast_statistic.xml");
    }
    
    cout << "\nAll done !\n\n";

    // Free memory
    deleteData();
    deleteNAST();
  }

  catch (bad_XOgastan & b) {
    cerr << "\n-->An error occured !!\n";
    b.printMessages ();
  }

  catch (const XMLException & toCatch)  {
    cerr << "\nAn error occured\n  Error: "
      << a2b::XMLChar2string (toCatch.getMessage ()) << "\n" << endl;
    exit (EXIT_FAILURE);
  }

  catch (...) {
    cerr << "\n-->An error occured !!\n";
    exit (EXIT_FAILURE);
  }

  // And call the termination method
  XMLPlatformUtils::Terminate ();

  return 0;
}

