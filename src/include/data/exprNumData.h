/***************************************************************************
			   exprNumData.h  -  description
			      -------------------
     begin                : Aug 31 2001
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

#ifndef _EXPR_NUM_DATA_H
#define _EXPR_NUM_DATA_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "data/dataObj.h"

#include "nast/nast_code.h"

#include <string>

// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

//! This class holds informations about the number of expressions
/*!
  This class can be used to hold the number of expressions present 
  in a function, in all the nast, in sub-block of function.

  The expression counted are a subset of alls the expressions.
  They are only the expression present in the C standard ANSI
  grammar.
*/
class exprNumData : public dataObj
{

 private:

  //---- Attributes

  //! The number of the expressions counted
  static const int exprNumber = 40;

  //! The array of the counted expressions
  /*!
    Each element of this array can be associated with 
    one or more expr_n.
  */
  long             counted[exprNumber];

  //! The enumeration of the index of the array counted
  enum {
    // unary
    negate_index = 0, bit_not_index, sizeof_index, 
    truth_not_index, addr_index, indirect_ref_index,
    
    // binary
    plus_index, minus_index, mult_index, div_index,
    mod_index, lshift_index, rshift_index, 
    bit_ior_index, bit_xor_index, bit_and_index,
    predecrement_index, preincrement_index,
    postdecrement_index, postincrement_index,
    logical_and_index, logical_or_index,
    lt_index, le_index, gt_index,
    ge_index, eq_index, ne_index,
    compound_index, component_ref_index,
    assignement_index, array_ref_index, call_index, 
    
    // ternary
    cond_index,

    // others
    othr_index,
    
    // index for the error, used for the non expression code
    error_index
  };

  //! Access to the elements of the array
  /*!
    Given a nast_code it return the currespondent array index
    
    \param code nast_code
    
    \return The index of the array currespondent to code
  */
  int nast_code2index(nast_code code);

 public:
  //! Constructor
  exprNumData();
  
  //! Destructor
  ~exprNumData() { }

  //---- Members

  //---- Add

  //! Add an expression
  /*!
    \param code The code of the expression
  */
  void addExpr(nast_code code); 
  
  //---- GET

  //! Get total number of an expression
  /*!
    \param code The code of the expression
    
    \return The numebr of presence of the expression
  */
  long numExpr(nast_code code);

  //---- TOTAL

  //! Get total number of unary expressions
  /*!
    \return The number of 
    negate (-), bit_not (~), sizeof, 
    truth_not (!), addr (&), indirect_ref (*)
  */
  long totalUnaryExpr(void);

  //! Get total number of binary expressions
  /*!
    \return The number of 
    plus (+), minus (-), mult (*), div (/),
    mod (%), lshift (<<), rshift (>>), 
    bit_ior (^), bit_xor (|), bit_and (&),
    predecrement (--a), preincrement (++a),
    postdecrement (a--), postincrement (a++),
    logical_and (&&), logical_or (||),
    lt (<), le (<=), gt (>),
    ge (>=), eq (==), ne (!=),
    compound (,), component_ref (.),
    assignement (=), array_ref ([]), call ( () )
  */
  long totalBinaryExpr(void);

  //! Get total number of ternary expressions
  /*!
    \return The number of 
    cond (?:)
  */
  long totalTernaryExpr(void);

  //! Get total number of others expressions
  /*!
    \return The number of expressions that AREN'T :
    negate (-), bit_not (~), sizeof, 
    truth_not (!), addr (&), indirect_ref (*),
    plus (+), minus (-), mult (*), div (/),
    mod (%), lshift (<<), rshift (>>), 
    bit_ior (^), bit_xor (|), bit_and (&),
    predecrement (--a), preincrement (++a),
    postdecrement (a--), postincrement (a++),
    logical_and (&&), logical_or (||),
    lt (<), le (<=), gt (>),
    ge (>=), eq (==), ne (!=),
    compound (,), component_ref (.),
    assignement (=), array_ref ([]), call ( () ),
    cond (?:)
  */
  long totalOthrExpr(void);
  
  //! Get total number of  expressions
  /*!
    \return The number of 
    negate (-), bit_not (~), sizeof, 
    truth_not (!), addr (&), indirect_ref (*),
    plus (+), minus (-), mult (*), div (/),
    mod (%), lshift (<<), rshift (>>), 
    bit_ior (^), bit_xor (|), bit_and (&),
    predecrement (--a), preincrement (++a),
    postdecrement (a--), postincrement (a++),
    logical_and (&&), logical_or (||),
    lt (<), le (<=), gt (>),
    ge (>=), eq (==), ne (!=),
    compound (,), component_ref (.),
    assignement (=), array_ref ([]), call ( () ),
    cond (?:)
  */
  long totalExpr(void);
  
};

#endif


  



