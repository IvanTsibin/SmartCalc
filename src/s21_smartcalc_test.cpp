#include "s21_credit.h"
#include "s21_deposit.h"
#include "s21_smartcalc.h"
#include <cmath>
#include <gtest/gtest.h>
#include <iostream>

TEST(calculator_1, test_1) {
  using namespace s21;
  char init_str[255] = "2^3^4";
  s21::calculator temp;
  double rezult1 = temp.calculate_init_str(init_str);
  double rezult2 = pow(pow(2, 3), 4);
  double diff = abs(rezult1 - rezult2);
  EXPECT_LT(diff, 0.0000001);
}

TEST(calculator_1, test_2) {
  using namespace s21;
  char init_str[255] = "sin(0.5)";
  s21::calculator temp;
  double rezult1 = temp.calculate_init_str(init_str);
  double rezult2 = sin(0.5);
  double diff = abs(rezult1 - rezult2);
  EXPECT_LT(diff, 0.0000001);
}

TEST(calculator_1, test_3) {
  using namespace s21;
  char init_str[255] = "cos(0.5)";
  s21::calculator temp;
  double rezult1 = temp.calculate_init_str(init_str);
  double rezult2 = cos(0.5);
  double diff = abs(rezult1 - rezult2);
  EXPECT_LT(diff, 0.0000001);
}

TEST(calculator_1, test_4) {
  using namespace s21;
  char init_str[255] = "tan(0.5)";
  s21::calculator temp;
  double rezult1 = temp.calculate_init_str(init_str);
  double rezult2 = tan(0.5);
  double diff = abs(rezult1 - rezult2);
  EXPECT_LT(diff, 0.0000001);
}

TEST(calculator_1, test_5) {
  using namespace s21;
  char init_str[255] = "sqrt(0.5)";
  s21::calculator temp;
  double rezult1 = temp.calculate_init_str(init_str);
  double rezult2 = sqrt(0.5);
  double diff = abs(rezult1 - rezult2);
  EXPECT_LT(diff, 0.0000001);
}

TEST(calculator_1, test_6) {
  using namespace s21;
  char init_str[255] = "log(0.5)";
  s21::calculator temp;
  double rezult1 = temp.calculate_init_str(init_str);
  double rezult2 = log10(0.5);
  double diff = abs(rezult1 - rezult2);
  EXPECT_LT(diff, 0.0000001);
}

TEST(calculator_1, test_7) {
  using namespace s21;
  char init_str[255] = "ln(0.5)";
  s21::calculator temp;
  double rezult1 = temp.calculate_init_str(init_str);
  double rezult2 = log(0.5);
  double diff = abs(rezult1 - rezult2);
  EXPECT_LT(diff, 0.0000001);
}

TEST(calculator_1, test_8) {
  using namespace s21;
  char init_str[255] = "asin(0.5)";
  s21::calculator temp;
  double rezult1 = temp.calculate_init_str(init_str);
  double rezult2 = asin(0.5);
  double diff = abs(rezult1 - rezult2);
  EXPECT_LT(diff, 0.0000001);
}

TEST(calculator_1, test_9) {
  using namespace s21;
  char init_str[255] = "acos(0.5)";
  s21::calculator temp;
  double rezult1 = temp.calculate_init_str(init_str);
  double rezult2 = acos(0.5);
  double diff = abs(rezult1 - rezult2);
  EXPECT_LT(diff, 0.0000001);
}

TEST(calculator_1, test_10) {
  using namespace s21;
  char init_str[255] = "atan(0.5)";
  s21::calculator temp;
  double rezult1 = temp.calculate_init_str(init_str);
  double rezult2 = atan(0.5);
  double diff = abs(rezult1 - rezult2);
  EXPECT_LT(diff, 0.0000001);
}

TEST(calculator_1, test_11) {
  using namespace s21;
  char init_str[255] = "1+2*3+5mod1";
  s21::calculator temp;
  double rezult1 = temp.calculate_init_str(init_str);
  double rezult2 = 1 + 2 * 3;
  double diff = abs(rezult1 - rezult2);
  EXPECT_LT(diff, 0.0000001);
}

