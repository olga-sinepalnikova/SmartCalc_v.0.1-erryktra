#ifdef __cplusplus
extern "C" {
#endif
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define FAILURE 1
#define VALIDATION_ERROR 2

// Needed ascii symbols
#define ASCII_open_bracket 40
#define ASCII_close_bracket 41
#define ASCII_mult_sign 42
// all other operations (and .) lie in between, except ^ => 94
#define ASCII_divis_sign 47
#define ASCII_0 48
#define ASCII_9 57

#define M_PI 3.14159265358979323846

enum lexem_type {
  Number_or_X = 0,
  Arithmetics = 1,   // + - * /
  Trigonometry = 2,  // (a-) sin, cos, tg, ctg
  Logarithms = 3,    // log, ln
  Mod = 4,
  Power = 5,
  Sqare_root = 6
};

typedef union lexem_value {
  double value;
  double (*unary_funciton)(double);
  double (*binary_funciton)(double, double);
} lexem_value;

typedef struct lexem {
  lexem_value l_value;
  char type;
  int priority;
} lexem;

typedef struct node {
  lexem data;
  struct node *next;
  // size_t size;
} node;

lexem pop(node **input);
lexem peek(node **input);
node push(node **input, lexem data);

int validator(char *string);
int check_brackets(char *string);
int check_functions(char *string, int *shift);
int is_next_symbol_valid(char *symbol);
int is_char_int(char symb);

int parser(char *string, node **numbers_stack, node **operations_stack,
           double x);
double get_double(char *string, int *skip, int *code);
int detect_operation(char *symbol, lexem *current_lexem);
int detect_functions(char *symbol, lexem *current_lexem);

double add(double a, double b);
double minus(double a, double b);
double multiply(double a, double b);
double division(double a, double b);

double calculation(node **nums_stack, node **ops_stack);
double get_result(char *string, double x, int *code);

// for credit calculator
double get_monthly_payment_ann(double credit_sum, double annual_rate,
                               int payments_count);
double get_monthly_payment_diff(double credit_sum, double annual_rate,
                                int payments_count, double debt_left);

#ifdef __cplusplus
}
#endif