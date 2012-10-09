/***************************************************************************
			   XMLBuilder.h  -  description
			      -------------------
     begin                : Sept 6 2001
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

#ifndef _XML_BUILDER_H
#define _XML_BUILDER_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "dom/DOM.hpp"

// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

//! The base class for the XML DOM building process
/*!
  The deriveds classes are used to build the
  XML DOM obejct.

  This class is an interface for the base
  operation.
*/

class XMLBuilder
{
 protected:

  //---- Attributes

  //! The DOM document that we are building
  DOMDocument *doc;

  //! The root element of the document
  DOM_Element root;

  //---- Members

  //! Create a new DOMDocument
  virtual void newDOM_Document(void) = 0;
 
 public:
  //! Constructor
  XMLBuilder() { }

  //! Destructor
  ~XMLBuilder() { }

  //---- Members

  //! Get the DOM document 
  /*!
    \return The DOM document that we have been built.
  */ 
  DOMDocument *getDOMDocument(void) 
    { return doc; }

  //! Build an XML DOM document
  virtual void buildDOM(void) = 0;

};


#endif



