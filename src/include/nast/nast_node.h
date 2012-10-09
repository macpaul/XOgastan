/***************************************************************************
			   nast_node.h  -  description
			      -------------------
     begin                : July 12 2001
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


#ifndef _NAST_NODE_H
#define _NAST_NODE_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------

#include "nast/nast_code.h"
#include "nast/edge_code.h"


#include "error/bad_nast.h"

#include <map>


// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

class visitor;

//! The base class of the hierarcy of all the nodes of a nast_tree
/*! The base class of the hierarcy of all the nodes of a nast_tree

  The node is the elementary element of the nast_tree. It is composed by 2
  parts : 
  
  - some attributes
  - a list of the output edges 
  
  We can have differents types of nodes. Each node reflect a syntax element
  of the C/C++ grammar. For example we have nodes for declarations (
  vars, functions, ...), for types (int, float, ...) and so on ...
  
  In this implementation :
  
  - some C nodes have its own class : see var_decl_n, for_stmt_n, ...
  - others C/C++ nodes are grouped togheter to form a single class :
  see the nodes for the expressions, the C++ nodes, ... 

  All these classes form a three level hierarcy structure.
  The father of the hierracy is the class nast_node.  
  The first level of child classes is formed by : decl_n, type_n, stmt_n, 
  cst_n, othr_n, expr_n.
  At the third level we have the special case of nodes : var_decl_n, 
  type_decl_n, integer_type_n, for_stmt_n, and a lot of other nodes.
  

  The attributes are distributed along the classes.
  We have 2 attributes common to all the classes; they are the index of
  the node and the code of the nodes. 
  Some of the others derived classes have our attribute, but a lot of them
  don't have any attribute.
  For example the declaration nodes have the attributes number_of_line, 
  name_of_the_source_file, ... The constant nodes don't have any attributes, ...

    
  The edges are organized in a map. The map of the edges is defined 
  into the base class nast_node, and each edge has its code; so the
  key of the map is the code of the edge, and the value is the 
  output link (the address) to the nast_node. We defines 
  all the methods that can used to access edges. We can access to the
  edge map using :
  
  - the list method : by browsing from the first to the last edge
  - the direct access method : by the code of the edge
  
  For more info about the nast_code and the edge_code see the file
  nast_code.def and edge_code.def.
  In these two file we use the syntax :
  
  DEFnastCODE ( UPP_CODE, str_code, common_attr, private_attr)
  where :
  - UPP_CODE is the code used in the enumeration nast_code
  - str_code is the string used in the gxl document for the code
  - common_attr is the number of attributes common with the base class
  - private_attribute is the number of the private attributes (not
  present in the base class)

  DEFedgeCODE(str_code, UPP_CODE)
  where :
  - UPP_CODE is the code used in the enumeration edge_code
  - str_code is the string used in the gxl document for the code

*/
class nast_node {

 private:

  //*** Attributes

  //! The code of the node
  /*! The code of the node */
  nast_code 	code;   
  //! The index of the node
  /*! The index of the node */
  long 		id;	
	
  //! The map for the output edges
  /*! The map for the output edges
    
    Each output edge has its entry in this map.
    The key is the edge_code and the value is the link (pointer)
    to the currespondent nast_node
  */
  map<edge_code, nast_node *> edges; 

  //! The iterator used to browse the map of edges
  /*! The iterator used to browse the map of edges */
  map<edge_code, nast_node *>::iterator p_edges;

  //! The number of the current element pointed by the iterator p_edges
  /*! The number of the current element pointed by the iterator p_edges */
  unsigned long p_pos;

 public:
  //! Constructor
  /*! Constructor */
  nast_node() : code(NO_NAST_CODE), id(0) { return; }

  //! Constructor
  /*! Constructor */
  nast_node(nast_code c, long idnt) : code(c), id(idnt) { return; }

  //! Destructor
  /*! Destructor */
  ~nast_node() {}

  //*** Members

  // access to the base attributes 
  
  //! Set the code of the node 
  /*! Set the code of the node 

   \param c the code of the node
  */
  void setCode(nast_code c);

