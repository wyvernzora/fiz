/*
 * CS-252 Spring 2015
 * fiz.y: parser for the FIZ interpreter
 *
 * This parser compiles the following grammar:
 * (inc (inc 2))
 *
 */

/********************************************************************************
 * Beginning of Section 1: Definition of tokens and non-terminal in the grammar *
 ********************************************************************************/

// Tokens are defined here.
// The lexical analyzer, specified in fiz.l, will read input and generate a stream of tokens
// More tokens need to be added
%token <number_val> NUMBER
%token <string_val> IDENTIFIER
%token DEFINE
%token OPENPAR
%token CLOSEPAR

// This defines what value will be returned after parsing an expression
%type <node_val> expr
%type <node_val> exprs
%type <node_val> identifier
%type <node_val> identifiers

%union  {
  int    number_val;
  char   *string_val;
  struct TREE_NODE *node_val;
}

/********************************************************************************
 * Beginning of Section 2: C data type and global variable definitions to be    *
 *  included in the generated y.tab.c file                                      *
 ********************************************************************************/
%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "func.h"
  #include "ast.h"
  #include "resolve.h"
  #include "eval.h"

  void yyerror(const char * s);
  void prompt();
  int yylex();

  // Verbose mode switch
  int verbose = 0;
  int noprompt = 0;

  int err_value = 0;
%}

/********************************************************************************
 * Beginning of Section 3: Grammar production rule definitions and associated   *
 *  C code                                                                      *
 ********************************************************************************/
%%

  statements:
    statement | statement statements
  ;

  statement:
    OPENPAR DEFINE OPENPAR identifier CLOSEPAR expr CLOSEPAR {
      Func* fn = (Func*) malloc(sizeof(Func));
      fn->name = strdup($4 -> strValue);
      fn->argc = 0;
      resolve($6, NULL);
      fn->body = $6;
      def_function(fn);

      deleteNode($4);
      free(fn);

      if (verbose) { printf("func = %s; no-args\n", fn->name); }

      prompt();
    } |
    OPENPAR DEFINE OPENPAR identifier identifiers CLOSEPAR expr CLOSEPAR {
      Func* fn = (Func*) malloc(sizeof(Func));
      fn->name = strdup($4 -> strValue);
      fn->argc = $5 -> argc;

      if (verbose) { printf("func = %s; args = [", fn->name); }

      for (int i = 0; i < fn->argc; i++) {
        fn->argv[i] = strdup($5->argv[i]->strValue);
        if (verbose) { printf("%s ", fn->argv[i]); }
      }
      def_function(fn);

      deleteNode($4);
      deleteNode($5);
      free(fn);

      fn = find_function(fn->name);

      resolve($7, fn);
      fn->body = $7;

      if (verbose) { printf("]\n"); }

      prompt();
    } |
    expr {
      int success = resolve($1, NULL);

      if (success) {
        printf ("%d\n", eval($1, NULL));
      }
      deleteNode($1);

      prompt();
    }
  ;

  identifier:
    IDENTIFIER {
      AstNode *node = (AstNode*) malloc(sizeof(AstNode));
      node -> type = ID_NODE;
      node -> strValue = $1;
      $$ = node;
    }
  ;

  identifiers:
    identifier {
      AstNode *node = (AstNode*) malloc(sizeof(AstNode));
      node -> type = LIST_NODE;
      node -> argv[0] = $1;
      node -> argc = 1;
      $$ = node;
    } |
    identifiers identifier {
      if ($1->argc >= MAX_ARGUMENTS) {
        fprintf(stderr, "Number of arguments exceeds 10.\n");
        exit(1);
      }
      $1 -> argv[$1->argc++] = $2;
      $$ = $1;
    }
  ;

  expr:
    OPENPAR identifier CLOSEPAR {
      AstNode *node = (AstNode*) malloc(sizeof(AstNode));
      node -> type = FCALL_NODE;
      node -> argv[0] = $2;

      AstNode *argn = (AstNode*) malloc(sizeof(AstNode));
      argn -> type = LIST_NODE;
      argn -> argc = 0;

      node -> argv[1] = argn;
      $$ = node;
    } |
    OPENPAR identifier exprs CLOSEPAR {
      AstNode *node = (AstNode*) malloc(sizeof(AstNode));
      node -> type = FCALL_NODE;
      node -> argv[0] = $2;
      node -> argv[1] = $3;
      $$ = node;
    } |
    NUMBER {
      AstNode *node = (AstNode*) malloc(sizeof(AstNode));
      node -> type = NUMBER_NODE;
      node -> intValue = $1;
      $$ = node;
    } |
    identifier
  ;

  exprs:
    expr {
      AstNode *node = (AstNode*) malloc(sizeof(AstNode));
      node -> type = LIST_NODE;
      node -> argv[0] = $1;
      node -> argc = 1;
      $$ = node;

    } |
    exprs expr {
      if ($1->argc >= MAX_ARGUMENTS) {
        fprintf(stderr, "Number of arguments exceeds 10.\n");
        exit(1);
      }
      $1->argv[$1->argc++] = $2;
      $$ = $1;
    }
  ;
%%
/********************************************************************************
 * Beginning of Section 4: C functions to be included in the y.tab.c.           *
 ********************************************************************************/

void yyerror(const char * s) {
  fprintf(stderr,"%s", s);
}

void prompt() {
  if (!noprompt) { printf("fiz> "); }
}

int main(int argc, char *argv[]) {

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-v") == 0) { verbose = 1; }
    if (strcmp(argv[i], "-n") == 0) { noprompt = 1; }
  }

  prompt();
  yyparse();
  return 0;
}
