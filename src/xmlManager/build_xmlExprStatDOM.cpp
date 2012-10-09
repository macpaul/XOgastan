/***************************************************************************
			   build_xmlExprStatDOM.cpp  -  description
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
#include "xmlManager/build_xmlExprStatDOM.h"


// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

void 
build_xmlExprStatDOM::newDOM_Document(void) {
  
  doc = new DOMDocument;

  *doc = DOMDocument::createDocument();
  doc->appendChild(doc->createDocumentType("expr_statistic"));
  root = doc->createElement("expr_statistic");
  doc->appendChild(root);

  return;
}


void 
build_xmlExprStatDOM::buildDOM(void) 
  throw (bad_XML) 
{
  dataDrawerListIterator   p;         // browse the list
  dataDrawer               *dataB;    // current dataDrawer
  exprNumData           *enData;   // datas to write


  try {
    newDOM_Document();
    
    rowNumber = 0;
    p = dataBL->begin();
    while (p != dataBL->end()) {
      dataB = *p;
      p++;
      
      // extract data of the function and the declaration list
      fData = dataB->getFnctData();
      if ((enData = dataB->getExprNumData())) {
	string fnctName = fData->getName();
	
	addRow(fnctName, a2b::nast_code2string(NEGATE_EXPR),
	       enData->numExpr(NEGATE_EXPR));
	addRow(fnctName, a2b::nast_code2string(BIT_NOT_EXPR),
	       enData->numExpr(BIT_NOT_EXPR));
	addRow(fnctName, a2b::nast_code2string(TRUTH_NOT_EXPR),
	       enData->numExpr(TRUTH_NOT_EXPR));
	addRow(fnctName, a2b::nast_code2string(ADDR_EXPR),
	       enData->numExpr(ADDR_EXPR));
	addRow(fnctName, a2b::nast_code2string(INDIRECT_REF),
	       enData->numExpr(INDIRECT_REF));
	addRow(fnctName, a2b::nast_code2string(SIZEOF_EXPR),
	       enData->numExpr(SIZEOF_EXPR));
	addRow(fnctName, a2b::nast_code2string(PLUS_EXPR),
	       enData->numExpr(PLUS_EXPR));
	addRow(fnctName, a2b::nast_code2string(MINUS_EXPR),
	       enData->numExpr(MINUS_EXPR));
	addRow(fnctName, a2b::nast_code2string(MULT_EXPR),
	       enData->numExpr(MULT_EXPR));
	// also RDIV_EXPR
	addRow(fnctName, a2b::nast_code2string(TRUNC_DIV_EXPR),
	       enData->numExpr(TRUNC_DIV_EXPR));
	addRow(fnctName, a2b::nast_code2string(TRUNC_MOD_EXPR),
	       enData->numExpr(TRUNC_MOD_EXPR));
	addRow(fnctName, a2b::nast_code2string(LSHIFT_EXPR),
	       enData->numExpr(LSHIFT_EXPR));
	addRow(fnctName, a2b::nast_code2string(RSHIFT_EXPR),
	       enData->numExpr(RSHIFT_EXPR));
	addRow(fnctName, a2b::nast_code2string(BIT_IOR_EXPR),
	       enData->numExpr(BIT_IOR_EXPR));
	addRow(fnctName, a2b::nast_code2string(BIT_XOR_EXPR),
	       enData->numExpr(BIT_XOR_EXPR));
	addRow(fnctName, a2b::nast_code2string(BIT_AND_EXPR),
	       enData->numExpr(BIT_AND_EXPR));
	addRow(fnctName, a2b::nast_code2string(PREDECREMENT_EXPR),
	       enData->numExpr(PREDECREMENT_EXPR));
	addRow(fnctName, a2b::nast_code2string(POSTDECREMENT_EXPR),
	       enData->numExpr(POSTDECREMENT_EXPR));
	addRow(fnctName, a2b::nast_code2string(PREINCREMENT_EXPR),
	       enData->numExpr(PREINCREMENT_EXPR));
	addRow(fnctName, a2b::nast_code2string(POSTINCREMENT_EXPR),
	       enData->numExpr(POSTINCREMENT_EXPR));
	// also TRUTH_AND_EXPR
	addRow(fnctName, a2b::nast_code2string(TRUTH_ANDIF_EXPR),
	       enData->numExpr(TRUTH_ANDIF_EXPR));
	// also TRUTH_OR_EXPR
	addRow(fnctName, a2b::nast_code2string(TRUTH_ORIF_EXPR),
	       enData->numExpr(TRUTH_ORIF_EXPR));
	addRow(fnctName, a2b::nast_code2string(LT_EXPR),
	       enData->numExpr(LT_EXPR));
	addRow(fnctName, a2b::nast_code2string(LE_EXPR),
	       enData->numExpr(LE_EXPR));
	addRow(fnctName, a2b::nast_code2string(GT_EXPR),
	       enData->numExpr(GT_EXPR));
	addRow(fnctName, a2b::nast_code2string(GE_EXPR),
	       enData->numExpr(GE_EXPR));
	addRow(fnctName, a2b::nast_code2string(EQ_EXPR),
	       enData->numExpr(EQ_EXPR));
	addRow(fnctName, a2b::nast_code2string(NE_EXPR),
	       enData->numExpr(NE_EXPR));
	addRow(fnctName, a2b::nast_code2string(COMPOUND_EXPR),
	       enData->numExpr(COMPOUND_EXPR));
	addRow(fnctName, a2b::nast_code2string(COMPONENT_REF),
	       enData->numExpr(COMPONENT_REF));
	// also INIT_EXPR
	addRow(fnctName, a2b::nast_code2string(MODIFY_EXPR),
	       enData->numExpr(MODIFY_EXPR));
	addRow(fnctName, a2b::nast_code2string(ARRAY_REF),
	       enData->numExpr(ARRAY_REF));
	addRow(fnctName, a2b::nast_code2string(CALL_EXPR),
	       enData->numExpr(CALL_EXPR));
	addRow(fnctName, a2b::nast_code2string(COND_EXPR),
	       enData->numExpr(COND_EXPR));
    
      }
    
    }
    
  
  }

  catch (const XMLException& e)
    {
      throw bad_XML("build_xmlExprStatDOM",
		    a2b::XMLChar2string(e.getMessage()) );
    }

  catch (const DOM_DOMException& e)
    {
      XMLDOM_str_exception DOMse;
      throw bad_XML("build_xmlExprStatDOM",
		    DOMse(e.code));
    }

  catch (...) 
    {
      throw bad_XML("build_xmlExprStatDOM",
		    "An unknown error occured during DOM manipulation\n ");
    }
  
  return;
}










