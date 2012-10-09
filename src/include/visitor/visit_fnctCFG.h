/***************************************************************************
			   visit_fnctCFG.cpp  -  description
			      -------------------
     begin                : AUG 28 2001
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

#ifndef _VISIT_FNCT_CFG_H
#define _VISIT_FNCT_CFG_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "nast/nast_node.h"
#include "nast/type_n.h"
#include "nast/decl_n.h"
#include "nast/stmt_n.h"
#include "nast/expr_n.h"
#include "nast/othr_n.h"
#include "nast/cst_n.h"

#include "data/graphData.h"

#include "visitor/visitor.h"

#include "error/bad_nast.h"

#include <map>
#include <list>
#include <stack>
#include <string>

// ---------------------------------------------------------------------------
//  CLASS
// ---------------------------------------------------------------------------

//! This visitor builds a ControlFlowGraph of the function's body
/*!
  <b>Purpose</b> :<br>
  Build the control flow graph of the body of the function.

  <b>Rules</b> :<br>
  From the entry point of the body of a function_decl
  it visit the statements in the body.<br>
  When a stmt_n node is reached we insert int into the ControlFlowGraph.
  After we insert the edges to the children nodes and we visit them.<br>

  <b>Action</b> :<br> 
  see visit_fnctCFG.cpp

  <b>dataObj</b> used :<br>
  cfgGraphData 
  
  The caller of this visitor must use it to visit
  the body of function. So, the caller browse the 
  declarations into the global namespace, one node for time, 
  and for each function_decl_n it visit the body.
  The protocol must be like :

  \code
  visit_fnctCFG    v;
  nast_node            *node;
  nast_node            *body;
  cfgGraphData         g;
  
  if (node is a function_decl_n) {
    v.setCallGraphData(&g);
    body = get the body of node;
    v.init();
    body->accept(v);
    v.finish();
  }
  \endcode

*/
class visit_fnctCFG : public visitor 
{

 private:
  
  //! The graph with the CFG
  cfgGraphData                            *graph;

  //---- Maps for the indexes
  
  //! The map of the number assigned to the node
  /*!
    When we visit the function's body each statement 
    take a number (index).

    Key  : the nast_node *
    Value: the number assigned to the nast_node *
  */
  map<nast_node *, long> indexMap;

  //! The map of the nast_node assigned to the number
  /*!
    Map an index into a nat_node *.

    Key  : the number
    Value: the nast_node * assigned to the number
  */
  map<long, nast_node *> nodesMap;

  //! The last index assigned to a node
  long lastIndex;


  //--- Multimap for the edges 

  //! The to point of an edge
  typedef struct {
    //! The nast_node * of the destination
    nast_node *to;
    //! The label assigned to the edge
    char      *label;
  } toPoint;
  
  //! The multimap of the edges
  /*!    
    This multimap holds the egdes of the CFG.
    An edge is composed by couple of nast_node *.
    The first nast_node * is the from node,
    the second nast_node * is the to node.

    Key  : the nast_node * FROM (init point of the edge)
    Value: the toPoint * TO (end point of the edge)
  */
  multimap<nast_node *,toPoint *> edges;

  //---- Maps of the next stmt edges

  //! The map of the next nodes
  /*! 
    In this map is hold the next node 
    of each node (only for cycle or condition node).
    
    Key  : the nast_node * A
    Value: the next nast_node * of A (NEXT_STMT_EDGE)
  */
  map<nast_node *, nast_node *> nextNodeMap;

  //---- Stacks for various uses

  //! The stack of cycle nodes or switch node for the break_stmt
  /*!
    Can contain :

    breakStack <- do  for  while  switch  loop_expr

    This stack hold the last cycle node (for, do , while, loop_expr)
    or switch visited.
    
    It is use by the break_stmt to hold the exitPoint of
    the break.

    Take the code :

    \code
    for1 (...)
      for2 (...)
         for3 (...) {
	     if (somethingHappens)
	        break
	     else {...}
	 }
    \endcode

    The stack contains : [for1, for2, for3 <-top.  <br>
    We know that the exit point of the break is the nast_node * after for3.
  */
  stack<nast_node *>                      breakStack;

  //! This stack  of cycle nodes for the continue_stmt
  /*!
    Can contain :

    continueStack <- do  for  while loop_expr

    This stack hold the last cycle node (for, do , 
    while, loop_expr) visited.

    The management is similar to the breackStack, but it is
    used by the continue_stmt to old the reiterPoint.

    Take the code :

    \code
    for1 (...)
      for2 (...)
         for3 (...) {
	     if (somethingHappens)
	        break
	     else {...}
	 }
    \endcode

    The stack contains : [for1, for2, for3 <-top.  <br>
    We know that the reiterPoint of the continue is the nast_node * for3.
  */
  stack<nast_node *> continueStack;

