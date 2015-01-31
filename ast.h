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

// Allowed node types in the syntax tree; more need to be added for the full language
typedef enum {
 INC_NODE,    // corresponds to (inc exp)
 DEC_NODE,    // corresponds to (dec exp)
 IFZ_NODE,    // corresponds to (ifz exp exp exp)
 HALT_NODE,   // corresponds to (halt)
 DEF_NODE,    // corresponds to (define ...)
 IDS_NODE,    // corresponds to an identifier array
 ID_NODE,     // corresponds to an identifier
 FCALL_NODE,  // corresponds to a function call
 VAR_NODE,    // corresponds to a variable name
 NUMBER_NODE,
} NodeType;

// Below is the data type for a node in the syntax tree
typedef struct TREE_NODE {
 NodeType type;
 int argc;
 union {
   struct TREE_NODE *argv[MAX_ARGUMENTS]; // All arguments
   char*  strValue;                       // For ID_NODE
   int    arg_num;                        // Number of args
   int    intValue;                       // For NUMBER_NODE
 };
} AstNode;


#endif
