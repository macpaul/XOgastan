/***************************************************************************
			   operativeMachine.cpp  -  description
			      -------------------
     begin                : Aug 7 2001
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
#include "factory/operativeMachine.h"

// ---------------------------------------------------------------------------
//  MEMBERS
// ---------------------------------------------------------------------------

//---- Constructor 

operativeMachine::operativeMachine() {
  
  // translation for START_gxl_*
  start2input["graph"] = START_gxl_GRAPH;
  start2input["node"] = START_gxl_NODE;
  start2input["attr"] = START_gxl_ATTR;
  start2input["edge"] = START_gxl_EDGE;
  start2input["type"] = START_gxl_TYPE;
  start2input["string"] = START_gxl_STRING;
  start2input["int"] = START_gxl_INT;

  // translation for END_gxl_*
  end2input["graph"] = END_gxl_GRAPH;
  end2input["node"] = END_gxl_NODE;
  end2input["attr"] = END_gxl_ATTR;
  end2input["edge"] = END_gxl_EDGE;
  end2input["type"] = END_gxl_TYPE;
  end2input["string"] = END_gxl_STRING;
  end2input["int"] = END_gxl_INT;

  c_nnp = 0;
  c_gep = 0;
  c_ga.reset();
  c_type = "";
  c_value = "";
  c_node_index = 0;
  first_node_index = 0;
}

//---- Destructor

operativeMachine::~operativeMachine() {
    gxl_edge     *gep;    // edge to destroy

    // free the list of edges
    while (!edgeL.empty ())  {
      gep = edgeL.front ();
      edgeL.pop_front ();
      delete gep;
    }
    
    // free the map start2input and end2input
    start2input.clear();
    end2input.clear();
}


//---- Error handlers

void
operativeMachine::error (const SAXParseException & e)
{
  throw bad_XOgastan("operativeMachine at file " + 
		     a2b::XMLChar2string (e.getSystemId ()),
		     a2b::XMLChar2string (e.getMessage ()));
}

void
operativeMachine::fatalError (const SAXParseException & e)
{

  throw bad_XOgastan("operativeMachine at file " + 
		     a2b::XMLChar2string (e.getSystemId ()),
		     a2b::XMLChar2string (e.getMessage ()));
		     
}

void
operativeMachine::warning (const SAXParseException & e)
{
  printWarning("operativeMachine at file " + 
	       a2b::XMLChar2string (e.getSystemId ()),
	       a2b::XMLChar2string(e.getMessage ()));
}


//---- SAX handler methods

void
operativeMachine::startDocument ()
{
  // astVerbosity output
  if (astVerbosity)
    cout << "Start document...\n";
  
}


void
operativeMachine::startElement (const XMLCh * const name, 
				AttributeList & attributes) 
{
  output_signal                         toDo;   // controlMachine's command 
  string 
    gxl_element = a2b::XMLChar2string (name);   // string with the element name

  if (gxl_element == "gxl")
    cm.setState (start_gxl);
  else { 

    try {

      // astVerbosity output
      if (astVerbosity)       
	cout << "Reading begin of gxl element " << gxl_element << "...\n";
      
      // Is legal element recognized by XOgastan ?
      // Remember : <bool>, <set>, and so on ... are not
      //            recognized by XOgastan
      if (start2input.find(gxl_element) != start2input.end())
	toDo = whatWeDo (start2input[gxl_element]);
      else
	throw bad_XOgastan ("operativeMachine", 
			    "Unexpected gxl element : #" + gxl_element + "#");

      switch (toDo) {
	
      case BEGIN_build:
	prolog ();
	break;
	
      case BEGIN_build_node:
	// get the node INDEX, and memorize it in c_node_index
	c_node_index =  
	  getGXLindex(a2b::XMLChar2string(attributes.getValue ("id")));
	break;

      case BEGIN_build_edge:
	c_gep = new gxl_edge;
	// get the FROM index, and set it
	c_gep->setFrom
	  ( getGXLindex(a2b::XMLChar2string(attributes.getValue("from"))) );
	// get the TO index, and set it
	c_gep->setTo
	  ( getGXLindex (a2b::XMLChar2string (attributes.getValue ("to"))) );
	break;

      case BEGIN_build_attr:
	// get the NAME, and set it
	c_ga.setName (a2b::XMLChar2string (attributes.getValue ("name")));
	break;

      case BEGIN_build_int:
	c_ga.setType (gxl_attr::intType);      	// set the TYPE of the attr
	break;

      case BEGIN_build_string:
	c_ga.setType (gxl_attr::stringType);	// set the TYPE of the attr
	break;

      case BEGIN_build_type:
	// get the NAME of the TYPE, and set it
	c_type = 
	  getGXLtype (a2b::XMLChar2string (attributes.getValue ("xlink:href")));
	break;
      }

    }

    catch (bad_XOgastan & b)  {
      throw bad_factory (b.getBaseMessage (), b.getOtherMessage ());
    }
    
    catch (...) {
      throw bad_factory ("operativeMachine", "Unknown event !");
    }

  }
  
  return;
}


void
operativeMachine::characters (const XMLCh * const chars, const unsigned int length)
{
  output_signal                         toDo;   // controlMachine's command 

  try
  {

    // astVerbosity output
    if (astVerbosity) 
      cout << "Reading xml PCDATA:" << a2b::XMLChar2string(chars) << "...\n";

    // get the output signal
    toDo = whatWeDo (CHAR_gxl_DATA);

    // Now, what will we do ?
    switch (toDo) {
      // add the first value
    case GET_int_value:
    case GET_string_value:
      c_value = a2b::XMLChar2string (chars);
      break;
      
      // concat other value
    case ADD_int_value:
    case ADD_string_value:
      c_value += a2b::XMLChar2string (chars);
      break;
    }
    
  }
  
  catch (bad_XOgastan & b)  {
    throw bad_factory (b.getBaseMessage (), b.getOtherMessage ());
  }
  
  catch (...) {
    throw bad_factory ("operativeMachine", "unknown event !");
  }
  
  return;

}


void
operativeMachine::endElement (const XMLCh * const name)
{
  output_signal                         toDo;   // controlMachine's command 
  string 
    gxl_element = a2b::XMLChar2string (name);   // string with the element name

  if (gxl_element != "gxl") {
    
    try {

      // astVerbosity output
      if (astVerbosity)       
	cout << "Reading end of gxl element " << gxl_element << "...\n";

      // Is legal element recognized by XOgastan ?
      // Remember : <bool>, <set>, and so on ... are not
      //            recognized by XOgastan
      if (end2input.find(gxl_element) != end2input.end())
	toDo = whatWeDo (end2input[gxl_element]);
      else
	throw bad_XOgastan ("operativeMachine", 
			    "Unexpected gxl element : " + gxl_element);

      switch (toDo) {

      case END_build:
	epilog ();
	break;

      case INSERT_node:
	// set the first nast_node read
	if (nastM.empty())
	  first_node_index = c_node_index;

	nastM[c_node_index] = c_nnp;      // add nast_node * to map
	c_nnp = NULL;                     // reset the nast_node*
	break;

      case INSERT_edge:
	edgeL.push_front (c_gep); 	  // add the gxl_edge* to list
	c_gep = NULL;	                  // reset the gxl_edge*
	break;

      case INSERT_attr:
	addAttrInNode ();	          // add the attr to the nast_node
	c_ga.reset ();	                  // reset the gxl_attr
	break;

      case INSERT_int_value:
      case INSERT_string_value:
	c_ga.setValue (c_value);
	break;

      case WRITE_type_node:
	c_nnp = newNastNode (c_type, c_node_index);   // Create new nast_node
	break;

      case WRITE_type_edge:
	c_gep->setType (c_type);          // set the TYPE of the edge
	break;
      }

    }
  
    catch (bad_XOgastan & b)  {
      throw bad_factory (b.getBaseMessage (), b.getOtherMessage ());
    }

    catch (...) {
      throw bad_factory ("operativeMachine", "unknown event !");
    }
    
  }
  return;
 
}
  
void
operativeMachine::endDocument ()
{
  if (astVerbosity) 
    cout << "End document...\n";
}


nast_node* 
operativeMachine::getNast(void)
  throw (bad_factory) {

  // If there are node the make else throw
  if (!nastM.empty())
    return nastM[first_node_index];
  else
    throw bad_factory("operativeMachine",
		      "No nodes builts");
}

list<nast_node *> *
operativeMachine::getNastList(void) 
  throw (bad_factory) {
  
  list<nast_node *>                   *listNast;    // list to build
  map< long, nast_node*>::iterator    p;            // browse the map of nodes

  // If there are node the make else throw
  if (!nastM.empty()) {
    
    listNast = new list<nast_node *>;          // create list
    p = nastM.begin();
    while (p != nastM.end()) {
      listNast->push_back(p->second);         // push element
      p++;                                    // go to next element
    }

    return listNast;                          // return list
  }
  else
    throw bad_factory("operativeMachine",
		      "No nodes builts");

}




// ---------------------------------------------------------------------------
//  Members FOR building
// ---------------------------------------------------------------------------

//--- Private Member

void
operativeMachine::prolog ()
{
  gxl_edge     *gep;    // edge to destroy
  
  // free the list of edges
  while (!edgeL.empty ())  {
    gep = edgeL.front ();
    edgeL.pop_front ();
    delete gep;
  }
  
  // Initialize the common informations
  c_nnp = 0;
  if (c_gep) {
    delete c_gep;
    c_gep = 0;
  }
  c_ga.reset();
  c_type = "";
  c_value = "";
  c_node_index = 0;
  first_node_index = 0;
}


void
operativeMachine::epilog (void)  throw (bad_factory) { 
  /*! for each edge in edgeL :
    
    - search the FROM nast_node
    - search the TO nast_node
    - insert the edge in FROM nast_node
    
    if TO or FROM nast_node doesn't exist then error

    - check if case_label is a case or a default
  */

  // use to find from_node and to_node
  map < long, nast_node * >::iterator p_nastM; 
  
  long          from_index;   // from index
  long          to_index;     // to index
  nast_node     *from_node;   // from nast_node *
  nast_node     *to_node;     // to nast_node *
  string        edge_type;    // code of the edge 
  edge_code     ec;           // edege code currespondent to edge_type
  nast_node     *nnp;         // used to adjust the case_label

  while (!edgeL.empty ())  {
    // pop the first element
    c_gep = edgeL.front ();
    edgeL.pop_front ();
    
    // get informations of the edge
    edge_type = c_gep->getType();
    from_index = c_gep->getFrom ();
    to_index = c_gep->getTo ();

    // delete the edge
    delete c_gep;

    // get FROM nast_node *
    if ((p_nastM = nastM.find (from_index)) != nastM.end ())
      from_node = p_nastM->second;
    else
      throw bad_factory ("operativeMachine",
			 "Unknown FROM node for edge:" + edge_type);

    // get TO nast_node *
    if ((p_nastM = nastM.find (to_index)) != nastM.end ())
      to_node = p_nastM->second;
    else
      throw bad_factory ("operativeMachine",
			 "Unknown TO node for edge:" + edge_type);
    
    
    if (from_node->hasEdgeName(ec = a2b::string2edge_code (edge_type)))
      throw bad_factory("operativeMachine", 
			"Impossibile to add the edge : duplicate edge");
    else
      from_node->addEdge (ec , to_node);

    // astVerbosity output
    if (astVerbosity)
      cout << "Add edge " << edge_type 
	   << " from node:" << from_index 
	   << " to node:" << to_index << "...\n";
  }

  // Adjust the case label
  for (p_nastM = nastM.begin(); p_nastM != nastM.end(); p_nastM++) { 
    nnp = p_nastM->second;
    if ( (nnp->getCode() == CASE_LABEL) && (!nnp->hasEdgeName(LOW_VALUE_EDGE)) )
      ((case_label_n *)nnp)->setDefault();
  }
  
  return;
}


