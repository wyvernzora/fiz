// ------------------------------------------------------------------------- //
//                                                                           //
// CS252 Lab02 - FIZ Interpreter                                             //
// Copyright © 2015 Denis Luchkin-Zhou                                       //
//                                                                           //
// parser.cc                                                                 //
// This file contains the logic for the Parser class that contains           //
// functions that take care of building the AST.                             //
//                                                                           //
// ------------------------------------------------------------------------- //
#include <stdlib.h>
#include <stdio.h>

#include "fiz.h"
#include "ast.h"
#include "func.h"
#include "parser.h"


// ------------------------------------------------------------------------- //
// Defines a FIZ-scripted function.                                          //
// ------------------------------------------------------------------------- //
void Parser::define(char *name, IdList *args, AstNode *body) {
  UserFunc *fn = new UserFunc(name, args, body);
  // Try to register the function
  if (!FuncRegistry::reg(fn)) {
    delete fn;
    throw FIZ_DUP_FUNC;
  }
  // Resolve the function
  fn -> body -> resolve(fn);
}

// ------------------------------------------------------------------------- //
// Execute a FIZ statement.                                                  //
// ------------------------------------------------------------------------- //
int Parser::execute(AstNode *expr) {
  expr -> resolve(NULL);
  int i = expr -> eval(NULL);
  delete expr;
  return i;
}

// ------------------------------------------------------------------------- //
// Builds an expression list. If list is null, create an empty one.          //
// ------------------------------------------------------------------------- //
NodeList* Parser::expr_list(AstNode *arg, NodeList *list) {
  if (!list) { list = new NodeList();   }
  if (arg)   { list -> push_front(arg); }
  return list;
}

// ------------------------------------------------------------------------- //
// Builds an ID list. If list is null, create an empty one.                  //
// ------------------------------------------------------------------------- //
IdList* Parser::id_list(char *arg, IdList *list) {
  if (!list) { list = new IdList(); }
  if (arg)   { list -> push_front(arg); }
  return list;
}
