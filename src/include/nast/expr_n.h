/***************************************************************************
			   expr_n.h  -  description
			      -------------------
     begin                : July 13 2001
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


#ifndef _EXPR_N_H
#define _EXPR_N_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "nast/nast_node.h"

#include <string>



// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------
//! The base class of the expressions
/*! The base class of the expressions
  The Expression classes are used to represent the expression
  element in the C/C++ grammar. They are :

  ## C unary expressions :
  
  DEFnastCODE(ENTRY_VALUE_EXPR, entry_value_expr, 0, 0) 
  DEFnastCODE(FIX_TRUNC_EXPR, fix_trunc_expr, 0, 0) 
  DEFnastCODE(FIX_CEIL_EXPR, fix_ceil_expr, 0, 0) 
  DEFnastCODE(FIX_FLOOR_EXPR, fix_floor_expr, 0, 0) 
  DEFnastCODE(FIX_ROUND_EXPR, fix_round_expr, 0, 0) 
  DEFnastCODE(FLOAT_EXPR, float_expr, 0, 0) 
  DEFnastCODE(NEGATE_EXPR, negate_expr, 0, 0) 
  DEFnastCODE(ABS_EXPR, abs_expr, 0, 0) 
  DEFnastCODE(FFS_EXPR, ffs_expr, 0, 0) 
  DEFnastCODE(BIT_NOT_EXPR, bit_not_expr, 0, 0) 
  DEFnastCODE(CARD_EXPR, card_expr, 0, 0) 
  DEFnastCODE(CONVERT_EXPR, convert_expr, 0, 0) 
  DEFnastCODE(NOP_EXPR, nop_expr, 0, 0) 
  DEFnastCODE(NON_LVALUE_EXPR, non_lvalue_expr, 0, 0) 
  DEFnastCODE(CONJ_EXPR, conj_expr, 0, 0) 
  DEFnastCODE(REALPART_EXPR, realpart_expr, 0, 0) 
  DEFnastCODE(IMAGPART_EXPR, imagpart_expr, 0, 0) 
  DEFnastCODE(SIZEOF_EXPR, sizeof_expr, 0, 0) 
  DEFnastCODE(ALIGNOF_EXPR, alignof_expr, 0, 0) 
  DEFnastCODE(REFERENCE_EXPR, reference_expr, 0, 0) 
  DEFnastCODE(RETURN_EXPR, return_expr, 0, 0) 
  DEFnastCODE(VA_ARG_EXPR, va_arg_expr, 0, 0) 
  DEFnastCODE(TRUTH_NOT_EXPR, truth_not_expr, 0, 0) 
  DEFnastCODE(ADDR_EXPR, addr_expr, 0, 0) 
  DEFnastCODE(CLEANUP_POINT_EXPR, cleanup_point_expr, 0, 0) 
  DEFnastCODE(SAVE_EXPR, save_expr, 0, 0) 
  
  ## C binary expressions :
  
  DEFnastCODE(GOTO_SUBROUTINE_EXPR, goto_subroutine_expr, 0, 0) 
  DEFnastCODE(LABELED_BLOCK_EXPR, labeled_block_expr, 0, 0) 
  DEFnastCODE(RTL_EXPR, rtl_expr, 0, 0) 
  DEFnastCODE(SWITCH_EXPR, switch_expr, 0, 0) 
  DEFnastCODE(TRY_FINALLY_EXPR, try_finally_expr, 0, 0) 
  DEFnastCODE(EXIT_BLOCK_EXPR, exit_block_expr, 0, 0) 
  DEFnastCODE(PLUS_EXPR, plus_expr, 0, 0) 
  DEFnastCODE(MINUS_EXPR, minus_expr, 0, 0) 
  DEFnastCODE(MULT_EXPR, mult_expr, 0, 0) 
  DEFnastCODE(TRUNC_DIV_EXPR, trunc_div_expr, 0, 0) 
  DEFnastCODE(CEIL_DIV_EXPR, ceil_div_expr, 0, 0) 
  DEFnastCODE(FLOOR_DIV_EXPR, floor_div_expr, 0, 0) 
  DEFnastCODE(ROUND_DIV_EXPR, round_div_expr, 0, 0) 
  DEFnastCODE(TRUNC_MOD_EXPR, trunc_mod_expr, 0, 0) 
  DEFnastCODE(CEIL_MOD_EXPR, ceil_mod_expr, 0, 0) 
  DEFnastCODE(FLOOR_MOD_EXPR, floor_mod_expr, 0, 0) 
  DEFnastCODE(ROUND_MOD_EXPR, round_mod_expr, 0, 0) 
  DEFnastCODE(RDIV_EXPR, rdiv_expr, 0, 0) 
  DEFnastCODE(EXACT_DIV_EXPR, exact_div_expr, 0, 0) 
  DEFnastCODE(EXPON_EXPR, expon_expr, 0, 0) 
  DEFnastCODE(MIN_EXPR, min_expr, 0, 0) 
  DEFnastCODE(MAX_EXPR, max_expr, 0, 0) 
  DEFnastCODE(LSHIFT_EXPR, lshift_expr, 0, 0) 
  DEFnastCODE(RSHIFT_EXPR, rshift_expr, 0, 0) 
  DEFnastCODE(LROTATE_EXPR, lrotate_expr, 0, 0) 
  DEFnastCODE(RROTATE_EXPR, rrotate_expr, 0, 0) 
  DEFnastCODE(BIT_IOR_EXPR, bit_ior_expr, 0, 0) 
  DEFnastCODE(BIT_XOR_EXPR, bit_xor_expr, 0, 0) 
  DEFnastCODE(BIT_AND_EXPR, bit_and_expr, 0, 0) 
  DEFnastCODE(BIT_ANDTC_EXPR, bit_andtc_expr, 0, 0) 
  DEFnastCODE(IN_EXPR, in_expr, 0, 0) 
  DEFnastCODE(RANGE_EXPR, range_expr, 0, 0) 
  DEFnastCODE(COMPLEX_EXPR, complex_expr, 0, 0) 
  DEFnastCODE(LT_EXPR, lt_expr, 0, 0) 
  DEFnastCODE(LE_EXPR, le_expr, 0, 0) 
  DEFnastCODE(GT_EXPR, gt_expr, 0, 0) 
  DEFnastCODE(GE_EXPR, ge_expr, 0, 0) 
  DEFnastCODE(EQ_EXPR, eq_expr, 0, 0) 
  DEFnastCODE(NE_EXPR, ne_expr, 0, 0) 
  DEFnastCODE(UNORDERED_EXPR, unordered_expr, 0, 0) 
  DEFnastCODE(ORDERED_EXPR, ordered_expr, 0, 0) 
  DEFnastCODE(UNLT_EXPR, unlt_expr, 0, 0) 
  DEFnastCODE(UNLE_EXPR, unle_expr, 0, 0) 
  DEFnastCODE(UNGT_EXPR, ungt_expr, 0, 0) 
  DEFnastCODE(UNGE_EXPR, unge_expr, 0, 0) 
  DEFnastCODE(UNEQ_EXPR, uneq_expr, 0, 0) 
  DEFnastCODE(SET_LE_EXPR, set_le_expr, 0, 0) 
  DEFnastCODE(TRUTH_ANDIF_EXPR, truth_andif_expr, 0, 0) 
  DEFnastCODE(TRUTH_ORIF_EXPR, truth_orif_expr, 0, 0) 
  DEFnastCODE(INIT_EXPR, init_expr, 0, 0) 
  DEFnastCODE(MODIFY_EXPR, modify_expr, 0, 0) 
  DEFnastCODE(COMPOUND_EXPR, compound_expr, 0, 0) 
  DEFnastCODE(PREDECREMENT_EXPR, predecrement_expr, 0, 0) 
  DEFnastCODE(PREINCREMENT_EXPR, preincrement_expr, 0, 0) 
  DEFnastCODE(POSTDECREMENT_EXPR, postdecrement_expr, 0, 0) 
  DEFnastCODE(POSTINCREMENT_EXPR, postincrement_expr, 0, 0) 
  
  ## C ternary expressions :
  
  DEFnastCODE(COND_EXPR, cond_expr, 0, 0) 
  
  ## C reference expressions :
  
  DEFnastCODE(COMPONENT_REF, component_ref, 0, 0) 
  DEFnastCODE(ARRAY_REF, array_ref, 0, 0) 
  DEFnastCODE(BIT_FIELD_REF, bit_field_ref, 0, 0) 
  DEFnastCODE(BUFFER_REF, buffer_ref, 0, 0) 
  DEFnastCODE(INDIRECT_REF, indirect_ref, 0, 0) 
  
  ## Other C/C++ expressions :
  
  DEFnastCODE(CALL_EXPR, call_expr, 0, 0) 
  DEFnastCODE(EXC_PTR_EXPR, exc_ptr_expr, 0, 0) 
  DEFnastCODE(PLACEHOLDER_EXPR, placeholder_expr, 0, 0) 
  DEFnastCODE(CONSTRUCTOR, constructor, 0, 0)
  DEFnastCODE(STMT_EXPR, stmt_expr, 0, 0) 
  DEFnastCODE(BIND_EXPR, bind_expr, 0, 0) 
  DEFnastCODE(LOOP_EXPR, loop_expr, 0, 0) 
  DEFnastCODE(EXIT_EXPR, exit_expr, 0, 0) 
  DEFnastCODE(TARGET_EXPR, target_expr, 0, 0) 
  DEFnastCODE(EXPR_WITH_FILE_LOCATION, expr_with_file_location, 0, 0)
  DEFnastCODE(THROW_EXPR, throw_expr, 0, 0) 
  DEFnastCODE(AGGR_INIT_EXPR, aggr_init_expr, 0, 0) 
  DEFnastCODE(WITH_CLEANUP_EXPR, with_cleanup_expr, 0, 0) 
  DEFnastCODE(WITH_RECORD_EXPR, with_record_expr, 0, 0) 
  
  ## Other C/C++ ternary expressions :
    
  DEFnastCODE(NW_EXPR, nw_expr, 0, 0) 
  DEFnastCODE(VEC_NW_EXPR, vec_nw_expr, 0, 0) 
  DEFnastCODE(NEW_EXPR, new_expr, 0, 0) 
  DEFnastCODE(VEC_NEW_EXPR, vec_new_expr, 0, 0) 
  DEFnastCODE(PSEUDO_DTOR_EXPR, pseudo_dtor_expr, 0, 0) 
  DEFnastCODE(MODOP_EXPR, modop_expr, 0, 0) 
  
  ## Other C/C++ binary expressions :
  
  DEFnastCODE(DL_EXPR, dl_expr, 0, 0) 
  DEFnastCODE(VEC_DL_EXPR, vec_dl_expr, 0, 0) 
  DEFnastCODE(DOTSTAR_EXPR, dotstar_expr, 0, 0) 
  DEFnastCODE(DELETE_EXPR, delete_expr, 0, 0) 
  DEFnastCODE(VEC_DELETE_EXPR, vec_delete_expr, 0, 0) 
  DEFnastCODE(USER_CONV, user_conv, 0, 0) 
  DEFnastCODE(CTOR_INITIALIZER, ctor_initializer, 0, 0)
  DEFnastCODE(RETURN_INIT, return_init, 0, 0)
  DEFnastCODE(TEMPLATE_ID_EXPR, template_id_expr, 0, 0) 
  
  ## Other C/C++ unary expressions :
  
  DEFnastCODE(CAST_EXPR, cast_expr, 0, 0) 
  DEFnastCODE(REINTERPRET_CAST_EXPR, reinterpret_cast_expr, 0, 0) 
  DEFnastCODE(CONST_CAST_EXPR, const_cast_expr, 0, 0) 
  DEFnastCODE(DYNAMIC_CAST_EXPR, dynamic_cast_expr, 0, 0) 
  DEFnastCODE(STATIC_CAST_EXPR, static_cast_expr, 0, 0) 

  ## Other C/C++ special unary expressions :
  
  DEFnastCODE(TYPEID_EXPR, typeid_expr, 0, 0) 
  DEFnastCODE(IDENTITY_CONV, identity_conv, 0, 0) 
  DEFnastCODE(LVALUE_CONV, lvalue_conv, 0, 0) 
  DEFnastCODE(QUAL_CONV, qual_conv, 0, 0) 
  DEFnastCODE(STD_CONV, std_conv, 0, 0) 
  DEFnastCODE(PTR_CONV, ptr_conv, 0, 0) 
  DEFnastCODE(PMEM_CONV, pmem_conv, 0, 0) 
  DEFnastCODE(BASE_CONV, base_conv, 0, 0) 
  DEFnastCODE(REF_BIND, ref_bind, 0, 0)
  DEFnastCODE(AMBIG_CONV, ambig_conv, 0, 0) 
  DEFnastCODE(RVALUE_CONV, rvalue_conv, 0, 0) 
  DEFnastCODE(TYPE_EXPR, type_expr, 0, 0) 
  DEFnastCODE(LOOKUP_EXPR, lookup_expr, 0, 0) 
  
  All the expressions haven't any attributes.

  \note Only the C element are good defined.
*/  
class expr_n : public nast_node {
  