output_signal 
operativeMachine::whatWeDo (input_signal is) throw (bad_factory)
{
  output_signal                         toDo;   // controlMachine's command 

  if (isErrorOutputSignal (toDo = cm.nextOutput (is))) {

    

    // What error is it ?
    switch (toDo)	{

    case SIGNAL_ERROR_gxl:
      throw bad_factory ("operativeMachine",
			 "Bad structure in the gxl document");
      break;
    case SIGNAL_ERROR_graph:
      throw bad_factory ("operativeMachine", 
			 "Bad structure in the graph");
      break;
    case SIGNAL_ERROR_node:
      throw bad_factory ("operativeMachine",
			 "Bad structure in the gxl <node>...</node>");
      break;
    case SIGNAL_ERROR_attr:
      throw bad_factory ("operativeMachine",
			 "Bad structure in the gxl <attr>...</attr>");
      break;
    case SIGNAL_ERROR_int:
      throw bad_factory ("operativeMachine",
			 "Bad structure in the gxl <int>...</int>");
      break;
    case SIGNAL_ERROR_string:
      throw bad_factory ("operativeMachine",
			 "Bad structure in the gxl <string>...</string>");
      break;
    case SIGNAL_ERROR_edge:
      throw bad_factory ("operativeMachine",
			 "Bad structure in the gxl <edge>...</edge>");
      break;
    case SIGNAL_ERROR_type_node:
      throw bad_factory ("operativeMachine",
			 "Bad node type in the gxl <type>...</type>");
      break;
    case SIGNAL_ERROR_type_edge:
      throw bad_factory ("operativeMachine",
			 "Bad edge type in the gxl <type>...</type>");
      break;
    }
    
  }
  cm.nextState (is);    // get the next state
  return toDo;
}


