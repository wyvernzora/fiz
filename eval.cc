#include "ast.h"
#include "func.h"
#include "eval.h"

//Evaluates an expression node
int eval(AstNode *node, int *env) {

  switch(node->type)
  {
    case NUMBER_NODE: {
      return node->intValue;
    }

    case FCALL_NODE: {
      char      *name = node->argv[0]->strValue;
      int        count = node->argv[1]->argc;
      AstNode  **arguments = node->argv[1]->argv;
      
      return call_function(name, arguments, count, env);
    }

    case ID_NODE: {
      return env[node->index];
    }

    default: {
      fprintf(stderr, "Unexpected node type during evaluation.\n");
      exit(1);
    }
  }
}
