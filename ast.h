// ========================================================================= //
//                                                                           //
// FIZ Interpreter                                                           //
// Author: Denis Luchkin-Zhou                                                //
//                                                                           //
// ========================================================================= //
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef AST_H
#define AST_H

// Maximum number of arguments a function can have
#define MAX_ARGUMENTS 10

// Forward declaration of Func type
class Func;

// AST Node Types
typedef enum {
  LIST_NODE,   // corresponds to a list of random stuff
  ID_NODE,     // corresponds to an identifier
  FCALL_NODE,  // corresponds to a function call
  NUMBER_NODE
} NodeType;

// AST Node
class AstNode {
public:

  NodeType      type;                 // Node type
  int           argc;                 // Number of arguments

  union {
    int         index;                // Variable index
    Func*       func;                 // Function reference
  };

  union {
    AstNode    *argv[MAX_ARGUMENTS];  // All arguments
    char       *strValue;             // For ID_NODE
    int         intValue;             // For NUMBER_NODE
  };

  AstNode(NodeType);
  ~AstNode(void);

  void pushArg(AstNode*);
  int resolve(Func*);
  int eval(int*);
};

#endif
