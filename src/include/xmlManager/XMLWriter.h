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
#include <util/PlatformUtils.hpp>
#include <util/XMLString.hpp>
#include <util/XMLUniDefs.hpp>
#include <framework/XMLFormatter.hpp>
#include <util/TranscodingException.hpp>


#include <dom/DOM_DOMException.hpp>

#include <dom/DOM.hpp>
#include <string.h>
#include <stdlib.h>

#include <fstream>


// ---------------------------------------------------------------------------
//  FILES
// ---------------------------------------------------------------------------
namespace XMLWriter {
  //! Write a DOM_Document on the file path
  /*!
    \param doc the document to write
    \param filePath the path of the output file 
  */
  extern void write_XMLonFile(DOM_Document *doc, const char *filePath);
}
#endif





