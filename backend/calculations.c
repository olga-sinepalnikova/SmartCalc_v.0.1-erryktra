#include "../s21_smartcalc.h"

double calculation(node **nums_stack, node **ops_stack) {
  int code = OK;
  double a = pop(nums_stack).l_value.value;
  lexem operation = pop(ops_stack);
  lexem temp;
  if (operation.priority < 5) {
    double b = pop(nums_stack).l_value.value;
    if (operation.type == 'm') {
      temp.l_value.value = operation.l_value.binary_funciton(b, a);
    } else {
      temp.l_value.value = operation.l_value.binary_funciton(b, a);
    }
  } else {
    if (peek(ops_stack).type != '(')
      temp.l_value.value = operation.l_value.unary_funciton(a);
  }

  temp.priority = 0;
  temp.type = Number_or_X;
  // if (*nums_stack == NULL && *ops_stack != NULL) temp.l_value.value =
  // -INFINITY;
  if (isnan(temp.l_value.value) || temp.l_value.value == -INFINITY)
    return FAILURE;
  push(nums_stack, temp);
  return code;
}