nast_node *
operativeMachine::newNastNode (string type, long index)
{

  nast_node                       *nnp;    // The new nast_node
  nast_code 
    code = a2b::string2nast_code(type);    // The code of the nast_node

  // is other_* node ?
  if (isOthrDecl (code))
    nnp = new othr_decl_n;
  else if (isOthrType (code))
    nnp = new othr_type_n;
  else if (isOthrCst (code))
    nnp = new othr_cst_n ();
  else if (isOthrStmt (code))
    nnp = new othr_stmt_n;
  else if (isOthrOthr (code))
    nnp = new special_n;
  else if (isOthrExpr (code))
    nnp = new othr_expr_n;

  // is expr_* node ?
  else if (isUnaryExpr (code))
    nnp = new unary_expr_n;

  else if (isBinaryExpr (code))
    nnp = new binary_expr_n;

  else if (isTernaryExpr (code))
    nnp = new ternary_expr_n;

  else if (isRefExpr (code))
    nnp = new ref_expr_n;

  else
    // is a well know node ?
    switch (code) {
      // allocate the declaration nodes
    case VAR_DECL:
      nnp = new var_decl_n; break;
    case PARM_DECL:
      nnp = new parm_decl_n; break;
    case CONST_DECL:
      nnp = new const_decl_n; break;
    case RESULT_DECL:
      nnp = new result_decl_n; break;
    case FIELD_DECL:
      nnp = new field_decl_n; break;
    case TYPE_DECL:
      nnp = new type_decl_n; break;
    case FUNCTION_DECL:
      nnp = new function_decl_n; break;
    case LABEL_DECL:
      nnp = new label_decl_n; break;
      
      // allocate the type nodes
    case VOID_TYPE:
      nnp = new void_type_n; break;
    case INTEGER_TYPE:
      nnp = new integer_type_n; break;
    case ENUMERAL_TYPE:
      nnp = new enumeral_type_n; break;
    case REAL_TYPE:
      nnp = new real_type_n; break;
    case ARRAY_TYPE:
      nnp = new array_type_n; break;
    case UNION_TYPE:
      nnp = new union_type_n; break;
    case RECORD_TYPE:
      nnp = new record_type_n; break;
    case POINTER_TYPE:
      nnp = new pointer_type_n; break;
    case FUNCTION_TYPE:
      nnp = new function_type_n; break;
      
      // allocate the constant nodes
    case INTEGER_CST:
      nnp = new integer_cst_n; break;
    case REAL_CST:
      nnp = new real_cst_n; break;
    case STRING_CST:
      nnp = new string_cst_n; break;
      
      // allocate the statement nodes 
    case BREAK_STMT:
      nnp = new break_stmt_n; break;
    case CONTINUE_STMT:
      nnp = new continue_stmt_n; break;
    case SCOPE_STMT:
      nnp = new scope_stmt_n; break;
    case EXPR_STMT:
      nnp = new expr_stmt_n; break;
    case RETURN_STMT:
      nnp = new return_stmt_n; break;
    case DECL_STMT:
      nnp = new decl_stmt_n; break;
    case GOTO_STMT:
      nnp = new goto_stmt_n; break;
    case LABEL_STMT:
      nnp = new label_stmt_n; break;
    case IF_STMT:
      nnp = new if_stmt_n; break;
    case SWITCH_STMT:
      nnp = new switch_stmt_n; break;
    case FOR_STMT:
      nnp = new for_stmt_n; break;
    case WHILE_STMT:
      nnp = new while_stmt_n; break;
    case DO_STMT:
      nnp = new do_stmt_n; break;
    case COMPOUND_STMT:
      nnp = new compound_stmt_n; break;
    case ASM_STMT:
      nnp = new asm_stmt_n; break;
      
      // allocate the other node
    case IDENTIFIER_NODE:
      nnp = new identifier_n; break;
    case TREE_LIST:
      nnp = new tree_list_n; break;
    case CASE_LABEL:
      nnp = new case_label_n; break;
      
    default:
      throw bad_factory ("operativeMachine",
			 "Unknown node type, impossibile to create the nast_n");
    }

  nnp->setId (index);         // set the node index
  nnp->setCode (code);        // set the node code

  return nnp;
}



