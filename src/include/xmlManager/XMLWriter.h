/***************************************************************************
			   XMLWriter.h  -  description
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

#ifndef _XML_WRITER_H
#define _XML_WRITER_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/framework/XMLFormatter.hpp>
#include <xercesc/util/TranscodingException.hpp>

#include <xercesc/dom/DOMException.hpp>

#include <xercesc/dom/DOM.hpp>
#include <string.h>
#include <stdlib.h>

#include <fstream>

using namespace std;
XERCES_CPP_NAMESPACE_USE

// ---------------------------------------------------------------------------
//  FILES
// ---------------------------------------------------------------------------
namespace XMLWriter {
  //! Write a DOMDocument on the file path
  /*!
    \param doc the document to write
    \param filePath the path of the output file 
  */
  extern void write_XMLonFile(DOMDocument *doc, const char *filePath);
}
#endif





