/***************************************************************************
                          nast_node.cpp  -  description
                             -------------------
    begin                : July 15 2001
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
#include "nast/nast_node.h"


// ---------------------------------------------------------------------------
//  MEMBER
// ---------------------------------------------------------------------------

void
nast_node::setCode (nast_code c) 
{
  code = c;
}

nast_code
nast_node::getCode (void) 
{
  return code;
}

long
nast_node::getId (void) 
{
  return id;
}


void
nast_node::setId (long idnt) 
{
  id = idnt;
}


// EDGES manipulation





nast_node *
nast_node::firstEdge(void) throw (bad_edge) {
  // the first edges if it exist or THROW

  // is the map empty ?
  if ( edges.size() ) {
    p_pos = 1;
    p_edges = edges.begin();
    
    return p_edges->second;
  } 
  else 
    throw bad_edge("Nast_node::firstEdge",
		   "The first edge doesn't exsist");

}


    
nast_node *
nast_node::nextEdge(void) throw (bad_edge) {
  // the next edges if it exist or THROW

  // is there a next edge ?
  if ( nast_node::hasNextEdge() ) {

    p_pos++;
    p_edges++;
    return p_edges->second;

  } 
  else 
    throw bad_edge("Nast_node::nextEdge",
		   "The next edge doesn't exsist");

}



edge_code 
nast_node::currentEdgeCode(void) throw (bad_edge) {

  // have we pointed a legal element in the map ?
  if (p_pos <= edges.size())
    return p_edges->first;
  else
    throw bad_edge("Nast_node::currentEdgeCode",
		   "Impossibile to get current edge code");

}


bool
nast_node::hasEdges(void) {
  return (edges.size() > 0);
}



bool
nast_node::hasNextEdge(void) {
  unsigned int num_edges;

  return ( ((num_edges = edges.size()) > 0) 
	   && (p_pos < num_edges));
}


nast_node *
nast_node::edgeName(edge_code ec) throw (bad_edge) {
  // return the edge with the code ec or THROW
  
  map<edge_code, nast_node *>::iterator search_p;

  // is the map empty ?
  if (edges.size()) {
  
    // if we have an element with key ec return it also THROW
    if ( (search_p = edges.find(ec)) != edges.end() )       
      return search_p->second;
    else 
      throw bad_edge("Nast_node::edgeName",
		     "It doesn't exisist the specified edge name");
  
  }
  else throw bad_edge("Nast_node::edgeName",
		      "The map is empty");

}    

bool
nast_node::hasEdgeName(edge_code ec) {

  // is the map empty ?
  if (edges.size()) {
    // if we have an element with key ec return true
    if ( edges.find(ec) != edges.end() )       
      return true;
    else 
      return false;
  }
  return false;
}    


void 
nast_node::addEdge(edge_code ec, nast_node *nnp) throw (bad_edge) {

  // if we have an element with key ec THROW
  if ( edges.find(ec) != edges.end() ) {
    throw bad_edge("Nast_node:addEdge",
		   "Impossibile to add the edge : duplicate edge");
  }
  else 
    edges[ec] = nnp;
  
}    


void 
nast_node::delEdge(edge_code ec) throw (bad_edge) {
  map<edge_code, nast_node *>::iterator search_p;

  // is the map empty ?
  if (edges.size()) {
  
    // if we have an element with key ec remove it also THROW
    if ( (search_p = edges.find(ec)) != edges.end() )
      edges.erase(search_p);

    else 
      throw bad_edge("Nast_node::delEdge",
		     "Impossibile to delete the specified edge name");
  
  }
  else 
    throw bad_edge("Nast_node::delEdge",
		   "impossibile to delete the specified edge name, no edges");

}


int 
nast_node::edgesNum (void) {
  // NUMBER of edges
  return edges.size();
}


void
nast_node::accept (visitor &) 
{ 
  return;
}

// ---------------------------------------------------------------------------
//  MEMBER nast_node_Cmp
// ---------------------------------------------------------------------------

bool nast_node_Cmp::operator()(nast_node& nn1, 
			       nast_node& nn2) {
  return (nn1.getId() < nn2.getId());
}

bool nast_node_Cmp::operator()(nast_node* nn1, 
			       nast_node* nn2) {
  return (nn1->getId() < nn2->getId());
}





