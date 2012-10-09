/***************************************************************************
                          controlMachine.h  -  description
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

/*!
  \file In this file are defined the enumeration values of the input signal, 
  output signal, and of the state.
  Moreover, in this file is defined the class controlMachine. This
  class implement the state machine used during the parsing 
  process of a gxl document.

  \sa state_machine.def
*/

#ifndef _CONTROL_MACHINE_H
#define _CONTROL_MACHINE_H

// ---------------------------------------------------------------------------
// INCLUDES
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// ENUMERATIONS
// ---------------------------------------------------------------------------

//-------------------------
// Define input signals 
//-------------------------

#define  DEFinputSM(INPUT, CODE, ATTRS) 	INPUT,

#define  DEFstateSM(STATE)
#define  DEFoutputSM(OUTPUT)
#define  DEFtranSM(CURRENT_STATE, CURRENT_INPUT, NEXT_STATE, NEW_OUTPUT)


//! Enumeration of the input signal of the state_machine
/*!
  This enumeration is the list of the inputs signals
  that the state machine can recognize.
  
  FIRST_INPUT_SIGNAL and LAST_INPUT_SIGNAL are not used by the
  state machine.

  The value of FIRST_INPUT_SIGNAL is -1 because all the input
  signal are used to index the transiction tables (a C++
  bidimensional array), and so its following value must
  begin from 0.
*/
typedef enum {
	FIRST_INPUT_SIGNAL = -1,
#include "factory/state_machine.def"
	LAST_INPUT_SIGNAL
} input_signal;

#undef  DEFstateSM
#undef  DEFoutputSM
#undef  DEFtranSM

#undef DEFinputCODE


//-------------------------
// Define states 
//-------------------------

#define  DEFinputSM(INPUT, CODE, ATTRS) 	

#define  DEFstateSM(STATE)     STATE,

#define  DEFoutputSM(OUTPUT)
#define  DEFtranSM(CURRENT_STATE, CURRENT_INPUT, NEXT_STATE, NEW_OUTPUT)


//! Enumeration of the the states of the state_machine
/*!
  This enumeration is the list of the states
  that the state machine can assume.
  
  FIRST_STATE and LAST_STATE are not used by the
  state machine.

  The value of FIRST_STATE is -1 because all the states
  are used to index the transiction tables (a C++
  bidimensional array), and so its following value must
  begin from 0.
*/
typedef enum {
	FIRST_STATE = -1,
#include "factory/state_machine.def"
	LAST_STATE
} state;

#undef  DEFstateSM

#undef  DEFoutputSM
#undef  DEFtranSM
#undef DEFinputCODE


//-------------------------
// Define outputs
//-------------------------

#define  DEFinputSM(INPUT, CODE, ATTRS) 	
#define  DEFstateSM(STATE)     

#define  DEFoutputSM(OUTPUT)    OUTPUT,

#define  DEFtranSM(CURRENT_STATE, CURRENT_INPUT, NEXT_STATE, NEW_OUTPUT)

//! Enumeration of the output signal of the  state_machine
/*!
  This enumeration is the list of the output signals
  that the state machine can produce.
  
  FIRST_OUTPUT_SIGNAL and LAST_OUTPUT_SIGNAL are not used by the
  state machine.

  The value of FIRST_OUTPUT_SIGNAL is -1 for convenction, but
  it shall assume anything value.
*/
typedef enum {
	FIRST_OUTPUT_SIGNAL = -1,
#include "factory/state_machine.def"
	LAST_OUTPUT_SIGNAL
} output_signal;

#undef  DEFstateSM

#undef  DEFoutputSM

#undef  DEFtranSM
#undef DEFinputCODE


// ---------------------------------------------------------------------------
// CLASSES
// ---------------------------------------------------------------------------

//! This class help the operativeMachine to build NAST
/*!  
  This class implement a state machine. Remember : the state 
  machine known what are we building ! So we can tell :
  
  <b>"the controlMachine is the mind, and the 
  operativeMachine is the hand !!"</b>
  
  This class contains 2 big matrix : one is for state transictions, 
  the other one is for output transictions.
  
  The members of this class allows the evolution 
  of the  state machine.

  In the documentaion of this class we use the symbols :

  - I for the set of the input signals
  - S for the set of the states
  - O for the set of the output signals

  \sa state_machine.def
*/
class controlMachine {

private:

  //*** Attributes

  //! The state transiction table
  /*!
    It is used to implement the state transiction  :

    state_transiction : S x I -> S
    
    The current_state (s) and the current_input (i) are used 
    to index this matrix. The element matrix[s][i] holds
    the next_state.
    
    The dimension is : (28 states) X (15 input_signals)
  */
  state state_trans_table[28][15];
  
  //! The output transiction table
  /*!   
    It is used to implement the generation of the next output
    signal :

    output_generetaion: S x I -> O
    
    The current_state (s) and the current_input (i) are used 
    to index this matrix. The element matrix[s][i] holds
    the new_output.
    
    The dimension is : (28 states) X (15 input_signals)
  */
  output_signal output_trans_table[28][15];
  
  
  //! The current state of the state machine
  state current_state;
 
 //! The last output produced 
  output_signal last_output;
  
 public:
  //! Constructor
  controlMachine();

  //! Destructor
  ~controlMachine() { }

  //*** Members

  //! Set the next state using the state_trans_table
  /*!
    Write in curren_state the next state.

    \param i the input signal
    \return The new state of the state machine.
  */
  state nextState(input_signal i);


  //! Set the new output signal using the output_trans_table
  /*!
    Write in last_output the next output.

    \param i the input signal
    \return The output generated by the state machine.
  */
  output_signal nextOutput(input_signal i);
  
  //! Set the state
  /*!
    \param s the state that must be set
  */
  void setState(state s);

  //! Get the current state
  /*!    
    \return The current state of the state machine
  */
  state getState(void);

  //! Ask if the state machine is in GRAPH_subset state
  /*!
    \param sm the state machine that we check
    \return True if sm is in a GRAPH_subset state, false otherwhise
  */
  friend bool isInGraphSubset(controlMachine sm);

  //! Ask if the state machine is in NODE_subset state
  /*!
    \param sm the state machine that we check
    \return True if sm is in a NODE_subset state, false otherwhise
  */
  friend bool isInNodeSubset(controlMachine sm);

  //! Ask if the state machine is in EDGE_subset state
  /*!
    \param sm the state machine that we check
    \return True if sm is in a EDGE_subset state, false otherwhise
  */
  friend bool isInEdgeSubset(controlMachine sm);

};


// ---------------------------------------------------------------------------
// Others useful functions
// ---------------------------------------------------------------------------

//! Ask if the output_signal is a SIGNAL_ERROR_* state
/*!
  \param os the output state that we checks
  \return True if s is a SIGNAL_ERROR_* state, false otherwhise
*/
bool isErrorOutputSignal(output_signal os);


#endif

