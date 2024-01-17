#include "../s21_smartcalc.h"

int validator(char* string) {
  int code = OK;
  for (char* symbol = string; *symbol != '\0' && code == OK; symbol++) {
    while (*symbol == ' ') symbol++;
    char* temp = symbol;
    if (ASCII_mult_sign <= *symbol && *symbol <= ASCII_divis_sign) {
      ++temp;
      code = is_next_symbol_valid(temp);
    }
    if (*symbol == ASCII_open_bracket && code == OK) {
      code = check_brackets(string);
      temp++;
      if (*temp != '-' && *temp != '+' && is_next_symbol_valid(temp))
        code = FAILURE;
    }
    if (*symbol == ASCII_close_bracket && code == OK) {
      code = check_brackets(string);
      temp++;
      if ((ASCII_mult_sign > *temp || *temp > ASCII_divis_sign) &&
          *temp != '^' && *temp != '\0') {
        code = FAILURE;
      }
    }
    // cstal is for Cos, Sin or Sqrt, Tan, Asin/cos/tan, Ln/Log
    if (strchr("cstal", *symbol) != NULL && code == OK) {
      int shift_by = 0;
      code = check_functions(symbol, &shift_by);
      symbol += shift_by - 1;
    }
    temp = symbol;
    if (is_next_symbol_valid(symbol) && *temp++ == 'm' && code == OK) {
      if (strncmp(temp, "mod", 3) != 0) {
        code = FAILURE;
      }
      if (code == OK) {
        temp += 3;
        code = is_char_int(*temp);
      }
    }
  }
  if (code == FAILURE) code = VALIDATION_ERROR;
  return code;
}
