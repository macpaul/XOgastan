/***************************************************************************
			   is_functions.cpp  -  description
			      -------------------
     begin                : Aug 6 2001
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
#include "utils/is_functions.h"


// ---------------------------------------------------------------------------
//  Functions
// ---------------------------------------------------------------------------


bool
isDecl (nast_code nc)
{

  switch (nc)
    {

    case TYPE_DECL:
    case FUNCTION_DECL:
    case PARM_DECL:
    case VAR_DECL:
    case FIELD_DECL:
    case CONST_DECL:
    case LABEL_DECL:
    case RESULT_DECL:

      return true;

    default:
      return false;
    }

}



bool
isType (nast_code nc)
{

  switch (nc)
    {

    case VOID_TYPE:
    case FUNCTION_TYPE:
    case INTEGER_TYPE:
    case ENUMERAL_TYPE:
    case REAL_TYPE:
    case POINTER_TYPE:
    case ARRAY_TYPE:
    case RECORD_TYPE:
    case UNION_TYPE:

      return true;

    default:
      return false;
    }

}



bool
isCst (nast_code nc)
{

  switch (nc)
    {

    case INTEGER_CST:
    case REAL_CST:
    case STRING_CST:

      return true;

    default:
      return false;
    }

}


bool
isStmt (nast_code nc)
{

  switch (nc)
    {

    case BREAK_STMT:
    case CONTINUE_STMT:
    case COMPOUND_STMT:
    case DECL_STMT:
    case EXPR_STMT:
    case DO_STMT:
    case WHILE_STMT:
    case FOR_STMT:
    case GOTO_STMT:
    case LABEL_STMT:
    case IF_STMT:
    case SWITCH_STMT:
    case SCOPE_STMT:
    case RETURN_STMT:
    case ASM_STMT:

      return true;

    default:
      return false;
    }

}


bool
isOthr (nast_code nc)
{

  switch (nc)
    {

    case TREE_LIST:
    case IDENTIFIER_NODE:
    case CASE_LABEL:

      return true;

    default:
      return false;
    }

}



bool
isExpr (nast_code nc)
{

  return (isUnaryExpr (nc) ||
	  isBinaryExpr (nc) || isTernaryExpr (nc) || 
	  isRefExpr (nc));

}

bool
isUnaryExpr (nast_code nc)
{

  switch (nc)
    {

    case ENTRY_VALUE_EXPR:
    case FIX_TRUNC_EXPR:
    case FIX_CEIL_EXPR:
    case FIX_FLOOR_EXPR:
    case FIX_ROUND_EXPR:
    case FLOAT_EXPR:
    case NEGATE_EXPR:
    case ABS_EXPR:
    case FFS_EXPR:
    case BIT_NOT_EXPR:
    case CARD_EXPR:
    case CONVERT_EXPR:
    case NOP_EXPR:
    case NON_LVALUE_EXPR:
    case CONJ_EXPR:
    case REALPART_EXPR:
    case IMAGPART_EXPR:
    case SIZEOF_EXPR:
    case ALIGNOF_EXPR:
    case REFERENCE_EXPR:
    case RETURN_EXPR:
    case VA_ARG_EXPR:
    case TRUTH_NOT_EXPR:
    case ADDR_EXPR:
    case CLEANUP_POINT_EXPR:
    case SAVE_EXPR:

      return true;

    default:
      return false;
    }

}



bool
isBinaryExpr (nast_code nc)
{

  switch (nc)
    {

    case GOTO_SUBROUTINE_EXPR:
    case LABELED_BLOCK_EXPR:
    case RTL_EXPR:
    case SWITCH_EXPR:
    case TRY_FINALLY_EXPR:
    case EXIT_BLOCK_EXPR:
    case PLUS_EXPR:
    case MINUS_EXPR:
    case MULT_EXPR:
    case TRUNC_DIV_EXPR:
    case CEIL_DIV_EXPR:
    case FLOOR_DIV_EXPR:
    case ROUND_DIV_EXPR:
    case TRUNC_MOD_EXPR:
    case CEIL_MOD_EXPR:
    case FLOOR_MOD_EXPR:
    case ROUND_MOD_EXPR:
    case RDIV_EXPR:
    case EXACT_DIV_EXPR:
    case EXPON_EXPR:
    case MIN_EXPR:
    case MAX_EXPR:
    case LSHIFT_EXPR:
    case RSHIFT_EXPR:
    case LROTATE_EXPR:
    case RROTATE_EXPR:
    case BIT_IOR_EXPR:
    case BIT_XOR_EXPR:
    case BIT_AND_EXPR:
    case BIT_ANDTC_EXPR:
    case IN_EXPR:
    case RANGE_EXPR:
    case COMPLEX_EXPR:
    case LT_EXPR:
    case LE_EXPR:
    case GT_EXPR:
    case GE_EXPR:
    case EQ_EXPR:
    case NE_EXPR:
    case UNORDERED_EXPR:
    case ORDERED_EXPR:
    case UNLT_EXPR:
    case UNLE_EXPR:
    case UNGT_EXPR:
    case UNGE_EXPR:
    case UNEQ_EXPR:
    case SET_LE_EXPR:
    case TRUTH_ANDIF_EXPR:
    case TRUTH_ORIF_EXPR:
    case INIT_EXPR:
    case MODIFY_EXPR:
    case COMPOUND_EXPR:
    case PREDECREMENT_EXPR:
    case PREINCREMENT_EXPR:
    case POSTDECREMENT_EXPR:
    case POSTINCREMENT_EXPR:

      return true;

    default:
      return false;
    }

}



bool
isTernaryExpr (nast_code nc)
{

  switch (nc)
    {

    case COND_EXPR:

      return true;

    default:
      return false;
    }

}



bool
isRefExpr (nast_code nc)
{

  switch (nc)
    {

    case COMPONENT_REF:
    case ARRAY_REF:
    case BIT_FIELD_REF:
    case BUFFER_REF:
    case INDIRECT_REF:

      return true;

    default:
      return false;
    }

}



bool
isOthrDecl (nast_code nc)
{

  switch (nc)
    {

    case NAMESPACE_DECL:
    case TEMPLATE_DECL:
    case USING_DECL:

      return true;

    default:
      return false;
    }

}



bool
isOthrType (nast_code nc)
{

  switch (nc)
    {

    case COMPLEX_TYPE:
    case LANG_TYPE:
    case BOOLEAN_TYPE:
    case REFERENCE_TYPE:
    case METHOD_TYPE:
    case CHAR_TYPE:
    case FILE_TYPE:
    case QUAL_UNION_TYPE:
    case SET_TYPE:
    case VECTOR_TYPE:
    case TYPENAME_TYPE:
    case TYPEOF_TYPE:

      return true;

    default:
      return false;
    }

}



bool
isOthrCst (nast_code nc)
{

  switch (nc)
    {

    case COMPLEX_CST:
    case PTRMEM_CST:

      return true;

    default:
      return false;
    }

}



bool
isOthrStmt (nast_code nc)
{

  switch (nc)
    {

    case START_CATCH_STMT:
    case USING_STMT:
    case OVERLOAD:
    case TRY_BLOCK:
    case EH_SPEC_BLOCK:
    case CLEANUP_STMT:
    case CTOR_STMT:
    case HANDLER:
    case MUST_NOT_THROW_EXPR:
    case SUBOBJECT:

      return true;

    default:
      return false;
    }

}



bool
isOthrOthr (nast_code nc)
{

  switch (nc)
    {

    case BINFO:
    case BLOCK:
    case ERROR_MARK:
    case OP_IDENFIER:
    case SRCLOC:
    case TREE_VEC:
    case ARROW_EXPR:
    case METHOD_CALL_EXPR:
    case TAG_DEFN:
    case EMPTY_CLASS_EXPR:
    case FUNCTION_NAME:
    case TEMPLATE_PARM_INDEX:
    case TEMPLATE_PARM_LEVEL:
    case DEFAULT_ARG:
    case CPLUS_BINDING:
    case WRAPPER:
    case OFFSET_REF:
    case SCOPE_REF:
    case MEMBER_REF:
    case TEMPLATE_TYPE_PARM:
    case TEMPLATE_TEMPLATE_PARM:
    case BOUND_TEMPLATE_TEMPLATE_PARM:

      return true;

    default:
      return false;
    }

}



bool
isOthrExpr (nast_code nc)
{


  switch (nc)
    {

    case CALL_EXPR:
    case EXC_PTR_EXPR:
    case PLACEHOLDER_EXPR:
    case CONSTRUCTOR:
    case STMT_EXPR:
    case BIND_EXPR:
    case LOOP_EXPR:
    case EXIT_EXPR:
    case TARGET_EXPR:
    case EXPR_WITH_FILE_LOCATION:
    case THROW_EXPR:
    case AGGR_INIT_EXPR:
    case WITH_CLEANUP_EXPR:
    case WITH_RECORD_EXPR:
    case NW_EXPR:
    case VEC_NW_EXPR:
    case NEW_EXPR:
    case VEC_NEW_EXPR:
    case PSEUDO_DTOR_EXPR:
    case MODOP_EXPR:
    case DL_EXPR:
    case VEC_DL_EXPR:
    case DOTSTAR_EXPR:
    case DELETE_EXPR:
    case VEC_DELETE_EXPR:
    case USER_CONV:
    case CTOR_INITIALIZER:
    case RETURN_INIT:
    case TEMPLATE_ID_EXPR:
    case CAST_EXPR:
    case REINTERPRET_CAST_EXPR:
    case CONST_CAST_EXPR:
    case DYNAMIC_CAST_EXPR:
    case STATIC_CAST_EXPR:
    case TYPEID_EXPR:
    case IDENTITY_CONV:
    case LVALUE_CONV:
    case QUAL_CONV:
    case STD_CONV:
    case PTR_CONV:
    case PMEM_CONV:
    case BASE_CONV:
    case REF_BIND:
    case AMBIG_CONV:
    case RVALUE_CONV:
    case TYPE_EXPR:
    case LOOKUP_EXPR:

      return true;

    default:
      return false;
    }

}
