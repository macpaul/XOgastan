/***************************************************************************
			   graphData.h  -  description
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

#ifndef _GRAPH_DATA_H
#define _GRAPH_DATA_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "data/dataObj.h"

#include "utils/a2b.h"

#include "error/bad_data.h"

#include <string>
#include <list>
#include <map>
#include <fstream>

// ---------------------------------------------------------------------------
//  typedef
// ---------------------------------------------------------------------------

//! The base data for a node
/*!
  Each node has :
  - an identifier (it is unique into the graph)
  - a name
  - a color
*/
typedef struct { 
  //! The identifier 
  int      id;
  //! The name 
  char     *name;
  //! The color 
  int      c;
} node;


//! The out link of an edge
/*!
  An edge links a FROM point (initial node) to 
  a TO point (final node).
  This struct is used to hold informations about
  the TO (final) point of an edge, and about the label 
  of the edge itself.
*/
typedef struct {
  //! The TO point
  int      to;
  //! The label
  char     *label;
} outEdge;


// ---------------------------------------------------------------------------
//  CLASS graphData
// ---------------------------------------------------------------------------

//! This class implements a graph
/*! 
  The graph is composed by :
  - a set of nodes
  - a set of edges
  
  Each node has :
  - an identifier
  - a name
  - a color
  
  Each edge has :
  - a from point
  - a to point
  - a label
  
  We define :
  - operation to add a node
  - operation to add an edge
  - operations to browse the nodes
  - operation to dump a dot file of the graph
  
  To browse the node we must use the follow protocol :
  
  \code
  graphData   graph;
  node        *n;
  
  if (graphNodes.has()) {
    n = graph.firstNode();
    use n;
    while (graph.hasNextNode()) {
      n = graph.nextNode();
      use n;
    }
  }
  \endcode
*/
class graphData : public dataObj
{
 protected:
  
  //---- Attributes

  //! The list of the nodes
  /*!
    The nodes are stored into a list !
  */
  list<node *>                nodesL;

  //! The multimap of the edges 
  /*!
    An edge is specified using :
    - the id of the from node
    - the struct outEdge of the TO point
    
    \note Two edge e1 and e2 are equals only if 
    (e1.from == e2.from) && (e1.outEdge.to == e2.outEdge.to) && 
    (e1.outEdge.label == e2.outEdge.label)
    
  */
  multimap<int, outEdge *>     edgesMM;

  //! The iterator to the list of the nodes
  list<node *>::iterator       pNodesL;

  //! The ordinal position of pNodesL into the list
  long                         pNodesL_pos;

  //! The number of nodes
  long                         nodesNum;

  //---- Members
  
  //! Return the name of a node
  /*!
    \param id the identifier of the node
    
    \return The name of the node (the field
    node.name).
  */
  string getNodeName(int id)
    throw (bad_data);

 public:
  //! Constructor
  graphData() 
    { nodesNum = 0; }
  
  //! Destructor
  ~graphData();
  
  //---- Typedef
  
  //! The enumeration for the color
  /*!
    These value are used to define the color
    of a node.
  */
  typedef enum {yellow, cyan, green, red} color;
  
  //---- Members
  
  //! Add a node to the graph
  /*!
    \param id the identifier
    \param name the name
    \param c the color
    
    Pre : no node in nodeL must have the same id     
    
    Post: the node is added in nodeL, and numNodes is 
    incremented
    
    notPre : THROW exeception
  */
  void addNode(int id, char *name, int c)
    throw (bad_data);
  
  //! Add an edge to the graph
  /*!
    \param from the from node
    \param to the to node
    \prama label the label of the edge
    
    
    The edge is added in edgeMM.
    If the edge exisist it isn't added !
  */
  void addEdge(int from, int to, char *label);
  
  //---- HAS ... ?
  
  //! Ask if there is a node with the id specified
  /*!
    \param id the id of the node
    
    \return True if the node exisist,
    false otherwise.
  */
  bool hasNode(int id);
  
  //---- Browse the nodes
  // SEQUENTIAL access to the  nodes
  
  //! The first node if it exist
  /*!
    \return A pointer to the fisrt node
  */
  node *firstNode (void)
    throw (bad_data);
  
  //! The next node if it exist 
  /*!
    \return A pointer to the ndext node (after the last got)
  */
  node *nextNode(void)
    throw (bad_data);

  //! Ask if the node has some nodes
  /*!
    \return True if the graph have some node,
    false otherwise
  */
  bool hasNodes(void);

  //! Ask if there is next node
  /*!
    \return True, if the graph have a next node (after the last got),
    false otherwise
  */
  bool hasNextNode(void);
  
  //---- Dump
  
  //! Dump a dot file of the graph 
  /*!
    \param fileName the name of the file
    \param shape how we draw the node
  */
  void dumpDotFile(const char *fileName, const char *shape);
  
};

// ---------------------------------------------------------------------------
//  CLASS cfgGraphData
// ---------------------------------------------------------------------------

//! This class represent a cfg graph
/*!
  A cfg graph defers from a norma graphData because :
  - a cfg graph is associated to a specific function 
  - a cfg graph can be dumped using an additional formalism 
*/
class cfgGraphData : public graphData
{
 private:
  
  //! The name of the function
  string       fnctName;

 public:
  //! Constructor
  cfgGraphData() { }
  
  //! Destructor
  ~cfgGraphData() { }

  //! Set the name of the function
  /*!
    \param fnctName The name of the function
  */
  void setFnctName(string fnctName) 
    { this->fnctName = fnctName; }

  //! Get the name of the function
  /*!
    \return The name of the function
  */
  string getFnctName(void)
    { return this->fnctName; }
  
  //! Dump a cfg file of the graph 
  /*!
    \param fileName the name of the file

    \note This function is used only if the graph is a CFG
  */
  void dumpCfgFile(const char *fileName);

};

// ---------------------------------------------------------------------------
//  CLASS callGraphData
// ---------------------------------------------------------------------------

//! This class represent a call graph
/*! 
  the attributes that we add are :
  - the name of the function associated to the call graph
  - the number of calls of each node
*/
class callGraphData : public graphData
{
 private:
  
  //! the name of the function
  string              fnctName;

  //! Map of the calls
  /*!
    The key is the id of a node, the value the number of calls
  */
  map<int, int>       calls;

 public:
  //! Constructor
  callGraphData() { }
  
  //! Destructor
  ~callGraphData();

  //---- Members

  //! Set the name of the function
  /*!
    \param fnctName The name of the function
  */
  void setFnctName(string fnctName) 
    { this->fnctName = fnctName; }

  //! Get the name of the function
  /*!
    \return The name of the function
  */
  string getFnctName(void)
    { return this->fnctName; }

  //! Add a call to a function
  /*!
    If the id isn't in the map "calls" then calls[id],
    else increment calls[id].
    
    \param id The identifier of the node
  */
  void addCall(int id);

  //! Get the number of calls
  /*!
    If the id isn't in map calls then return 0,
    else return the value calls[id].

    \param id The identifier of the node

    \return calls[id]
  */
  int getCalls(int id);


};

#endif