void
operativeMachine::addAttrInNode (void)
{
  /* NOTE : constant nodes and expression nodes (unary, binary, 
     ternary, reference, others) haven't any attributes
  */

  nast_code 
    code = c_nnp->getCode ();    // The code of the nast_node


  // What node class belong to ?

  // declaration nodes
  if (isDecl (code) || isOthrDecl (code))
    addAttrInDecl ();

  // type nodes
  else if (isType (code) || isOthrType (code))
    addAttrInType ();

  // statement nodes
  else if (isStmt (code) || isOthrStmt (code))
    addAttrInStmt ();

  // other nodes
  else if (isOthr (code))
    addAttrInOthr ();

  else
    printWarning ("operativeMachine",
		  "The attribute doesn't belong to any node");

  return;
}


void
operativeMachine::addAttrInDecl ()
{
  string      msg;                            // warning message
  bool        setted = true;                  // true if attr will be set
  nast_code   code = c_nnp->getCode ();       // code of the nast_node
  long        id = c_nnp->getId ();           // id of the nast_node
  string      name = c_ga.getName ();         // attr's name
  string      value = c_ga.getStringValue (); // attr's value

  decl_n      *dcl_np = dynamic_cast < decl_n * >(c_nnp);


  // Set common attributes : artificial, source file, source line
  if (name == "source_file")
    dcl_np->setSource (value);
  else if (name == "source_line")
    dcl_np->setLine (c_ga.getIntValue ());
  else if (name == "flag") {

    // Remember : we can have different flag in the decl_n
    if (value == "artificial")
      dcl_np->setArtificial ();

    else
      // Set private attribute
      switch (code) {
	
      case FUNCTION_DECL: {
	function_decl_n 
	  *f_dcl_np = dynamic_cast < function_decl_n * >(c_nnp);
	
	setted = true;
	// Set one of the private attributes : extern, static, undefined 
	if (value == "static")
	  f_dcl_np->setStatic ();
	else if (value == "extern") 
	  f_dcl_np->setExtern ();
	else if (value == "undefined")
	  f_dcl_np->setUndefined ();
	else {
	  msg = "Unknown attribute for FUNCTION_DECL : ";
	  setted = false;
	}
      }
      break;
      
      case VAR_DECL: {
	var_decl_n 
	  *v_dcl_np = dynamic_cast < var_decl_n * >(c_nnp);
	
	if (value == "register") 
	  v_dcl_np->setRegister ();
	else {
	  msg = "Unknown attribute for VAR_DECL : ";
	  setted = false;
	}
      }   
      break;

      case PARM_DECL: {
	parm_decl_n 
	  *p_dcl_np = dynamic_cast < parm_decl_n * >(c_nnp);

	if (value == "register")
	  p_dcl_np->setRegister ();
	else {
	  msg = "Unknown attribute for PARM_DECL : ";
	  setted = false;
	}
      }   
      break;

      case FIELD_DECL: {
	field_decl_n 
	  *fl_dcl_np = dynamic_cast < field_decl_n * >(c_nnp);

	if (value == "bitfield")
	  fl_dcl_np->setBitfield ();
	else {
	  msg = "Unknown attribute for FIELD_DECL : ";
	  setted = false;
	}
      }
      break;
	    
      default:
	msg = "Impossibile to set the attr : ";
	setted =false;
      }
  }
  else 
    msg = "Impossibile to set the attr : ";

  // Isn't the attribute set ?
  if (!setted)
    printWarning ("operativeMachine", msg + name + "=" + value );

  // astVerbosity output
  if (astVerbosity)
    cout << "Adding attribute (" << name << "=" << value 
	 << ") to node " << id << "...\n";

  return;
}


