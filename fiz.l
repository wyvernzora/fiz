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

#include "ast.h"
#include "y.tab.h"
#include "fiz.h"
#include "parser.h"

int loading;
%}

%x incl
%%

"import"                      { BEGIN(incl); }

<incl>[ \t]*                  {  }
<incl>[^ \t\n]+               {
                                // Open file, throw if failed
                                yyin = fopen(yytext, "r");
                                if (!yyin) { throw FIZ_INCLUDE_FAIL; }
                                loading = 1;

                                // Make parser process it
                                yypush_buffer_state(yy_create_buffer(yyin, YY_BUF_SIZE));
                                BEGIN(INITIAL);
                              }
<<EOF>>                       {
                                yypop_buffer_state();
                                loading = 0;
                                if (!YY_CURRENT_BUFFER) { yyterminate(); }
                                printf("\x1B[36mfiz> \x1B[0m");
                              }

"define"                      { return DEF; }

[_a-zA-Z][_a-zA-Z0-9]*        {
                                yylval.str_val = strdup(yytext);
                                return ID;
                              }

"("                           { return OP; }

")"                           { return CP; }

0|[1-9][0-9]*                 {
                              	yylval.num_val = atoi(yytext);
                              	return NUM;
                              }

[ \t\n] 	                    { /* Discard spaces, tabs, and new lines */ }

;.*                           { /* Discard comments */ }

".*$"	                        { throw FIZ_SYNTAX_ERROR; }
