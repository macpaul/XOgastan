/***************************************************************************
			   write_htmlNastStat.cpp  -  description
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

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "htmlWriter/write_htmlNastStat.h"

// ---------------------------------------------------------------------------
//  Members
// ---------------------------------------------------------------------------

void 
write_htmlNastStat::writeGlobalStatistics(void) {

  htmlpage << "The follows table list the number of each nast_node "
	   << "found into the NAST<br>\n";
  
  htmlpage << "Maybe this number is less than the real number of "
	   << "nodes in the currespondent file, but remember ... "
	   << "this version of XOgastan analyse only the C "
	   << "part of a GccAST !<br><br>\n";
  
  htmlpage << *nastStat;

  totals = nastStat->totalNastNode();

  return;
}


void 
write_htmlNastStat::writeCell(string value) {
  // value
  htmlpage << "\t<td  bgcolor=\"blue\" width=\"70\">"
	   << "<font color=\"yellow\"b>"
	   << value << "</font><td>\n";
  return;
}

void 
write_htmlNastStat::writeCell(long value, double valueX100) {
  // value
  htmlpage << "\t<td  bgcolor=\"blue\" width=\"70\">"
	   << "<font color=\"yellow\"b>"
	   << value << ", " << valueX100 << "%</font><td>\n";
  return;
}

void 
write_htmlNastStat::writePartialStatistics(void){
  dataDrawerListIterator   p;         // browse the list
  dataDrawer               *dataB;    // dataDrawer of the function
  fnctData                 *fData;    // current function Data
  nastNumData              *nnData;   // statistics of a function
  long                     sumTot;    // sum of the totals node in the functions

  htmlpage << "This table show what's the portion that can be "
	   << "reached when, from a first compound_stmt of the"
	   << "function's body, we navigate between the nodes<br><br>\n";

  htmlpage << "<table border=\"0\" width=\"420\" cellspacing=\"2\">\n";

  htmlpage << "\t<tr>\n";
  // table titles
  writeCell("");
  writeCell("*_TYPE");
  writeCell("*_DECL");
  writeCell("*_STMT");
  writeCell("*_CST");
  writeCell("*_EXPR");
  writeCell("Other");
  writeCell("<b>TOTAL<b>");
  htmlpage << "\t</tr>\n";

  // browse one function for time
  p = dataBL->begin();
  while (p != dataBL->end()) {
    dataB = *p;
    p++;
    
    fData = dataB->getFnctData();
    
    if (fData->hasBody()) {
      
      nnData = dataB->getNastNumData();

      htmlpage << "\t<tr>\n";

      htmlpage << "\t<td  bgcolor=\"lightblue\" width=\"70\">"
	       << "<a href=\"" 
	       << HTMLfilesRegister::htmlFile(*fData)
	       << "\">" << fData->getName() << "</a><td>\n";
      
      // write partial stat
      writeCell(nnData->totalTypeNastNode(),
		getX100(nnData->totalTypeNastNode(),totals));
      writeCell(nnData->totalDeclNastNode(),
		getX100(nnData->totalDeclNastNode(),totals));
      writeCell(nnData->totalStmtNastNode(),
		getX100(nnData->totalStmtNastNode(),totals));
      writeCell(nnData->totalCstNastNode(),
		getX100(nnData->totalCstNastNode(),totals));
      writeCell(nnData->totalExprNastNode(),
		getX100(nnData->totalExprNastNode(),totals));
      writeCell(nnData->totalOthrNastNode(),
		getX100(nnData->totalOthrNastNode(),totals));

      sumTot = (nnData->totalTypeNastNode() +
		nnData->totalDeclNastNode() +
		nnData->totalStmtNastNode() +
		nnData->totalCstNastNode() +
		nnData->totalExprNastNode() +
		nnData->totalOthrNastNode());
      writeCell(sumTot,getX100(sumTot,totals));

      htmlpage << "\t</tr>\n";

    }
  }
  
  htmlpage << "</table>";
  
  return;
}


void 
write_htmlNastStat::writePage(void) 
{
  pageTitle = "NAST statistics";
  htmlpage.open (HTMLfilesRegister::nastStatistics);
  writeHead();
  writeIndex();

  // Global statistics
  writeSectionTitle("Statistics about all the NAST");
  writeGlobalStatistics();
  
  // Partial statistics
  writeSectionTitle("Statistics about the functions with body");
  writePartialStatistics();

  writeIndex();
  writeFoot();
  htmlpage.close();

  return;
}






