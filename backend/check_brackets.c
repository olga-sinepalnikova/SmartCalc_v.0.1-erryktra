#include "../s21_smartcalc.h"

int check_brackets(char *string) {
  int code = 0;
  int open_brackets_counter = 0;
  int close_brackets_counter = 0;
  for (char *symbol = string; *symbol != '\0'; symbol++) {
    char *temp = symbol;
    if (*symbol == ASCII_open_bracket && is_next_symbol_valid(temp++) == OK) {
      open_brackets_counter++;
    } else if (*symbol == ASCII_close_bracket) {
      close_brackets_counter++;
    }
  }
  if (open_brackets_counter != close_brackets_counter) {
    code = FAILURE;
  }
  return code;
}