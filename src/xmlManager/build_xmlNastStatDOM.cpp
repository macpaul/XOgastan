/***************************************************************************
			   build_xmlNastStatDOM.cpp  -  description
			      -------------------
     begin                : Sept 6 2001
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
#include "xmlManager/build_xmlNastStatDOM.h"


// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------
extern char *xmlFile;


void 
build_xmlNastStatDOM::newDOM_Document(void) {
  
  doc = new DOM_Document;

  *doc = DOM_Document::createDocument();
  doc->appendChild(doc->createDocumentType("nast_statistic"));
  root = doc->createElement("nast_statistic");
  doc->appendChild(root);

  return;
}


void 
build_xmlNastStatDOM::buildDOM(void) 
  throw (bad_XML) 
{
  int      i;       // counter

  try {
    newDOM_Document();
    
    rowNumber = 0;
	
    // Types
    for (i = VOID_TYPE; i <= UNION_TYPE; i++) 
      addRow(xmlFile, a2b::nast_code2string((nast_code)i), 
	     nastStat->numNast((nast_code)i) );
    addRow(xmlFile,"Total_TYPE",
	   nastStat->totalTypeNastNode() );
    
    // Decls
    for (i = TYPE_DECL; i <= RESULT_DECL; i++) 
      addRow(xmlFile, a2b::nast_code2string((nast_code)i), 
	     nastStat->numNast((nast_code)i) );
    addRow(xmlFile, "Total_DECL",
	   nastStat->totalDeclNastNode() );
    
    // Stmts
    for (i = BREAK_STMT; i <= ASM_STMT; i++) 
      addRow(xmlFile, a2b::nast_code2string((nast_code)i), 
	     nastStat->numNast((nast_code)i) );
    addRow(xmlFile, "Total_STMT",
	   nastStat->totalStmtNastNode() );
    
    //  Csts
    addRow(xmlFile, "integer_cst",
	   nastStat->numNast(INTEGER_CST) );
    
    addRow(xmlFile, "real_cst",
	   nastStat->numNast(REAL_CST) );
    addRow(xmlFile, "string_cst",
	   nastStat->numNast(STRING_CST) );
    addRow(xmlFile, "Total_CST",
	   nastStat->totalCstNastNode() );
    
    // Expr
    addRow(xmlFile, a2b::nast_code2string(NEGATE_EXPR),
	   nastStat->numNast(NEGATE_EXPR));
    addRow(xmlFile, a2b::nast_code2string(BIT_NOT_EXPR),
	   nastStat->numNast(BIT_NOT_EXPR));
    addRow(xmlFile, a2b::nast_code2string(TRUTH_NOT_EXPR),
	   nastStat->numNast(TRUTH_NOT_EXPR));
    addRow(xmlFile, a2b::nast_code2string(ADDR_EXPR),
	   nastStat->numNast(ADDR_EXPR));
    addRow(xmlFile, a2b::nast_code2string(INDIRECT_REF),
	   nastStat->numNast(INDIRECT_REF));
    addRow(xmlFile, a2b::nast_code2string(SIZEOF_EXPR),
	   nastStat->numNast(SIZEOF_EXPR));
    addRow(xmlFile, a2b::nast_code2string(PLUS_EXPR),
	   nastStat->numNast(PLUS_EXPR));
    addRow(xmlFile, a2b::nast_code2string(MINUS_EXPR),
	   nastStat->numNast(MINUS_EXPR));
    addRow(xmlFile, a2b::nast_code2string(MULT_EXPR),
	   nastStat->numNast(MULT_EXPR));
    // also RDIV_EXPR
    addRow(xmlFile, 
	   a2b::nast_code2string(TRUNC_DIV_EXPR) + "+" +
	   a2b::nast_code2string(RDIV_EXPR),
	   nastStat->numNast(TRUNC_DIV_EXPR));
    addRow(xmlFile, a2b::nast_code2string(TRUNC_MOD_EXPR),
	       nastStat->numNast(TRUNC_MOD_EXPR));
    addRow(xmlFile, a2b::nast_code2string(LSHIFT_EXPR),
	   nastStat->numNast(LSHIFT_EXPR));
    addRow(xmlFile, a2b::nast_code2string(RSHIFT_EXPR),
	   nastStat->numNast(RSHIFT_EXPR));
    addRow(xmlFile, a2b::nast_code2string(BIT_IOR_EXPR),
	   nastStat->numNast(BIT_IOR_EXPR));
    addRow(xmlFile, a2b::nast_code2string(BIT_XOR_EXPR),
	   nastStat->numNast(BIT_XOR_EXPR));
    addRow(xmlFile, a2b::nast_code2string(BIT_AND_EXPR),
	   nastStat->numNast(BIT_AND_EXPR));
    addRow(xmlFile, a2b::nast_code2string(PREDECREMENT_EXPR),
	   nastStat->numNast(PREDECREMENT_EXPR));
    addRow(xmlFile, a2b::nast_code2string(POSTDECREMENT_EXPR),
	   nastStat->numNast(POSTDECREMENT_EXPR));
    addRow(xmlFile, a2b::nast_code2string(PREINCREMENT_EXPR),
	   nastStat->numNast(PREINCREMENT_EXPR));
    addRow(xmlFile, a2b::nast_code2string(POSTINCREMENT_EXPR),
	   nastStat->numNast(POSTINCREMENT_EXPR));
    // also TRUTH_AND_EXPR
    addRow(xmlFile, 
	   a2b::nast_code2string(TRUTH_ANDIF_EXPR) + "+" +
	   a2b::nast_code2string(TRUTH_AND_EXPR),
	   nastStat->numNast(TRUTH_ANDIF_EXPR));
    // also TRUTH_OR_EXPR
    addRow(xmlFile, 
	   a2b::nast_code2string(TRUTH_ORIF_EXPR) + "+" +
	   a2b::nast_code2string(TRUTH_ORIF_EXPR),
	   nastStat->numNast(TRUTH_ORIF_EXPR));
    addRow(xmlFile, a2b::nast_code2string(LT_EXPR),
	   nastStat->numNast(LT_EXPR));
    addRow(xmlFile, a2b::nast_code2string(LE_EXPR),
	   nastStat->numNast(LE_EXPR));
    addRow(xmlFile, a2b::nast_code2string(GT_EXPR),
	   nastStat->numNast(GT_EXPR));
    addRow(xmlFile, a2b::nast_code2string(GE_EXPR),
	   nastStat->numNast(GE_EXPR));
    addRow(xmlFile, a2b::nast_code2string(EQ_EXPR),
	   nastStat->numNast(EQ_EXPR));
    addRow(xmlFile, a2b::nast_code2string(NE_EXPR),
	   nastStat->numNast(NE_EXPR));
    addRow(xmlFile, a2b::nast_code2string(COMPOUND_EXPR),
	   nastStat->numNast(COMPOUND_EXPR));
    addRow(xmlFile, a2b::nast_code2string(COMPONENT_REF),
	   nastStat->numNast(COMPONENT_REF));
    // also INIT_EXPR
    addRow(xmlFile, 
	   a2b::nast_code2string(MODIFY_EXPR) + "+" +
	   a2b::nast_code2string(INIT_EXPR),
	   nastStat->numNast(MODIFY_EXPR));
    addRow(xmlFile, a2b::nast_code2string(ARRAY_REF),
	   nastStat->numNast(ARRAY_REF));
    addRow(xmlFile, a2b::nast_code2string(CALL_EXPR),
	   nastStat->numNast(CALL_EXPR));
    addRow(xmlFile, a2b::nast_code2string(COND_EXPR),
	   nastStat->numNast(COND_EXPR));
    addRow(xmlFile, "Total_EXPR",
	   nastStat->totalExprNastNode() );
    
    // Othrs
    addRow(xmlFile, "tree_list",
	   nastStat->numNast(TREE_LIST) );
    addRow(xmlFile, "identifier_node",
	   nastStat->numNast(IDENTIFIER_NODE) );
    addRow(xmlFile, "case_label",
	   nastStat->numNast(CASE_LABEL) );
    addRow(xmlFile, "Total_OTHR",
	   nastStat->totalOthrNastNode() );
    
    // Totals
    addRow(xmlFile, "Total_NAST_NODES",
	   nastStat->totalNastNode() );
    
  }
  
  catch (const XMLException& e)
    {
      throw bad_XML("build_xmlNastStatDOM",
		    a2b::XMLChar2string(e.getMessage()) );
    }

  catch (const DOM_DOMException& e)
    {
      XMLDOM_str_exception DOMse;
      throw bad_XML("build_xmlNastStatDOM",
		    DOMse(e.code));
    }

  catch (...) 
    {
      throw bad_XML("build_xmlNastStatDOM",
		    "An unknown error occured during DOM manipulation\n ");
    }
  
  return;
}




