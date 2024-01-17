#include <check.h>

#include "../s21_smartcalc.h"

START_TEST(validator_test) {
  char *expression = "(2*444)-cos(pi)^5";
  ck_assert_int_eq(OK, validator(expression));
}

START_TEST(validator_test_2) {
  char *expression = "2*-+44";
  ck_assert_int_eq(VALIDATION_ERROR, validator(expression));
}

START_TEST(validator_test_3) {
  char *expression = "tan(pi) + atan(3*pi)";
  ck_assert_int_eq(VALIDATION_ERROR, validator(expression));
}

START_TEST(get_result_1) {
  char *expression = "4-2";
  int code = 0;
  ck_assert_int_eq(2, get_result(expression, 0, &code));
  ck_assert_int_eq(OK, code);
}

START_TEST(get_result_2) {
  char *expression = "(7838-43+73^2) * cos(pi/2)   / 0";
  int code = 0;
  get_result(expression, 0, &code);
  ck_assert_int_eq(VALIDATION_ERROR, code);
}

START_TEST(get_result_3) {
  char *expression = "cos(pi)^2+sin(pi)^2";
  int code = 0;
  ck_assert_int_eq(1, get_result(expression, 0, &code));
  ck_assert_int_eq(OK, code);
}

START_TEST(get_result_4) {
  char *expression = "-3-4.5";
  int code = 0;
  ck_assert_double_eq(-7.5, get_result(expression, 0, &code));
  ck_assert_int_eq(OK, code);
}

START_TEST(get_result_5) {
  char *expression = "4*8/4";
  int code = 0;
  ck_assert_double_eq(8.0, get_result(expression, 0, &code));
  ck_assert_int_eq(OK, code);
}

START_TEST(get_result_6) {
  char *expression = "tan(1)+atan(1)";
  int code = 0;
  ck_assert_double_eq_tol(1.55741, get_result(expression, 0, &code), 7);
  ck_assert_int_eq(OK, code);
}

START_TEST(get_result_7) {
  char *expression = "ln(100)";
  int code = 0;
  ck_assert_double_eq_tol(2, get_result(expression, 0, &code), 7);
  ck_assert_int_eq(OK, code);
}

START_TEST(credit_test_ann) {
  double first = get_monthly_payment_ann(300000,  15, 18);
  ck_assert_double_eq_tol(18715.44, first, 3);
}

START_TEST(credit_test_diff) {
  double first = get_monthly_payment_diff(300000, 15, 18, 300000);
  ck_assert_double_eq_tol(20365.30, first, 3);
}

int main(void) {
  Suite *s1 = suite_create("s21_matrix: ");
  TCase *tc1_1 = tcase_create("s21_matrix: ");
  SRunner *sr = srunner_create(s1);
  int not_failed;
  suite_add_tcase(s1, tc1_1);

  tcase_add_test(tc1_1, validator_test);
  tcase_add_test(tc1_1, validator_test_2);
  tcase_add_test(tc1_1, validator_test_3);
  tcase_add_test(tc1_1, get_result_1);
  tcase_add_test(tc1_1, get_result_2);
  tcase_add_test(tc1_1, get_result_3);
  tcase_add_test(tc1_1, get_result_4);
  tcase_add_test(tc1_1, get_result_5);
  tcase_add_test(tc1_1, get_result_6);
  tcase_add_test(tc1_1, get_result_7);
  tcase_add_test(tc1_1, credit_test_ann);
  tcase_add_test(tc1_1, credit_test_diff);
  srunner_run_all(sr, CK_ENV);
  not_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return not_failed == 0 ? 0 : 1;
}
