// ========================================================================= //
//                                                                           //
// FIZ Interpreter                                                           //
// Author: Denis Luchkin-Zhou                                                //
//                                                                           //
// ========================================================================= //
#ifndef EVAL_H
#define EVAL_H

// Evaluate an expression in a particular environment (which provides values for the actual arguments)
int eval(struct TREE_NODE * node, int *env);

#endif
