/***************************************************************************
			   graphData.cpp  -  description
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
#include "data/graphData.h"

// ---------------------------------------------------------------------------
//  Members of graphData
// ---------------------------------------------------------------------------

//---- Destructor

graphData::~graphData() {
  //
  // 1. delete the list of nodes
  // 2. delet the outEdge * in the map

  list <node *>::iterator                p;      // browse the list of nodes
  node                                   *n;     // a node
  multimap<int, outEdge *>::iterator     pmm;    // browse the multimap of edge
  outEdge                                *oe;    // an output edge


  // delete the edges multimap
  for (p = nodesL.begin(); p != nodesL.end(); p++) {
    typedef multimap<int, outEdge *>::iterator MI;
    pair<MI,MI>         p2;      // lower and upper limits

    n = *p;
    p2 = edgesMM.equal_range(n->id);
    for (MI q = p2.first; q != p2.second; ++q) {
      outEdge      *oe = q->second;
      delete oe;
     }
  }
  edgesMM.clear();

  // Delete node list
  for (p = nodesL.begin(); p != nodesL.end(); p++) {
    n = *p;
    delete n;
  }
  nodesL.clear();

  
}

//---- Members
void 
graphData::addNode(int id, char *name, int c)
  throw (bad_data) 
{
  node                          *n;     // a new node

  // Checks the precondition
  if (graphData::hasNode(id)) 
    throw bad_data("graphData::addNode",
		   "Duplicate node ! Impossibile add the node " +
		   a2b::long2string(id));
  else {
    n = new node;
    n->id = id;
    n->name = name;
    n->c = c;
    nodesL.push_back(n);
    nodesNum++;
  }

  return;
}
  

void 
graphData::addEdge(int from, int to, char *label)
{
  typedef multimap<int, outEdge *>::iterator MI;
  pair<MI,MI>                   p;      // lower and upper limits
  bool                          found;  // verify the precondition
  outEdge                       *oe;    // a new out edge link
  string                        labelP; // string value of the parameter label
  string                        labelE; // string value of the current edge 
                                        // label browsed

  labelP = label;
  p = edgesMM.equal_range(from);
  found = false;
  for (MI g = p.first; (!found) && (g != p.second); ++g) {
    labelE = (g->second)->label;
    found = ((g->second)->to == to) && (labelP == labelE); 
  }

  if (!found) {
    oe = new outEdge;
    oe->to = to;
    oe->label = label;
    edgesMM.insert( make_pair(from, oe) );
  }

  return;
}


string 
graphData::getNodeName(int id) 
  throw (bad_data)
{
  string                        name;   // the name of the node
  list <node *>::iterator       p;      // browse the list
  node                          *n;     // a node
  bool                          build;  // flag for building the name

  build = false;
  for (p = nodesL.begin();(p != nodesL.end()) && (!build); p++) {
    n = *p;
    if ( build = (n->id == id) ) 
      name = n->name; 
  }
 
  if (!build) 
    throw bad_data("graphData::getNodeName",
		   "Can't build the name of a node.");
  
  return name;
}


void 
graphData::dumpDotFile(const char *fileName, const char *shape) {
  ofstream                      fout;   // the ouput file
  list <node *>::iterator       p;      // browse the list
  node                          *n;     // a node

  fout.open(fileName);
  
  fout << "digraph G {\n\n\tnode "
       << "[style=filled, shape=" << shape << ", heigth=.3]\n\n";

  //write the nodes 
  for (p = nodesL.begin(); p != nodesL.end(); p++) {
    n = *p;

    fout << "\t" << n->name << "_" << n->id
	 << "[color=";
    switch (n->c) {
    case yellow: fout << "yellow"; break;
    case cyan: fout << "cyan"; break;
    case green: fout << "green"; break;
    case red: fout << "red"; break;
    default: fout << "yellow"; break;
    }     
    fout << "]\n";

  }
  fout << "\n\n";


  // write the edges 
  for (p = nodesL.begin(); p != nodesL.end(); p++) {
    typedef multimap<int, outEdge *>::iterator MI;
    pair<MI,MI>         p2;      // lower and upper limits

    n = *p;
    p2 = edgesMM.equal_range(n->id);
    for (MI q = p2.first; q != p2.second; ++q) {
      outEdge      *oe = q->second;
      
      fout << "\t" << n->name << "_" << n->id 
	   << "->" << getNodeName(oe->to)  << "_" << oe->to
	   << "[label=\"" << oe->label << "\"]\n";
    }
  }
  fout << "\n\n}";

  fout.close();

  return;
}

bool 
graphData::hasNode(int id) {
  list <node *>::iterator       p;      // browse the list
  bool                          found;  // verify the precondition

  // Checks the precondition
  for (p = nodesL.begin(), found = false;
       (!found) && (p != nodesL.end());
       p++) 
    found = ( (*p)->id == id );

  return found;
}


node *
graphData::firstNode (void) 
  throw (bad_data)
{

  // is the list empty ?
  if ( nodesL.size() ) {
    pNodesL_pos = 1;
    pNodesL = nodesL.begin();
    
    return *pNodesL;
  } 
  else 
    throw bad_data("graphData::firstNode",
		   "The first node don't exsist");
}



node *
graphData::nextNode(void) 
  throw (bad_data)
{
  // is there a next node ?
  if ( graphData::hasNextNode() ) {

    pNodesL_pos++;
    pNodesL++;
    return *pNodesL;

  } 
  else 
    throw bad_data("graphData::nextNode",
		   "The next node doesn't exsist");
}


bool 
graphData::hasNodes(void) {
  return (nodesL.size() > 0);
}


bool 
graphData::hasNextNode(void) {
  int num_nodes;

  return ( ((num_nodes = nodesL.size()) > 0) 
	   && (pNodesL_pos < num_nodes));
}


// ---------------------------------------------------------------------------
//  Members of cfgGraphData
// ---------------------------------------------------------------------------

void 
cfgGraphData::dumpCfgFile(const char *fileName) {
  typedef multimap<int, outEdge *>::iterator MI;
  ofstream                      fout;   // the ouput file
  pair<MI,MI>                   pMM;    // lower and upper limits
  outEdge                       *oe;    // a new out edge link
  list <node *>::iterator       pL;     // browse the list
  node                          *n;     // a node
  int                           i;      // counter  

  fout.open(fileName);

  fout << "new-procedure\n"
       << "name " << "\n"
       << "start-node 1\n" 
       << "end-node " << nodesNum << "\n"
       << "start-prologue " << fnctName << "\n"
       << "end-prologue\n\n"
       << "local-var\n"
       << "end-local\n\n"
       << "new-node\n" 
       << "type ENTRY\n"
       << "id 1\n"
       << "end-node\n\n";

  //write the nodes 
  for (pL = nodesL.begin(); pL != nodesL.end(); pL++) {
    n = *pL;

    fout << "new-node\n"
	 << "node-id " << n->id << "\n";
    if (n->name == "goto") {
      pMM = edgesMM.equal_range(i);
      MI q = pMM.first; 
      oe = q->second;
      fout << "jump-to " << oe->to << "\n";
    }
    fout << "type " << n->name << "_" << n->id << "\n"
	 << "end-node\n\n";
  }
  

  
  fout << "start-edges\n"
       << "1,2" << "\n";

  // write the edges 
  for (i = 2; i <= nodesNum; i++) {
    
    pMM = edgesMM.equal_range(i);
   
    if (pMM.first != pMM.second) 
      fout << i;
    
    for (MI q = pMM.first; q != pMM.second; ++q) {
      oe = q->second;
      fout << "," << oe->to;
    }
    
    if (pMM.first != pMM.second) 
      fout << "\n";
  
  }
      
  fout << "end-edges\n\n"
       << "end-procedure";
  
  return;
}


// ---------------------------------------------------------------------------
//  Members of callGraphData
// ---------------------------------------------------------------------------

//---- Destructor 

callGraphData::~callGraphData() 
{
  // 
  // The call graph is used by the visitor visit_fcntCallGraph
  // The name of the node are built using the static method
  // a2b::cpp_string2c_string(string s). 
  // This method create a char * with a new call.
  // Now we must delete the memory of the name by calling a delete !
  
  list <node *>::iterator       p;      // browse the list
  node                          *n;     // a node

  // Browse the node list one node for time and delete the name
  for (p = nodesL.begin(); p != nodesL.end(); p++) {
    n = *p;
    delete n->name;
  }
  
}

//---- Member

void 
callGraphData::addCall(int id) {
  // By default map[key] == 0 if the key don't exisist
  calls[id]++;
  return;
}
    
  
int 
callGraphData::getCalls(int id) {
  // By default map[key] == 0 if the key don't exisist
  return calls[id];
}



