// ========================================================================= //
// Builtin function handlers.                                                //
// ========================================================================= //
#include "builtins.h"

int fiz_inc(NodeList *args, int *env) {
  int value = args -> at(0) -> eval(env);
  return value + 1;
}
int fiz_dec(NodeList *args, int *env) {
  int value = args -> at(0) -> eval(env);
  if (value <= 0) { throw FIZ_DEC_ZERO; }
  return value - 1;
}
int fiz_ifz(NodeList *args, int *env) {
  int cond = args -> at(0) -> eval(env);
  printf("cond = %d\n", cond);
  int value;
  if (!cond) {
    value = args -> at(1) -> eval(env);
  } else {
    value = args -> at(2) -> eval(env);
  }
  printf("value = %d\n", value);
  return value;
}
int fiz_hlt(NodeList *args, int *env) {
  throw FIZ_HALT;
}
