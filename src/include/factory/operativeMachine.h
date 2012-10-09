/***************************************************************************
			   operativeMachine.h  -  description
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

#ifndef _OPERATIVE_MACHINE_H
#define _OPERATIVE_MACHINE_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "factory/gxl_attr.h"
#include "factory/gxl_edge.h"
#include "factory/controlMachine.h"

#include "error/bad_factory.h"

#include "nast/nast_code.h"
#include "nast/nast_node.h"
#include "nast/type_n.h"
#include "nast/decl_n.h"
#include "nast/stmt_n.h"
#include "nast/expr_n.h"
#include "nast/othr_n.h"
#include "nast/cst_n.h"

#include "utils/is_functions.h"
#include "utils/get_functions.h"
#include "utils/print_warning.h"
#include "utils/a2b.h"
#include "utils/flags.h"

#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/sax/AttributeList.hpp>
#include <xercesc/framework/XMLFormatter.hpp>
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/util/XMLString.hpp>

#include <list>
#include <map>
#include <string>

// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

//! The event driven class to build NAST
/*!  
  In accord with the SAX API specific this class
  read the gxl document and execute the event handler when
  an XML element is read.

  The operativeMachine raise the trigger of the ASTBuilder and so it
  starts and drives the building process.

  For a complete documentantion of the SAX API see the manual
  reference. 
  We talk only about the use of the SAX API in the XOgastan 
  software.

  This class performs the building process of NAST, or in 
  other words it builds the NewAbastractSyntaxTree
  
  The builder process is performed using some classes :

  - operativeMachine, the HandlerBase class for the xerces SAX API. It
  build the edges and the nodes
  - controlMachine, stores the context (state) during the building process
  
  So we can tell :

  <b>"The SAXParser read the gxl file one element at time and communicate to
  the operativeMachine what element we have read. The operativeMachine asks to 
  controlMachine which we will do. The controlMachine
  answers with a command that the operativeMachine excute. !!"</b>

  The operativeMachine contains all the data structures that 
  are used during the building :
  
  - two <map> for the translation string2input_signal (of the controlMachine)
  - gxl_attr class that holds one attribute of a node
  - gxl_edge class that holds one edge
  - one <list> of pointer to gxl_edge that holds all the edges built
  - one <list> of pointer to nast_node that holds all the nodes built
  - one controlMachine object that assist the building process 
  
  We can divide the building process in some steps :
  
  - prolog  : prepare all the structure
  - bulding : build the nodes (and their attributes) and the edges
  - epilog  : insert the edges into the nodes (remapping the 
  integer indexes of the nodes in nast_node *),and adjust the
  case_label nodes.
  
  During the prolog and the epilog the  operative Machine don't communicate with
  the controlMachine.
  
  During the building step the operativeMachine is event driven by 
  the SAXParser (that pass the gxl element read from the gxl document), and it 
  communicate with the controlMachine that drives the building process.
  
  The data structure that we use are presents in the C++ standard library.

  \note This class holds in an attribute the first nast_node * of the
  NAST.
*/

class operativeMachine : public HandlerBase
{
 private:

  //---- ATTRIBUTES

  //! The state machine
  /*!    
    The state machine help the operativeMachine during the building process.
    
    The gxl document that we parse have a well defined structure. It's
    generated by the gcc2gxl.pl perl tool, and we know how the gxl
    element are used, how they are nested, and so on ...
    
    The state machine reflect the structure of the gxl element. The
    parser trig an event to operativeMachine and this last asks to controlMachine
    which will do. If the controlMachine recognize an error then it
    communicate a SIGNAL_ERROR_* output signal, otherwhise it returns an
    output signal that the operativeMachine excute.
    
    We can tell :
    
    <b>"the controlMachine is the mind, and the 
    operativeMachine is the hand !!"</b>

    The processor in modern PC work similarly ! We have two internal parts
    (into the processor) : control-part (CP) and operative-part (OP).
    The OP has all the hardware elements to read data from cache, to execute
    add, mult, shift, jump, and so on ... The CP provides mechanism to 
    interpret the instruction reda by the OP, and to decide what the OP
    will do !
  */
  controlMachine cm;

  //! Map of pointer to nast_nodes
  /*!
    All the nodes that we have partially or completely built are placed in
    this map.
    
    The key is index of the nast_node, and the value is the currespondent
    pointer (address) of he nast_node :
    
    <i><index, nast_node *></i>
    
    At the end of the building process all the nodes read from the gxl element
    are in this map.
    
    \note The index of nast node is the id assigned by the GCC during the 
    dumping process.
  */
  map < long, nast_node * > nastM;

