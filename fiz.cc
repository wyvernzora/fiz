// ------------------------------------------------------------------------- //
//                                                                           //
// CS252 Lab02 - FIZ Interpreter                                             //
// Copyright © 2015 Denis Luchkin-Zhou                                       //
//                                                                           //
// fiz.cc                                                                    //
// This file contains the logic for global functions, errors and public      //
// FIZ evaluation API.                                                       //
//                                                                           //
// ------------------------------------------------------------------------- //
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "fiz.h"
#include "func.h"

// ------------------------------------------------------------------------- //
// Handles the YACC errors.                                                  //
// ------------------------------------------------------------------------- //
void yyerror(const char * s) { throw FIZ_SYNTAX_ERROR; }

// ------------------------------------------------------------------------- //
// Prints an input prompt (only when in TTY mode).                           //
// ------------------------------------------------------------------------- //
void prompt() { if (isatty(0)) { printf("\x1B[1;36mfiz> \x1B[0m"); } }

// ------------------------------------------------------------------------- //
// Outputs the result of a signle FIZ statement.                             //
// ------------------------------------------------------------------------- //
void output(int i) {
  printf("%d\n", i);
}


// ------------------------------------------------------------------------- //
// Main program entry point (only when compiled as standalone executable).   //
// ------------------------------------------------------------------------- //
int main(int argc, char *argv[]) {

  // Initialize function registry
  FuncRegistry::init();

  // Parse the stream
  try {
    prompt();
    yyparse();
  }
  catch (FizError err) {
    fprintf(stderr, "[%d] %s\n", FIZ_ERRNO(err), FIZ_STRERR(err));
  }

  return 0;
}
