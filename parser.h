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

#include <vector>
#include "ast.h"

#define ST static

extern FILE *yyin;

typedef void (*PromptHandler)(void);
typedef void (*OutputHandler)(int);

class Parser {
private:
  ST PromptHandler _prompt;
  ST OutputHandler _output;


  ST void  output(int);

public:
  ST void  setInput(int);                      // Sets the parser input.
  ST int   getInput();                         // Gets input file descriptor.

  ST void  prompt();                           // Prints the prompt if tty.
  ST void  setPrompt(PromptHandler);           // Sets the prompt handler.
  ST void  setOutput(OutputHandler);           // Sets the output handler.

  ST void  define(char*, IdList*, AstNode*);   // Defines a function.
  ST int   execute(AstNode*);                  // Executes a statement.

  ST IdList*   id_list(char*, IdList*);        // Builds an ID list.
  ST NodeList* expr_list(AstNode*, NodeList*); // Builds an AST node list.
};

#endif
