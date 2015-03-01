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
#include "fiz.h"

// ------------------------------------------------------------------------- //
// Handles the YACC errors.                                                  //
// ------------------------------------------------------------------------- //
void yyerror(const char * s) { throw FIZ_SYNTAX_ERROR; }
