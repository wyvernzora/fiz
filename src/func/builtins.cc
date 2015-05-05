// ========================================================================= //
// Builtin function handlers.                                                //
// ========================================================================= //
#include "builtins.h"
#include "ast/list.h"
#include "ast/num.h"
#include "fiz/fiz.h"

#define ARGS NodeList *args, AstNode *env[]

AstNode* fiz_inc(ARGS) {
  NumNode *result = dynamic_cast<NumNode*>(args -> at(0) -> eval(env));
  if (!result) { throw FIZ_BAD_TYPE; }
  result -> value += 1;
  return result;
}
AstNode* fiz_dec(ARGS) {
  NumNode *result = dynamic_cast<NumNode*>(args -> at(0) -> eval(env));
  if (!result) { throw FIZ_BAD_TYPE; }
  result -> value -= 1;
  if (result -> value < 0) { throw FIZ_DEC_ZERO; }
  return result;
}
AstNode* fiz_ifz(ARGS) {
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
AstNode* fiz_hlt(ARGS) {
  throw FIZ_HALT;
}

AstNode* flip_list(ARGS) {
  AstNode  *arg0 = args -> at(0) -> eval(env);
  ListNode *arg1 = dynamic_cast<ListNode*>(args -> at(1) -> eval(env));
  if (!arg0 || !arg1) { throw FIZ_BAD_TYPE; }

  arg1 -> argv -> push_front(arg0);
  return arg1;
}
AstNode* flip_head(ARGS) {
  ListNode *arg0 = dynamic_cast<ListNode*>(args -> at(0) -> eval(env));
  if (!arg0) { throw FIZ_BAD_TYPE; }
  if (arg0 -> argv -> empty()) { throw FIZ_EMPTY_LIST; }

  return arg0 -> argv -> at(0);
}
AstNode* flip_tail(ARGS) {
  ListNode *arg0 = dynamic_cast<ListNode*>(args -> at(0) -> eval(env));
  if (!arg0) { throw FIZ_BAD_TYPE; }
  if (arg0 -> argv -> empty()) { throw FIZ_EMPTY_LIST; }

  AstNode* head = arg0 -> argv -> front();
  arg0 -> argv -> pop_front();
  delete head;

  return arg0;
}
AstNode* flip_ife(ARGS)  {
  ListNode *arg0 = dynamic_cast<ListNode*>(args -> at(0) -> eval(env));
  if (!arg0) { throw FIZ_BAD_TYPE; }
  AstNode *value;
  if (arg0 -> argv -> empty()) {
    value = args -> at(1) -> eval(env);
  } else {
    value = args -> at(2) -> eval(env);
  }
  return value;
}
