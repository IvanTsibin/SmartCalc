#include "s21_credit.h"
#include <cmath>
#include <stdio.h>
#include <stdlib.h>

s21::s21_credit::s21_credit() {
  in_credit_.summ = 0;
  in_credit_.type = DIFF;
  in_credit_.month_time = 0;
  in_credit_.percents = 0;
  for (int i = 0; i < 360; i++) {
    in_credit_.payment_per_month[i] = 0;
    in_credit_.summ_per_month[i] = 0;
    in_credit_.percents_per_month[i] = 0;
  }
}

s21::s21_credit::~s21_credit() {}

void s21::s21_credit::start_credit_summ(double sum) {
  this->in_credit_.summ = sum;
}
void s21::s21_credit::start_credit_type(credit_type_t type) {
  this->in_credit_.type = type;
}
void s21::s21_credit::start_credit_month_time(int time_in_month) {
  this->in_credit_.month_time = time_in_month;
}
void s21::s21_credit::start_credit_percents(double percents) {
  this->in_credit_.percents = percents;
}
double s21::s21_credit::return_payment_per_month(int month_number) {
  return this->in_credit_.payment_per_month[month_number];
}
double s21::s21_credit::return_summ_per_month(int month_number) {
  return this->in_credit_.summ_per_month[month_number];
}
double s21::s21_credit::return_percents_per_month(int month_number) {
  return this->in_credit_.percents_per_month[month_number];
}
double s21::s21_credit::return_summ_for_all() {
  return this->in_credit_.summ_for_all;
}
double s21::s21_credit::return_percents_for_all() {
  return this->in_credit_.percents_for_all;
}
int s21::s21_credit::return_month_amount() {
  return this->in_credit_.month_time;
}

void s21::s21_credit::calculate_credit() {
  if (in_credit_.type == DIFF) {
    diff_credit_calculate();
  } else {
    anun_credit_calculate();
  }
}

void s21::s21_credit::diff_credit_calculate() {
  double summ_per_month = in_credit_.summ / (double)in_credit_.month_time;
  double ppm = in_credit_.percents / 1200, temp;
  temp = in_credit_.summ;
  in_credit_.percents_for_all = 0;
  in_credit_.summ_for_all = 0;
  for (int i = 0; i < in_credit_.month_time; i++) {
    in_credit_.percents_per_month[i] = temp * ppm;
    in_credit_.summ_per_month[i] = summ_per_month;
    temp = temp - summ_per_month;
    in_credit_.payment_per_month[i] =
        in_credit_.percents_per_month[i] + in_credit_.summ_per_month[i];
    in_credit_.percents_for_all =
        in_credit_.percents_for_all + in_credit_.percents_per_month[i];
    in_credit_.summ_for_all =
        in_credit_.summ_for_all + in_credit_.payment_per_month[i];
  }
}

void s21::s21_credit::anun_credit_calculate() {
  double month_payment, ppm = in_credit_.percents / 1200, temp;
  temp = pow((1 + ppm), (double)in_credit_.month_time) - 1;
  temp = ppm + ppm / temp;
  month_payment = in_credit_.summ * temp;
  in_credit_.percents_for_all = 0;
  in_credit_.summ_for_all = 0;
  for (int i = 0; i < in_credit_.month_time; i++) {
    in_credit_.payment_per_month[i] = month_payment;
    in_credit_.percents_per_month[i] = ppm * in_credit_.summ;
    in_credit_.summ_per_month[i] =
        month_payment - in_credit_.percents_per_month[i];
    in_credit_.summ = in_credit_.summ - in_credit_.summ_per_month[i];
    in_credit_.percents_for_all =
        in_credit_.percents_for_all + in_credit_.percents_per_month[i];
    in_credit_.summ_for_all =
        in_credit_.summ_for_all + in_credit_.payment_per_month[i];
  }
}
