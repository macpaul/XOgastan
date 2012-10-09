/***************************************************************************
			   gxl_edge.h  -  description
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


#ifndef _GXL_EDGE_H
#define _GXL_EDGE_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------

#include <string>

using namespace std;

// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

//! The class for the gxl edge
/*!
   This class is used o represent a gxl edge.

   Each edge has :

   - a <b>type</b> : string
   - a <b>from</b> point : long
   - a <b>to</b> point : long

   The gxl edge is defined how :

   <!-- edge --> <br>
   <!ELEMENT edge (type?, attr*, graph* %edge-extension;) > <br>
   <!ATTLIST edge <br>
   id            ID       #IMPLIED <br>
   from          IDREF    #REQUIRED <br>
   to            IDREF    #REQUIRED <br>
   fromorder     CDATA    #IMPLIED <br>
   toorder       CDATA    #IMPLIED <br>
   isdirected    ( true | false ) #IMPLIED <br>
   %edge-attr-extension; <br>
   > <br>

   We only store the information about the from and to point, and the type.
   
   \note In this class the from and to point have long type. An edge
   connects the two nodes with the identifier from and to. 
   The operativeMachine  uses this class to hold information 
   about the edges read from the gxl  document; 
   at the end of the reading process the operativeMachine
   trasform the link from two identifier node into a link from two
   nast_node *.
*/
class gxl_edge  {
  
 private:
  
  //*** Attributes
  
  //! The type of the edge
  /*!
    The type of the edhe has string type.
    The operativeMachine transform this string
    into an edge_code

    \sa edge_code.def edge_code.h nast_node.h
   */
  string type;

  //! The from points
  /*!
    Its value is the index (not the memory address) of the from
    <node>...</node>
  */
  long from;

  //! The to points
  /*!  
    Its value is the index (not the memory address) of the to
    <node>...</node>
  */
  long to;
  
 public:
  //! Constructor
  gxl_edge() : type(""), from(0), to(0) { }

  //! Constructor
  gxl_edge(string type, long from, long to);

  //*** Members

  //! Set the type of the edge
  /*!
    \param type the type of the edge

    \sa edge_code.def edge_code.h nast_node.h
   */
  void setType(string type);

  //! Set the from point of the edge
  /*!
    \param from the from point of the edge

   */
  void setFrom(long from);

  //! Set the to point of the edge
  /*!
    \param to the to point of the edge

   */
  void setTo(long to);

  //! Get the type of the edge
  /*!
    \return The type of the edge

    \sa edge_code.def edge_code.h nast_node.h
  */
  string getType(void);

  //! Get the from point of the edge
  /*!
    \return The from point of the edge
   */
  long getFrom(void);

  //! Get the to point of the edge
  /*!
    \return The to point of the edge
   */
  long getTo(void);

};

#endif
