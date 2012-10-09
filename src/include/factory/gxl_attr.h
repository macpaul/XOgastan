/***************************************************************************
			   gxl_attr.h  -  description
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


#ifndef _GXL_ATTR_H
#define _GXL_ATTR_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------

#include <string>
#include <cstdlib>

using namespace std;

// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

//! The class for the gxl attributes
/*!  
  This class is used to represent a gxl attributes.
  
  Each attribute has :
  
  - a <b>name</b> : the purpose of the attribute
  - a <b>type</b> : <int> or <string>
  - a <b>value</b> : can be integer value or string value
  
  \note This class is used to represent only the <int> and <string>
  gxl element. They are defined how :
  <!-- atomic values --><br>
  <!ELEMENT int     (#PCDATA) ><br>
  <!ELEMENT string  (#PCDATA) ><br>
  
*/
class gxl_attr  {
  
 private:
  
  //---- Attributes

  //! The name of the attribute
  string name;

  //! Flag for attribute <int>
  /*!    
    It value is :
    - true if the type is <int>
    - false if the type is <string>
  */
  bool is_int;

  //! The value of the attribute 
  /*!    
    \note The value is always stored how a string.
    The integer value are converted from string to int (long int C++)
    by calling the method getIntValue.
  */
  string value;
  
 public:
  //! Constructor
  gxl_attr() : name(""), is_int(false), value("") { }

  //! Destructor
  ~gxl_attr() { name = ""; value = ""; }

  //---- Enumeration for the type
  
  //! Enumeration for the type of the attribute
  enum attributeType { stringType, intType };

  //---- Members
  
  //! Set the name of the attribute
  /*!
    \param name the name of the attribute
   */
  void setName(string name);

  //! Set the type of the attribute : <int>...</int> or <string>...</string>
  /*!
    We can recognize the type of the attribute by checking the value of
    the attribute is_int : true(intType), false (stringType).

    \param type the type of the attribute : the value of the string "type"
    is "int" if the type is <int>, "string" if the type is <string>
   */
  void setType(enum attributeType type);

  //! Set the value of the attribute (always a string)
  /*!
    \param value the value of the attribute
   */
  void setValue(string value);

  //! Reset the attribute
  /*!
    Cancel the name and the value, and set the type to <string>...</string>
   */
  void reset(void);

  //! Get the name of the attribute
  string getName(void);

  //! Ask if the type is <string>...</string>
  /*!    
    \return True if the type is <string>...</string>, false otherwhise
   */
  bool isString(void);

  //! Ask if the type is <int>...</int>
  /*!    
    \return True if the type is <int>...</int>, false otherwhise
   */
  bool isInt(void);
  
  //! Get the value of the <string>...</string>
  /*!
    \return The value of <string>...</string>
  */
  string getStringValue(void);

  //! Get the value of the <int>...</int>
  /*!
    \return The value of <int>...</int> 

    \note This method make a conversion from string to long int (C++ type)
  */
  long getIntValue(void);

};

#endif





