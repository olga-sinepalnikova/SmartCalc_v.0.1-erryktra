#include "../s21_smartcalc.h"

int is_next_symbol_valid(char *symbol) {
  while (*symbol == ' ') symbol++;
  if ((is_char_int(*symbol) != OK && *symbol != 'x' &&
       *symbol != ASCII_open_bracket && *symbol != 'p' &&
       strchr("cstal", *symbol) == NULL) ||
      *symbol == '\0') {
    return FAILURE;
  } else {
    return OK;
  }
}

int is_char_int(char symb) {
  return ((ASCII_0 <= symb && symb <= ASCII_9) || symb == 'x') ? OK : FAILURE;
}