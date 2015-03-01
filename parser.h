// ------------------------------------------------------------------------- //
//                                                                           //
// CS252 Lab02 - FIZ Interpreter                                             //
// Copyright © 2015 Denis Luchkin-Zhou                                       //
//                                                                           //
// parser.h                                                                  //
// This file contains definitions for the Parser class that contains         //
// functions that take care of building the AST.                             //
//                                                                           //
// ------------------------------------------------------------------------- //
#ifndef PARSER_H_
#define PARSER_H_

#include "ast.h"

class Parser {
public:
  static void  define(char*, IdList*, AstNode*);   // Defines a function
  static int   execute(AstNode*);                  // Executes a statement

  static IdList*   id_list(char*, IdList*);        // Builds an ID list
  static NodeList* expr_list(AstNode*, NodeList*); // Builds an AST node list
};

#endif
