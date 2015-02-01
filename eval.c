#include "ast.h"
#include "func.h"
#include "eval.h"

//Evaluates an expression node
int eval(struct TREE_NODE * node, int *env) {

  switch(node->type)
  {
    case NUMBER_NODE: {
      return node->intValue;
    }

    case FCALL_NODE: {
      return call_function(node->argv[0]->strValue, node->argv[1]->argv, node->argv[1]->argc, env);
    }

    case ID_NODE: {
      return env[node->argc];
    }

    default: {
      fprintf(stderr, "Unexpected node type during evaluation.\n");
      exit(1);
    }
  }
}
