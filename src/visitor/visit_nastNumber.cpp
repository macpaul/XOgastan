/***************************************************************************
			   visit_nastNumber.cpp  -  description
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
#include "visitor/visit_nastNumber.h"

// ---------------------------------------------------------------------------
//  MEMBERS
// ---------------------------------------------------------------------------



// visit declarations
void
visit_nastNumber::visit_var_decl (var_decl_n *np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());

    if (np->hasEdgeName(NAME_EDGE)) {
      child = np->edgeName(NAME_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(ASSEMBLER_NAME_EDGE)) {
      child = np->edgeName(ASSEMBLER_NAME_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(TYPE_EDGE)) {
      child = np->edgeName(TYPE_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(SCOPE_EDGE)) {
      child = np->edgeName(SCOPE_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(NEXT_DECL_EDGE)) {
      child = np->edgeName(NEXT_DECL_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(INITIAL_VALUE_EDGE)) {
      child = np->edgeName(INITIAL_VALUE_EDGE);
      child->accept(*this);
    }

  }

  return;
}

void
visit_nastNumber::visit_parm_decl (parm_decl_n *np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());

    if (np->hasEdgeName(NAME_EDGE)) {
      child = np->edgeName(NAME_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(ASSEMBLER_NAME_EDGE)) {
      child = np->edgeName(ASSEMBLER_NAME_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(TYPE_EDGE)) {
      child = np->edgeName(TYPE_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(SCOPE_EDGE)) {
      child = np->edgeName(SCOPE_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(NEXT_DECL_EDGE)) {
      child = np->edgeName(NEXT_DECL_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(INITIAL_VALUE_EDGE)) {
      child = np->edgeName(INITIAL_VALUE_EDGE);
      child->accept(*this);
    }

  }
  return;
}

void
visit_nastNumber::visit_result_decl (result_decl_n *np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());


    if (np->hasEdgeName(NAME_EDGE)) {
      child = np->edgeName(NAME_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(TYPE_EDGE)) {
      child = np->edgeName(TYPE_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(SCOPE_EDGE)) {
      child = np->edgeName(SCOPE_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(NEXT_DECL_EDGE)) {
      child = np->edgeName(NEXT_DECL_EDGE);
      child->accept(*this);
    }

  }
  return;
}

void
visit_nastNumber::visit_const_decl (const_decl_n *np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());


    if (np->hasEdgeName(NAME_EDGE)) {
      child = np->edgeName(NAME_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(ASSEMBLER_NAME_EDGE)) {
      child = np->edgeName(ASSEMBLER_NAME_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(TYPE_EDGE)) {
      child = np->edgeName(TYPE_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(SCOPE_EDGE)) {
      child = np->edgeName(SCOPE_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(NEXT_DECL_EDGE)) {
      child = np->edgeName(NEXT_DECL_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(VALUES_EDGE)) {
      child = np->edgeName(VALUES_EDGE);
      child->accept(*this);
    }

  }
  return;
}

void
visit_nastNumber::visit_field_decl (field_decl_n *np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());


    if (np->hasEdgeName(NAME_EDGE)) {
      child = np->edgeName(NAME_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(ASSEMBLER_NAME_EDGE)) {
      child = np->edgeName(ASSEMBLER_NAME_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(TYPE_EDGE)) {
      child = np->edgeName(TYPE_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(SCOPE_EDGE)) {
      child = np->edgeName(SCOPE_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(NEXT_DECL_EDGE)) {
      child = np->edgeName(NEXT_DECL_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(BIT_POSITION_EDGE)) {
      child = np->edgeName(BIT_POSITION_EDGE);
      child->accept(*this);
    }

  }
  return;
}

void
visit_nastNumber::visit_type_decl (type_decl_n *np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());


    if (np->hasEdgeName(NAME_EDGE)) {
      child = np->edgeName(NAME_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(ASSEMBLER_NAME_EDGE)) {
      child = np->edgeName(ASSEMBLER_NAME_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(TYPE_EDGE)) {
      child = np->edgeName(TYPE_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(SCOPE_EDGE)) {
      child = np->edgeName(SCOPE_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(NEXT_DECL_EDGE)) {
      child = np->edgeName(NEXT_DECL_EDGE);
      child->accept(*this);
    }

  }

  return;
}

void
visit_nastNumber::visit_function_decl (function_decl_n *np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());


    if (np->hasEdgeName(NAME_EDGE)) {
      child = np->edgeName(NAME_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(ASSEMBLER_NAME_EDGE)) {
      child = np->edgeName(ASSEMBLER_NAME_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(TYPE_EDGE)) {
      child = np->edgeName(TYPE_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(SCOPE_EDGE)) {
      child = np->edgeName(SCOPE_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(NEXT_DECL_EDGE)) {
      child = np->edgeName(NEXT_DECL_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(ARGUMENTS_EDGE)) {
      child = np->edgeName(ARGUMENTS_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(BODY_EDGE)) {
      child = np->edgeName(BODY_EDGE);
      child->accept(*this);
    }
  }
  return;
}

void
visit_nastNumber::visit_label_decl (label_decl_n *np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());


    if (np->hasEdgeName(NAME_EDGE)) {
      child = np->edgeName(NAME_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(ASSEMBLER_NAME_EDGE)) {
      child = np->edgeName(ASSEMBLER_NAME_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(TYPE_EDGE)) {
      child = np->edgeName(TYPE_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(SCOPE_EDGE)) {
      child = np->edgeName(SCOPE_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(NEXT_DECL_EDGE)) {
      child = np->edgeName(NEXT_DECL_EDGE);
      child->accept(*this);
    }

  }
  return;
}

void
visit_nastNumber::visit_othr_decl (othr_decl_n *np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());


    if (np->hasEdgeName(NAME_EDGE)) {
      child = np->edgeName(NAME_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(ASSEMBLER_NAME_EDGE)) {
      child = np->edgeName(ASSEMBLER_NAME_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(TYPE_EDGE)) {
      child = np->edgeName(TYPE_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(SCOPE_EDGE)) {
      child = np->edgeName(SCOPE_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(NEXT_DECL_EDGE)) {
      child = np->edgeName(NEXT_DECL_EDGE);
      child->accept(*this);
    }

    // namespace_decl : get the declarations
    if ( (np->getCode() == NAMESPACE_DECL) &&
	 (np->hasEdgeName(DECLARATIONS_EDGE)) ) {
      
      child = np->edgeName(DECLARATIONS_EDGE);
      child->accept(*this);
    }

  }

  return;
}

  // visit types
void
visit_nastNumber::visit_void_type (void_type_n *np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());


    if (np->hasEdgeName(NAME_EDGE)) {
      child = np->edgeName(NAME_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(MAIN_VARIANT_EDGE)) {
      child = np->edgeName(MAIN_VARIANT_EDGE);
      child->accept(*this);
    }
    
  }
  return;
}

void
visit_nastNumber::visit_integer_type (integer_type_n *np)
{
  
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());


    if (np->hasEdgeName(NAME_EDGE)) {
      child = np->edgeName(NAME_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(MAIN_VARIANT_EDGE)) {
      child = np->edgeName(MAIN_VARIANT_EDGE);
      child->accept(*this);
    }
    
  }
  return;
}

void
visit_nastNumber::visit_enumeral_type (enumeral_type_n *np)
{

  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());


    if (np->hasEdgeName(NAME_EDGE)) {
      child = np->edgeName(NAME_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(MAIN_VARIANT_EDGE)) {
      child = np->edgeName(MAIN_VARIANT_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(CONSTANTS_EDGE)) {
      child = np->edgeName(CONSTANTS_EDGE);
      child->accept(*this);
    }
  }
  return;
}

void
visit_nastNumber::visit_real_type (real_type_n *np)
{

  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());


    if (np->hasEdgeName(NAME_EDGE)) {
      child = np->edgeName(NAME_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(MAIN_VARIANT_EDGE)) {
      child = np->edgeName(MAIN_VARIANT_EDGE);
      child->accept(*this);
    }
    
  }
  return;
}

void
visit_nastNumber::visit_array_type (array_type_n *np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());


    if (np->hasEdgeName(NAME_EDGE)) {
      child = np->edgeName(NAME_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(MAIN_VARIANT_EDGE)) {
      child = np->edgeName(MAIN_VARIANT_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(ELEMENTS_EDGE)) {
      child = np->edgeName(ELEMENTS_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(DOMAIN_INDEX_EDGE)) {
      child = np->edgeName(DOMAIN_INDEX_EDGE);
      child->accept(*this);
    }
  }
  return;
}

void
visit_nastNumber::visit_record_type (record_type_n *np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());


    if (np->hasEdgeName(NAME_EDGE)) {
      child = np->edgeName(NAME_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(MAIN_VARIANT_EDGE)) {
      child = np->edgeName(MAIN_VARIANT_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(FIELDS_EDGE)) {
      child = np->edgeName(FIELDS_EDGE);
      child->accept(*this);
    }
    
  }
  return;
}

void
visit_nastNumber::visit_union_type (union_type_n *np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());


    if (np->hasEdgeName(NAME_EDGE)) {
      child = np->edgeName(NAME_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(MAIN_VARIANT_EDGE)) {
      child = np->edgeName(MAIN_VARIANT_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(FIELDS_EDGE)) {
      child = np->edgeName(FIELDS_EDGE);
      child->accept(*this);
    }
    
  }
  return;
}

void
visit_nastNumber::visit_pointer_type (pointer_type_n *np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());


    if (np->hasEdgeName(NAME_EDGE)) {
      child = np->edgeName(NAME_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(MAIN_VARIANT_EDGE)) {
      child = np->edgeName(MAIN_VARIANT_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(POINTED_TO_EDGE)) {
      child = np->edgeName(POINTED_TO_EDGE);
      child->accept(*this);
    }
    
  }
  return;
}

void
visit_nastNumber::visit_function_type (function_type_n *np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());


    if (np->hasEdgeName(NAME_EDGE)) {
      child = np->edgeName(NAME_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(MAIN_VARIANT_EDGE)) {
      child = np->edgeName(MAIN_VARIANT_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(TYPE_RETURNED_EDGE)) {
      child = np->edgeName(TYPE_RETURNED_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(ARGUMENTS_EDGE)) {
      child = np->edgeName(ARGUMENTS_EDGE);
      child->accept(*this);
    }
  }
  return;
}

void
visit_nastNumber::visit_othr_type (othr_type_n *np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());


    if (np->hasEdgeName(NAME_EDGE)) {
      child = np->edgeName(NAME_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(MAIN_VARIANT_EDGE)) {
      child = np->edgeName(MAIN_VARIANT_EDGE);
      child->accept(*this);
    }
    
  }
  return;
}


// visit constants
void
visit_nastNumber::visit_integer_cst (integer_cst_n *np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());

    if (np->hasEdgeName(TYPE_EDGE)) {
      child = np->edgeName(TYPE_EDGE);
      child->accept(*this);
    }

  }
  return;
}


void
visit_nastNumber::visit_real_cst (real_cst_n *np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());

    if (np->hasEdgeName(TYPE_EDGE)) {
      child = np->edgeName(TYPE_EDGE);
      child->accept(*this);
    }

  }
  return;
}


void
visit_nastNumber::visit_string_cst (string_cst_n *np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());

    if (np->hasEdgeName(TYPE_EDGE)) {
      child = np->edgeName(TYPE_EDGE);
      child->accept(*this);
    }

  }
  return;
}


void
visit_nastNumber::visit_othr_cst (othr_cst_n *np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());

    if (np->hasEdgeName(TYPE_EDGE)) {
      child = np->edgeName(TYPE_EDGE);
      child->accept(*this);
    }

  }
  return;
}


// visit statements
void
visit_nastNumber::visit_break_stmt (break_stmt_n * np)
{
  if (!haveVisited(np)) {

    nast_node *child;
    
    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());

    if (np->hasEdgeName(NEXT_STMT_EDGE)) {
      child = np->edgeName(NEXT_STMT_EDGE);
      child->accept(*this);
    }
	
  }

  return;
}

void
visit_nastNumber::visit_continue_stmt (continue_stmt_n * np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());

    if (np->hasEdgeName(NEXT_STMT_EDGE)) {
      child = np->edgeName(NEXT_STMT_EDGE);
      child->accept(*this);
    }

  }

  return;
}

void
visit_nastNumber::visit_scope_stmt (scope_stmt_n * np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());

    if (np->hasEdgeName(NEXT_STMT_EDGE)) {
      child = np->edgeName(NEXT_STMT_EDGE);
      child->accept(*this);
    }

  }
  return;
}

void
visit_nastNumber::visit_decl_stmt (decl_stmt_n * np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());

    if (np->hasEdgeName(NEXT_STMT_EDGE)) {
      child = np->edgeName(NEXT_STMT_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(DECLARATIONS_EDGE)) {
      child = np->edgeName(DECLARATIONS_EDGE);
      child->accept(*this);
    }


  }
  return;
}

void
visit_nastNumber::visit_expr_stmt (expr_stmt_n * np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());

    if (np->hasEdgeName(NEXT_STMT_EDGE)) {
      child = np->edgeName(NEXT_STMT_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(EXPRESSION_EDGE)) {
      child = np->edgeName(EXPRESSION_EDGE);
      child->accept(*this);
    }

  }
  return;
}

void
visit_nastNumber::visit_goto_stmt (goto_stmt_n * np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());

    if (np->hasEdgeName(NEXT_STMT_EDGE)) {
      child = np->edgeName(NEXT_STMT_EDGE);
      child->accept(*this);
    }
	
    if (np->hasEdgeName(DESTINATION_EDGE)) {
      child = np->edgeName(DESTINATION_EDGE);
      child->accept(*this);
    }

  }
  return;
}

void
visit_nastNumber::visit_label_stmt (label_stmt_n * np)
{
  if (!haveVisited(np)) {

    nast_node *child;
    
    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());

    if (np->hasEdgeName(NEXT_STMT_EDGE)) {
      child = np->edgeName(NEXT_STMT_EDGE);
      child->accept(*this);
    }

  }
  return;
}

void
visit_nastNumber::visit_return_stmt (return_stmt_n * np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());

    if (np->hasEdgeName(NEXT_STMT_EDGE)) {
      child = np->edgeName(NEXT_STMT_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(EXPRESSION_EDGE)) {
      child = np->edgeName(EXPRESSION_EDGE);
      child->accept(*this);
    }

  }
  return;
}

void
visit_nastNumber::visit_if_stmt (if_stmt_n * np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());

    if (np->hasEdgeName(NEXT_STMT_EDGE)) {
      child = np->edgeName(NEXT_STMT_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(THEN_EDGE)) {
      child = np->edgeName(THEN_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(ELSE_EDGE)) {
      child = np->edgeName(ELSE_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(CONDITION_EDGE)) {
      child = np->edgeName(CONDITION_EDGE);
      child->accept(*this);
    }

  }
  return;
}

void
visit_nastNumber::visit_switch_stmt (switch_stmt_n * np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());

    if (np->hasEdgeName(NEXT_STMT_EDGE)) {
      child = np->edgeName(NEXT_STMT_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(BODY_EDGE)) {
      child = np->edgeName(BODY_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(CONDITION_EDGE)) {
      child = np->edgeName(CONDITION_EDGE);
      child->accept(*this);
    }

  }
  return;
}

void
visit_nastNumber::visit_for_stmt (for_stmt_n * np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());

    if (np->hasEdgeName(NEXT_STMT_EDGE)) {
      child = np->edgeName(NEXT_STMT_EDGE);
      child->accept(*this);
    }
    
    if (np->hasEdgeName(BODY_EDGE)) {
      child = np->edgeName(BODY_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(CONDITION_EDGE)) {
      child = np->edgeName(CONDITION_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(EXPRESSION_EDGE)) {
      child = np->edgeName(EXPRESSION_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(INITIALIZATION_EDGE)) {
      child = np->edgeName(INITIALIZATION_EDGE);
      child->accept(*this);
    }

  }
  return;
}

void
visit_nastNumber::visit_while_stmt (while_stmt_n * np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());

    if (np->hasEdgeName(NEXT_STMT_EDGE)) {
      child = np->edgeName(NEXT_STMT_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(BODY_EDGE)) {
      child = np->edgeName(BODY_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(CONDITION_EDGE)) {
      child = np->edgeName(CONDITION_EDGE);
      child->accept(*this);
    }

  }
  return;
}

void
visit_nastNumber::visit_do_stmt (do_stmt_n * np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());

    if (np->hasEdgeName(NEXT_STMT_EDGE)) {
      child = np->edgeName(NEXT_STMT_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(BODY_EDGE)) {
      child = np->edgeName(BODY_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(CONDITION_EDGE)) {
      child = np->edgeName(CONDITION_EDGE);
      child->accept(*this);
    }

  }
  return;
}

void
visit_nastNumber::visit_compound_stmt (compound_stmt_n * np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());

    if (np->hasEdgeName(NEXT_STMT_EDGE)) {
      child = np->edgeName(NEXT_STMT_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(BODY_EDGE)) {
      child = np->edgeName(BODY_EDGE);
      child->accept(*this);
    }

  }
  return;
}

void
visit_nastNumber::visit_asm_stmt (asm_stmt_n * np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());

    if (np->hasEdgeName(NEXT_STMT_EDGE)) {
      child = np->edgeName(NEXT_STMT_EDGE);
      child->accept(*this);
    }

  }
  return;
}

void
visit_nastNumber::visit_othr_stmt (othr_stmt_n * np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());
    
    if (np->hasEdgeName(NEXT_STMT_EDGE)) {
      child = np->edgeName(NEXT_STMT_EDGE);
      child->accept(*this);
    }

  }
  return;
}



// visit expressions
void
visit_nastNumber::visit_unary_expr (unary_expr_n *np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());


    if (np->hasEdgeName(OPERAND_0_EDGE)) {
      child = np->edgeName(OPERAND_0_EDGE);
      child->accept(*this);
    }

  }
  return;
}

void
visit_nastNumber::visit_binary_expr (binary_expr_n *np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());


    if (np->hasEdgeName(OPERAND_0_EDGE)) {
      child = np->edgeName(OPERAND_0_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(OPERAND_1_EDGE)) {
      child = np->edgeName(OPERAND_1_EDGE);
      child->accept(*this);
    }

  }
  return;
}

void
visit_nastNumber::visit_ternary_expr (ternary_expr_n *np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());


    if (np->hasEdgeName(CONDITION_EDGE)) {
      child = np->edgeName(CONDITION_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(THEN_VALUE_EDGE)) {
      child = np->edgeName(THEN_VALUE_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(ELSE_VALUE_EDGE)) {
      child = np->edgeName(ELSE_VALUE_EDGE);
      child->accept(*this);
    }

  }
  return;
}

void
visit_nastNumber::visit_ref_expr (ref_expr_n *np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());


    if (np->hasEdgeName(OPERAND_0_EDGE)) {
      child = np->edgeName(OPERAND_0_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(OPERAND_1_EDGE)) {
      child = np->edgeName(OPERAND_1_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(OPERAND_2_EDGE)) {
      child = np->edgeName(OPERAND_2_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(AGGREGATE_EDGE)) {
      child = np->edgeName(AGGREGATE_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(FIELD_EDGE)) {
      child = np->edgeName(FIELD_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(ARRAY_EDGE)) {
      child = np->edgeName(ARRAY_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(INDEX_EDGE)) {
      child = np->edgeName(INDEX_EDGE);
      child->accept(*this);
    }

  }
  return;
}

void
visit_nastNumber::visit_othr_expr (othr_expr_n *np)
{
  if (!haveVisited(np)) {

    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());


    if (np->getCode() == LOOP_EXPR) {
      if (np->hasEdgeName(BODY_EDGE)) {
	child = np->edgeName(BODY_EDGE);
	child->accept(*this);
      }
    }

    if (np->getCode() == CALL_EXPR) {

      if (np->hasEdgeName(TYPE_EDGE)) {
	child = np->edgeName(TYPE_EDGE);
	child->accept(*this);
      }

      //if (np->hasEdgeName(FUNCTION_EDGE)) {
      //	child = np->edgeName(FUNCTION_EDGE);
      //	child->accept(*this);
      //}

      if (np->hasEdgeName(ARGUMENTS_EDGE)) {
	child = np->edgeName(ARGUMENTS_EDGE);
	child->accept(*this);
      }

    }


  }
  return;
}


// visit other nodes
void
visit_nastNumber::visit_identifier (identifier_n *np)
{
  if (!haveVisited(np)) {

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());

  }
  return;
}


void
visit_nastNumber::visit_tree_list (tree_list_n *np)
{
  if (!haveVisited(np)) {
    
    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());

    if (np->hasEdgeName(PURPOSE_EDGE)) {
      child = np->edgeName(PURPOSE_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(VALUE_EDGE)) {
      child = np->edgeName(VALUE_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(NEXT_EDGE)) {
      child = np->edgeName(NEXT_EDGE);
      child->accept(*this);
    }
  }
  return;
}

void
visit_nastNumber::visit_special (special_n *np)
{
  if (!haveVisited(np)) {

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());

  }
  return;
}

void 
visit_nastNumber::visit_case_label(case_label_n *np) 
{
  if (!haveVisited(np)) {
    
    nast_node *child;

    justVisited[np->getId()] = np;
    nnData->addNast(np->getCode());

    if (np->hasEdgeName(LOW_VALUE_EDGE)) {
      child = np->edgeName(LOW_VALUE_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(HIGH_VALUE_EDGE)) {
      child = np->edgeName(HIGH_VALUE_EDGE);
      child->accept(*this);
    }

    if (np->hasEdgeName(NEXT_STMT_EDGE)) {
      child = np->edgeName(NEXT_STMT_EDGE);
      child->accept(*this);
    }

  }
  return;
}



bool
visit_nastNumber::haveVisited (nast_node *np)
{
  return (justVisited.find(np->getId()) != justVisited.end());
}


void 
visit_nastNumber::init(void) { 
  justVisited.clear();
}