  //! List of pointer to gxl_edge
  /*!
    All the edges that we read from the gxl document, and that the 
    operativeMachine has been built, are placed in this list.
    
    The building process of the edges is perfomed in two steps :
    
    - first, alls the edges that we read from the gxl element are built how
    gxl_edge and placed in thi list.
    - second, when the SAXParser has read all the gxl document then the 
    gxl_edges in this list are added to the currespondent nast_node (if
    the nast_node don't exist an error is raised ... )
  */
  list < gxl_edge * >edgeL;

  //! The maps for translation of the gxl string element to input_signal
  /*!
    The container start2input maps the string with the gxl_element 
    in input_signal
    
    For example given the gxl_element string "node" then :
    
    start2input["node"] == START_gxl_NODE
    
    This map is used by the method startElement to recognize what
    kind of gxl_element has been read.
  */
  map < string, input_signal > start2input;


  //! The maps for translation of gxl string element to input_signal
  /*!
    The container end2input maps the string with the gxl_element 
    in input_signal
    
    For example given the gxl_element string "node" then :
    
    end2input["node"] == END_gxl_NODE
    
    This map is used by the method endElement to recognize what
    kind of gxl_element has been read.
  */
  map < string, input_signal > end2input;

  //! The current node index
  /*!
    \note c_index means current_index
  */
  long c_node_index;
  
  //! Index of the first node added in the map
  long first_node_index;

  //! The current type of node or of edge
  /*!
    \sa nast_code.def nast_code.h edge_code.def edge_code.h

    \note c_type means current_type
  */
  string c_type;

  //! The current value of the <attr> (it may be string or int) 
  string c_value;

  //! The  pointer to nast_node 
  /*!        
    It points to the nast_node that we are building. Before
    start the building of a new node this current_nast_node_pointer
    is added into the map nastM :
    
    <c_nnp->getId(), c_nnp>
    
    After, the node will build by reading its content : one <type>...</type>,
    and zero, one or more <attr>...</attr>

    \note c_nnp means current_nast_node_pointer
  */
  nast_node *c_nnp;
  
  //! The attribute of a nast_node
  /*!    
    When we build a node, we fill the attribute following the 
    steps :
    
    - first, we build the gxl_attr object one for time. It is filled
    with the information read from the gxl file (this information
    is the <string>...</string> or <int>...</int> value).
    - second, when the <attr>...</attr> has been parsed we register
    the attribute into the nast_node.
    
    \note c_ga stay for current_gxl_attribute
  */
  gxl_attr c_ga;

  //! The  pointer to gxl_edge
  /*!
    It points to the gxl_edge that we are building. Before
    start the building of a new edge this current_gxl_edge_pointer
    is added into the list edgeL.

    \note c_gep stay for current_gxl_edge_pointer
  */
  gxl_edge *c_gep;

  
  //---- Members
  
  //! The prolog
  /*!    
    During the prolog step we initialize some data structure and
    prepare the operativeMachine for the building process.   
  */
  void prolog ();
  
  //! The epilog
  /*!    
    During the epilog  we insert the edges into the nodes and we 
    perform some others operation for the finalitazion step
    (set the case_label how case or decfault clause).
    
    An exception is raised if is impossibile to add an edge into a node.
  */
  void epilog (void)
    throw (bad_factory);
  
  //! controlMachine Management
  /*!    
    We compute the output signal and the next state of the 
    controlMachine.
    If an SIGNAL_ERROR_* is sent by the controlMachine then an
    exception is raised.

    \param is the input_signal triggered by the SAXParser
    \return The output signal of the controlMachine : the command
    that the operativeMachine must excute.

    Pre : true
    Post: 
  */
  output_signal whatWeDo (input_signal is)
    throw (bad_factory);
  

  //----  Member used during the building process

  //! Build a new nast_node
  /*!    
    \param type the code of the nast_node (it is used for the dynamic cast)
    \param index the index of the nast_node
    
    \return The pointer of the nast_node created
  */
  nast_node *newNastNode (string type, long index);
  
  
  //! Insert the attribute into the nast_node
  /*!    
    Insert the c_ga into c_nnp.
  */
  void addAttrInNode (void);
  
  
  //! Insert the attribute into the declaration nast_node
  /*!    
    Insert the c_ga into c_nnp (where c_nnp is a decl_n)

    The activity diagram has the follow base schema :
    \image html addAttr.png
  */
  void addAttrInDecl (void);
  
  
  //! Insert the attribute into the type nast_node
  /*!    
    Insert the c_ga into c_nnp (where c_nnp is a type_n)

    The activity diagram has the follow base schema :
    \image html addAttr.png
  */
  void addAttrInType (void);
  