void
operativeMachine::addAttrInType (void)
{
  string      msg;                            // warning message
  bool        setted = true;                  // true if attr will be set
  nast_code   code = c_nnp->getCode ();       // code of the nast_node
  long        id = c_nnp->getId ();           // id of the nast_node
  string      name = c_ga.getName ();         // attr's name
  string      value = c_ga.getStringValue (); // attr's value

  type_n      *type_np = dynamic_cast < type_n * >(c_nnp);

  // Set one common attribute : qualifier
  if (name == "qualifier")  {
    
    if (value == "constant")
      type_np->setConstant ();
    else if (value == "volatile")
      type_np->setVolatile ();
    else if (value == "restrict")
      type_np->setRestrict ();
    else {
      msg = "Unknown qualifier for *_TYPE : ";
      setted = false;
    }
  }
  else
    // Set private attribute
    switch (code) {

    case INTEGER_TYPE: {
      integer_type_n 
	*i_type_np = dynamic_cast < integer_type_n * >(c_nnp);
      
      // Set private attribute : unsigned
      if (name == "flag") {
	if (value == "unsigned")
	  i_type_np->setUnsigned ();
	else {
	  msg = "Unknown attribute for INTEGER_TYPE : ";
	  setted = false;
	}
      }
      else {
	msg = "Unknown attribute for INTEGER_TYPE : ";
	setted = false;
      }
    }
    break;

    case ENUMERAL_TYPE: {
      enumeral_type_n 
	*e_type_np = dynamic_cast < enumeral_type_n * >(c_nnp);
      
      // Set private attribute : unsigned
      if (name == "flag") {
	if (value == "unsigned")
	  e_type_np->setUnsigned ();
	else {
	  msg = "Unknown attribute for ENUMERAL_TYPE : ";
	  setted = false;
	}
      }
      else {
	msg = "Unknown attribute for ENUMERAL TYPE : ";
	setted = false;
      }
    }
    break;
      
    default:
      msg = "impossibile to set the attr : ";
      setted = false;
    }

  // Isn't the attribute set ?
  if (!setted)
    printWarning ("operativeMachine", msg + name + "=" + value );

  // astVerbosity output
  if (astVerbosity)
    cout << "Adding attribute (" << name << "=" << value 
	 << ") to node " << id << "...\n";

  return;
}



