// ========================================================================= //
// Builtin function handlers.                                                //
// ========================================================================= //
#include "builtins.h"
#include "ast/num.h"
#include "fiz/fiz.h"

AstNode* fiz_inc(NodeList *args, AstNode *env[]) {
  NumNode *result = dynamic_cast<NumNode*>(args -> at(0) -> eval(env));
  if (!result) { throw FIZ_BAD_TYPE; }
  int value = result -> value + 1;
  delete result;
  return new NumNode(value);
}
AstNode* fiz_dec(NodeList *args, AstNode *env[]) {
  NumNode *result = dynamic_cast<NumNode*>(args -> at(0) -> eval(env));
  if (!result) { throw FIZ_BAD_TYPE; }
  int value = result -> value - 1;
  if (value < 0) { throw FIZ_DEC_ZERO; }
  delete result;
  return new NumNode(value);
}
AstNode* fiz_ifz(NodeList *args, AstNode *env[]) {
  NumNode *cond = dynamic_cast<NumNode*>(args -> at(0) -> eval(env));
  if (!cond) { throw FIZ_BAD_TYPE; }
  AstNode *value;
  if (!cond -> value) {
    value = args -> at(1) -> eval(env);
  } else {
    value = args -> at(2) -> eval(env);
  }
  return value;
}
AstNode* fiz_hlt(NodeList *args, AstNode *env[]) {
  throw FIZ_HALT;
}