  //! Insert the attribute into the stmt nast_node
  /*!  
    Insert the c_ga into c_nnp (where c_nnp is a stmt_n)
    
    The activity diagram has the follow base schema :
    \image html addAttr.png
  */
  void addAttrInStmt (void);
  
  
  //! Insert the attribute into the othr nast_node
  /*!    
    Insert the c_ga into c_nnp (where c_nnp is a othr_n)

    The activity diagram has the follow base schema :
    \image html addAttrInOthr.png
  */
  void addAttrInOthr (void);

  //---- ERROR Handlers

  //! Receive notification of a parser warning.
  void warning(const SAXParseException& exception);

  //! Receive notification of a recoverable parser error.
  void error(const SAXParseException& exception);
  
  //! Report a fatal XML parsing error.
  void fatalError(const SAXParseException& exception);

 public:
  //! Constructor
  operativeMachine();

  //! Destructor
  ~operativeMachine();
  
  //---- SAX Handlers overrideds members
  
  //! The gxl document start
  void startDocument();

  //! A new starting element is read from the gxl file !
  /*!    
    This event is raised by the SAXParser when it recognize 
    the begin of a gxl element.
    
    \param name the element that th SAXParser recognize
    \param attributes the list of the gxl attributes of the element
    
    We note that :
    when a gxlElement start we can have same attributes
    associates with it, but not all this attributes
    are importants during the building process.

    The list of the gxlElement and their attributes is :
	
    \code
	<graph id="foo">	
		id 		not important	

	<node id="foo">		
		id		important, foo is the address

	<attr name="foo">	
		name		important, foo is the purpose

	<edge from="foo1" to="foo2">
		from		important, foo1 is the base address
		to		important, foo2 is the destination

	<type xlink:href="gccast.xml#foo">
		xlink:href	important, foo is the type of the element
    \endcode		

    This method ask to controlMachine what will do. The controlMachine
    send and answer and some operation is performed.
    The question is sent using an input signal of the state machine,
    the answer is an output signal of the state machine.
    The operations perfomed depend on the output signal
    returned by the controlMachine. It collects some informations :
    
    - the <b>"id"</b>, for <node id="??">
    - the <b>"from"</b>, for <edge from="??" to="??">
    - the <b>"to"</b>, for <edge from="??" to="??">
    - the <b>"name"</b>, for <attr name="??">
    - the <b>"xlink:href"</b>, for <type xlink:href="??">
    - the type of the attr value : int or string

    The sequence diagram is :
    \image html startElement.jpg

    If the name (the gxl element passed by argument) isn't a legal
    element (in other word it doesn't match any input signal) the
    an exception is raised. See the follow sequence diagram :
    \image html nameNolegal.jpg
    
    \note The id and xlink:href must be parsed. 
    The id has the syntax nd<number>, and the string nd must be eliminate.
    The xlink:href has the syntax gccast.xml#<type>, and the string 
    gccast.xml# must be eliminate.

  */
  void startElement(const XMLCh* const name, AttributeList& attributes);

  //! A new data element is read from the gxl file !
  /*!    
    This event is raised by the SAXParser when it recognize
    the CDATA element.
    
    \param chars the XMLCh * string with the data read from the gxl document
    \param length the number of XMLCharacters into the string
    
    This event is used when we build the elements <int>...</int> or
    <string>...</string>

    The sequence diagram is :
    \image html characters.jpg
  */
  void characters(const XMLCh* const chars, const unsigned int length);


  //! A new ending element is read from the gxl file !
  /*!
    This event is raised by the SAXParser when it recognize 
    the end of a gxl element.
    
    \param name the element that th SAXParser recognize
    
    This method ask to controlMachine what will do. The controlMachine
    send and answer and some operation is performed.
    The question is sent using an input signal of the state machine,
    the answer is an output signal of the state machine.
    The operations perfomed depend on the output signal
    returned by the controlMachine. The operations can be :
    
    - add a nast_node into the currespondent map
    - add a gxl_edge into the currespondent list
    - set the type of an gxl_edge
    - create a new nast_node 
    - get the value of a string attribute
    - get the value of an int attribute
    - add the attr to the current node

    The sequence diagram is :
    \image html endElement.jpg

  */
  void endElement(const XMLCh* const name);

  //! The gxl document end
  void endDocument();

  //! Return the fisrt node built
  /*!
    \return The pointer to the first nast_node built. This
    node is father of the NAST.
  */
  nast_node* getNast(void)
    throw (bad_factory);

  //! Return a list of the nast_node * built
  /*!
    \return The list of the nast node built
  */
  list<nast_node *> *getNastList(void) 
    throw (bad_factory);
};


#endif
