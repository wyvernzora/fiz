// ========================================================================= //
//                                                                           //
// FIZ Interpreter                                                           //
// Author: Denis Luchkin-Zhou                                                //
//                                                                           //
// ========================================================================= //
#include "func.h"
#include "ast.h"

#ifndef RESOLVE_H
#define RESOLVE_H

// Resolve the usage of functions and arguments in an expression
void resolve(AstNode*, Func*);

#endif
