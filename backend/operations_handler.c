#include "../s21_smartcalc.h"

int detect_operation(char *symbol, lexem *current_lexem) {
  int skip = 0;
  switch (*symbol) {
    case '+':
      current_lexem->l_value.binary_funciton = &add;
      current_lexem->type = '+';
      current_lexem->priority = 1;
      break;
    case '-':
      current_lexem->l_value.binary_funciton = &minus;
      current_lexem->type = '-';
      current_lexem->priority = 1;
      break;
    case '*':
      current_lexem->l_value.binary_funciton = &multiply;
      current_lexem->type = '*';
      current_lexem->priority = 2;
      break;
    case '/':
      current_lexem->l_value.binary_funciton = &division;
      current_lexem->type = '/';
      current_lexem->priority = 2;
      break;
    case '(':
      current_lexem->l_value.value = -666;
      current_lexem->type = '(';
      current_lexem->priority = 0;
      break;
    case '^':
      current_lexem->l_value.binary_funciton = &pow;
      current_lexem->type = '^';
      current_lexem->priority = 3;
      break;
    case ')':
      break;
    default:
      skip = -1;
      break;
  }
  if (strchr("cstalm", *symbol) != NULL) {
    skip = detect_functions(symbol, current_lexem);
  }
  return skip;
}

int detect_functions(char *symbol, lexem *current_lexem) {
  int skip = -1;
  if (*symbol == 's') {
    if (strncmp(symbol, "sin(", 4) == 0) {
      current_lexem->l_value.unary_funciton = &sin;
      current_lexem->type = 's';
      skip = 2;
    } else if (strncmp(symbol, "sqrt(", 5) == 0) {
      current_lexem->l_value.unary_funciton = &sqrt;
      current_lexem->type = 'S';
      skip = 3;
    }
  } else if (*symbol == 'c' && strncmp(symbol, "cos(", 4) == 0) {
    current_lexem->l_value.unary_funciton = &cos;
    current_lexem->type = 'c';
    skip = 2;
  } else if (*symbol == 't' && strncmp(symbol, "tan(", 4) == 0) {
    current_lexem->l_value.unary_funciton = &tan;
    current_lexem->type = 't';
    skip = 2;
  } else if (*symbol == 'l') {
    if (strncmp(symbol, "ln(", 3) == 0) {
      current_lexem->l_value.unary_funciton = &log10;
      current_lexem->type = 'l';
      skip = 1;
    } else if (strncmp(symbol, "log(", 4) == 0) {
      current_lexem->l_value.unary_funciton = &log;
      current_lexem->type = 'L';
      skip = 2;
    }
  } else if (*symbol == 'a') {
    if (strncmp(symbol, "acos(", 5) == 0) {
      current_lexem->l_value.unary_funciton = &acos;
      current_lexem->type = 'C';
    } else if (strncmp(symbol, "asin(", 5) == 0) {
      current_lexem->l_value.unary_funciton = &asin;
      current_lexem->type = 'A';
    } else if (strncmp(symbol, "atan(", 5) == 0) {
      current_lexem->l_value.unary_funciton = &atan;
      current_lexem->type = 'T';
    }
    skip = 3;
  } else if (*symbol == 'm') {
    if (strncmp(symbol, "mod", 3) == 0) {
      current_lexem->l_value.binary_funciton = &fmod;
      current_lexem->priority = 2;
      current_lexem->type = 'm';
      skip = 2;
    }
  }

  if (skip >= 0 && *symbol != 'm') current_lexem->priority = 5;
  return skip;
}