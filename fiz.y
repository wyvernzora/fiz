/*
 * CS-252 Spring 2015
 * fiz.y: parser for the FIZ interpreter
 *
 * This parser compiles the following grammar:
 * (inc (inc 2))
 *
 */

/********************************************************************************
  * Beginning of Section 1: C data type and global variable definitions to be    *
  *  included in the generated y.tab.c file                                      *
  ********************************************************************************/
 %{
   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include <unistd.h>
   #include "ast.h"
   #include "global.h"
   #include "func.h"
   #include "trace.h"

   #define YYMAXDEPTH 1000000

   void yyerror(const char * s);
   void prompt();
   int yylex();

   // Verbose mode switch
   int verbose = 0;
   int noprompt = 0;

   int err_value = 0;
 %}

/********************************************************************************
 * Beginning of Section 2: Definition of tokens and non-terminal in the grammar *
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
  int      number_val;
  char    *string_val;
  AstNode *node_val;
}

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

      #ifndef FUNC_ZERO_ARG
        WARN("Function definitions without arguments are not allowed.\n");
        PANIC("#define FUNC_NO_ARGS to enable this behavior.\n");
      #endif

      Func* fn = new Func($4 -> strValue);
      fn->argc = 0;
      $6->resolve(NULL);
      fn->body = $6;
      int success = functions -> reg(fn);

      if (!success) {
        delete fn;
        delete $6;
      }

      if (verbose) { printf("func = %s; no-args\n", fn->name); }

      delete $4;

      prompt();
    } |
    OPENPAR DEFINE OPENPAR identifier identifiers CLOSEPAR expr CLOSEPAR {
      Func* fn = new Func($4 -> strValue);
      fn->argc = $5 -> argc;

      if (verbose) { printf("func = %s; args = [", fn->name); }

      for (int i = 0; i < fn->argc; i++) {
        fn->argv[i] = strdup($5->argv[i]->strValue);
        if (verbose) { printf("%s ", fn->argv[i]); }
      }

      functions -> temporary = fn;
      if ($7 -> resolve(fn)) {
        fn -> body = $7;
        functions -> temporary = NULL;

        if (!functions -> reg(fn)) {
          WARN("Function '%s' already defined.\n", fn -> name);
          delete fn;
          delete $7;
        }

      }
      else {
        delete fn;
        delete $7;
      }

      delete $4;
      delete $5;

      if (verbose) { printf("]\n"); }

      prompt();
    } |
    expr {
      int success = $1 -> resolve(NULL);

      if (success) { success = $1 -> eval(NULL); }
      if (success >= 0) { printf ("%d\n", success); }
      delete $1;

      prompt();
    }
  ;

  identifier:
    IDENTIFIER {
      AstNode *node = new AstNode(ID_NODE);
      node -> strValue = $1;
      $$ = node;
    }
  ;

  identifiers:
    identifier {
      AstNode *node = new AstNode(LIST_NODE);
      node -> pushArg($1);
      $$ = node;
    } |
    identifiers identifier {
      $1 -> pushArg($2);
      $$ = $1;
    }
  ;

  expr:
    OPENPAR identifier CLOSEPAR {
      AstNode *node = new AstNode(FCALL_NODE);
      node -> argv[0] = $2;

      AstNode *argn = new AstNode(LIST_NODE);
      argn -> argc = 0;

      node -> argv[1] = argn;
      $$ = node;
    } |
    OPENPAR identifier exprs CLOSEPAR {
      AstNode *node = new AstNode(FCALL_NODE);
      node -> argv[0] = $2;
      node -> argv[1] = $3;
      $$ = node;
    } |
    NUMBER {
      AstNode *node = new AstNode(NUMBER_NODE);
      node -> intValue = $1;
      $$ = node;
    } |
    identifier
  ;

  exprs:
    expr {
      AstNode *node = new AstNode(LIST_NODE);
      node -> pushArg($1);
      $$ = node;
    } |
    exprs expr {
      $1 -> pushArg($2);
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
  if (!noprompt) { printf("\x1B[36mfiz> \x1B[0m"); }
}

int main(int argc, char *argv[]) {

  // Command line arguments
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-v") == 0) { verbose = 1; }
  }

  // Function Registry
  functions = new FuncRegistry();

  // Load builtin functions
  functions -> reg(new NativeFunc("inc",  1, &fiz_inc));
  functions -> reg(new NativeFunc("dec",  1, &fiz_dec));
  functions -> reg(new NativeFunc("ifz",  3, &fiz_ifz));
  functions -> reg(new NativeFunc("halt", 0, &fiz_halt));

  // Detect STDIN
  if (!isatty(fileno(stdin))) { noprompt = 1; }

  prompt();
  yyparse();
  return 0;
}
