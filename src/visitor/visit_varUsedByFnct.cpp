/***************************************************************************
			   visit_varUsedByFnct.cpp  -  description
			      -------------------
     begin                : Aug 28 2001
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
#include "visitor/visit_varUsedByFnct.h"

// ---------------------------------------------------------------------------
//  MEMBERS
// ---------------------------------------------------------------------------

void 
visit_varUsedByFnct::clearData(void) {
    tempS = "";
    name = "";
    type = "";
    typeExtra = "";
    constantSetted = false;
    volatileSetted = false;
    restrictSetted = false;
    starNumber = 0;
    squareNumber = 0;
    argumentsList = "";
}


// visit declarations
void
visit_varUsedByFnct::visit_var_decl (var_decl_n *np)
{
  nast_node      *child;
  varUsedData*   vuData;
  
  clearData();
    
  vuData = new varUsedData;
  vuData->setNodeP(np);
  vuData->setPosName(fnctName);
  vuData->setLine(np->getLine());
  
  // get the name
  if (np->hasEdgeName(NAME_EDGE)) {
    child = np->edgeName(NAME_EDGE);
    child->accept(*this);
    name = tempS;
  }
  
  // get the type
  if (np->hasEdgeName(TYPE_EDGE)) {
    child = np->edgeName(TYPE_EDGE);
    child->accept(*this);
  }

  if (constantSetted)
    typeExtra += "constant ";
  if (volatileSetted)
    typeExtra += "volatile ";
  if (restrictSetted)
    typeExtra += "restrict";
  
  // set the data about the declaration
  vuData->setName(name);
  vuData->setType(type);
  vuData->setTypeExtra(typeExtra);
  vuData->setStarNumber(starNumber);
  vuData->setSquareNumber(squareNumber);
  
  // Check if the variable used has just inserted into the 
  // list of variables used
  varUsedListIterator       p;          // browse the varUsedList
  varUsedData               *vuD;       // an object varUsed
  bool                      found;      // true, if the variables has
                                        // just inserted into varUsedList
  // read one variable used, one for time 
  for (found = false, p = vuL->begin(); (!found) && (p != vuL->end());  p++) {
    vuD = *p;
    found = (vuD->getNodeP() == np);
  }
  // add the data to the list
  if (!found) 
    vuL->push_front(vuData);
  
return;
}

void
visit_varUsedByFnct::visit_parm_decl (parm_decl_n *np)
{
  nast_node      *child;
  varUsedData*   vuData;
  
  clearData();
    
  vuData = new varUsedData;
  vuData->setNodeP(np);
  vuData->setPosName(fnctName);
  vuData->setLine(np->getLine());
  
  // get the name
  if (np->hasEdgeName(NAME_EDGE)) {
    child = np->edgeName(NAME_EDGE);
    child->accept(*this);
    name = tempS;
  }
  
  // get the type
  if (np->hasEdgeName(TYPE_EDGE)) {
    child = np->edgeName(TYPE_EDGE);
    child->accept(*this);
  }

  if (constantSetted)
    typeExtra += "constant ";
  if (volatileSetted)
    typeExtra += "volatile ";
  if (restrictSetted)
    typeExtra += "restrict";
  
  // set the data about the declaration
  vuData->setName(name);
  vuData->setType(type);
  vuData->setTypeExtra(typeExtra);
  vuData->setStarNumber(starNumber);
  vuData->setSquareNumber(squareNumber);

  // Check if the variable used has just inserted into the 
  // list of variables used
  varUsedListIterator       p;          // browse the varUsedList
  varUsedData               *vuD;       // an object varUsed
  bool                      found;      // true, if the variables has
                                        // just inserted into varUsedList
  // read one variable used, one for time 
  for (found = false, p = vuL->begin(); (!found) && (p != vuL->end());  p++) {
    vuD = *p;
    found = (vuD->getNodeP() == np);
  }
  // add the data to the list
  if (!found) 
    vuL->push_front(vuData);

  // We insert it into the local list of variable used 
  // A function can use only its parameters !!
  declStmtL.push_front(np);  

  return;
}


// visit types
void
visit_varUsedByFnct::visit_void_type (void_type_n *np)
{
  type = "void ";

  constantSetted = (constantSetted) ? true : np->isConstant();
  volatileSetted = (volatileSetted) ? true : np->isVolatile();
  restrictSetted = (restrictSetted) ? true : np->isRestrict();

  return;
}

void
visit_varUsedByFnct::visit_integer_type (integer_type_n *np)
{
  nast_node *child;

  // get the name
  if (np->hasEdgeName(MAIN_VARIANT_EDGE))
    // In this case it is a "typedef ..." type
    child = np->edgeName(MAIN_VARIANT_EDGE);
  else 
    // In this case it is a "int " type
    child = np->edgeName(NAME_EDGE);
  
  while (child->hasEdgeName(NAME_EDGE))
    child = child->edgeName(NAME_EDGE);
  
  child->accept(*this);

  type = tempS + " ";
  
  constantSetted = (constantSetted) ? true : np->isConstant();
  volatileSetted = (volatileSetted) ? true : np->isVolatile();
  restrictSetted = (restrictSetted) ? true : np->isRestrict();
  return;
}

void
visit_varUsedByFnct::visit_enumeral_type (enumeral_type_n *np)
{
  nast_node *child;
  
  // get the name
  if (np->hasEdgeName(MAIN_VARIANT_EDGE))
    // In this case it is a "typedef ..." type
    child = np->edgeName(MAIN_VARIANT_EDGE);
  else 
    // In this case it is a "int " type
    child = np->edgeName(NAME_EDGE);
  
  while (child->hasEdgeName(NAME_EDGE))
    child = child->edgeName(NAME_EDGE);
  
  child->accept(*this);

  type = "enum " + tempS + " ";
  
  constantSetted = (constantSetted) ? true : np->isConstant();
  volatileSetted = (volatileSetted) ? true : np->isVolatile();
  restrictSetted = (restrictSetted) ? true : np->isRestrict();

  return;
}

void
visit_varUsedByFnct::visit_real_type (real_type_n *np)
{

  nast_node *child;

  // get the name
  if (np->hasEdgeName(MAIN_VARIANT_EDGE))
    // In this case it is a "typedef ..." type
    child = np->edgeName(MAIN_VARIANT_EDGE);
  else 
    // In this case it is a "long, double, ... " type
    child = np->edgeName(NAME_EDGE);
  
  while (child->hasEdgeName(NAME_EDGE))
    child = child->edgeName(NAME_EDGE);
  
  child->accept(*this);

  type = tempS + " ";
  
  constantSetted = (constantSetted) ? true : np->isConstant();
  volatileSetted = (volatileSetted) ? true : np->isVolatile();
  restrictSetted = (restrictSetted) ? true : np->isRestrict();
  
  return;
}

void
visit_varUsedByFnct::visit_array_type (array_type_n *np)
{
  nast_node *child;
  
  // get the name 
  if (np->hasEdgeName(ELEMENTS_EDGE)) {
    child = np->edgeName(ELEMENTS_EDGE);
    child->accept(*this);
    type += "[]";
    squareNumber++;
  }
  
  constantSetted = (constantSetted) ? true : np->isConstant();
  volatileSetted = (volatileSetted) ? true : np->isVolatile();
  restrictSetted = (restrictSetted) ? true : np->isRestrict();
  
  return;
}

void
visit_varUsedByFnct::visit_record_type (record_type_n *np)
{
  nast_node *child;

  // get the name
  if (np->hasEdgeName(MAIN_VARIANT_EDGE))
    // In this case it is a "typedef struct record R" type
    child = np->edgeName(MAIN_VARIANT_EDGE);
  else 
    // In this case it is a "struct record" type
    child = np->edgeName(NAME_EDGE);
  
  while (child->hasEdgeName(NAME_EDGE))
    child = child->edgeName(NAME_EDGE);
  
  child->accept(*this);

  type = "struct " + tempS + " ";
  
  constantSetted = (constantSetted) ? true : np->isConstant();
  volatileSetted = (volatileSetted) ? true : np->isVolatile();
  restrictSetted = (restrictSetted) ? true : np->isRestrict();
  return;
}

void
visit_varUsedByFnct::visit_union_type (union_type_n *np)
{
  nast_node *child;

  // get the name
  if (np->hasEdgeName(MAIN_VARIANT_EDGE))
    // In this case it is a "typedef struct record R" type
    child = np->edgeName(MAIN_VARIANT_EDGE);
  else 
    // In this case it is a "struct record" type
    child = np->edgeName(NAME_EDGE);
  
  while (child->hasEdgeName(NAME_EDGE))
    child = child->edgeName(NAME_EDGE);
  
  child->accept(*this);
  
  type =  "union " + tempS + " ";
  
  constantSetted = (constantSetted) ? true : np->isConstant();
  volatileSetted = (volatileSetted) ? true : np->isVolatile();
  restrictSetted = (restrictSetted) ? true : np->isRestrict();
  
  return;
}

void
visit_varUsedByFnct::visit_pointer_type (pointer_type_n *np)
{
  nast_node *child;
  
  // get the pointer to the of the elements of the array
  if (np->hasEdgeName(POINTED_TO_EDGE)) {
    child = np->edgeName(POINTED_TO_EDGE);
    
    child->accept(*this);

    if (child->getCode() == FUNCTION_TYPE)       
      type = type +  " (*FUNCTION)(" + argumentsList + ")";
    else 
      type = type + "*";

    starNumber++;
  }
  
  constantSetted = (constantSetted) ? true : np->isConstant();
  volatileSetted = (volatileSetted) ? true : np->isVolatile();
  restrictSetted = (restrictSetted) ? true : np->isRestrict();
  return;
}

void
visit_varUsedByFnct::visit_function_type (function_type_n *np)
{
  nast_node *child;
  
  // get the type returned
  if (np->hasEdgeName(TYPE_RETURNED_EDGE)) {
    child = np->edgeName(TYPE_RETURNED_EDGE);
    
    // search the indentifier_n
    if (child->getCode() == TYPE_DECL) 
      child = child->edgeName(NAME_EDGE);
    
    child->accept(*this);
    // Don't save tempS it is to build the type returned by
    // the function pointed to
    //
    // The type_node visited using this child->accept(*this)
    // build in fnctType or parmType the type returned by 
    // the function pointed to
  }
  
  // get the arguments list
  if (np->hasEdgeName(ARGUMENTS_EDGE)) {
    child = np->edgeName(ARGUMENTS_EDGE);
    
    // remeber : the list of arguments is alist of tree_node
    child->accept(*this);
  }

  return;
}

void
visit_varUsedByFnct::visit_othr_type (othr_type_n *np)
{
  nast_node *child;
  
  // get the name
  if (np->hasEdgeName(MAIN_VARIANT_EDGE))
    // In this case it is a "typedef ..." type
    child = np->edgeName(MAIN_VARIANT_EDGE);
  else 
    // In this case it is a "int " type
    child = np->edgeName(NAME_EDGE);
  
  while (child->hasEdgeName(NAME_EDGE))
    child = child->edgeName(NAME_EDGE);
  
  child->accept(*this);

  type = "(non ANSI C) " + tempS + " ";
  
  constantSetted = (constantSetted) ? true : np->isConstant();
  volatileSetted = (volatileSetted) ? true : np->isVolatile();
  restrictSetted = (restrictSetted) ? true : np->isRestrict();
  return;
}

// visit statements
void
visit_varUsedByFnct::visit_break_stmt (break_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  return;
}

void
visit_varUsedByFnct::visit_continue_stmt (continue_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }

  return;
}

void
visit_varUsedByFnct::visit_scope_stmt (scope_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  return;
}

void
visit_varUsedByFnct::visit_decl_stmt (decl_stmt_n * np)
{
  nast_node *child;

  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(DECLARATIONS_EDGE)) {
    child = np->edgeName(DECLARATIONS_EDGE);
    declStmtL.push_front(child);
  }

  return;
}

void
visit_varUsedByFnct::visit_expr_stmt (expr_stmt_n * np)
{
  nast_node *child;

  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(EXPRESSION_EDGE)) {
    child = np->edgeName(EXPRESSION_EDGE);
    child->accept(*this);
  }

  return;
}

void
visit_varUsedByFnct::visit_goto_stmt (goto_stmt_n * np)
{
  nast_node *child;

  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(DESTINATION_EDGE)) {
    child = np->edgeName(DESTINATION_EDGE);
    child->accept(*this);
  }
  
}

void
visit_varUsedByFnct::visit_label_stmt (label_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  return;
}

void
visit_varUsedByFnct::visit_return_stmt (return_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(EXPRESSION_EDGE)) {
    child = np->edgeName(EXPRESSION_EDGE);
    child->accept(*this);
  }
  
  return;
}

void
visit_varUsedByFnct::visit_if_stmt (if_stmt_n * np)
{
  nast_node *child;
  
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

  return;
}

void
visit_varUsedByFnct::visit_switch_stmt (switch_stmt_n * np)
{
  nast_node *child;
  
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

  return;
}

void
visit_varUsedByFnct::visit_for_stmt (for_stmt_n * np)
{
  nast_node *child;

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

  return;
}

void
visit_varUsedByFnct::visit_while_stmt (while_stmt_n * np)
{
  nast_node *child;
  
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
  
  return;
}

void
visit_varUsedByFnct::visit_do_stmt (do_stmt_n * np)
{
  nast_node *child;
  
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
  
  return;
}

void
visit_varUsedByFnct::visit_compound_stmt (compound_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(BODY_EDGE)) {
    child = np->edgeName(BODY_EDGE);
    child->accept(*this);
  }

  return;
}

void
visit_varUsedByFnct::visit_asm_stmt (asm_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }

  return;
}

void
visit_varUsedByFnct::visit_othr_stmt (othr_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  return;
}



// visit expressions
void
visit_varUsedByFnct::visit_unary_expr (unary_expr_n *np)
{
  nast_node *child;
  
  if (np->hasEdgeName(OPERAND_0_EDGE)) {
    child = np->edgeName(OPERAND_0_EDGE);
    child->accept(*this);
  }

  return;
}

void
visit_varUsedByFnct::visit_binary_expr (binary_expr_n *np)
{
  nast_node *child;

  if (np->hasEdgeName(OPERAND_0_EDGE)) {
    child = np->edgeName(OPERAND_0_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(OPERAND_1_EDGE)) {
    child = np->edgeName(OPERAND_1_EDGE);
    child->accept(*this);
  }

  return;
}

void
visit_varUsedByFnct::visit_ternary_expr (ternary_expr_n *np)
{
  nast_node *child;
  
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
  
  return;
}

void
visit_varUsedByFnct::visit_ref_expr (ref_expr_n *np)
{
  nast_node *child;

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
  
  return;
}

void
visit_varUsedByFnct::visit_othr_expr (othr_expr_n *np)
{
  nast_node *child;
  
  if (np->getCode() == LOOP_EXPR) {
    if (np->hasEdgeName(BODY_EDGE)) {
      child = np->edgeName(BODY_EDGE);
      child->accept(*this);
    }
  }
  
  if (np->getCode() == CALL_EXPR) {
    
    // visit argument to build the expression
    if (np->hasEdgeName(ARGUMENTS_EDGE)) {
      child = np->edgeName(ARGUMENTS_EDGE);
      child->accept(*this);
    }

    // visit the function : We can have a variable with pointer to function
    if (np->hasEdgeName(FUNCTION_EDGE)) {
      child = np->edgeName(FUNCTION_EDGE);
      child->accept(*this);
    }

  }

  // used for the temporary object linke the var V in function call foo(V,10)
  if (np->getCode() == TARGET_EXPR) {
    
    if (np->hasEdgeName(INITIALIZER_EDGE)) {
      child = np->edgeName(INITIALIZER_EDGE);
      child->accept(*this);
    }

  }

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

  return;
}

// visit other nodes
void
visit_varUsedByFnct::visit_identifier (identifier_n *np)
{
  tempS = np->getString();
  return;
}


void
visit_varUsedByFnct::visit_tree_list (tree_list_n *np)
{
  /* This method is used :
     - to visit (and build) the list of arguments of a function type
     - how entry point for the expression

     We don't use any flag to dinstinguish the two 
     purposes. 
     When it build an argument the the local variable and the 
     attribute of the class visit_varUsedByFnct are setted and after
     are used by the caller of this method.
     When it build an argument the the local variable and the 
     attribute of the class visit_varUsedByFnct are setted
     but they aren't used by the caller of this method.

     Remember : the parm_decl and var_decl clear the attribute of the
     class visit_varUsedByFnct, so it don't use any illegal 
     value built during the visit of the expression.
  */
  nast_node *child;
  string saveType;
  int saveStarNumber;
  int saveSquareNumber;
  
  // get the type of the current type_n
  if (np->hasEdgeName(VALUE_EDGE)) {
    saveType = type;
    saveStarNumber = starNumber;
    saveSquareNumber = squareNumber;
    
    child = np->edgeName(VALUE_EDGE);
    child->accept(*this);
    
    argumentsList += type;
    
    type = saveType;
    starNumber = saveStarNumber;
    squareNumber = saveSquareNumber;
  }
  
  // visit next tree_list
  if (np->hasEdgeName(NEXT_EDGE)) {
    child = np->edgeName(NEXT_EDGE);
    argumentsList += ", ";
    child->accept(*this);
  }
  
  return;
}

