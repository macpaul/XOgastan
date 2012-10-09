/***************************************************************************
			   exprNumData.cpp  -  description
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
#include "data/exprNumData.h"

// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

// constructor
exprNumData::exprNumData() { 
  long i;
  for (i=0; i < exprNumber; i++)
    counted[i]=0;
  return;
}




int 
exprNumData::nast_code2index(nast_code code) {
  int index;
  
  switch(code) {
  // unary
  case NEGATE_EXPR:
    index = negate_index; break; 
  case BIT_NOT_EXPR:
    index = bit_not_index; break; 
  case SIZEOF_EXPR:
    index = sizeof_index; break; 
  case TRUTH_NOT_EXPR:
    index = truth_not_index; break; 
  case ADDR_EXPR:
    index = addr_index; break; 
  case INDIRECT_REF:
    index = indirect_ref_index; break;
    
    // binary
  case PLUS_EXPR:
    index = plus_index; break; 
  case MINUS_EXPR:
    index = minus_index; break; 
  case MULT_EXPR:
    index = mult_index; break; 
  case TRUNC_DIV_EXPR:
  case RDIV_EXPR:
    index = div_index; break;
  case TRUNC_MOD_EXPR:
    index = mod_index; break; 
  case LSHIFT_EXPR:
    index = lshift_index; break; 
  case RSHIFT_EXPR:
    index = rshift_index; break; 
  case BIT_IOR_EXPR:
    index = bit_ior_index; break; 
  case BIT_XOR_EXPR:
    index = bit_xor_index; break; 
  case BIT_AND_EXPR:
    index = bit_and_index; break;
  case PREDECREMENT_EXPR:
    index = predecrement_index; break; 
  case PREINCREMENT_EXPR:
    index = preincrement_index; break;
  case POSTDECREMENT_EXPR:
    index = postdecrement_index; break; 
  case POSTINCREMENT_EXPR:
    index = postincrement_index; break;
  case TRUTH_ANDIF_EXPR:
  case TRUTH_AND_EXPR:
    index = logical_and_index; break; 
  case TRUTH_ORIF_EXPR:
  case TRUTH_OR_EXPR:
    index = logical_or_index; break;
  case LT_EXPR:
    index = lt_index; break; 
  case LE_EXPR:
    index = le_index; break; 
  case GT_EXPR:
    index = gt_index; break;
  case GE_EXPR:
    index = ge_index; break; 
  case EQ_EXPR:
    index = eq_index; break; 
  case NE_EXPR:
    index = ne_index; break;
  case COMPOUND_EXPR:
    index = compound_index; break; 
  case COMPONENT_REF:
    index = component_ref_index; break;
  case MODIFY_EXPR:
  case INIT_EXPR:
    index = assignement_index; break; 
  case ARRAY_REF:
    index = array_ref_index; break; 
  case CALL_EXPR:
    index = call_index; break; 
    
    // ternary
  case COND_EXPR:
    index = cond_index; break;
    
    // others
  default:
    index = othr_index; break;
  }

  return index;
}

void 
exprNumData::addExpr(nast_code code) {
  this->counted[nast_code2index(code)]++;
  return;
}
  
long 
exprNumData::numExpr(nast_code code) {
  return this->counted[nast_code2index(code)];
}

long 
exprNumData::totalUnaryExpr(void) {
  long total;
  long i;
  for (i=negate_index, total=0; i <= indirect_ref_index; i++)
	total += counted[i];
  
  return total;
}



long 
exprNumData::totalBinaryExpr(void) {
  long total;
  long i;
  for (i=plus_index, total=0; i <= call_index; i++)
	total += counted[i];
  return total;
}

long 
exprNumData::totalTernaryExpr(void) {
  return this->counted[cond_index];
}

long 
exprNumData::totalOthrExpr(void) {
  return this->counted[othr_index];
}

long 
exprNumData::totalExpr(void) {
  long total;
  long i;
  
  for (i=0, total=0; i < exprNumber; i++)
	total += counted[i];
  
  return total;
}

  