void
operativeMachine::addAttrInStmt (void)
{
  string      msg;                            // warning message
  bool        setted = true;                  // true if attr will be set
  nast_code   code = c_nnp->getCode ();       // code of the nast_node
  long        id = c_nnp->getId ();           // id of the nast_node
  string      name = c_ga.getName ();         // attr's name
  string      value = c_ga.getStringValue (); // attr's value

  stmt_n      *stmt_np = dynamic_cast < stmt_n * >(c_nnp);

  // Set one common attribute : line
  if (name == "line")
      stmt_np->setLine (c_ga.getIntValue ());
  else
    // Set private attribute
    switch (code)  {

    case SCOPE_STMT: {
      scope_stmt_n 
	*sc_stmt_np = dynamic_cast < scope_stmt_n * >(c_nnp);
	
      // Set private attribute : unsigned
      if (name == "flag") {
	
	if (value == "begin")
	  sc_stmt_np->setBegin ();
	else if (value == "end")
	  sc_stmt_np->setEnd ();
	else if (value == "no_variable")
	  sc_stmt_np->setVariables ();
	else {
	  msg = "Unknown attribute for SCOPE_STMT : ";
	  setted = false;
	}
      }
      else {
	msg = "Unknown attribute for SCOPE_STMT : ";
	setted = false;
      }
    }
    break;
	
    default:
      msg = "Impossibile to set the attr : ";
      setted = false;
    }

  // Isn't the attribute set ?
  if (!setted)
    printWarning ("operativeMachine", msg + name + "=" + value );

  // astVerbosity output
  if (astVerbosity)
    cout << "Adding attribute (" << name << "=" << value 
	 << ") to node " << id << "...\n";
  
  return;
}


void
operativeMachine::addAttrInOthr (void)
{
  string      msg;                            // warning message
  bool        setted = true;                  // true if attr will be set
  nast_code   code = c_nnp->getCode ();       // code of the nast_node
  long        id = c_nnp->getId ();           // id of the nast_node
  string      name = c_ga.getName ();         // attr's name
  string      value = c_ga.getStringValue (); // attr's value

  // Set private attribute
  if (code == IDENTIFIER_NODE) {
    identifier_n 
      *id_np = dynamic_cast < identifier_n * >(c_nnp);
    
    // Set private attribute : string
    if (name == "string")
      id_np->setString (value);
    else {
      msg = "Unknown attribute for IDENTIFIER_NODE : ";
      setted = false;
    }
  }
  else {
    msg = "Impossibile to set the attr : ";
    setted = false;
  }

  // CASE_LABEL IS default: ONLY IF IT HASN'T ANY EDGES

  // Isn't the attribute set ?
  if (!setted)
    printWarning ("operativeMachine", msg + name + "=" + value );

  // astVerbosity output
  if (astVerbosity)
    cout << "Adding attribute (" << name << "=" << value 
	 << ") to node " << id << "...\n";
  
  return;
}
