#include "../s21_smartcalc.h"
#define ann_credit 1
#define diff_credit 2

double get_monthly_payment_ann(double credit_sum, double annual_rate,
                               int payments_count) {
  double monthly_rate = (annual_rate / 12) / 100;
  double ratio = 0.0;
  double part = pow((1 + monthly_rate), payments_count);
  double numerator = monthly_rate * part;
  double denominator = part - 1;
  ratio = numerator / denominator;

  return credit_sum * ratio;
}

double get_monthly_payment_diff(double credit_sum, double annual_rate,
                                int payments_count, double debt_left) {
  double main_debt_part, percents_sum = 0.0;
  main_debt_part = credit_sum / payments_count;
  percents_sum = debt_left * (annual_rate / 100) * 30 / 365;
  // 100 - перевод из % в дробь, 30 - усреднённое кол-во дней, 365 - кол-во дней
  // в году
  return main_debt_part + percents_sum;
}
