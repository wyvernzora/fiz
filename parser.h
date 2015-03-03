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

extern FILE *fizin;

// ------------------------------------------------------------------------- //
// Shorthands for commonly used long type names.                             //
// ------------------------------------------------------------------------- //
typedef void (*PromptHandler)(void);
typedef void (*OutputHandler)(int);

// ------------------------------------------------------------------------- //
// Called to start the YACC parsing process.                                 //
// ------------------------------------------------------------------------- //
int  fizlex();

// ------------------------------------------------------------------------- //
// Handles the YACC errors.                                                  //
// ------------------------------------------------------------------------- //
void fizerror(const char*);

// ------------------------------------------------------------------------- //
// YACC parse function definition.                                           //
// ------------------------------------------------------------------------- //
void fizrestart(FILE*);
int  fizparse(void);

class Parser {
private:
  ST PromptHandler _prompt;                    // Prompt handler.
  ST OutputHandler _output;                    // Output handler.

  ST void  output(int);                        // Internal output handler.

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
