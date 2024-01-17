#include "../s21_smartcalc.h"

double add(double a, double b) { return a + b; }

double minus(double a, double b) { return a - b; }

double multiply(double a, double b) { return a * b; }

double division(double a, double b) {
  if (b != 0) {
    return a / b;
  } else {
    return -INFINITY;
  }
}