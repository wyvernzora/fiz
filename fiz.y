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
%token INC DEC IFZ HALT DEFINE OPENPAR CLOSEPAR

// This defines what value will be returned after parsing an expression
%type <node_val> expr
%type <node_val> identifier
%type <node_val> identifiers
//%type <node_val> fcall

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

  int err_value = 0;
%}

/********************************************************************************
 * Beginning of Section 3: Grammar production rule definitions and associated   *
 *  C code                                                                      *
 ********************************************************************************/
%%

  statements: statement | statement statements;

  identifier:
    IDENTIFIER {
      AstNode *node = (AstNode*) malloc(sizeof(AstNode));
      node -> type = ID_NODE;
      node -> strValue = strdup($1);
      $$ = node;
    }
  ;

  identifiers:
    identifier {
      AstNode *node = (AstNode*) malloc(sizeof(AstNode));
      node -> type = IDS_NODE;
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

  statement:
    OPENPAR DEFINE OPENPAR identifier identifiers CLOSEPAR expr CLOSEPAR {

      printf("func = %s; args = [", $4 -> strValue);
      for (int i = 0; i < $5->argc; i++) {
        printf("%s ", $5 -> argv[i] -> strValue);
      }
      printf("]\n");

      prompt();
    } |
    expr {
      err_value = 0;
      resolve($1, NULL);

      if (err_value == 0) {
        printf ("%d\n", eval($1, NULL));
      }

      prompt();
    }
  ;

  expr:
    OPENPAR INC expr CLOSEPAR {
      AstNode *node = (AstNode*) malloc(sizeof(AstNode));
      node -> type = INC_NODE;
      node -> argv[0] = $3;
      $$ = node;
    } |
    OPENPAR DEC expr CLOSEPAR {
      AstNode *node = (AstNode*) malloc(sizeof(AstNode));
      node -> type = DEC_NODE;
      node -> argv[0] = $3;
      $$ = node;
    } |
    OPENPAR IFZ expr expr expr CLOSEPAR {
      AstNode *node = (AstNode*) malloc(sizeof(AstNode));
      node -> type = IFZ_NODE;
      node -> argv[0] = $3;
      node -> argv[1] = $4;
      node -> argv[2] = $5;
      $$ = node;
    } |
    OPENPAR HALT CLOSEPAR {
      AstNode *node = (AstNode*) malloc(sizeof(AstNode));
      node -> type = HALT_NODE;
      $$ = node;
    } |
    IDENTIFIER {
      AstNode *node = (AstNode*) malloc(sizeof(AstNode));
      node -> type = VAR_NODE;
      node -> strValue = strdup($1);
      $$ = node;
    } |
    NUMBER {
      AstNode *node = (AstNode*) malloc(sizeof(AstNode));
      node -> type = NUMBER_NODE;
      node -> intValue = $1;
      $$ = node;
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
  if (!verbose) { printf("fiz> "); }
}

int main(int argc, char *argv[]) {

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-v") == 0) { verbose = 1; }
  }

  prompt();
  yyparse();
  return 0;
}
