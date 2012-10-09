/***************************************************************************
			   HTMLofstream.cpp  -  description
			      -------------------
     begin                : Aug 29 2001
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
#include "htmlWriter/HTMLofstream.h"

// ---------------------------------------------------------------------------
//  Methods
// ---------------------------------------------------------------------------

void 
HTMLofstream::open(const char *pageName){
  string pathName = "html/";
  pathName += pageName;
  page.open (pathName.c_str());
  return;
}


void 
HTMLofstream::close() {
  page.close();
}


void 
HTMLofstream::statisticRow(string name, long value, bool bold) {

  page << "\t<tr>\n";
  
  // name
  page << "\t<td  bgcolor=\"blue\" width=\"80%\">"
       << "<font color=\"yellow\"b>";
  if (bold) 
    page << "<b>" << name << " :</b><td>\n";
  else 
    page << name << " :<td>\n";
  
  // value
  page << "\t<td  bgcolor=\"blue\" width=\"20%\">"
       << "<font color=\"yellow\"b>"
       << value << "</font><td>\n";
  
  page << "\t</tr>\n";
}


void 
HTMLofstream::statisticRowX100(string name, long value, 
			       double x100, bool bold) {
  
  page << "\t<tr>\n";
  
  // name
  page << "\t<td  bgcolor=\"blue\" width=\"60%\">"
       << "<font color=\"yellow\"b>";
  if (bold) 
    page << "<b>" << name << " :</b><td>\n";
  else 
    page << name << " :<td>\n";
  
  // value
  page << "\t<td  bgcolor=\"blue\" width=\"20%\">"
       << "<font color=\"yellow\"b>"
       << value << "</font><td>\n";
  
  // x100 
  page << "\t<td  bgcolor=\"blue\" width=\"20%\">"
       << "<font color=\"yellow\"b>"
       << x100 << "%</font><td>\n";
  
  page << "\t</tr>\n";
}

// ---------------------------------------------------------------------------
//  FRIENDS
// ---------------------------------------------------------------------------

HTMLofstream& 
operator<<(HTMLofstream& HTMLos, char *c) {
  HTMLos.page << c;
  return HTMLos;
}

HTMLofstream& 
operator<<(HTMLofstream& HTMLos, string s) {
  HTMLos.page << s;
  return HTMLos;
}

HTMLofstream& 
operator<<(HTMLofstream& HTMLos, long l) {
  HTMLos.page << l;
  return HTMLos;
}

HTMLofstream& 
operator<<(HTMLofstream& HTMLos, double d) {
  HTMLos.page << d;
  return HTMLos;
}

HTMLofstream& 
operator<<(HTMLofstream& HTMLos, fnctData& fd)
{

  HTMLos.page << "\n<!-- Write fnctData -->\n";

  // write function name
  HTMLos.page << "<table border=\"0\" width=\"100%\">\n"
	      << "\t<td  bgcolor=\"#00FFFF\" width=\"100%\">\n\t<b>"
	      << fd.getName() << "</b>\n\t</td>\n</table>\n";


  // Is C standard 
  if (fd.isStdC())
    HTMLos.page << "<b>Is a function of the C standard library</b><br><br>\n";

  // Nast information
  HTMLos.page << "<b>Nast data :</b><br>"
	      << "AST node index of the function_decl : " 
	      << (fd.getNodeP())->getId() << "<br>\n";

  // Type returned
  HTMLos.page << "<b>Type returned :</b><br>"
	      << fd.getType() << "<br>\n";
  
  // Parameters list
  if (fd.hasParm()) {

    HTMLos.page << "<b>List of the parameters :</b><br>\n";
    HTMLos << fd.getParmList();
    
  }
	 
  return HTMLos;
}


HTMLofstream& 
operator<<(HTMLofstream& HTMLos, parmData& pd) 
{
  
  HTMLos.page << "<ul>\n"
	      << "\t<li>" 
	      << pd.getTypeExtra() << " "
	      << pd.getType() << " "
	      << pd.getName() << "\n"
	      << "</ul>\n";
  
  return HTMLos;
}
  


//! Write an object declsList on the output
HTMLofstream& 
operator<<(HTMLofstream& HTMLos, declsList& dL) 
{
  declData            *dData;    // informations to write
  declsListIterator   p;         // browse the list
  
  HTMLos.page << "<br><br>\n"
	      << "List of the declaration found into the function.<br>\n"
	      << "We have a short description of each declaration : <br>\n"
	      << "<ol>\n"
	      << "\t<li>Type of declaration (typedef or var decl)\n"
	      << "\t<li>The line in the source file\n"
	      << "\t<li>The qualifiers\n"
	      << "\t<li>The type\n"
	      << "\t<li>The name\n"
	      << "\t<li>The number of *\n"
	      << "\t<li>The number of []\n"
	      << "</ol>\n";
  
  HTMLos.page << "<table border=\"0\" width=\"100%\" cellspacing=\"2\">\n\n";
  HTMLos.page << "\t<tr>\n";
  HTMLos.page << "\t<td width=\"18%\">"
	      << "<b>What</b>"
	      << "</td>\n\n";
  HTMLos.page << "\t<td width=\"18%\">"
	      << "<b>Line</b>"
	      << "</td>\n\n";
  HTMLos.page << "\t<td width=\"18%\">"
	      << "<b>Qual.</b>"
	      << "</td>\n\n";
  HTMLos.page << "\t<td width=\"18%\">"
	      << "<b>Type</b>"
	      << "</td>\n\n";
  HTMLos.page << "\t<td width=\"18%\">"
	      << "<b>Name</b>"
	      << "</td>\n\n";
  HTMLos.page << "\t<td width=\"5%\">"
	      << "<b>*</b>"
	      << "</td>\n\n";
  HTMLos.page << "\t<td width=\"5%\">"
	      << "<b>[]</b>"
	      << "</td>\n\n";
  HTMLos.page << "\t</tr>\n";
  
  p = dL.begin();
  while (p != dL.end()) {
    dData = *p;
    p++;
    
    HTMLos.page << "\t<tr>\n";

    // write WHAT
    HTMLos.page << "\t<td bgcolor=\"#AFF7ED\" width=\"18%\">";
    switch(dData->getCode()) {
    case TYPE_DECL:
      HTMLos.page << "<b>typedef</b>"; break;
    case VAR_DECL:
      HTMLos.page << "<b>var</b>"; break;
    default:
      HTMLos.page << "Other decl"; break;
    }
    HTMLos.page << "</td>\n";

    // write the LINE
    HTMLos.page << "\t<td bgcolor=\"#AFF7ED\" width=\"18%\">"
		<< dData->getLine() 
		<< "</td>\n";

    // write the QUAL
    HTMLos.page << "\t<td bgcolor=\"#AFF7ED\" width=\"22%\">"
		<< dData->getTypeExtra() 
		<< "</td>\n";
    
    // write the TYPE
    HTMLos.page << "\t<td bgcolor=\"#AFF7ED\" width=\"22%\">"
	   << dData->getType() 
	   << "</td>\n";
    
    // write the NAME
    HTMLos.page << "\t<td bgcolor=\"#AFF7ED\" width=\"22%\">"
		<< dData->getName() 
		<< "</td>\n";
    
    // write the *
    HTMLos.page << "\t<td bgcolor=\"#AFF7ED\" width=\"6%\">"
		<< dData->getStarNumber() 
		<< "</td>\n";
    
    // write the *
    HTMLos.page << "\t<td bgcolor=\"#AFF7ED\" width=\"6%\">"
		<< dData->getSquareNumber() 
		<< "</td>\n";
  }

  HTMLos.page << "</table>\n\n";

  return HTMLos;
}




HTMLofstream& operator<<(HTMLofstream& HTMLos, varUsedList& vuL) {
  varUsedData            *vuData;    // informations to write
  varUsedListIterator    p;          // browse the list
  
  HTMLos.page << "<br><br>\n"
	      << "List of the variables used by the function.<br>\n"
	      << "We have a short description of each declaration : <br>\n"
	      << "<ol>\n"
	      << "\t<li>Is a local decl ?\n"
	      << "\t<li>The line in the source file where is defined\n"
	      << "\t<li>The qualifiers\n"
	      << "\t<li>The type\n"
	      << "\t<li>The name\n"
	      << "\t<li>The number of *\n"
	      << "\t<li>The number of []\n"
	      << "</ol>\n";
  
  HTMLos.page << "<table border=\"0\" width=\"100%\" cellspacing=\"2\">\n\n";
  HTMLos.page << "\t<tr>\n";
  HTMLos.page << "\t<td width=\"18%\">"
	      << "<b>What</b>"
	      << "</td>\n\n";
  HTMLos.page << "\t<td width=\"18%\">"
	      << "<b>Line</b>"
	      << "</td>\n\n";
  HTMLos.page << "\t<td width=\"18%\">"
	      << "<b>Qual.</b>"
	      << "</td>\n\n";
  HTMLos.page << "\t<td width=\"18%\">"
	      << "<b>Type</b>"
	      << "</td>\n\n";
  HTMLos.page << "\t<td width=\"18%\">"
	      << "<b>Name</b>"
	      << "</td>\n\n";
  HTMLos.page << "\t<td width=\"5%\">"
	      << "<b>*</b>"
	      << "</td>\n\n";
  HTMLos.page << "\t<td width=\"5%\">"
	      << "<b>[]</b>"
	      << "</td>\n\n";
  HTMLos.page << "\t</tr>\n";
  
  p = vuL.begin();
  while (p != vuL.end()) {
    vuData = *p;
    p++;
    
    HTMLos.page << "\t<tr>\n";
    
    // write WHAT
    HTMLos.page << "\t<td bgcolor=\"#AFF7ED\" width=\"18%\">";
    // Position
    if (vuData->isLocal())
      HTMLos.page << "local";
    else
      HTMLos.page << "global";
    // Var or Parm ?
    if ( (vuData->getNodeP())->getCode() == PARM_DECL )
      HTMLos.page << " parm";
    else if ( (vuData->getNodeP())->getCode() == VAR_DECL )
      HTMLos.page << " var";
    else 
      HTMLos.page << " other";
    HTMLos.page << "</td>\n";

    // write the LINE
    HTMLos.page << "\t<td bgcolor=\"#AFF7ED\" width=\"18%\">"
		<< vuData->getLine() 
		<< "</td>\n";

    // write the QUAL
    HTMLos.page << "\t<td bgcolor=\"#AFF7ED\" width=\"18%\">"
		<< vuData->getTypeExtra() 
		<< "</td>\n";
    
    // write the TYPE
    HTMLos.page << "\t<td bgcolor=\"#AFF7ED\" width=\"18%\">"
		<< vuData->getType() 
		<< "</td>\n";
    
    // write the NAME
    HTMLos.page << "\t<td bgcolor=\"#AFF7ED\" width=\"18%\">"
		<< vuData->getName() 
		<< "</td>\n";
    
    // write the *
    HTMLos.page << "\t<td bgcolor=\"#AFF7ED\" width=\"5%\">"
		<< vuData->getStarNumber() 
		<< "</td>\n";
    
    // write the []
    HTMLos.page << "\t<td bgcolor=\"#AFF7ED\" width=\"5%\">"
		<< vuData->getSquareNumber() 
		<< "</td>\n";
    
  }

  HTMLos.page << "</table>\n\n";

  return HTMLos;
}


HTMLofstream& operator<<(HTMLofstream& HTMLos, parmList& pL) {
  parmData            *pData;    // informations to write
  parmListIterator    p;         // browse the list
  
  HTMLos.page << "<table border=\"0\" width=\"100%\" cellspacing=\"2\">\n\n";
  HTMLos.page << "\t<tr>\n";
  HTMLos.page << "\t<td width=\"30%\">"
	      << "<b>Qual.</b>"
	      << "</td>\n\n";
  HTMLos.page << "\t<td width=\"30%\">"
	      << "<b>Type</b>"
	      << "</td>\n\n";
  HTMLos.page << "\t<td width=\"30%\">"
	      << "<b>Name</b>"
	      << "</td>\n\n";
  HTMLos.page << "\t<td width=\"5%\">"
	      << "<b>*</b>"
	      << "</td>\n\n";
  HTMLos.page << "\t<td width=\"5%\">"
	      << "<b>[]</b>"
	      << "</td>\n\n";
  HTMLos.page << "\t</tr>\n";
  
  p = pL.begin();
  while (p != pL.end()) {
    pData = *p;
    p++;
    
    HTMLos.page << "\t<tr>\n";

    // write the QUAL
    HTMLos.page << "\t<td bgcolor=\"#AFF7ED\" width=\"30%\">"
		<< pData->getTypeExtra() 
		<< "</td>\n";
    
    // write the TYPE
    HTMLos.page << "\t<td bgcolor=\"#AFF7ED\" width=\"30%\">"
		<< pData->getType() 
		<< "</td>\n";
    
    // write the NAME
    HTMLos.page << "\t<td bgcolor=\"#AFF7ED\" width=\"30%\">"
		<< pData->getName() 
		<< "</td>\n";
    
    // write the *
    HTMLos.page << "\t<td bgcolor=\"#AFF7ED\" width=\"5%\">"
		<< pData->getStarNumber() 
		<< "</td>\n";
    
    // write the *
    HTMLos.page << "\t<td bgcolor=\"#AFF7ED\" width=\"5%\">"
		<< pData->getSquareNumber() 
		<< "</td>\n";
    
  }

  HTMLos.page << "</table>\n\n";

  return HTMLos;
}

HTMLofstream& 
operator<<(HTMLofstream& HTMLos, stmtNumData& snd) {


  HTMLos.page << "<table border=\"0\" width=\"400\" cellspacing=\"2\">";

  HTMLos.statisticRow("Asm statements",
		      snd.numStmt(ASM_STMT),false);
  
  HTMLos.statisticRow("Break statements",
		      snd.numStmt(BREAK_STMT),false);
  
  HTMLos.statisticRow("Compound statements",
		      snd.numStmt(COMPOUND_STMT),false);
  
  HTMLos.statisticRow("Continue statements",
		      snd.numStmt(CONTINUE_STMT),false);
  
  HTMLos.statisticRow("Decl statements",
		      snd.numStmt(DECL_STMT),false);
  
  HTMLos.statisticRow("Do statements",
		      snd.numStmt(DO_STMT),false);
  
  HTMLos.statisticRow("Expr statements",
		      snd.numStmt(EXPR_STMT),false);
  
  HTMLos.statisticRow("For statements",
		      snd.numStmt(FOR_STMT),false);
  
  HTMLos.statisticRow("Goto statements",
		      snd.numStmt(GOTO_STMT),false);
  
  HTMLos.statisticRow("If statements",
		      snd.numStmt(IF_STMT),false);
  
  HTMLos.statisticRow("Label statements",
		      snd.numStmt(LABEL_STMT),false);
  
  HTMLos.statisticRow("Return statements",
		      snd.numStmt(RETURN_STMT),false);
  
  HTMLos.statisticRow("Switch statements",
		      snd.numStmt(SWITCH_STMT),false);
  
  HTMLos.statisticRow("Scope statements",
		      snd.numStmt(SCOPE_STMT),false);
  
  HTMLos.statisticRow("While statements",
		      snd.numStmt(WHILE_STMT),false);
  
  HTMLos.statisticRow("Case_label statements",
		      snd.numStmt(CASE_LABEL),false);
  
  HTMLos.page << "</table>";
  
  // Totals
  
  HTMLos.page << "<table border=\"0\" width=\"500\" cellspacing=\"2\">";
  
  HTMLos.statisticRow("Total condition stmts",
		      snd.totalSelectStmt(),false);
  
  HTMLos.statisticRow("Total iteration stmts",
		      snd.totalIterStmt(),false);
  
  HTMLos.statisticRow("Total flow modifier stmts",
		      snd.totalFlowModifierStmt(),false);

  HTMLos.statisticRow("Total stmts",
		      snd.totalStmt(),true);
  
  HTMLos.page << "</table>";
  
  // short legend
  HTMLos.page << "<br>Condition stmts : if, switch"
	      << "<br>Iteration stmts : for, do, while"
	      << "<br>Flow modifier stmts : break, continue, "
	      << "return, goto\n\n";
  
  return HTMLos;
}




HTMLofstream&
operator<<(HTMLofstream& HTMLos, exprNumData& end) {


  HTMLos.page << "<table border=\"0\" width=\"500\" cellspacing=\"2\">";

  HTMLos.statisticRow("Unary minus <b>-</b>",
		      end.numExpr(NEGATE_EXPR),false);
  
  HTMLos.statisticRow("Bitwise negation <b>~</b>",
		      end.numExpr(BIT_NOT_EXPR),false);
  
  HTMLos.statisticRow("Logical not <b>!</b>",
		      end.numExpr(TRUTH_NOT_EXPR),false);
  
  HTMLos.statisticRow("Address of <b>&amp;</b>",
		      end.numExpr(ADDR_EXPR),false);
  
  HTMLos.statisticRow("Indirect ref <b>*</b>",
		      end.numExpr(INDIRECT_REF),false);
  
  HTMLos.statisticRow("<b>sizeof</b>",
		      end.numExpr(SIZEOF_EXPR),false);
  
  HTMLos.statisticRow("Plus <b>+</b>",
		      end.numExpr(PLUS_EXPR),false);
  
  HTMLos.statisticRow("Minus <b>-</b>",
		      end.numExpr(MINUS_EXPR),false);
  
  HTMLos.statisticRow("Multiplication <b>*</b>",
		      end.numExpr(MULT_EXPR),false);
  
  // also RDIV_EXPR
  HTMLos.statisticRow("Division <b>/</b>",
		      end.numExpr(TRUNC_DIV_EXPR),false);
  
  HTMLos.statisticRow("Mod <b>%</b>",
		      end.numExpr(TRUNC_MOD_EXPR),false);
  
  HTMLos.statisticRow("Left shift <b>&lt;&lt</b>",
		      end.numExpr(LSHIFT_EXPR),false);
  
  HTMLos.statisticRow("Right shift <b>&gt;&gt;</b>",
		      end.numExpr(RSHIFT_EXPR),false);
  
  HTMLos.statisticRow("Bitwise <b>|</b>",
		      end.numExpr(BIT_IOR_EXPR),false);
  
  HTMLos.statisticRow("Bitwise <b>^</b>",
		      end.numExpr(BIT_XOR_EXPR),false);
  
  HTMLos.statisticRow("Bitwise <b>&amp;</b>",
		      end.numExpr(BIT_AND_EXPR),false);
  
  HTMLos.statisticRow("Predecrement <b>--a</b>",
		      end.numExpr(PREDECREMENT_EXPR),false);
  
  HTMLos.statisticRow("Postdecrement <b>a--</b>",
		      end.numExpr(POSTDECREMENT_EXPR),false);
  
  HTMLos.statisticRow("Preincrement <b>++a</b>",
		      end.numExpr(PREINCREMENT_EXPR),false);
  
  HTMLos.statisticRow("Postincrement <b>a++</b>",
		      end.numExpr(POSTINCREMENT_EXPR),false);
  
  // also TRUTH_AND_EXPR
  HTMLos.statisticRow("Logical and <b>&amp;&amp;</b>",
		      end.numExpr(TRUTH_ANDIF_EXPR),false);
  
  // also TRUTH_OR_EXPR
  HTMLos.statisticRow("Logical or <b>||</b>",
		      end.numExpr(TRUTH_ORIF_EXPR),false);
  
  HTMLos.statisticRow("Less than <b>&lt;</b>",
		      end.numExpr(LT_EXPR),false);
  
  HTMLos.statisticRow("Less that or equal to <b>&lt;=</b>",
		      end.numExpr(LE_EXPR),false);
  
  HTMLos.statisticRow("Greater than <b>&gt;</b>",
		      end.numExpr(GT_EXPR),false);
  
  HTMLos.statisticRow("Greater than or equal to <b>&gt;=</b>",
		      end.numExpr(GE_EXPR),false);
  
  HTMLos.statisticRow("Equal <b>==</b>",
		      end.numExpr(EQ_EXPR),false);
  
  HTMLos.statisticRow("Not equal <b>!=</b>",
		      end.numExpr(NE_EXPR),false);
  
  HTMLos.statisticRow("Comma <b>,</b>",
		      end.numExpr(COMPOUND_EXPR),false);
  
  HTMLos.statisticRow("Dot access <b>.</b>",
		      end.numExpr(COMPONENT_REF),false);
  
  // also INIT_EXPR
  HTMLos.statisticRow("Assignement <b>=</b>",
		      end.numExpr(MODIFY_EXPR),false);
  
  HTMLos.statisticRow("Square <b>[]</b>",
		      end.numExpr(ARRAY_REF),false);
  
  HTMLos.statisticRow("Call <b>()</b>",
		      end.numExpr(CALL_EXPR),false);
  
  HTMLos.statisticRow("Conditional <b>?:</b>",
		      end.numExpr(COND_EXPR),false);
  
  HTMLos.page << "</table>";

  // Totals

  HTMLos.page << "<table border=\"0\" width=\"600\" cellspacing=\"2\">";

  HTMLos.statisticRow("Total unary expressions",
		      end.totalUnaryExpr(),false);

  HTMLos.statisticRow("Total binary expressions",
		      end.totalBinaryExpr(),false);

  HTMLos.statisticRow("Total ternary expressions",
		      end.totalTernaryExpr(),false);

  HTMLos.statisticRow("Total expressions",
		      end.totalExpr(),true);

  HTMLos.page << "</table>";

  // short legend
  HTMLos.page << "<br>Unary exprs : -, ~, !, &amp;, *, sizeof"
	      << "<br>Binary exprs : +, -, *, /, %, &lt;&lt;, &gt;&gt;,"
	      << " ^, |, &amp;, --, ++, &amp;&amp;, ||,"
	      << " &lt;, &lt=;, &gt;, &gt;=, ==, !=, ,(comma), .(dot), =, [], ()" 
	      << "<br>Ternary exprs : ?:\n\n";

  return HTMLos;
}





//! Write an object nastNumData on the output
HTMLofstream& 
operator<<(HTMLofstream& HTMLos, nastNumData& nnd) {
  int i;
  long total;

  total = nnd.totalNastNode();

  // Type
  HTMLos.page << "<table border=\"0\" width=\"500\" cellspacing=\"2\">";
  for (i = VOID_TYPE; i <= UNION_TYPE; i++) 
    HTMLos.statisticRowX100( a2b::nast_code2string((nast_code)i), 
			     nnd.numNast((nast_code)i),
			     getX100(nnd.numNast((nast_code)i), total),
		     false);
  HTMLos.page << "</table>\n\n";
  HTMLos.page << "<table border=\"0\" width=\"600\" cellspacing=\"2\">";
  HTMLos.statisticRowX100( "Total *_TYPE :",
			   nnd.totalTypeNastNode(),
			   getX100(nnd.totalTypeNastNode(), total),
			   true);
  HTMLos.page << "</table>\n\n";
  
  HTMLos.page << "<br>\n\n";

  // Decls
  HTMLos.page << "<table border=\"0\" width=\"500\" cellspacing=\"2\">";
  for (i = TYPE_DECL; i <= RESULT_DECL; i++) 
    HTMLos.statisticRowX100( a2b::nast_code2string((nast_code)i), 
			     nnd.numNast((nast_code)i),
			     getX100(nnd.numNast((nast_code)i), total),
			     false);
  HTMLos.page << "</table>\n\n";
  HTMLos.page << "<table border=\"0\" width=\"600\" cellspacing=\"2\">";
  HTMLos.statisticRowX100( "Total *_DECL :",
			   nnd.totalDeclNastNode(),
			   getX100(nnd.totalDeclNastNode(), total),
			   true);
  HTMLos.page << "</table>\n\n";
  
  HTMLos.page << "<br>\n\n";

  // Stmts
  HTMLos.page << "<table border=\"0\" width=\"500\" cellspacing=\"2\">";
  for (i = BREAK_STMT; i <= ASM_STMT; i++) 
    HTMLos.statisticRowX100( a2b::nast_code2string((nast_code)i), 
			     nnd.numNast((nast_code)i),
			     getX100(nnd.numNast((nast_code)i), total),
		     false);
  HTMLos.page << "</table>\n\n";
  HTMLos.page << "<table border=\"0\" width=\"600\" cellspacing=\"2\">";
  HTMLos.statisticRowX100( "Total *_STMT :",
			   nnd.totalStmtNastNode(),
			   getX100(nnd.totalStmtNastNode(), total),
			   true);
  HTMLos.page << "</table>\n\n";
  
  HTMLos.page << "<br>\n\n";
  
  //  Csts
  HTMLos.page << "<table border=\"0\" width=\"500\" cellspacing=\"2\">";
  HTMLos.statisticRowX100( "integer_cst",
			   nnd.numNast(INTEGER_CST),
			   getX100(nnd.numNast(INTEGER_CST), total),
			   false);
  HTMLos.statisticRowX100( "real_cst",
			   nnd.numNast(REAL_CST),
			   getX100(nnd.numNast(REAL_CST), total),
			   false);
  HTMLos.statisticRowX100( "string_cst",
			   nnd.numNast(STRING_CST),
			   getX100(nnd.numNast(STRING_CST), total),
			   false);
  HTMLos.page << "</table>\n\n";
  
  HTMLos.page << "<table border=\"0\" width=\"600\" cellspacing=\"2\">";
  HTMLos.statisticRowX100( "Total *_CST :",
			   nnd.totalCstNastNode(),
			   getX100(nnd.totalCstNastNode(), total),
			   true);
  HTMLos.page << "</table>\n\n";
  
  HTMLos.page << "<br>\n\n";
  
  // Expr
  HTMLos.page << "<table border=\"0\" width=\"500\" cellspacing=\"2\">";
  HTMLos.statisticRowX100("negate_expr",
			  nnd.numNast(NEGATE_EXPR),
			  getX100(nnd.numNast(NEGATE_EXPR), total),
			  false);
  HTMLos.statisticRowX100("bit_not_expr",
			  nnd.numNast(BIT_NOT_EXPR),
			  getX100(nnd.numNast(BIT_NOT_EXPR), total),
			  false);
  HTMLos.statisticRowX100("truth_not_expr",
			  nnd.numNast(TRUTH_NOT_EXPR),
			  getX100(nnd.numNast(TRUTH_NOT_EXPR), total),
			  false);
  HTMLos.statisticRowX100("addr_expr",
			  nnd.numNast(ADDR_EXPR),
			  getX100(nnd.numNast(ADDR_EXPR), total),
			  false);
  HTMLos.statisticRowX100("indirect_ref",
			  nnd.numNast(INDIRECT_REF),
			  getX100(nnd.numNast(INDIRECT_REF), total),
			  false);
  HTMLos.statisticRowX100("sizeof_expr",
			  nnd.numNast(SIZEOF_EXPR),
			  getX100(nnd.numNast(SIZEOF_EXPR), total),
			  false);
  HTMLos.statisticRowX100("plus_expr",
			  nnd.numNast(PLUS_EXPR),
			  getX100(nnd.numNast(PLUS_EXPR), total),
			  false);
  HTMLos.statisticRowX100("minus_expr",
			  nnd.numNast(MINUS_EXPR),
			  getX100(nnd.numNast(MINUS_EXPR), total),
			  false);
  HTMLos.statisticRowX100("mult_expr",
			  nnd.numNast(MULT_EXPR),
			  getX100(nnd.numNast(MULT_EXPR), total),
			  false);
  // also RDIV_EXPR
  HTMLos.statisticRowX100("trunc_div_expr + rdiv_expr",
			  nnd.numNast(TRUNC_DIV_EXPR),
			  getX100(nnd.numNast(TRUNC_DIV_EXPR), total),
			  false);
  HTMLos.statisticRowX100("trunc_mod_expr",
			  nnd.numNast(TRUNC_MOD_EXPR),
			  getX100(nnd.numNast(TRUNC_MOD_EXPR), total),
			  false);
  HTMLos.statisticRowX100("lshift_expr",
			  nnd.numNast(LSHIFT_EXPR),
			  getX100(nnd.numNast(LSHIFT_EXPR), total),
			  false);
  HTMLos.statisticRowX100("rshift_expr",
			  nnd.numNast(RSHIFT_EXPR),
			  getX100(nnd.numNast(RSHIFT_EXPR), total),
			  false);
  HTMLos.statisticRowX100("bit_ior_expr",
			  nnd.numNast(BIT_IOR_EXPR),
			  getX100(nnd.numNast(BIT_IOR_EXPR), total),
			  false);
  HTMLos.statisticRowX100("bit_xor_expr",
			  nnd.numNast(BIT_XOR_EXPR),
			  getX100(nnd.numNast(BIT_XOR_EXPR), total),
			  false);
  HTMLos.statisticRowX100("bit_and_expr",
			  nnd.numNast(BIT_AND_EXPR),
			  getX100(nnd.numNast(BIT_AND_EXPR), total),
			  false);
  HTMLos.statisticRowX100("predrecrement_expr",
			  nnd.numNast(PREDECREMENT_EXPR),
			  getX100(nnd.numNast(PREDECREMENT_EXPR), total),
			  false);
  HTMLos.statisticRowX100("postdecrement_expr",
			  nnd.numNast(POSTDECREMENT_EXPR),
			  getX100(nnd.numNast(POSTDECREMENT_EXPR), total),
			  false);
  HTMLos.statisticRowX100("preincrement_expr",
			  nnd.numNast(PREINCREMENT_EXPR),
			  getX100(nnd.numNast(PREINCREMENT_EXPR), total),
			  false);
  HTMLos.statisticRowX100("postincrement_expr",
			  nnd.numNast(POSTINCREMENT_EXPR),
			  getX100(nnd.numNast(POSTINCREMENT_EXPR), total),
			  false);
  // also TRUTH_AND_EXPR
  HTMLos.statisticRowX100("truth_andif_expr + truth_and_expr",
			  nnd.numNast(TRUTH_ANDIF_EXPR),
			  getX100(nnd.numNast(TRUTH_ANDIF_EXPR), total),
			  false);
  // also TRUTH_OR_EXPR
  HTMLos.statisticRowX100("truth_orif_expr + truth_or_expr",
			  nnd.numNast(TRUTH_ORIF_EXPR),
			  getX100(nnd.numNast(TRUTH_ORIF_EXPR), total),
			  false);
  HTMLos.statisticRowX100("lt_expr",
			  nnd.numNast(LT_EXPR),
			  getX100(nnd.numNast(LT_EXPR), total),
			  false);
  HTMLos.statisticRowX100("le_expr",
			  nnd.numNast(LE_EXPR),
			  getX100(nnd.numNast(LE_EXPR), total),
			  false);
  HTMLos.statisticRowX100("gt_expr",
			  nnd.numNast(GT_EXPR),
			  getX100(nnd.numNast(GT_EXPR), total),
			  false);
  HTMLos.statisticRowX100("ge_expr",
			  nnd.numNast(GE_EXPR),
			  getX100(nnd.numNast(GE_EXPR), total),
			  false);
  HTMLos.statisticRowX100("eq_expr",
			  nnd.numNast(EQ_EXPR),
			  getX100(nnd.numNast(EQ_EXPR), total),
			  false);
  HTMLos.statisticRowX100("ne_expr",
			  nnd.numNast(NE_EXPR),
			  getX100(nnd.numNast(NE_EXPR), total),
			  false);
  HTMLos.statisticRowX100("compound_expr",
			  nnd.numNast(COMPOUND_EXPR),
			  getX100(nnd.numNast(COMPOUND_EXPR), total),
			  false);
  HTMLos.statisticRowX100("component_ref",
			  nnd.numNast(COMPONENT_REF),
			  getX100(nnd.numNast(COMPONENT_REF), total),
			  false);
  // also INIT_EXPR
  HTMLos.statisticRowX100("modify_expr + init_expr",
			  nnd.numNast(MODIFY_EXPR),
			  getX100(nnd.numNast(MODIFY_EXPR), total),
		   false);
  HTMLos.statisticRowX100("array_ref",
			  nnd.numNast(ARRAY_REF),
			  getX100(nnd.numNast(ARRAY_REF), total),
			  false);
  HTMLos.statisticRowX100("call_expr",
			  nnd.numNast(CALL_EXPR),
			  getX100(nnd.numNast(CALL_EXPR), total),
			  false);
  HTMLos.statisticRowX100("cond_expr",
			  nnd.numNast(COND_EXPR),
			  getX100(nnd.numNast(COND_EXPR), total),
			  false);
  HTMLos.page << "</table>\n\n";
  
  HTMLos.page << "<table border=\"0\" width=\"600\" cellspacing=\"2\">";
  HTMLos.statisticRowX100( "Total *_EXPR :",
			   nnd.totalExprNastNode(),
			   getX100(nnd.totalExprNastNode(), total),
			   true);
  HTMLos.page << "</table>\n\n";
  
  
  // Othrs
  HTMLos.page << "<table border=\"0\" width=\"500\" cellspacing=\"2\">";
  HTMLos.statisticRowX100( "tree_list",
			   nnd.numNast(TREE_LIST),
			   getX100(nnd.numNast(TREE_LIST), total),
			   false);
  HTMLos.statisticRowX100( "identifier_node",
			   nnd.numNast(IDENTIFIER_NODE),
			   getX100(nnd.numNast(IDENTIFIER_NODE), total),
			   false);
  HTMLos.statisticRowX100( "case_label",
			   nnd.numNast(CASE_LABEL),
			   getX100(nnd.numNast(CASE_LABEL), total),
			   false);
  HTMLos.page << "</table>\n\n";

  HTMLos.page << "<table border=\"0\" width=\"600\" cellspacing=\"2\">";
  HTMLos.statisticRowX100( "Total Others :",
			   nnd.totalOthrNastNode(),
			   getX100(nnd.totalOthrNastNode(), total),
			   true);
  HTMLos.page << "</table>\n\n";
  
  HTMLos.page << "<br>\n\n";
  
  // Totals
  HTMLos.page << "<table border=\"0\" width=\"600\" cellspacing=\"2\">";
  HTMLos.statisticRow( "<b>Total NAST NODES :</b>",
		       nnd.totalNastNode(),true);
  HTMLos.page << "</table>\n\n";
  
  HTMLos.page << "<br>\n\n";
  
  return HTMLos;
}

HTMLofstream& operator<<(HTMLofstream& HTMLos, exprsList &eL) {
  exprData               *eData;    // informations to write
  exprsListIterator      p;         // browse the list
  int                    i;         // integer counter

  HTMLos.page << "<br><br>\n"
	      << "List of the expression into the function.<br>\n"
	      << "For each expression we list : <br>\n"
	      << "<ol>\n"
	      << "\t<li>The statistic about the operator used.\n"
	      << "\t<li>The list of the variables used\n"
	      << "</ol>\n";
  
  i = 0;
  p = eL.begin();
  while (p != eL.end()) {
    eData = *p;
    p++;
    
    HTMLos.page << "<b>Expression</b> number " << i << "<br>"
		<< "at line : " << eData->getLine() << "<br>"
		<< "statement : " << a2b::nast_code2string(eData->getPosName())
		<< "<br><br>";

    HTMLos.page << "Operator used : " << "<br>";
    HTMLos << *(eData->getExprStat()) << "<br>";
    
    HTMLos.page << "Variables used : " << "<br>";
    HTMLos << *(eData->getVarUsed()) << "<br>";

    i++;
  }

  return HTMLos;
}





