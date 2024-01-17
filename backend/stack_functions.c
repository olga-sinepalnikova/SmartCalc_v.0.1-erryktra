#include "../s21_smartcalc.h"

lexem pop(node **input) {
  if (*input != NULL) {
    node *temp = *input;
    lexem result = temp->data;
    // (*input)->size = temp->size - 1;
    *input = temp->next;
    free(temp);
    return result;
  }
  lexem error;
  error.priority = -1;
  return error;
}

lexem peek(node **input) {
  if (*input != NULL) {
    // node *temp = *input;
    lexem result = (*input)->data;
    // free(temp);
    return result;
  }
  lexem error;
  error.priority = -1;
  return error;
}

node push(node **input, lexem data) {
  node *new_stack = malloc(sizeof(node));
  if (new_stack != NULL) {
    new_stack->data = data;
    new_stack->next = *input;
    // new_stack->size = (*input)->size + 1;
    *input = new_stack;
  }
  return *new_stack;
}