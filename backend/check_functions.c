#include "../s21_smartcalc.h"

int check_functions(char *string, int *shift) {
  *shift = 0;
  int code = OK;
  int length_2 = 2;
  int length_3 = 3;
  int length_4 = 4;
  int length_5 = 5;
  if (*string == 'c' && strncmp(string, "cos(", length_4) == 0) {
    *shift = length_3;
  } else if (*string == 's') {
    if (strncmp(string, "sin(", length_4) == 0) {
      *shift = length_3;
    }
    if (strncmp(string, "sqrt(", length_5) == 0) {
      *shift = length_4;
    }
  } else if (*string == 't' && strncmp(string, "tan(", length_4) == 0) {
    *shift = length_3;
  } else if (*string == 'a') {
    if (strncmp(string, "acos(", length_5) == 0 ||
        strncmp(string, "asin(", length_5) == 0 ||
        strncmp(string, "atan(", length_5) == 0) {
      *shift = length_4;
    }
  } else if (*string == 'l') {
    if (strncmp(string, "ln(", length_3) == 0) {
      *shift = length_2;
    }
    if (strncmp(string, "log(", length_4) == 0) {
      *shift = length_3;
    }
  } else {
    code = FAILURE;
  }
  if (*shift == 0) {
    code = FAILURE;
  }
  char *temp = string + *shift + 1;

  if (is_next_symbol_valid(&temp[0]) != OK &&
      strchr("cstal", temp[0]) == NULL) {
    code = FAILURE;
  }
  return code;
}