// ========================================================================= //
//                                                                           //
// FIZ Interpreter                                                           //
// Author: Denis Luchkin-Zhou                                                //
//                                                                           //
// ========================================================================= //
#include "ast.h"

#ifndef EVAL_H
#define EVAL_H

// Evaluate an expression in a particular environment (which provides values for the actual arguments)
int eval(AstNode*, int*);

#endif