  // NO ATTRIBUTES

 public:
  //! Constructor
  /*! Constructor */
  expr_n() { return; }

  //! Destructor
  /*! Destructor */
  ~expr_n() { }
  
};


//! The class for the unary expressions
/*! The class for the unary expressions 

  Used to represent a unary expression like :
      ~a; 
      !a; 
      a++;

  This image shows the possibile output edges.
  
  \image html unary_expr.gif
 */
class unary_expr_n : public expr_n {
  
  // NO ATTRIBUTES

 public:
  //! Constructor
  /*! Constructor */
  unary_expr_n() { return; }

  //! Destructor
  /*! Destructor */
  ~unary_expr_n() { }
  
  //*** Member

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);
};


//! The class for the binary expressions
/*! The class for the binary expressions 

  Used to represent an binary expression like :
     a * b;
     a - b;
     a && b;
     a & b;

  This image shows the possibile output edges.
  
  \image html binary_expr.gif
*/
class binary_expr_n : public expr_n {
  
  // NO ATTRIBUTES

 public:
  //! Constructor
  /*! Constructor */
  binary_expr_n() { return; }

  //! Destructor
  /*! Destructor */
  ~binary_expr_n() { }
  
  //*** Member

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);
};



//! The class for the ternary expressions
/*! The class for the ternary expressions 

  Used to represent an ternary expression like :
     a ? a++ : a--;

  This image shows the possibile output edges.
  
  \image html cond_expr.gif
*/
class ternary_expr_n : public expr_n {
  
  // NO ATTRIBUTES

 public:
  //! Constructor
  /*! Constructor */
  ternary_expr_n() { return; }

  //! Destructor
  /*! Destructor */
  ~ternary_expr_n() { }
  
  //*** Member

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);
};


//! The class for the reference expressions
/*! The class for the reference expressions 

  Used to represent a reference expression like :
     s.a;
     s->a;
     *b;

  This image shows the possibile output edges.
  
  \image html component_ref.gif
  \image html array_ref.gif
  \image html bit_field_ref.gif
  \image html buffer_ref.gif
  \image html indirect_ref.gif
*/
class ref_expr_n : public expr_n {
  
  // NO ATTRIBUTES

 public:
  //! Constructor
  /*! Constructor */
  ref_expr_n() { return; }

  //! Destructor
  /*! Destructor */
  ~ref_expr_n() { }
  
  //*** Member

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);
};




//! The class for the other expressions
/*! The class for the other expressions */
class othr_expr_n : public expr_n {
  
  // NO ATTRIBUTES

 public:
  //! Constructor
  /*! Constructor */
  othr_expr_n() { return; }

  //! Destructor
  /*! Destructor */
  ~othr_expr_n() { }
  
  //*** Member

  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);
};

#endif