TEST(calculator_1, test_12) {
  using namespace s21;
  char init_str[255] = "x+2*3+5mod1";
  s21::calculator temp;
  double rezult1 = temp.calculate_x_factor(init_str, 1);
  double rezult2 = 1 + 2 * 3;
  double diff = abs(rezult1 - rezult2);
  EXPECT_LT(diff, 0.0000001);
}

TEST(calculator_1, test_13) {
  using namespace s21;
  char init_str[255] = "-1+1.0e2";
  s21::calculator temp;
  double rezult1 = temp.calculate_x_factor(init_str, 1);
  double rezult2 = -1 + 100;
  double diff = abs(rezult1 - rezult2);
  EXPECT_LT(diff, 0.0000001);
}

TEST(calculator_1, test_14) {
  using namespace s21;
  char init_str[255] = "2+(-5+6)";
  s21::calculator temp;
  double rezult1 = temp.calculate_x_factor(init_str, 1);
  double rezult2 = 2 + (-5 + 6);
  double diff = abs(rezult1 - rezult2);
  EXPECT_LT(diff, 0.0000001);
}

TEST(calculator_1, test_15) {
  using namespace s21;
  char init_str[255] = "3*x+5";
  s21::calculator temp;
  double rezult1 = temp.calculate_x_factor(init_str, 5);
  double rezult2 = 3 * 5 + 5;
  double diff = abs(rezult1 - rezult2);
  EXPECT_LT(diff, 0.0000001);
}

TEST(calculator_1, test_16) {
  using namespace s21;
  char init_str[255] = "3(1+2)+2sqrt(4)";
  s21::calculator temp;
  double rezult1 = temp.calculate_x_factor(init_str, 5);
  double rezult2 = 3 * (1 + 2) + 2 * sqrt(4);
  double diff = abs(rezult1 - rezult2);
  EXPECT_LT(diff, 0.0000001);
}

TEST(calculator_1, test_17) {
  using namespace s21;
  char init_str[255] = "2+(-(10-2))";
  s21::calculator temp;
  double rezult1 = temp.calculate_x_factor(init_str, 5);
  double rezult2 = 2 + (-(10 - 2));
  double diff = abs(rezult1 - rezult2);
  EXPECT_LT(diff, 0.0000001);
}

TEST(calculator_1, test_18) {
  using namespace s21;
  char init_str[255] = "-sqrt(4)";
  s21::calculator temp;
  double rezult1 = temp.calculate_x_factor(init_str, 5);
  double rezult2 = -sqrt(4);
  double diff = abs(rezult1 - rezult2);
  EXPECT_LT(diff, 0.0000001);
}

TEST(banking_credit_1, test_1) {
  using namespace s21;
  s21::s21_credit temp;
  temp.start_credit_summ(1000000);
  temp.start_credit_type(DIFF);
  temp.start_credit_month_time(1);
  temp.start_credit_percents(10);
  temp.calculate_credit();
  double diff = abs(temp.return_summ_for_all() - 1008333.33);
  for (int i = 0; i < temp.return_month_amount() + 1; i++) {
    printf("month %2d payment = %.2lf summ = %.2lf percents = %.2lf\n", i + 1,
           temp.return_payment_per_month(i), temp.return_summ_per_month(i),
           temp.return_percents_per_month(i));
  }
  printf(
      "\ncredit type = DIFF summ_for_all = %.2lf percents_for_all = %.10lf\n",
      temp.return_summ_for_all(), temp.return_percents_for_all());
  EXPECT_LT(diff, 0.01);
}

TEST(banking_credit_1, test_2) {
  using namespace s21;
  s21::s21_credit temp;
  temp.start_credit_summ(1000000);
  temp.start_credit_type(ANUN);
  temp.start_credit_month_time(1);
  temp.start_credit_percents(10);
  temp.calculate_credit();
  double diff = abs(temp.return_summ_for_all() - 1008333.33);
  EXPECT_LT(diff, 0.01);
}

