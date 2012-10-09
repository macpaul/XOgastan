/***************************************************************************
			   othr_n.h  -  description
			      -------------------
     begin                : July 13 2001
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

#ifndef _OTHR_N_H
#define _OTHR_N_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "nast/nast_node.h"

#include <string>



// ---------------------------------------------------------------------------
//  CLASSES
// ---------------------------------------------------------------------------

//! The base class of the others nodes
/*! The base class of the others nodes
  The Others classes are used to represent some common 
  element in the C/C++ grammar that don't belong to any
  particular class (in cst, decl, type, stmt, expr). They are :

  ## Standard C :
  
  DEFnastCODE(TREE_LIST, tree_list, 0, 0)
  DEFnastCODE(IDENTIFIER_NODE, identifier_node, 0, 0)
  DEFnastCODE(CASE_LABEL, case_label, 0, 1)
  
  ## Special nodes :
  
  DEFnastCODE(BINFO, binfo, 0, 0)
  DEFnastCODE(BLOCK, block, 0, 0)
  DEFnastCODE(ERROR_MARK, error_mark, 0, 0)
  DEFnastCODE(OP_IDENFIER, op_idenfier, 0, 0)
  DEFnastCODE(SRCLOC, srcloc, 0, 0)
  DEFnastCODE(TREE_VEC, tree_vec, 0, 0)
  
  ## Special nodes (without field):
  
  DEFnastCODE(ARROW_EXPR, arrow_expr, 0, 0) 
  DEFnastCODE(METHOD_CALL_EXPR, method_call_expr, 0, 0) 
  DEFnastCODE(TAG_DEFN, tag_defn, 0, 0)
  DEFnastCODE(EMPTY_CLASS_EXPR, empty_class_expr, 0, 0) 
  DEFnastCODE(FUNCTION_NAME, function_name, 0, 0)
  DEFnastCODE(TEMPLATE_PARM_INDEX, template_parm_index, 0, 0)
  DEFnastCODE(TEMPLATE_PARM_LEVEL, template_parm_level, 0, 0)
  DEFnastCODE(DEFAULT_ARG, default_arg, 0, 0)
  DEFnastCODE(CPLUS_BINDING, cplus_binding, 0, 0)
  DEFnastCODE(WRAPPER, wrapper, 0, 0)
  DEFnastCODE(OFFSET_REF, offset_ref, 0, 0) 
  DEFnastCODE(SCOPE_REF, scope_ref, 0, 0) 
  DEFnastCODE(MEMBER_REF, member_ref, 0, 0) 
  
  ## Special nodes for template :
  
  DEFnastCODE(TEMPLATE_TYPE_PARM, template_type_parm, 0, 0) 
  DEFnastCODE(TEMPLATE_TEMPLATE_PARM, template_template_parm, 0, 0) 
  DEFnastCODE(BOUND_TEMPLATE_TEMPLATE_PARM, bound_template_template_parm, 0, 0) 
  
  The nodes in this class hierrarcy doesn't have any
  common attributes, but they may have only private
  attribute :
  
  - CASE_LABEL : 1 attribute
  -# case_default_flag
  
  - IDENTIFIER_NODE : 1 attribute
  -# name_of_the_indentifier

  \note Only the C elements (the firs three) are good defined.

*/
class othr_n : public nast_node {

  // NO ATTRIBUTES

 public:
  //! Constructor
  /*! Constructor */
  othr_n() { return; }


  //! Destructor
  /*! Destructor */
  ~othr_n() { }
};



//! The class for the identifier of types, functions, variables, ...
/*! The class for the identifier of types, functions, variables, ... 

  This image shows the possibile output edges.
  
  \image html identifier_node.gif
*/
class identifier_n : public othr_n {

 private:

  //*** Attributes

  //! The string of the identifier 
  /*! The string of the identifier */
  string       	node_string;
	  
 public:
  //! Constructor
  /*! Constructor */
  identifier_n() { return; }

  //! Destructor
  /*! Destructor */
  ~identifier_n() { }

  //*** Members

  //! Set the indentifier
  /*! Set the indentifier 

    \param s the indetifier's string
  */
  void setString(string s);


  //! Get the indentifier
  /*! Get the indentifier 

    \return The indetifier's string
  */
  string getString(void);


  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);
};



//! The class for the case/default in the switch
/*! The class for the case/default in the switch 

 Used to represent a case label, 
 range of case labels, or a default label.  
 
 This image shows the possibile output edges.
  
  \image html case_label.gif

  \note The case label is a statement node, but it is not
  reported in stmt_n hierarcy.
*/
class case_label_n : public othr_n {
  
 private:

  //*** Attributes
  
  //! Flag for the case/dedault status
  /*! Flag for the case/default status 
    
    True if it is a case label
    false if it is a default label.
  */
  bool		case_lb;	  
  
 public:
  //! Constructor
  /*! Constructor */
  case_label_n() : 
    case_lb(true) { return; }
  
  
  //! Destructor
  /*! Destructor */
  ~case_label_n() { }
  
  //*** Members
  
  //! Set the case/default status : it is case label
  /*! Set the case/default status : it is case label */
  void setCase(void);
  
  
  //! Set the case/default status : it is default label
  /*! Set the case/default status : it is default label */
  void setDefault(void);

  //! Pool if it is a case label
  /*! Pool if it is a case label
    
    \return True if it is case label
    false otherwise.
  */
  bool isCase(void);

  //! Pool if it is a default label
  /*! Pool if it is a default label

    \return True if it is default label
    false otherwise.
  */
  bool isDefault(void);
  
  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);

};



//! The class for an internal representation of a linked elements
/*! The class for an internal representation of a linked elements 

  This image shows the possibile output edges.
  
  \image html tree_list.gif
*/
class tree_list_n :  public othr_n { 

  // NO ATTRIBUTES

 public:
  //! Constructor
  /*! Constructor */
  tree_list_n() { return; }
  
  
  //! Destructor
  /*! Destructor */
  ~tree_list_n() { }

  
  //*** Member
  
  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);
};


//! The class for special nodes
/*! The class for special nodes */
class special_n :  public othr_n { 

  // NO ATTRIBUTES

 public:
  //! Constructor
  /*! Constructor */
  special_n() { return; }
  
  
  //! Destructor
  /*! Destructor */
  ~special_n() { }
  
  //*** Member
  
  //! Accept the visit
  /*! Accept the visit */
  virtual void accept(visitor &);
};


#endif
