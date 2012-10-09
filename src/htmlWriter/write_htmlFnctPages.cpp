/***************************************************************************
			   write_htmlFnctPages.cpp  -  description
			      -------------------
     begin                : Aug 30 2001
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
#include "htmlWriter/write_htmlFnctPages.h"

// ---------------------------------------------------------------------------
//  Members
// ---------------------------------------------------------------------------

void 
write_htmlFnctPages::writePageIndex(void) { 
  htmlpage << "<A name=\"TOP\">";

  if (!noBodyGraph)    
    htmlpage 
      << "<A href=\"#bodyGraph\">Graph of the body<BR></A>\n";
  if (!noCFG)    
    htmlpage 
      << "<A href=\"#CFG\">Control flow graph<BR></A>\n";
  if (!noStmtStat) 
    htmlpage 
      << "<A href=\"#stmtStatistics\">Statements statistics<BR></A>\n\n";
  if ( (!noDeclsList) && (dataB->hasDeclsList()) )
    htmlpage 
      << "<A href=\"#declsList\">Declarations into the function<BR></A>\n\n";
  if ( (!noVarUsed) && (dataB->hasVarUsedList()) )
    htmlpage 
      << "<A href=\"#varUsedList\">Variables used by the function<BR></A>\n\n";
  if ( (!noExprsList) && (dataB->hasExprsList()) ) 
    htmlpage 
      << "<A href=\"#exprsList\">List of the expressions</A><br>\n\n";
  if (!noExprStat) 
    htmlpage 
      << "<A href=\"#exprStatistics\">Expressions statistics<BR></A>\n\n";
  if (!noCallGraph)
    htmlpage << "<A href=\"#callGraph\">Call graph<BR></A>\n\n";
  
  htmlpage << "<br><br>";
  return;
}


void 
write_htmlFnctPages::writeBodyGraph(void) {

  htmlpage << "This is the graph of the tree statements of the function "
	   << fData->getName() << ".<br>\n"
	   << "The node's mame is composed by two part :<br>\n"
	   << "<ol>"
	   << "\t<li>The code of the statement\n"
	   << "\t<li>An index\n"
	   << "</ol>\n";

  // The graph of the body
  htmlpage << "<p><center><img src=\""
	   << "../img/" << dataB->getBodyGraphGIF()
	   << "\"  border=\"0\"></center></p>\n";
  
  htmlpage << "cyan - cycle node : for, do, while<br>"
	   << "green - condition node : if, switch<br>"
	   << "red - node that modify the execution flow : "
	   << "break, continue, return, goto<br>"
	   << "yellow : others node<br>\n";

  return;
}

void 
write_htmlFnctPages::writeCFG(void) {

  htmlpage << "This is CFG of the function "
	   << fData->getName() << ".<br>\n"
	   << "The node's mame is composed by two part :<br>\n"
	   << "<ol>"
	   << "\t<li>The code\n"
	   << "\t<li>An index\n"
	   << "</ol>\n";

  // The graph of the body
  htmlpage << "<p><center><img src=\""
	   << "../img/" << dataB->getCfgGIF()
	   << "\"  border=\"0\"></center></p>\n";
  
  return;
}


void 
write_htmlFnctPages::writeCallGraph(void) {

  htmlpage << "This is a call graph of the function called by "
	   << fData->getName() << ".<br>\n"
	   << "The node's mame of a function is composed by two part :<br>\n"
	   << "<ol>"
	   << "\t<li>The name of the function\n"
	   << "\t<li>The index of the node\n"
	   << "</ol>\n";

  // The call graph
  htmlpage << "<p><center><img src=\""
	   <<  "../img/"  << dataB->getCallGraphGIF() 
	   << "\"  border=\"0\"></center></p>\n";

  // The list of numbers of calls per function
  callGraphData        *callGraph;       // the call graph
  node                 *n;               // the node of the graph

  callGraph = dataB->getCallGraph();

  
  if (callGraph->hasNodes()) {

    htmlpage << "<table border=\"0\" width=\"100%\" cellspacing=\"2\">\n\n";
    htmlpage << "\t<tr>\n";
    htmlpage << "\t<td width=\"60%\">"
	     << "<b>Function</b>"
	     << "</td>\n\n";
    htmlpage << "\t<td width=\"20%\">"
	     << "<b>Index</b>"
	     << "</td>\n\n";
    htmlpage << "\t<td width=\"20%\">"
	     << "<b>Calls</b>"
	     << "</td>\n\n";
    htmlpage << "\t</tr>\n";
    
    n = callGraph->firstNode();
    
    htmlpage << "\t<tr>\n";
    // name
    htmlpage << "\t<td bgcolor=\"#AFF7ED\" width=\"60%\">"
	     << n->name
	     << "</td>\n";
    // index 
    htmlpage << "\t<td bgcolor=\"#AFF7ED\" width=\"20%\">"
	     << (long) n->id
	     << "</td>\n\n";
    // calls 
    htmlpage << "\t<td bgcolor=\"#AFF7ED\" width=\"20%\">"
	     << (long) callGraph->getCalls(n->id)
	     << "</td>\n\n";
    htmlpage << "\t</tr>\n";
    
    while (callGraph->hasNextNode()) {
      n = callGraph->nextNode();
      
      htmlpage << "\t<tr>\n";
      // name
      htmlpage << "\t<td bgcolor=\"#AFF7ED\" width=\"60%\">"
	       << n->name
	       << "</td>\n";
      // index 
      htmlpage << "\t<td bgcolor=\"#AFF7ED\" width=\"20%\">"
	       << (long) n->id
	       << "</td>\n\n";
      // calls 
      htmlpage << "\t<td bgcolor=\"#AFF7ED\" width=\"20%\">"
	       << (long) callGraph->getCalls(n->id)
	       << "</td>\n\n";
      htmlpage << "\t</tr>\n";
    }
    htmlpage << "</table>\n\n";
  }
  
  return;
}


void 
write_htmlFnctPages::writePage(void) 
{
  // most of the informations can be write only if the function has a body !

  dataDrawerListIterator   p;         // browse the list
  string                fnctName;     // name of the function

  
  // Browse list one function for time
  p = dataBL->begin();
  while (p != dataBL->end()) {
    dataB = *p;
    p++;
    
    fData = dataB->getFnctData();
    
    cout << "Generating html page for function " 
	 << (fnctName = fData->getName()) << "...\n";

    htmlpage.open((HTMLfilesRegister::htmlFile(*fData)).c_str());

    // begin of the page
    pageTitle = fnctName ;
    writeHead();
    writeIndex();
    
    htmlpage << "<br><br>\n";
    if (fnctName != "")
      htmlpage << "This is the page of the function " 
	       << fnctName << ".<br><br>\n";

    htmlpage << *fData
	     << "<br><l><br>\n\n";
    
    if (fData->hasBody()) {
      
      writePageIndex();
      
      // write body graph
      if (!noBodyGraph) {
	htmlpage << "<A name=\"bodyGraph\">\n";
	writeSectionTitle("Graph of the body");
	writeBodyGraph();
      }
      
      // write CFG
      if (!noCFG) {
	htmlpage << "<A name=\"CFG\">\n";
	writeSectionTitle("Control flow graph");
	writeCFG();
      }

      // write stmt stat
      if (!noStmtStat) {
	htmlpage << "<A name=\"stmtStatistics\">\n";
	writeSectionTitle("Statements statistics");
	htmlpage << *(dataB->getStmtNumData());
      }
      
      // write decl list
      if ( (!noDeclsList) && (dataB->hasDeclsList()) ) {
	htmlpage << "<A name=\"declsList\">\n";
	writeSectionTitle("Declarations into the function");
	htmlpage << *(dataB->getDeclsList());
      }
      
      // write var used
      if ( (!noVarUsed) && (dataB->hasVarUsedList()) ) {
	htmlpage << "<A name=\"varUsedList\">\n";
	writeSectionTitle("Variables used by the function");
	htmlpage << *(dataB->getVarUsedList());
      }

      // write exprs list
      if ( (!noExprsList) && (dataB->hasExprsList()) ) {
	htmlpage << "<A name=\"exprsList\">\n";
	writeSectionTitle("List of the expressions");
	htmlpage << *(dataB->getExprsList());
      }
      
      // write expr stat
      if (!noExprStat) {
	htmlpage << "<A name=\"exprStatistics\">\n";
	writeSectionTitle("Expression statistics");
	htmlpage << *(dataB->getExprNumData());
      }
      
      // write call graph
      if (!noCallGraph) {
	htmlpage << "<A name=\"callGraph\">\n";
	writeSectionTitle("Call graph");
	writeCallGraph();
      }

    }   

    // end of the page
    writeIndex();
    writeFoot();
    htmlpage.close();
  }

  return;
}






