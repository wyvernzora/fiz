#include "global.h"
#include "trace.h"
#include "func.h"
#include "ast.h"

AstNode::AstNode(NodeType t) {
  type  = t;
  argc  = 0;
  index = -1;
}

AstNode::~AstNode(void) {
  switch (type) {

    // LEAF: Identifier
    case ID_NODE: {
      TRACE("del ID_NODE [%s]\n", strValue);
      delete strValue; // Delete the identifier name
    }
    break;

    // LEAF: Number
    case NUMBER_NODE: {
      TRACE("del NUMBER_NODE [%d]\n", intValue);
    }
    break;

    case LIST_NODE: {
      TRACE("del LIST_NODE [%d]\n", argc);
      // Delete list contents
      for (int i = 0; i < argc; i++) { delete argv[i]; }
    }
    break;

    case FCALL_NODE: {
      TRACE("del FCALL_NODE [%s]\n", argv[0]->strValue);
      delete argv[0]; // Delete function name
      delete argv[1]; // Delete function arguments
    }
    break;
  }
}

void
AstNode::pushArg(AstNode *arg) {
  if (argc >= MAX_ARGUMENTS) {
    PANIC("Number of arguments exceeds %d.\n", MAX_ARGUMENTS);
  }
  argv[argc++] = arg;
}

int
AstNode::resolve(Func *fn) {
  switch (type) {

    case FCALL_NODE: {
      AstNode  *args   = argv[1];

      // Resolve arguments
      for (int i = 0; i < args -> argc; i++)
        if (!args -> argv[i] -> resolve(fn)) return 0;

      return 1;
    }

    case ID_NODE: {
      int   index = -1;
      char *name  = strValue;

      // Find the argument if there is a custom function
      if (fn) {
        for (int i = 0; i < fn->argc; i++) {
          if (!strcmp(fn->argv[i], name)) {
            index = i;
            break;
          }
        }
      }

      // Variable not found.. sad panda (Ｔ▽Ｔ)
      if (index < 0) {
        WARN("Variable '%s' is undefined.\n", name);
        return 0;
      }

      this->index = index;
      return 1;
    }

    default: return 1;
  }
}

int
AstNode::eval(int* env) {
  switch (type) {

    case NUMBER_NODE: return intValue;

    case ID_NODE: return env[index];

    case FCALL_NODE: {
      char      *name =      argv[0]->strValue;
      int        count =     argv[1]->argc;
      AstNode  **arguments = argv[1]->argv;

      Func* fn = functions -> find(name);
      if (!fn) {
        PANIC("Function '%s' is undefined.\n", argv[0] -> strValue);
      }
      func = fn;

      // Check the number of args
      if (count != fn -> argc) {
        PANIC("%s expects %d argument%s but got %d.\n",
          fn->name, fn->argc, (fn->argc == 1 ? "" : "s"), count);
      }

      return func -> call(arguments, count, env);
    }

    default: PANIC("Unexpected node type during evaluation.\n");

  }
}
