/***************************************************************************
			   visit_declsInFnct.cpp  -  description
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
#include "visitor/visit_declsInFnct.h"

// ---------------------------------------------------------------------------
//  MEMBERS
// ---------------------------------------------------------------------------

void 
visit_declsInFnct::clearData(void) {
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
visit_declsInFnct::visit_var_decl (var_decl_n *np)
{
  nast_node *child;
  declData* dData;

  clearData();
    
  dData = new declData;
  dData->setNodeP(np);
  dData->setPosName(fnctName);
  dData->setLine(np->getLine());  

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
  dData->setName(name);
  dData->setType(type);
  dData->setTypeExtra(typeExtra);
  dData->setStarNumber(starNumber);
  dData->setSquareNumber(squareNumber);

#ifdef TEST_VISIT_DECLS_IN_FNCT
  cout << "VAR DECLARATION\n"
       << "\tline : " << dData->getLine() << "\n"
       << "\tName : " << dData->getName() << "\n"
       << "\tType : " << dData->getType() << "\n"
       << "\tType Extra : " << dData->getTypeExtra() << "\n"
       << "\t* number: " << dData->getStarNumber() << "\n"
       << "\t[] number: " << dData->getSquareNumber() << "\n"
       << "\tVAR DECLARATION - END\n\n";
#endif
  
  // add the data to the list
  dL->push_front(dData);
  
  return;
}

void
visit_declsInFnct::visit_type_decl (type_decl_n *np)
{
  nast_node *child;
  declData* dData;
  
  clearData();

  dData = new declData;
  dData->setNodeP(np);
  dData->setPosName(fnctName);
  dData->setLine(np->getLine());  
  
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
  dData->setName(name);
  dData->setType(type);
  dData->setTypeExtra(typeExtra);
  dData->setStarNumber(starNumber);
  dData->setSquareNumber(squareNumber);

#ifdef TEST_VISIT_DECLS_IN_FNCT
  cout << "TYPE DECLARATION\n"
       << "\tline : " << dData->getLine() << "\n"
       << "\tName : " << dData->getName() << "\n"
       << "\tType : " << dData->getType() << "\n"
       << "\tType Extra : " << dData->getTypeExtra() << "\n"
       << "\t* number: " << dData->getStarNumber() << "\n"
       << "\t[] number: " << dData->getSquareNumber() << "\n"
       << "\tTYPE DECLARATION - END\n\n";
#endif
  
  // add the data to the list
  dL->push_front(dData);
  
  return;
}

// visit types
void
visit_declsInFnct::visit_void_type (void_type_n *np)
{
  type = "void ";

  constantSetted = (constantSetted) ? true : np->isConstant();
  volatileSetted = (volatileSetted) ? true : np->isVolatile();
  restrictSetted = (restrictSetted) ? true : np->isRestrict();

  return;
}

void
visit_declsInFnct::visit_integer_type (integer_type_n *np)
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
visit_declsInFnct::visit_enumeral_type (enumeral_type_n *np)
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
visit_declsInFnct::visit_real_type (real_type_n *np)
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
visit_declsInFnct::visit_array_type (array_type_n *np)
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
visit_declsInFnct::visit_record_type (record_type_n *np)
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
visit_declsInFnct::visit_union_type (union_type_n *np)
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
visit_declsInFnct::visit_pointer_type (pointer_type_n *np)
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
visit_declsInFnct::visit_function_type (function_type_n *np)
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
visit_declsInFnct::visit_othr_type (othr_type_n *np)
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
visit_declsInFnct::visit_break_stmt (break_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  return;
}

void
visit_declsInFnct::visit_continue_stmt (continue_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }

  return;
}

void
visit_declsInFnct::visit_scope_stmt (scope_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  return;
}

void
visit_declsInFnct::visit_decl_stmt (decl_stmt_n * np)
{
  nast_node *child;

  // Visit the declaration
  if (np->hasEdgeName(DECLARATIONS_EDGE)) {
    child = np->edgeName(DECLARATIONS_EDGE);
    child->accept(*this);
  }

  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  return;
}

void
visit_declsInFnct::visit_expr_stmt (expr_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }

  // Maybe a LOOP_EXPR !!
  if (np->hasEdgeName(EXPRESSION_EDGE)) {
    child = np->edgeName(EXPRESSION_EDGE);
    child->accept(*this);
  }
  
  return;
}

void
visit_declsInFnct::visit_goto_stmt (goto_stmt_n * np)
{
  nast_node *child;

  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  return;
}

void
visit_declsInFnct::visit_label_stmt (label_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }

  return;
}

void
visit_declsInFnct::visit_return_stmt (return_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }

  return;
}

void
visit_declsInFnct::visit_if_stmt (if_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(THEN_EDGE)) {
    child = np->edgeName(THEN_EDGE);
    child->accept(*this);
  }
  
  if (np->hasEdgeName(ELSE_EDGE)) {
    child = np->edgeName(ELSE_EDGE);
    child->accept(*this);
  }

  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  return;
}

void
visit_declsInFnct::visit_switch_stmt (switch_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(BODY_EDGE)) {
    child = np->edgeName(BODY_EDGE);
    child->accept(*this);
  }
  
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  return;
}

void
visit_declsInFnct::visit_for_stmt (for_stmt_n * np)
{
  nast_node *child;

  if (np->hasEdgeName(BODY_EDGE)) {
    child = np->edgeName(BODY_EDGE);
    child->accept(*this);
  }

  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  return;
}

void
visit_declsInFnct::visit_while_stmt (while_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(BODY_EDGE)) {
    child = np->edgeName(BODY_EDGE);
    child->accept(*this);
  }

  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }

  return;
}

void
visit_declsInFnct::visit_do_stmt (do_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(BODY_EDGE)) {
    child = np->edgeName(BODY_EDGE);
    child->accept(*this);
  }

  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }

  return;
}

void
visit_declsInFnct::visit_compound_stmt (compound_stmt_n * np)
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
visit_declsInFnct::visit_asm_stmt (asm_stmt_n * np)
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  
  return;
}

void
visit_declsInFnct::visit_othr_stmt (othr_stmt_n * np)
{
  nast_node *child;
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }
  return;
}


void
visit_declsInFnct::visit_othr_expr (othr_expr_n *np)
{
  nast_node *child;

  // An loop with the condition always true
  if (np->getCode() == LOOP_EXPR) {
    if (np->hasEdgeName(BODY_EDGE)) {
      child = np->edgeName(BODY_EDGE);
      child->accept(*this);
    }
  }

  return;
}

// visit other nodes
void
visit_declsInFnct::visit_identifier (identifier_n *np)
{
  tempS = np->getString();
  return;
}

void
visit_declsInFnct::visit_tree_list (tree_list_n *np)
{
  // Used to build the list of arguments of function type
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
visit_declsInFnct::visit_case_label(case_label_n *np) 
{
  nast_node *child;
  
  if (np->hasEdgeName(NEXT_STMT_EDGE)) {
    child = np->edgeName(NEXT_STMT_EDGE);
    child->accept(*this);
  }

  return;
}