  //! The stack of the latest switch
  /*!
    Can contain :
    
    lastSwitch <- switch
    
    It is use to build the edges from the switch to the
    different case_label into the switch.
  */
  stack<nast_node *> lastSwitch;

  //! The stack of last cycle or condition node
  /*!
    Can contain :
    
    lastCycleCond <- do  while  for  loop_expr if  switch

    We use this stack when the body of an if or
    a while, ... finish. In this case :
    - If the last node is an if or a switch (and
    if the chain that we are exploring finish) then
    the nextNode is into nextNodeStack.
    - If the last node is a do, a while, a for or a
    loop_expr (and
    if the chain that we are exploring finish) then
    the reiterPoint is the nast_node * at the top.
  */
  stack<nast_node *> lastCycleCond;


  //---- Structure for the goto_stmt management

  //! The destination of each goto
  /*! 
    The goto_stmt are very hard to manage. We use the follow
    algorithm :
    - When we reach a goto_stmt G we insert in this list the pair
    <destinationOfG, G> (remember : the destination of a goto_stmt
    isn't an stmt_n but a label_decl node).
    - When the the metho finish() is called then we browse the 
    pairs of this list one element for time. For each pair
    we use the map labelFound to build the edge from the goto_stmt
    to the currespondent label_stmt (the label_stmt points to a
    label_decl). 

    The pair of the list are like :
    
    First    : destinationOfGotoStmt (the nast_node *)
    Second   : goto_stmt (the nast_node *)
  */
  list< pair<nast_node*, nast_node*> >  pendingGoto;

  //! Map of label_decl, label_stmt
  /*! 
    In this map we hold all the label_decl and their
    currespodent label_stmt found during the visit.
    It is used to build the nodes from the goto_stmt
    to the label_stmt.

    Key  : label_decl
    Value: label_stmt currespondent to the label_decl
  */
  map<nast_node *, nast_node *>  labelFound;

  //---- Structure for the do_stmt management

  //! Map for the stmt before a do
  /*!
    Take the code :
    
    \code
    while (i < 0)
      i++;
    do {
      i--;
    } while (i > 0);
    \endcode

    If the doNode is the nast_node * to the do_stmt, and
    if whileNode is the nast_node * to the while_stm then :
    
    nodeBeforeDo[doNode] == whileDo;

    Key   : nast_node * to a do_stmt
    Value : nast_node * to the last stmt before the do_stmt
  */
  map<nast_node *, nast_node *> nodeBeforeDo;


  //! Map for the edge's label from last node before do_stm to first node in body
  /*!
    Take the code :
    
    \code
    while (i < 0)
      i++;
    do {
      i--;
    } while (i > 0);
    \endcode

    If the doNode is the nast_node * to the do_stmt, and
    if exprNode is the nast_node * to the i-- then :
    
    firstStmtInDo[doNode] == exprNode;

    Key   : nast_node * to a do_stmt
    Value : nast_node * to the first stmt into the do_stmt body
  */
  map<nast_node *, nast_node *> firstStmtInDo;


  //! Map for the edge's label from last node before do_stm to first node in body
  /*!
    Take the code :
    
    \code
    while (i < 0)
      i++;
    do {
      i--;
    } while (i > 0);
    \endcode

    If the doNode is the nast_node * to the do_stmt, and
    if whileNode is the nast_node * to the while_stm,
    and if exprNode is the nast_node * to the i-- then :
    
    labelBeforeDo[doNode] == "F";

    The do_stmt is on the FALSE branch of the while_stmt.
    This label marks the edge from whileNode to exprNode

    Key   : nast_node * to a do_stmt
    Value : the label of the edge between nodeBeforeDo[do] and firstStmtInDo[do]
  */
  map<nast_node *, char *> labelBeforeDo;

  //! Use to hold a chian of nested do_stmt
  /*!
    Take the code :

    \code
    do {
      do {
        do {
	   k--;
	   i--;
	   j++;
        } while (i > 0);
      } while (j < 0);
    } while (k > 0 ) ;
    \endcode

    If doNode1 is the nast_node * to the first do_stmy, and
    if doNode2 is the nast_node * to the second do_stmy (nested in doNode1), and
    if doNode3 is the nast_node * to the third do_stmy (nested in doNode2)
    then :
    - upperNestedDop[doNode3] == doNode2
    - upperNestedDop[doNode2] == doNode1
    - upperNestedDop[doNode1] == 0

    Key   : nast_node * to a do_stmt
    Value : nast_node * to the upper nested do_stmt
  */
  map<nast_node *, nast_node *> upperNestedDo;

