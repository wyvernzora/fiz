/* ------------------------------------------------------------------------- //
//                                                                           //
// CS252 Lab02 - FIZ Interpreter                                             //
// Copyright © 2015 Denis Luchkin-Zhou                                       //
//                                                                           //
// fiz.l                                                                     //
// Lexical analyzer for the FIZ interpreter.                                 //
//                                                                           //
// ------------------------------------------------------------------------- */

%{
#include <stdio.h>
#include <string.h>

#include "ast/ast.h"
#include "y.tab.h"
#include "fiz/fiz.h"
#include "parser/parser.h"

int loading;
%}

%option noyywrap

%x incl
%%

"import"                      { BEGIN(incl); }

<incl>[ \t]*                  {  }
<incl>[^ \t\n]+               {
                                // Open file, throw if failed
                                fizin = fopen(fiztext, "r");
                                if (!fizin) { throw FIZ_INCLUDE_FAIL; }
                                loading = 1;

                                // Make parser process it
                                fizpush_buffer_state(fiz_create_buffer(fizin, YY_BUF_SIZE));
                                BEGIN(INITIAL);
                              }
<<EOF>>                       {
                                fizpop_buffer_state();
                                loading = 0;
                                if (!YY_CURRENT_BUFFER) { yyterminate(); }
                                printf("\x1B[36mfiz> \x1B[0m");
                              }

"define"                      { return DEF; }

[$][_a-zA-Z][_a-zA-Z0-9]*     {
                                fizlval.str_val = strdup(fiztext + 1);
                                return XID;
                              }

[_a-zA-Z][_a-zA-Z0-9]*        {
                                fizlval.str_val = strdup(fiztext);
                                return ID;
                              }

"("                           { return OP; }

")"                           { return CP; }

0|[1-9][0-9]*                 {
                                fizlval.num_val = atoi(fiztext);
                              	return NUM;
                              }

[ \t\n] 	                    { /* Discard spaces, tabs, and new lines */ }

;.*                           { /* Discard comments */ }

".*$"	                        { throw FIZ_SYNTAX_ERROR; }
