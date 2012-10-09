/***************************************************************************
			   XMLDOM_str_exception.cpp  -  description
			      -------------------
     begin                : Sept 8 2001
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
#include "xmlManager/XMLDOM_str_exception.h"

// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------


char *XMLDOM_str_exception::operator()
  (const enum DOM_DOMException::ExceptionCode &code) {
  
  switch (code) {
    
  case DOM_DOMException::INDEX_SIZE_ERR: 
    return "index_size_err"; 
  case DOM_DOMException::DOMSTRING_SIZE_ERR: 
    return "domstring_size_err"; 
  case DOM_DOMException::HIERARCHY_REQUEST_ERR: 
    return "wrong_request_err"; 
  case DOM_DOMException::WRONG_DOCUMENT_ERR: 
    return "wrong_document_err"; 
  case DOM_DOMException::INVALID_CHARACTER_ERR: 
    return "invalid_character_err"; 
  case DOM_DOMException::NO_DATA_ALLOWED_ERR: 
    return "no_data_allowed_err"; 
  case DOM_DOMException::NO_MODIFICATION_ALLOWED_ERR: 
    return "no_modification_allowed_err"; 
  case DOM_DOMException::NOT_FOUND_ERR: 
    return "not_found_err"; 
  case DOM_DOMException::NOT_SUPPORTED_ERR: 
    return "not_supported_err"; 
  case DOM_DOMException::INUSE_ATTRIBUTE_ERR: 
    return "inuse_attribute_err"; 
  case DOM_DOMException::INVALID_STATE_ERR: 
    return "invalid_state_err"; 
  case DOM_DOMException::SYNTAX_ERR: 
    return "syntax_err"; 
  case DOM_DOMException::INVALID_MODIFICATION_ERR: 
    return "invalid_modification_err"; 
  case DOM_DOMException::NAMESPACE_ERR: 
    return "namespace_err"; 
  case DOM_DOMException::INVALID_ACCESS_ERR: 
    return "invalid_access_err"; 
  }

  return "unknow DOM_DOMexception";

}
