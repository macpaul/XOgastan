/***************************************************************************
			   nastNumData.cpp  -  description
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
#include "data/nastNumData.h"

// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

// Constructor
nastNumData::nastNumData() { 
  long i;
  for (i=0; i < nastNumber; i++)
    counted[i]=0;
  return;
}

long 
nastNumData::totalTypeNastNode(void) {
  int i;
  long total;

  for (i = VOID_TYPE, total=0; i <= UNION_TYPE; i++) 
    total += counted[i];

  return total;
}


long 
nastNumData::totalDeclNastNode(void) {
  int i;
  long total;

  for (i = TYPE_DECL, total=0; i <= RESULT_DECL; i++) 
    total += counted[i];

  return total;
}


long 
nastNumData::totalStmtNastNode(void) {
  int i;
  long total;

  for (i = BREAK_STMT, total=0; i <= ASM_STMT; i++) 
    total += counted[i];

  return total;
}


long 
nastNumData::totalCstNastNode(void) {
  return ( counted[INTEGER_CST] + 
	   counted[REAL_CST] + 
	   counted[STRING_CST]);
}


long 
nastNumData::totalExprNastNode(void) {
  return (
	  counted[NEGATE_EXPR] +   counted[BIT_NOT_EXPR] +
	  counted[SIZEOF_EXPR] +  counted[TRUTH_NOT_EXPR] +
	  counted[ADDR_EXPR] +  counted[INDIRECT_REF] +
	  counted[PLUS_EXPR] +  counted[MINUS_EXPR] +
	  counted[MULT_EXPR] +  counted[TRUNC_DIV_EXPR] +
	  counted[RDIV_EXPR] +  counted[TRUNC_MOD_EXPR] +
	  counted[LSHIFT_EXPR] +  counted[RSHIFT_EXPR] +
	  counted[BIT_IOR_EXPR] +  counted[BIT_XOR_EXPR] +
	  counted[BIT_AND_EXPR] +  counted[PREDECREMENT_EXPR] +
	  counted[PREINCREMENT_EXPR] +  counted[POSTDECREMENT_EXPR] +
	  counted[POSTINCREMENT_EXPR] +  counted[TRUTH_ANDIF_EXPR] +
	  counted[TRUTH_AND_EXPR] +  counted[TRUTH_ORIF_EXPR] +
	  counted[TRUTH_OR_EXPR] +  counted[LT_EXPR] +
	  counted[LE_EXPR] +  counted[GT_EXPR] +
	  counted[GE_EXPR] +  counted[EQ_EXPR] +
	  counted[NE_EXPR] +  counted[COMPOUND_EXPR] +
	  counted[COMPONENT_REF] +  counted[MODIFY_EXPR] +
	  counted[INIT_EXPR] +  counted[ARRAY_REF] +
	  counted[CALL_EXPR] +  counted[COND_EXPR]
	  );
  
}
  

long 
nastNumData::totalOthrNastNode(void) {
  return ( counted[TREE_LIST] + 
	   counted[IDENTIFIER_NODE] + 
	   counted[CASE_LABEL]);
}

long 
nastNumData::totalNastNode(void) {
  int i;
  long total;

  for (i = TYPE_DECL, total=0; i < nastNumber; i++) 
    total += counted[i];

  return total;
}

void 
nastNumData::reset(void) { 
  long i;
  for (i=0; i < nastNumber; i++)
    counted[i]=0;
  return;
}









