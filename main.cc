// ------------------------------------------------------------------------- //
//                                                                           //
// CS252 Lab02 - FIZ Interpreter                                             //
// Copyright © 2015 Denis Luchkin-Zhou                                       //
//                                                                           //
// main.cc                                                                   //
// This file contains the main entry point for the standalone FIZ            //
// interpreter executable. This file is not included in LibFiz.              //
//                                                                           //
// ------------------------------------------------------------------------- //
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "fiz.h"
#include "func.h"
#include "parser.h"

void prompt(void);
void output(int);

// ------------------------------------------------------------------------- //
// Prints an input prompt (only when in TTY mode).                           //
// ------------------------------------------------------------------------- //
void prompt() { printf("\x1B[1;36mfiz> \x1B[0m"); }

// ------------------------------------------------------------------------- //
// Outputs the result of a signle FIZ statement.                             //
// ------------------------------------------------------------------------- //
void output(int i) { printf("%d\n", i); }

// ------------------------------------------------------------------------- //
// Main program entry point (only when compiled as standalone executable).   //
// ------------------------------------------------------------------------- //
int main(int argc, char *argv[]) {

  // Initialize
  FuncRegistry::init();
  Parser::setInput(0);
  Parser::setOutput(&output);
  Parser::setPrompt(&prompt);

  // Parse the stream
  try {
    Parser::prompt();
    yyparse();
  }
  catch (FizError err) {
    fprintf(stderr, "[%d] %s\n", FIZ_ERRNO(err), FIZ_STRERR(err));
    return 1;
  }

  return 0;
}
