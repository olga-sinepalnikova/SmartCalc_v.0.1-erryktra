#include "../s21_smartcalc.h"

double get_result(char *string, double x, int *code) {
  if (string == NULL || strlen(string) == 0) return -0;
  double result = 0;
  node *nums = NULL;
  node *ops = NULL;
  *code = parser(string, &nums, &ops, x);
  if (*code == OK) {
    result = pop(&nums).l_value.value;
    return result;
  } else {
    return -INFINITY;
  }
}