TEST(banking_deposit_1, test_1) {
  using namespace s21;
  s21::s21_deposit temp;
  temp.scheme_start_summ(100000);
  temp.scheme_percents(12);
  temp.scheme_days_of_deposit(0);
  temp.scheme_months_of_deposit(0);
  temp.scheme_quaters_of_deposit(4);
  temp.scheme_type(QUARTERLY);
  temp.scheme_adding_type(QUARTERLY);
  temp.scheme_adding_periods(1);
  temp.scheme_adding_summ(10000);
  temp.scheme_removing_type(QUARTERLY);
  temp.scheme_removing_periods(2);
  temp.scheme_removing_summ(20000);
  temp.scheme_unremovble_summ(70000);
  temp.scheme_amount_of_periods(1);
  temp.scheme_tax_percents(13);
  temp.scheme_start_time();
  temp.deposit_full_calculating();
  double diff = abs(temp.return_full_summ_in_deposit() - 123169.15);
  printf("step |    date    | st_summ | adding | removing |  summ  | rzlt summ "
         "|  percents \n");
  for (int i = 0; i < temp.return_amount_of_periods() + 1; i++) {
    struct tm *temp_date;
    char s2[40] = {0};
    temp_date = localtime(temp.return_start_time(i));
    strftime(s2, 80, "%d.%m.%Y ", temp_date);
    printf(" %2d  | %s | %7.0lf |", i, temp.return_start_day(i),
           temp.return_start_period_summ(i));
    printf(" %6.0lf |  %6.0lf  | %6.0lf |", temp.return_addings(i),
           temp.return_removings(i), temp.return_summ(i));
    printf("   %6.0lf  | %6.0lf ", temp.return_summ_in_deposit(i),
           temp.return_percents_in_deposit(i));
    printf("\n");
  }
  printf("Final summ on account = %6.0lf \n",
         temp.return_full_summ_in_deposit());
  printf("Total amount of percents = %12.6lf\n",
         temp.return_percents_for_all_in_deposit());
  printf("Total amount of taxes = %12.6lf\n", temp.return_tax_summ_for_all());
  EXPECT_LT(diff, 0.01);
}

TEST(banking_deposit_1, test_2) {
  using namespace s21;
  s21::s21_deposit temp;
  temp.scheme_start_summ(100000);
  temp.scheme_percents(12);
  temp.scheme_days_of_deposit(365);
  temp.scheme_type(DAILLY);
  temp.scheme_adding_type(SIMPLE);
  temp.scheme_adding_periods(0);
  temp.scheme_adding_summ(0);
  temp.scheme_removing_type(SIMPLE);
  temp.scheme_removing_periods(0);
  temp.scheme_removing_summ(0);
  temp.scheme_unremovble_summ(0);
  temp.scheme_tax_percents(13);
  temp.deposit_full_calculating();
  double diff = abs(temp.return_percents_for_all_in_deposit() - 12747.46);
  EXPECT_LT(diff, 0.01);
}

TEST(banking_deposit_1, test_3) {
  using namespace s21;
  s21::s21_deposit temp;
  temp.scheme_start_summ(1000000);
  temp.scheme_percents(12);
  temp.scheme_months_of_deposit(12);
  temp.scheme_type(MONTHY);
  temp.scheme_adding_type(SIMPLE);
  temp.scheme_adding_periods(0);
  temp.scheme_adding_summ(0);
  temp.scheme_removing_type(SIMPLE);
  temp.scheme_removing_periods(0);
  temp.scheme_removing_summ(0);
  temp.scheme_unremovble_summ(0);
  temp.scheme_tax_percents(13);
  temp.deposit_full_calculating();
  double diff = abs(temp.return_percents_for_all_in_deposit() - 126825.03);
  EXPECT_LT(diff, 0.01);
}