  //! Get the code of the node 
  /*! Get the code of the node 
   
    \return The code of the node.
   */
  nast_code getCode(void);
  
  //! Set the index of the node 
  /*! Set the index of the node 

    \param id the index of then node
   */
  void setId(long id);

  //! Get the index of the node 
  /*! Get the index of the node 

    \return The index of the node.
   */
  long getId(void);
  
  
  // SEQUENTIAL access to the edges
  
  //! The first edges if it exist or THROW exception
  /*! The first edges if it exist or THROW exception.
    
    \return The pointer to first nast_node (linked to current nast_node)
  */
  nast_node *firstEdge (void) throw (bad_edge);
  
  //! The next edges if it exist or THROW exception
  /*! The next edges if it exist or THROW exception
    
    \return The pointer to next nast_node (linked to current nast_node)
    in the map
  */
  nast_node *nextEdge(void) throw (bad_edge);

  //! The edge code of the current edge pointed by p_edges or THROW exception
  /*! The edge code of the current edge pointed by p_edges or THROW exception
    
    \return  The current edge code
  */
  edge_code currentEdgeCode(void) throw (bad_edge);

  //! Checks if the node has some edge
  /*! Checks if the node has some edge 
    
    \return True if the node has almost one edge,
    false otherwise
  */
  bool hasEdges(void);

  //! Checks if the node has the next edge, after the current one
  /*! Checks if the node has the next edge, after the current one
    
    \return True if we have next edge, 
    false if is the map is empty or we haven't next edge
  */
  bool hasNextEdge(void);

  // DIRECT access to the edges

  //! Search edge by name or THROW exception
  /*! Search edge by name or THROW exception
  
    \param ec the name of the edge

    \return The edge with the code ec 
  */
  nast_node *edgeName(edge_code ec) throw (bad_edge);
  
  //! Checks if the node has the edge with the code ec
  /*! Checks if the node has the edge with the code ec
    
    \param ec the name of the edge

    \return True if we have the edge with th code ec,
    false if is the map is empty or we haven't the edge
  */
  bool hasEdgeName(edge_code ec);

  // edges MANAGEMENT

  //! Add an edge
  /*! Add an edge to a nast_node with the name ec.
    If the edge exist THROW exception.
  
    \param ec the key of the edge
    \param nnp the link of the edge

  */
  void addEdge(edge_code ec, nast_node *nnp) throw (bad_edge);


  //! Delete an edge
  /*! Delete the edge with name ec.
    If the edge doesn't exist THROW exception, or
    if the map is empty THROW exception.

    \param ec the name of the edge

  */
  void delEdge(edge_code ec) throw (bad_edge);

  //! The numbers of edges of the node
  /*! The numbers of edges of the node
    
    \return The number of the edges in the map
  */
  int edgesNum(void);

  //! Accept the visit 
  /*! Accept the visit 

    \sa visitor
   */
  virtual void accept(visitor &);
  
};

// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

//! The Class for the comparison between 2 objects nast_node
/*! 
  This class is used to compare 2 objects nast_node.
  
  The comparation between 2 nast_node is made used the attribute 
  id.
  Given the 2 object nast_node nn1 and nn2 then :

  - nn1 <  nn2 if only if nn1::id <  nn2::id
  - nn1 == nn2 if only if nn1::id == nn2::id
  - nn1 >  nn2 if only if nn1::id >  nn2::id
  
  Remember : the type of the attribute nast_node::id 
  is long.

  \note This class overload the operator ().
*/
class nast_node_Cmp {

 public:

  //! The member for the comparison
  /*!
    Overload the operator ().

    \param nn1 the first nast_node
    \param nn2 the second nast_node

    \return True if nn1::id < nn2::id,
    false otherwise.
  */
  bool operator()(nast_node& nn1, nast_node& nn2);

  //! The member for the comparison
  /*!
    Overload the operator ().

    \param nn1 the first nast_node
    \param nn2 the second nast_node

    \return True if nn1::id < nn2::id,
    false otherwise.
    
    \note This method differs from the previous in the type 
    of the parameters. Now we have pointer, in the previous
    method we have reference.
  */
  bool operator()(nast_node* nn1, nast_node* nn2);

};

#endif




