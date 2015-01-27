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
%token INC OPENPAR CLOSEPAR

// This defines what value will be returned after parsing an expression
%type <node_val> expr 

%union	{
		char   *string_val;				// Needed when identifier is used
		int		number_val;
		struct TREE_NODE *node_val;
}

%{
/********************************************************************************
 * Beginning of Section 2: C data type and global variable definitions to be    *
 *  included in the generated y.tab.c file                                      *
 ********************************************************************************/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char * s);
void prompt();
int yylex();

// Maximum number of function definitions the interpreter allow
#define MAX_FUNCTIONS 1000

// Maximum number of arguments a function can have
#define MAX_ARGUMENTS 10


// Allowed node types in the syntax tree; more need to be added for the full language
enum NODE_TYPE
{
	INC_NODE,		// corresponds to (inc exp)
	NUMBER_NODE,	
};

// Below is the data type for a node in the syntax tree
struct TREE_NODE
{
	enum NODE_TYPE type;
	union {
		struct TREE_NODE *first_arg;		// For INC_NODE and DEC_NODE
		int    intValue;					// For NUMBER_NODE
		// Other node types need to be added
	};
};

// Information we maintain for each defined function
struct FUNC_DECL	
{
	char *name;				// Function name
						    // Other information needs to be added
};

struct FUNC_DECL functions[MAX_FUNCTIONS];
int numFuncs;

int err_value = 0;

struct FUNC_DECL * find_function(char *name);

// Resolve the usage of functions and arguments in an expression
void resolve(struct TREE_NODE *node, struct FUNC_DECL *cf);

// Evaluate an expression in a particular environment (which provides values for the actual arguments)
int eval(struct TREE_NODE * node, int *env);

%}

%%
/********************************************************************************
 * Beginning of Section 3: Grammar production rule definitions and associated   *
 *  C code                                                                      *
 ********************************************************************************/ 

statements:
 statement 
|
 statement statements
;

statement:
  expr
  {
	err_value = 0;
	resolve($1, NULL);
	if (err_value == 0) {
		printf ("%d\n", eval($1, NULL)); 
	}
	prompt();
  }
;

expr: 
  OPENPAR INC expr CLOSEPAR
    {   
		struct TREE_NODE * node = (struct TREE_NODE *) malloc(sizeof(struct TREE_NODE));
		node -> type = INC_NODE;
		node -> first_arg = $3;
		$$ = node;    
	}
|
  NUMBER
  {
		struct TREE_NODE * node = (struct TREE_NODE *) malloc(sizeof(struct TREE_NODE));
		node -> type = NUMBER_NODE;
		node -> intValue = $1;
		$$ = node;
  }
;

%%
/********************************************************************************
 * Beginning of Section 4: C functions to be included in the y.tab.c.           *
 ********************************************************************************/ 

struct FUNC_DECL * find_function(char *name)
{
    int i;
	for (i=0; i<numFuncs; i++) {
		if (! strcmp(functions[i].name, name))
			return &functions[i];
	}
	return NULL;
}

void resolve(struct TREE_NODE *node, struct FUNC_DECL *cf)
{
	switch(node->type)
	{
		case INC_NODE:
			resolve(node->first_arg, cf);
			return;
	}
	return;
}

//Evaluates an expression node
int eval(struct TREE_NODE * node, int *env)
{

	switch(node->type)
	{
		case NUMBER_NODE:
			return node->intValue;

		case INC_NODE:
			return eval(node->first_arg, env) + 1;
			
	}
	printf("Unexpected node type during evaluation.\n");
	exit(1);
}


void yyerror(const char * s)
{
	fprintf(stderr,"%s", s);
}

void prompt()
{
    printf("fiz> ");
}

main()
{
    prompt();
    yyparse();
    return 0;
}