TEST(banking_deposit_1, test_4) {
  using namespace s21;
  s21::s21_deposit temp;
  temp.scheme_start_summ(1000000);
  temp.scheme_percents(12);
  temp.scheme_days_of_deposit(365);
  temp.scheme_type(SIMPLE);
  temp.scheme_adding_type(SIMPLE);
  temp.scheme_adding_periods(0);
  temp.scheme_adding_summ(0);
  temp.scheme_removing_type(SIMPLE);
  temp.scheme_removing_periods(0);
  temp.scheme_removing_summ(0);
  temp.scheme_unremovble_summ(0);
  temp.scheme_tax_percents(13);
  temp.deposit_full_calculating();
  double diff = abs(temp.return_percents_for_all_in_deposit() - 120000);
  EXPECT_LT(diff, 0.01);
}

TEST(banking_deposit_1, test_5) {
  using namespace s21;
  s21::s21_deposit temp;
  temp.scheme_start_summ(1000000);
  temp.scheme_percents(12);
  temp.scheme_days_of_deposit(0);
  temp.scheme_type(SIMPLE);
  temp.scheme_adding_type(SIMPLE);
  temp.scheme_adding_periods(0);
  temp.scheme_adding_summ(0);
  temp.scheme_removing_type(SIMPLE);
  temp.scheme_removing_periods(0);
  temp.scheme_removing_summ(0);
  temp.scheme_unremovble_summ(0);
  temp.scheme_tax_percents(13);
  temp.deposit_full_calculating();
  double diff = abs(temp.return_percents_for_all_in_deposit() - 0);
  EXPECT_LT(diff, 0.01);
}

TEST(banking_deposit_1, test_6) {
  using namespace s21;
  s21::s21_deposit temp;
  temp.scheme_start_summ(1000000);
  temp.scheme_percents(12);
  temp.scheme_months_of_deposit(12);
  temp.scheme_type(MONTHY);
  temp.scheme_adding_type(MONTHY);
  temp.scheme_adding_periods(12);
  temp.scheme_adding_summ(1000);
  temp.scheme_removing_type(QUARTERLY);
  temp.scheme_removing_periods(4);
  temp.scheme_removing_summ(2000);
  temp.scheme_unremovble_summ(70000);
  temp.scheme_tax_percents(13);
  temp.deposit_full_calculating();
  double diff = abs(temp.return_percents_for_all_in_deposit() - 126825.03);
  EXPECT_LT(diff, 0.01);
}

TEST(banking_deposit_1, test_7) {
  using namespace s21;
  s21::s21_deposit temp;
  temp.scheme_start_summ(1000000);
  temp.scheme_percents(12);
  temp.scheme_days_of_deposit(365);
  temp.scheme_type(DAILLY);
  temp.scheme_adding_type(MONTHY);
  temp.scheme_adding_periods(12);
  temp.scheme_adding_summ(1000);
  temp.scheme_removing_type(QUARTERLY);
  temp.scheme_removing_periods(4);
  temp.scheme_removing_summ(2000);
  temp.scheme_unremovble_summ(70000);
  temp.scheme_tax_percents(13);
  temp.deposit_full_calculating();
  double diff = abs(temp.return_percents_for_all_in_deposit() - 127474.62);
  EXPECT_LT(diff, 0.01);
}

TEST(banking_deposit_1, test_8) {
  using namespace s21;
  s21::s21_deposit temp;
  temp.scheme_start_summ(1000000);
  temp.scheme_percents(12);
  temp.scheme_months_of_deposit(12);
  temp.scheme_type(MONTHY);
  temp.scheme_adding_type(MONTHY);
  temp.scheme_adding_periods(12);
  temp.scheme_adding_summ(1000);
  temp.scheme_removing_type(QUARTERLY);
  temp.scheme_removing_periods(4);
  temp.scheme_removing_summ(0);
  temp.scheme_unremovble_summ(70000);
  temp.scheme_tax_percents(13);
  temp.deposit_full_calculating();
  double diff = abs(temp.return_percents_for_all_in_deposit() - 126825.03);
  EXPECT_LT(diff, 0.01);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
