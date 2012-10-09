/***************************************************************************
			   visit_fnctsInNast.cpp  -  description
			      -------------------
     begin                : Aug 29 2001
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
#include "visitor/visit_fnctsInNast.h"

// ---------------------------------------------------------------------------
//  MEMBERS
// ---------------------------------------------------------------------------
void 
visit_fnctsInNast::clearData(void) {
    tempS = "";
    fnctName = "";
    fnctType = "";
    parmName = "";
    parmType = "";
    parmTypeExtra = "";
    constantSetted = false;
    volatileSetted = false;
    restrictSetted = false;
    parmStarNumber = 0;
    parmSquareNumber = 0;
    argumentsList = "";
}

// visit declarations
void
visit_fnctsInNast::visit_var_decl (var_decl_n *np)
{
  nast_node *child;
  
  // get the next declaration
  if (np->hasEdgeName(NEXT_DECL_EDGE)) {
    child = np->edgeName(NEXT_DECL_EDGE);
    child->accept(*this);
  }
    
  return;
}

void
visit_fnctsInNast::visit_parm_decl (parm_decl_n *np)
{
  nast_node *child;
  parmData* pData;
  
  clearData();
  
  pData = new parmData;
  pData->setNodeP(np);
  pData->setPosName(fnctName);

#ifdef TEST_VISIT_FNCTS_IN_NAST
  cout << "\tPARAMETER\n";
#endif
  
  // get the name
  if (np->hasEdgeName(NAME_EDGE)) {
    child = np->edgeName(NAME_EDGE);
    child->accept(*this);
    parmName = tempS;
  }
  
  // get the type
  buildingFnctType = false;
  if (np->hasEdgeName(TYPE_EDGE)) {
    child = np->edgeName(TYPE_EDGE);
    child->accept(*this);
  }

  if (constantSetted)
    parmTypeExtra += "constant ";
  if (volatileSetted)
    parmTypeExtra += "volatile ";
  if (restrictSetted)
    parmTypeExtra += "restrict";
  
  // set the data about the declaration
  pData->setName(parmName);
  pData->setType(parmType);
  pData->setTypeExtra(parmTypeExtra);
  pData->setStarNumber(parmStarNumber);
  pData->setSquareNumber(parmSquareNumber);

#ifdef TEST_VISIT_FNCTS_IN_NAST
  cout << "\tName : " << pData->getName() << "\n"
       << "\tType : " << pData->getType() << "\n"
       << "\tType Extra : " << pData->getTypeExtra() << "\n"
       << "\t* number: " << pData->getStarNumber() << "\n"
       << "\t[] number: " << pData->getSquareNumber() << "\n"
       << "\tPARAMETER - END\n\n";
#endif
  
  // add the current parameter
  fData->addParm(pData);
  
  // visit the next parm_decl
  if (np->hasEdgeName(NEXT_DECL_EDGE)) {
    child = np->edgeName(NEXT_DECL_EDGE);
    child->accept(*this);
  }
  
  return;
}

void
visit_fnctsInNast::visit_result_decl (result_decl_n *np)
{
  nast_node *child;
  
  // get the next declaration
  if (np->hasEdgeName(NEXT_DECL_EDGE)) {
    child = np->edgeName(NEXT_DECL_EDGE);
    child->accept(*this);
  }

  return;
}

void
visit_fnctsInNast::visit_const_decl (const_decl_n *np)
{
  nast_node *child;

  // get the next declaration
  if (np->hasEdgeName(NEXT_DECL_EDGE)) {
    child = np->edgeName(NEXT_DECL_EDGE);
    child->accept(*this);
  }
  
  return;
}

void
visit_fnctsInNast::visit_field_decl (field_decl_n *np)
{
  nast_node *child;
  
  // get the next declaration
  if (np->hasEdgeName(NEXT_DECL_EDGE)) {
    child = np->edgeName(NEXT_DECL_EDGE);
    child->accept(*this);
  }
  
  return;
}

void
visit_fnctsInNast::visit_type_decl (type_decl_n *np)
{
  nast_node *child;
  
  // get the next declaration
  if (np->hasEdgeName(NEXT_DECL_EDGE)) {
    child = np->edgeName(NEXT_DECL_EDGE);
    child->accept(*this);
  }
  
}

void
visit_fnctsInNast::visit_function_decl (function_decl_n *np)
{
  nast_node *child;

  clearData();
  
  fData = new fnctData;
  fData->setNodeP(np);
  fData->setSource(np->getSource());

#ifdef TEST_VISIT_FNCTS_IN_NAST
  cout << "#FUNCTION - BEGIN\n";
#endif
  
  // get the name
  if (np->hasEdgeName(NAME_EDGE)) {
    child = np->edgeName(NAME_EDGE);
    child->accept(*this);
    if (tempS == "") 
      fnctName = "XOgastan_NOname" + a2b::long2string(++noNameNumber);
    else 
      fnctName = tempS;
  }
  
  // get the type
  buildingFnctType = true;
  if (np->hasEdgeName(TYPE_EDGE)) {
    child = np->edgeName(TYPE_EDGE);
    child->accept(*this);
  }

  // set the data about the declaration
  fData->setName(fnctName);
  fData->setType(fnctType);

#ifdef TEST_VISIT_FNCTS_IN_NAST
  cout << "type returned : " << fData->getType() << "\n"
       << "name : " << fData->getName() << "\n"
       << "source file : " << fData->getSource() << "\n";
#endif
  
  // visit the parameters
  if (np->hasEdgeName(ARGUMENTS_EDGE)) {
    child = np->edgeName(ARGUMENTS_EDGE);
    child->accept(*this);
  }
  
  // add the data to the list
  fL->push_front(fData);


#ifdef TEST_VISIT_FNCTS_IN_NAST
  cout << "number of paramaters : " << fData->numParm() << "\n"
       << "#FUNCTION - END\n\n";
#endif
     
  // visit the next declaration
  if (np->hasEdgeName(NEXT_DECL_EDGE)) {
    child = np->edgeName(NEXT_DECL_EDGE);
    child->accept(*this);
  }    

  return;
}

void
visit_fnctsInNast::visit_label_decl (label_decl_n *np)
{
  nast_node *child;
  
  // get the next declaration
  if (np->hasEdgeName(NEXT_DECL_EDGE)) {
    child = np->edgeName(NEXT_DECL_EDGE);
    child->accept(*this);
  }
  
  return;
}

void
visit_fnctsInNast::visit_othr_decl (othr_decl_n *np)
{
  nast_node *child;
  
  // get the next declaration
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
  
  return;
}


// visit types
void
visit_fnctsInNast::visit_void_type (void_type_n *np)
{
  if (buildingFnctType) 
    fnctType = "void ";
  else
    parmType = "void";

  constantSetted = (constantSetted) ? true : np->isConstant();
  volatileSetted = (volatileSetted) ? true : np->isVolatile();
  restrictSetted = (restrictSetted) ? true : np->isRestrict();
  
  return;
}


void
visit_fnctsInNast::visit_integer_type (integer_type_n *np)
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
  
  if (buildingFnctType) 
    fnctType = tempS + " ";
  else
    parmType = tempS + " ";
  
  constantSetted = (constantSetted) ? true : np->isConstant();
  volatileSetted = (volatileSetted) ? true : np->isVolatile();
  restrictSetted = (restrictSetted) ? true : np->isRestrict();
  
  return;
}

void
visit_fnctsInNast::visit_enumeral_type (enumeral_type_n *np)
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

  if (buildingFnctType) 
    fnctType = "enum " + tempS + " ";
  else
    parmType = "enum " + tempS + " ";
    
  constantSetted = (constantSetted) ? true : np->isConstant();
  volatileSetted = (volatileSetted) ? true : np->isVolatile();
  restrictSetted = (restrictSetted) ? true : np->isRestrict();

  return;
}

void
visit_fnctsInNast::visit_real_type (real_type_n *np)
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

  if (buildingFnctType) 
    fnctType = tempS + " ";
  else
    parmType = tempS + " ";
  
  constantSetted = (constantSetted) ? true : np->isConstant();
  volatileSetted = (volatileSetted) ? true : np->isVolatile();
  restrictSetted = (restrictSetted) ? true : np->isRestrict();
  
  return;
}

void
visit_fnctsInNast::visit_array_type (array_type_n *np)
{
  nast_node *child;
  
  // get the elements type
  if (np->hasEdgeName(ELEMENTS_EDGE)) {
    child = np->edgeName(ELEMENTS_EDGE);
    child->accept(*this);

    if (buildingFnctType) 
      fnctType = fnctType + "[] ";
    else
      parmType = parmType + "[]";

    parmSquareNumber = (!buildingFnctType) ?
      parmSquareNumber+1 : parmSquareNumber;
  }
  
  constantSetted = (constantSetted) ? true : np->isConstant();
  volatileSetted = (volatileSetted) ? true : np->isVolatile();
  restrictSetted = (restrictSetted) ? true : np->isRestrict();
  
  return;
}

void
visit_fnctsInNast::visit_record_type (record_type_n *np)
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

  if (buildingFnctType) 
    fnctType =  "struct " + tempS + " ";
  else
    parmType = "struct " + tempS + " ";

  constantSetted = (constantSetted) ? true : np->isConstant();
  volatileSetted = (volatileSetted) ? true : np->isVolatile();
  restrictSetted = (restrictSetted) ? true : np->isRestrict();
  
  return;
}

void
visit_fnctsInNast::visit_union_type (union_type_n *np)
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
  
  if (buildingFnctType) 
    fnctType =  "union " + tempS + " ";
  else
    parmType = "union " + tempS + " ";
  
  constantSetted = (constantSetted) ? true : np->isConstant();
  volatileSetted = (volatileSetted) ? true : np->isVolatile();
  restrictSetted = (restrictSetted) ? true : np->isRestrict();
  
  return;
}

void
visit_fnctsInNast::visit_pointer_type (pointer_type_n *np)
{
  nast_node *child;
  
  // get the pointer to the of the elements of the array
  if (np->hasEdgeName(POINTED_TO_EDGE)) {
    child = np->edgeName(POINTED_TO_EDGE);
    
    child->accept(*this);
    
    if (child->getCode() == FUNCTION_TYPE) {

      if (buildingFnctType) 
	fnctType = fnctType +  " (*FUNCTION)(" + argumentsList + ")";
      else
	parmType = parmType +  " (*FUNCTION)(" + argumentsList + ")";
    
    }
    else {

      if (buildingFnctType) 
	fnctType = fnctType +  "*";
      else
	parmType = parmType +  "*";
    }
    
  }
  
  parmStarNumber = (!buildingFnctType) ?
    parmStarNumber+1 : parmStarNumber;
    
  constantSetted = (constantSetted) ? true : np->isConstant();
  volatileSetted = (volatileSetted) ? true : np->isVolatile();
  restrictSetted = (restrictSetted) ? true : np->isRestrict();
  
  return;
}

void
visit_fnctsInNast::visit_function_type (function_type_n *np)
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
    
    // remeber : the list of arguments is a list of tree_node
    child->accept(*this);
  }

  return;
}

void
visit_fnctsInNast::visit_othr_type (othr_type_n *np)
{
  nast_node *child;
  
  // get the name
  if (np->hasEdgeName(NAME_EDGE)) {
    child = np->edgeName(NAME_EDGE);
    
    // search the indentifier_n
    if (child->getCode() == TYPE_DECL) 
      child = child->edgeName(NAME_EDGE);
    
    child->accept(*this);

    if (buildingFnctType) 
      fnctType = "(non ANSI C) " + tempS + " ";
    else
      parmType =  "(non ANSI C) " + tempS + " ";

  }
  
  constantSetted = (constantSetted) ? true : np->isConstant();
  volatileSetted = (volatileSetted) ? true : np->isVolatile();
  restrictSetted = (restrictSetted) ? true : np->isRestrict();
  
  return;
}


// visit other nodes
void
visit_fnctsInNast::visit_identifier (identifier_n *np)
{
  tempS = np->getString();
  return;
}

void
visit_fnctsInNast::visit_tree_list (tree_list_n *np)
{
  // Used to build the list of arguments of function type
  
  nast_node *child;
  string saveType;
  int saveStarNumber;
  int saveSquareNumber;
  
  // get the type of the current type_n
  if (np->hasEdgeName(VALUE_EDGE)) {

    if (buildingFnctType) 
      saveType = fnctType;
    else {
      saveType = parmType;
      saveStarNumber = parmStarNumber;
      saveSquareNumber = parmSquareNumber;
    }
    
    child = np->edgeName(VALUE_EDGE);
    child->accept(*this);
    
    if (buildingFnctType) 
      argumentsList += fnctType;
    else
      argumentsList += parmType;
    
    if (buildingFnctType) 
      fnctType = saveType;
    else {
      parmType = saveType;
      parmStarNumber = saveStarNumber;
      parmSquareNumber = saveSquareNumber;
    }

  }
  
  // visit next tree_list
  if (np->hasEdgeName(NEXT_EDGE)) {
    child = np->edgeName(NEXT_EDGE);
    argumentsList += ", ";    
    child->accept(*this);
  }
  
  return;
}

