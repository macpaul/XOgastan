/***************************************************************************
                          controlMachine.cpp  -  description
                             -------------------
    begin                : Aug 2 2001
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
// INCLUDES
// ---------------------------------------------------------------------------
#include "factory/controlMachine.h"

// ---------------------------------------------------------------------------
//  CONSTRUCTOR and MEMBERS
// ---------------------------------------------------------------------------

//*** Constructor
controlMachine::controlMachine ()
{

  // initialize the state transiction table
  //
#define  DEFinputSM(INPUT, CODE, ATTRS)
#define  DEFstateSM(STATE)
#define  DEFoutputSM(OUTPUT)

#define  DEFtranSM(CURRENT_STATE, CURRENT_INPUT, NEXT_STATE, NEW_OUTPUT)  state_trans_table[CURRENT_STATE][CURRENT_INPUT] = NEXT_STATE;

#include "factory/state_machine.def"

#undef  DEFstateSM
#undef  DEFoutputSM
#undef  DEFtranSM
#undef  DEFinputCODE


  // initialize the output transiction table
  //
#define  DEFinputSM(INPUT, CODE, ATTRS)
#define  DEFstateSM(STATE)
#define  DEFoutputSM(OUTPUT)

#define  DEFtranSM(CURRENT_STATE, CURRENT_INPUT, NEXT_STATE, NEW_OUTPUT)  output_trans_table[CURRENT_STATE][CURRENT_INPUT] = NEW_OUTPUT;

#include "factory/state_machine.def"

#undef  DEFstateSM
#undef  DEFoutputSM
#undef  DEFtranSM
#undef  DEFinputCODE

}


//*** Members

state 
controlMachine::nextState (input_signal i) {
  return (current_state = state_trans_table[current_state][i]);
}



output_signal 
controlMachine::nextOutput (input_signal i) {
  return (last_output = output_trans_table[current_state][i]);
}

void
controlMachine::setState (state s) {
  current_state = s;
}

state controlMachine::getState (void) {
  return current_state;
}

// ---------------------------------------------------------------------------
// FRIEND functions
// ---------------------------------------------------------------------------

bool
isInGraphSubset (controlMachine sm)
{
  // return :
  //
  // true if current state is one of state::GRAPH_subset
  // false otherwhise 
  //
  // see the file state_machine.def

  switch (sm.current_state)
    {

    case start_gxl:
    case in_graph:
    case end_gxl:
      return true;
    default:
      return false;
    }
}




bool
isInNodeSubset (controlMachine sm)
{
  // return :
  //
  // true if current state is one of state::NODE_subset
  // false otherwhise 
  //
  // see the file state_machine.def

  switch (sm.current_state)
    {
    case in_node_no_typed:
    case in_type_node:
    case in_node_typed:
    case in_attr:
    case start_int:
    case end_int:
    case start_string:
    case end_string:
      return true;
    default:
      return false;
    }
}


bool
isInEdgeSubset (controlMachine sm)
{
  // return :
  //
  // true if current state is one of state::EDGE_subset
  // false otherwhise 
  //
  // see the file state_machine.def

  switch (sm.current_state)
    {

    case in_edge_no_typed:
    case in_type_edge:
    case in_node_typed:
      return true;
    default:
      return false;
    }

}


// ---------------------------------------------------------------------------
// Others useful functions
// ---------------------------------------------------------------------------

bool
isErrorOutputSignal (output_signal os)
{
  // return :
  //  
  //  true if it is an SIGNAL_ERROR_*
  //  false otherwhise

  switch (os)
    {

    case SIGNAL_ERROR_gxl:
    case SIGNAL_ERROR_graph:
    case SIGNAL_ERROR_node:
    case SIGNAL_ERROR_attr:
    case SIGNAL_ERROR_int:
    case SIGNAL_ERROR_string:
    case SIGNAL_ERROR_type_node:
    case SIGNAL_ERROR_type_edge:
    case SIGNAL_ERROR_edge:
      return true;
    defualt:
      return false;
    }

}