  //---- Members

  //! Check if the current node is before a do_stmt
  /*!
    \param np the current nast_node *
    \param label the label of the edge that begin from np
    
    \return True if np came before a do_stmt.
    If the return value is true than this method 
    set also :
    - labelBeforeDo[doNode] = label;
    - nodeBeforeDo[doNode] = np;

    Take the code :
    
    \code
    while (i < 0)
      i++;
    do {
      i--;
    } while (i > 0);
    \endcode

    then :
    - labelBeforeDo[doNode] = "F";
    - nodeBeforeDo[doNode] = whileNode;
  */
  bool weAreBeforeDo(nast_node *np, char *label);

  //! Explore all the chained stmt from the current node
  /*!
    \param np the current nast_node *

    The node in the chain are linked by the edge NEXT_STMT_EDGE.
    For each node in the chain it set its successor in the 
    nastNodeMap.

    Take the code :
    
    \code
    i++;
    if (i)
      i--;
    while (i) i++;
    function(i);
    \endcode

    then :
    - it explore the chain exprNode1 (i++), ifNode (if), 
    whileNode (while), exprNode2 (function(i)).
    - set the nextNodeMap :
      -# nextNodeMap[exprNode1] = ifNode
      -# nextNodeMap[ifNode] = whileNode
      -# nextNodeMap[whileNode] = exprNode2
      -# nextNodeMap[expr2Node] = 0
  */
  void exploreChain(nast_node *np);


  //! Jump one or many sequential scope_stmt
  /*!
    \param np the start node for the jumping
    
    \return If there is a node different from the scope_stmt at the 
    end of the chain then return its nast_node *, else return 0.
  */
  nast_node *canJumpScopeStmt(nast_node *np);

  //! Return the next exit point in the map nextNodeMap
  /*!
    If the lastCycleCond.top() is a while, do, or for the exit point
    is the top.
    Else e rool back the stack lastCycleCond to the first not NULL node.
    If the exit point don't exsist we use the next_stm of the
    current node (also if it is a scope_stmt)

    Pre : !lastCycleCond.empty()
  */
  nast_node *nextExitPoint(nast_node *np);
  
  //! Add an edge to list of edges
  /*!
    \param  from the nast_node FROM (init point)
    \param  to   the nast_node TO (end point)
    \param  label the label of the edge
  */
  void addEdge(nast_node *from, nast_node *to, char *label);

  //! Make the pending edge from the current node
  /*!
    In accord to the definifition of the lastCycleCond
    this function make the edge from the current node
    to the exit point of a condition node, or the
    reiter point of a cycle node.

    Pre : !lastCycleCond.empty()
    
    \param node  the current node
  */
  void makePendingFromCurrentNode(nast_node *np);


  //! Assign an index to a node
  /*!
    If the node hasn't an index then a 
    new number is assigned.
    The new index is placed into the maps 
    indexMap[] and nodesMap[].

    \param node the nast_node * that ask for the index
  */
  void takeIndex(nast_node *np);

 public:
  //! Constructor
  visit_fnctCFG() { }
  
  //! Destructor
  ~visit_fnctCFG() { }

  
  //---- Members
  
  void setCfgGraphData(cfgGraphData *graph) 
    { this->graph = graph; }

  // visit statements
  virtual void visit_break_stmt(break_stmt_n *);
  virtual void visit_continue_stmt(continue_stmt_n *);
  virtual void visit_scope_stmt(scope_stmt_n *);
  virtual void visit_decl_stmt(decl_stmt_n *);
  virtual void visit_expr_stmt(expr_stmt_n *);
  virtual void visit_goto_stmt(goto_stmt_n *);
  virtual void visit_label_stmt(label_stmt_n *);
  virtual void visit_return_stmt(return_stmt_n *);
  virtual void visit_if_stmt(if_stmt_n *);
  virtual void visit_switch_stmt(switch_stmt_n *);
  virtual void visit_for_stmt(for_stmt_n *);
  virtual void visit_while_stmt(while_stmt_n *);
  virtual void visit_do_stmt(do_stmt_n *);
  virtual void visit_compound_stmt(compound_stmt_n *);
  virtual void visit_asm_stmt(asm_stmt_n *);
  virtual void visit_othr_stmt(othr_stmt_n *);

  // visit other nodes
  virtual void visit_case_label(case_label_n *);

  // visit expressions
  virtual void visit_othr_expr(othr_expr_n *);

  //! The initialization operation
  /*!    
    Dump the head of the dot file
  */
  void init(void);

  //! The finalization operation
  /*!    
    Dump the list of the dot edges on
    the output stream.
  */
  void finish(void);
		
};

#endif
