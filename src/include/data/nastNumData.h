/***************************************************************************
			   nastNumData.h  -  description
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

#ifndef _NAST_NUM_DATA_H
#define _NAST_NUM_DATA_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "data/dataObj.h"

#include "nast/nast_code.h"

// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

//! This class holds the information about the number of nast_node
/*!
  The implementation of this class depend of the file
  nast_code.def If we change this file something will go wrong.
*/
class nastNumData : public dataObj
{

 private:

  //---- Attributes

  //! The number of differents statements class
  static const int nastNumber = LAST_NAST_CODE;

  //! The array of the counted nast_node
  /*!
    Each element of this array is associated with a statement.
    
    The index of the arry are the nast_code.
  */
  long             counted[nastNumber];
  

 public:
  //! Constructor
  nastNumData();
  
  //! Destructor
  ~nastNumData() { }

  //---- Members

  //! Add an other nast_node
  /*!
    \param code The code of the nast_node
  */
  void addNast(nast_code code) {
    this->counted[code]++;
    return;
  }
  
  //---- GET
  
  //! Get total number of a nast_node
  /*!
    \param code The code of the nast_node
    
    \return The number of presence of the nast_node
  */
  long numNast(nast_code code) {
    return this->counted[code];
  }

  //---- TOTAL

  //! Get total number of type nodes
  /*!
    \return the number of :
    VOID_TYPE, 
    FUNCTION_TYPE, 
    INTEGER_TYPE, 
    ENUMERAL_TYPE, 
    REAL_TYPE, 
    POINTER_TYPE, 
    ARRAY_TYPE, 
    RECORD_TYPE, 
    UNION_TYPE
  */
  long totalTypeNastNode(void);

  //! Get total number of decl nodes
  /*!
    \return the number of :
    TYPE_DECL, 
    FUNCTION_DECL, 
    PARM_DECL, 
    VAR_DECL, 
    FIELD_DECL, 
    CONST_DECL, 
    LABEL_DECL, 
    RESULT_DECL
  */
  long totalDeclNastNode(void);

  //! Get total number of stmt nodes
  /*!
    \return the number of :
    BREAK_STMT, 
    CONTINUE_STMT, 
    COMPOUND_STMT, 
    DECL_STMT, 
    EXPR_STMT, 
    DO_STMT, 
    WHILE_STMT, 
    FOR_STMT, 
    GOTO_STMT, 
    LABEL_STMT, 
    IF_STMT, 
    SWITCH_STMT, 
    SCOPE_STMT, 
    RETURN_STMT, 
    ASM_STMT
  */
  long totalStmtNastNode(void);

  //! Get total number of cst nodes
  /*!
    \return the number of :
    INTEGER_CST, 
    REAL_CST, 
    STRING_CST
  */
  long totalCstNastNode(void);

  //! Get total number of expr nodes
  /*!
    \return the number of :
    NEGATE_EXPR,  BIT_NOT_EXPR,
    SIZEOF_EXPR, TRUTH_NOT_EXPR,
    ADDR_EXPR, INDIRECT_REF,
    PLUS_EXPR, MINUS_EXPR,
    MULT_EXPR, TRUNC_DIV_EXPR,
    RDIV_EXPR, TRUNC_MOD_EXPR,
    LSHIFT_EXPR, RSHIFT_EXPR,
    BIT_IOR_EXPR, BIT_XOR_EXPR,
    BIT_AND_EXPR, PREDECREMENT_EXPR,
    PREINCREMENT_EXPR, POSTDECREMENT_EXPR,
    POSTINCREMENT_EXPR, TRUTH_ANDIF_EXPR,
    TRUTH_AND_EXPR, TRUTH_ORIF_EXPR,
    TRUTH_OR_EXPR, LT_EXPR,
    LE_EXPR, GT_EXPR,
    GE_EXPR, EQ_EXPR,
    NE_EXPR, COMPOUND_EXPR,
    COMPONENT_REF, MODIFY_EXPR,
    INIT_EXPR, ARRAY_REF,
    CALL_EXPR, COND_EXPR
  */
  long totalExprNastNode(void);

  //! Get total number of othr nodes
  /*!
    \return the number of :
    TREE_LIST,
    IDENTIFIER_NODE,
    CASE_LABEL
  */
  long totalOthrNastNode(void);

  //! Get total number of nast nodes
  /*!
    \return the number of all the presence of nodes.
    This number may not be equal to :
    totalTypeNastNode +     totalDeclNastNode +    
    totalStmtNastNode +     totalCstNastNode +
    totalExprNastNode +     totalOthrNastNode.
    The surplus is represented by the extra nodes 
    that the GCC add into the AST but that don't
    have any currespondent into the C grammar element.
  */
  long totalNastNode(void);

  //---- RESET
  
  //! Reset the data counted
  /*! 
    Set to 0 all the presences.
  */
  void reset(void);

};

#endif









