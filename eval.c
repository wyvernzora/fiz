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

  case INC_NODE: {
    return eval(node->argv[0], env) + 1;
  }

  case DEC_NODE: {
    int num = eval(node->argv[0], env);
    if (num == 0) {
      fprintf(stderr, "Attempt to (dec 0).");
      exit(1);
    }
    return num - 1;
  }

  case IFZ_NODE: {
    int cond = eval(node -> argv[0], env);
    if (!cond) {
      return eval(node -> argv[1], env);
    } else {
      return eval(node -> argv[2], env);
    }
  }

  case HALT_NODE: {
    fprintf(stderr, "Halted.");
    exit(1);
  }

  case VAR_NODE: {
    printf("eval(VAR) -> %s\n", node->strValue);
    printf("VAR node value can not yet be retrieved\n");
    exit(1);
  }

  case FCALL_NODE: {
    printf("call(FUNC) -> %s\n", node->strValue);
    printf("Function calls not implemented yet.\n");
    exit(1);
  }

  default: {
    fprintf(stderr, "Unexpected node type during evaluation.\n");
    exit(1);
  }
}
}
