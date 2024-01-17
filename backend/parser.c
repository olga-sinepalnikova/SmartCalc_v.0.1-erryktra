#include "../s21_smartcalc.h"

int parser(char *string, node **numbers_stack, node **operations_stack,
           double x) {
  int code = OK;
  int skip = 0;
  lexem current_lexem;
  code = validator(string);
  if (*string == '-') {
    current_lexem.type = Number_or_X;
    current_lexem.l_value.value = 0;
    current_lexem.priority = 0;
    push(numbers_stack, current_lexem);
  }
  for (char *symbol = string; *symbol != '\0' && code == OK; symbol++) {
    while (*symbol == ' ') symbol++;
    if (is_char_int(*symbol) == OK) {
      if (*symbol == 'x') {
        current_lexem.l_value.value = x;
      } else {
        current_lexem.l_value.value = get_double(symbol, &skip, &code);
      }
      current_lexem.type = Number_or_X;
      current_lexem.priority = 0;
      push(numbers_stack, current_lexem);
      symbol += skip;
      continue;
    }
    if (*symbol == 'p') {
      symbol++;
      if (*symbol == 'i') {
        current_lexem.l_value.value = M_PI;
        current_lexem.type = Number_or_X;
        current_lexem.priority = 0;
        push(numbers_stack, current_lexem);
        continue;
      } else {
        symbol--;
        code = FAILURE;
      }
    }
    skip = detect_operation(symbol, &current_lexem);
    if (skip < 0) code = FAILURE;
    symbol += skip;
    if (*symbol == '(') {
      char *temp = symbol;
      temp++;
      if (*temp == '-') {
        lexem extra_zero;
        extra_zero.type = Number_or_X;
        extra_zero.l_value.value = 0;
        extra_zero.priority = 0;
        push(numbers_stack, extra_zero);
      }
      push(operations_stack, current_lexem);
      continue;
    }
    if (*operations_stack != NULL && current_lexem.type != Number_or_X &&
        code == OK) {
      lexem prev_operation = peek(operations_stack);
      if (current_lexem.priority <= prev_operation.priority) {
        calculation(numbers_stack, operations_stack);
      }
    }
    if (*symbol == ')') {
      while (peek(operations_stack).type != '(' && code == OK) {
        calculation(numbers_stack, operations_stack);
      }
      pop(operations_stack);
      continue;
    }
    push(operations_stack, current_lexem);
  }
  while (*operations_stack != NULL && code == OK) {
    code = calculation(numbers_stack, operations_stack);
  }
  return code;
}

double get_double(char *string, int *skip, int *code) {
  char *temp_str = calloc(sizeof(char), strlen(string));
  char *symbol = string;
  int counter = 0;
  int dots_count = 0;
  while ((is_char_int(*symbol) == OK || *symbol == '.') && dots_count < 2) {
    if (*symbol == '.') {
      dots_count++;
    }
    strncat(temp_str, symbol, 1);
    symbol++;
    counter++;
  }
  if (dots_count < 2) {
    double result = atof(temp_str);
    *skip = counter - 1;
    free(temp_str);
    return result;
  } else {
    *code = FAILURE;
    return -INFINITY;
  }
}