void 
visit_varUsedByFnct::visit_case_label(case_label_n *np) 
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }

  return;
}




//! The initialization operation
void 
visit_varUsedByFnct::init(void) {
  declStmtL.clear();
}

//! The finalization operation
void 
visit_varUsedByFnct::finish(void) {
  varUsedListIterator       p;
  varUsedData               *vuData;

  // read variables used, one for time 
  for (p = vuL->begin(); p != vuL->end();  p++) {
    list<nast_node *>::iterator  p2;
    nast_node                    *toSearch;

    vuData = *p;
    toSearch = vuData->getNodeP();

    // check if the variable used is local
    for (p2 = declStmtL.begin(); p2 != declStmtL.end(); p2++) 
      if (*p2 == toSearch) break;
      
    if (p2 != declStmtL.end())
      vuData->setLocal();
    else 
      vuData->unsetLocal();

#ifdef TEST_VISIT_VAR_USED_BY_FNCT
    if ( (vuData->getNodeP())->getCode() == VAR_DECL )
      cout << "USED VARIABLE\n";
    else if ( (vuData->getNodeP())->getCode() == PARM_DECL )
      cout << "USED PARAMETER\n";
    else 
      cout << "USED OTHER ELEMENT\n";
    cout << "\tIs local ? " << vuData->isLocal()
	 << "\tline : " << vuData->getLine()
	 << "\tName : " << vuData->getName() << "\n"
	 << "\tType : " << vuData->getType() << "\n"
	 << "\tType Extra : " << vuData->getTypeExtra() << "\n"
	 << "\t* number: " << vuData->getStarNumber()
	 << "\t[] number: " << vuData->getSquareNumber() << "\n"
	 << "\tUSED VARIABLE - END\n\n";
#endif
  }
  
}
