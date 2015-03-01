/* ------------------------------------------------------------------------- //
//                                                                           //
// CS252 Lab02 - FIZ Interpreter                                             //
// Copyright © 2015 Denis Luchkin-Zhou                                       //
//                                                                           //
// fiz.y                                                                     //
// Parser rules for the FIZ interpreter.                                     //
//                                                                           //
// ------------------------------------------------------------------------- */

%{
 #include "ast.h"
 #include "parser.h"
%}

%token OP
%token CP
%token DEF

%token <str_val>   ID
%token <num_val>   NUM
%type  <node_val>  expr
%type  <node_list> exprs
%type  <id_list>   idlist

%union  {
  int        num_val;
  char      *str_val;
  IdList    *id_list;
  AstNode   *node_val;
  NodeList  *node_list;
}

%%

statements:
  statement | statement statements;

statement:
  OP DEF OP ID idlist CP expr CP  { Parser::define($4, $5, $7);   prompt(); } |
  expr                            { output(Parser::execute($1));  prompt(); } ;

idlist:
  ID idlist                       { $$ = Parser::id_list($1,   $2);         } |
  /* EMPTY */                     { $$ = Parser::id_list(NULL, NULL);       } ;

expr:
  OP ID exprs CP                  { $$ = new FcallNode($2, $3);             } |
  ID                              { $$ = new VariableNode($1);              } |
  NUM                             { $$ = new NumNode($1);                   } ;

exprs:
  expr exprs                      { $$ = Parser::expr_list($1,   $2);       } |
  /* EMPTY */                     { $$ = Parser::expr_list(NULL, NULL);     } ;

%%
