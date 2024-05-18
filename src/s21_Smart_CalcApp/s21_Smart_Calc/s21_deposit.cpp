#include "s21_deposit.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NORMAL_YEAR_DAYS 365
#define LONG_YEAR_DAYS 366
s21::s21_deposit::s21_deposit() {
  for (int i = 0; i < DEPOS_AMOUNT; i++) {
    scheme_.start_period_summ[i] = 0;
    scheme_.addings[i] = 0;
    scheme_.removings[i] = 0;
  }
  scheme_.start_summ = 0;
  scheme_.percents = 0;
  scheme_.days_of_deposit = 0;
  scheme_.months_of_deposit = 0;
  scheme_.quaters_of_deposit = 0;
  scheme_.type = SIMPLE;
  scheme_.adding_type = SIMPLE;
  scheme_.adding_periods = 1;
  scheme_.adding_summ = 0;
  scheme_.removing_type = SIMPLE;
  scheme_.removing_periods = 1;
  scheme_.removing_summ = 0;
  scheme_.unremovble_summ = 0;
  scheme_.amount_of_periods = 1;
  scheme_.tax_percents = 0;
  const time_t initial_time = time(NULL);
  scheme_.start_time = initial_time;
}

s21::s21_deposit::~s21_deposit() {}

void s21::s21_deposit::scheme_start_summ(double sum) {
  scheme_.start_summ = sum;
}
void s21::s21_deposit::scheme_percents(double percents) {
  scheme_.percents = percents;
}
void s21::s21_deposit::scheme_days_of_deposit(int days) {
  scheme_.days_of_deposit = days;
  scheme_.months_of_deposit = 0;
  scheme_.quaters_of_deposit = 0;
}
void s21::s21_deposit::scheme_months_of_deposit(int months) {
  scheme_.days_of_deposit = 0;
  scheme_.months_of_deposit = months;
  scheme_.quaters_of_deposit = 0;
}
void s21::s21_deposit::scheme_quaters_of_deposit(int quaters) {
  scheme_.days_of_deposit = 0;
  scheme_.months_of_deposit = 0;
  scheme_.quaters_of_deposit = quaters;
}
void s21::s21_deposit::scheme_type(deposit_type_t type) { scheme_.type = type; }
void s21::s21_deposit::scheme_adding_type(deposit_type_t adding_type) {
  scheme_.adding_type = adding_type;
}
void s21::s21_deposit::scheme_adding_periods(int adding_periods) {
  scheme_.adding_periods = adding_periods;
}
void s21::s21_deposit::scheme_adding_summ(double adding_sum) {
  scheme_.adding_summ = adding_sum;
}
void s21::s21_deposit::scheme_removing_type(deposit_type_t removing_type) {
  scheme_.removing_type = removing_type;
}
void s21::s21_deposit::scheme_removing_periods(int removing_periods) {
  scheme_.removing_periods = removing_periods;
}
void s21::s21_deposit::scheme_removing_summ(double removing_sum) {
  scheme_.removing_summ = removing_sum;
}
void s21::s21_deposit::scheme_unremovble_summ(double unremovble_summ) {
  scheme_.unremovble_summ = unremovble_summ;
}
void s21::s21_deposit::scheme_amount_of_periods(int amount_of_periods) {
  scheme_.amount_of_periods = amount_of_periods;
}
void s21::s21_deposit::scheme_tax_percents(double tax_percents) {
  scheme_.tax_percents = tax_percents;
}
void s21::s21_deposit::scheme_start_time() {
  const time_t initial_time = time(NULL);
  scheme_.start_time = initial_time;
}
const time_t *s21::s21_deposit::return_start_time(int month_number) {
  return (const time_t *)&scheme_.deposits[month_number].start_time;
}
char *s21::s21_deposit::return_start_day(int month_number) {
  return scheme_.deposits[month_number].start_day;
}
double s21::s21_deposit::return_start_period_summ(int month_number) {
  return scheme_.start_period_summ[month_number];
}
double s21::s21_deposit::return_addings(int month_number) {
  return scheme_.addings[month_number];
}
double s21::s21_deposit::return_removings(int month_number) {
  return scheme_.removings[month_number];
}
double s21::s21_deposit::return_summ(int month_number) {
  return scheme_.deposits[month_number].summ;
}
double s21::s21_deposit::return_summ_in_deposit(int month_number) {
  return scheme_.deposits[month_number].summ_for_all;
}
double s21::s21_deposit::return_percents_in_deposit(int month_number) {
  return scheme_.deposits[month_number].percents_for_all;
}
double s21::s21_deposit::return_full_summ_in_deposit() {
  return scheme_.deposits[scheme_.amount_of_periods].summ;
}
double s21::s21_deposit::return_percents_for_all_in_deposit() {
  return scheme_.percents_for_all;
}
double s21::s21_deposit::return_tax_summ_for_all() {
  return scheme_.tax_summ_for_all;
}
int s21::s21_deposit::return_amount_of_periods() {
  return scheme_.amount_of_periods;
};

void s21::s21_deposit::deposit_full_calculating() {
  deposit_scheme_prepairing();
  deposit_duration_calculating();
  deposit_scheme_calculating();
}

void s21::s21_deposit::calculate_deposit(
    s21::s21_deposit::deposit_t *in_deposit) {
  struct tm *temp2_date = NULL;
  time_t temp_time = in_deposit->start_time;
  temp2_date = localtime(&temp_time);
  char s0[40] = {0};
  strftime(s0, 80, "%d.%m.%Y ", temp2_date);
  if (in_deposit->type == DAILLY) {
    dailly_deposit_calculate(in_deposit);
  } else if (in_deposit->type == MONTHY) {
    monthy_deposit_calculate(in_deposit);
  } else if (in_deposit->type == QUARTERLY) {
    quaterly_deposit_calculate(in_deposit);
  } else {
    simple_deposit_calculate(in_deposit);
  }
}

void s21::s21_deposit::dailly_deposit_calculate(
    s21::s21_deposit::deposit_t *in_deposit) {
  int days_of_deposit_left = in_deposit->days_of_deposit, year_counter = 1,
      days_in_the_year;
  double summ_of_percents = 0, temp;
  in_deposit->summ_for_all = in_deposit->summ;
  while (days_of_deposit_left > 0) {
    days_in_the_year = year_in_days(year_counter);
    days_of_deposit_left -= days_in_the_year;
    year_counter++;
    temp = pow((1 + in_deposit->percents / (100 * days_in_the_year)),
               (double)in_deposit->days_of_deposit) -
           1;
    temp = round(temp * in_deposit->summ * 100) / 100;
    summ_of_percents = summ_of_percents + temp;
    in_deposit->summ_for_all += summ_of_percents;
  }
  in_deposit->percents_for_all = summ_of_percents;
  in_deposit->summ_for_all = in_deposit->summ + summ_of_percents;
  in_deposit->tax_summ = summ_of_percents * in_deposit->tax_percents / 100;
}

void s21::s21_deposit::monthy_deposit_calculate(
    s21::s21_deposit::deposit_t *in_deposit) {
  int months_of_deposit_left = in_deposit->months_of_deposit, year_counter = 1;
  double summ_of_percents = 0, temp;
  in_deposit->summ_for_all = in_deposit->summ;
  while (months_of_deposit_left > 0) {
    months_of_deposit_left -= 12;
    year_counter++;
    temp = pow((1 + in_deposit->percents / (100 * 12)),
               (double)in_deposit->months_of_deposit) -
           1;
    temp = round(temp * in_deposit->summ * 100) / 100;
    summ_of_percents = summ_of_percents + temp;
    in_deposit->summ_for_all += summ_of_percents;
  }
  in_deposit->percents_for_all += summ_of_percents;
  in_deposit->tax_summ = summ_of_percents * in_deposit->tax_percents / 100;
}

void s21::s21_deposit::quaterly_deposit_calculate(
    s21::s21_deposit::deposit_t *in_deposit) {
  int quaters_of_deposit_left = in_deposit->quaters_of_deposit,
      year_counter = 1;
  double summ_of_percents = 0, temp;
  in_deposit->summ_for_all = in_deposit->summ;
  while (quaters_of_deposit_left > 0) {
    quaters_of_deposit_left -= 4;
    year_counter++;
    temp = pow((1 + in_deposit->percents / (100 * 4)),
               (double)in_deposit->quaters_of_deposit) -
           1;
    temp = round(temp * in_deposit->summ * 100) / 100;
    summ_of_percents = summ_of_percents + temp;
    in_deposit->summ_for_all += summ_of_percents;
  }
  in_deposit->percents_for_all = summ_of_percents;
  in_deposit->summ_for_all = in_deposit->summ + summ_of_percents;
  in_deposit->tax_summ = summ_of_percents * in_deposit->tax_percents / 100;
}

void s21::s21_deposit::simple_deposit_calculate(
    s21::s21_deposit::deposit_t *in_deposit) {
  int days_of_deposit_left = in_deposit->days_of_deposit, year_counter = 1,
      days_in_the_year;
  double summ_of_percents = 0, temp;
  while (days_of_deposit_left > 0) {
    days_in_the_year = year_in_days(year_counter);
    days_of_deposit_left -= days_in_the_year;
    year_counter++;
    temp = (in_deposit->summ * in_deposit->percents *
            (double)in_deposit->days_of_deposit) /
           (100 * days_in_the_year);
    temp = round(temp * 100) / 100;
    summ_of_percents = summ_of_percents + temp;
  }
  in_deposit->percents_for_all = summ_of_percents;
  in_deposit->summ_for_all = in_deposit->summ + summ_of_percents;
  in_deposit->tax_summ = summ_of_percents * in_deposit->tax_percents / 100;
}

int s21::s21_deposit::year_in_days(int year_number) {
  int year_in_days = NORMAL_YEAR_DAYS;
  const time_t current_time = time(NULL);
  struct tm *current_year = NULL;
  char s1[40] = {0}, s2[40] = {0};
  current_year = localtime(&current_time);
  strftime(s1, 80, "%d.%m.%Y %H:%M:%S ", current_year);
  int number_of_days = current_year->tm_yday;
  current_year->tm_year = current_year->tm_year + year_number;
  current_year->tm_yday = current_year->tm_yday + NORMAL_YEAR_DAYS;
  time_t next = mktime(current_year);
  current_year = localtime(&next);
  int next_year_number_of_days = current_year->tm_yday;
  strftime(s2, 80, "%d.%m.%Y %H:%M:%S ", current_year);
  if (next_year_number_of_days > number_of_days) {
    year_in_days = LONG_YEAR_DAYS;
  }
  return year_in_days;
}

void s21::s21_deposit::deposit_scheme_calculating() {
  scheme_.start_period_summ[0] = scheme_.deposits[0].summ;
  for (int i = 0; i < scheme_.amount_of_periods; i++) {
    double temp = scheme_.start_period_summ[i] + scheme_.addings[i] -
                  scheme_.removings[i];
    if (temp >= scheme_.unremovble_summ) {
      scheme_.deposits[i].summ = temp;
    } else {
      scheme_.deposits[i].summ = scheme_.unremovble_summ;
      scheme_.removings[i] = scheme_.start_period_summ[i] + scheme_.addings[i] -
                             scheme_.unremovble_summ;
      if (scheme_.removings[i] < 0)
        scheme_.removings[i] = 0;
    }
    calculate_deposit(&scheme_.deposits[i]);
    scheme_.deposits[i + 1].summ = scheme_.deposits[i].summ_for_all;
    scheme_.start_period_summ[i + 1] = scheme_.deposits[i].summ_for_all;
  }
  scheme_.percents_for_all = 0;
  scheme_.tax_summ_for_all = 0;
  struct tm *temp_date = NULL;
  for (int i = 0; i < scheme_.amount_of_periods; i++) {
    scheme_.percents_for_all += scheme_.deposits[i].percents_for_all;
    scheme_.tax_summ_for_all += scheme_.deposits[i].tax_summ;
    temp_date = localtime(&scheme_.deposits[i].start_time);
    strftime(scheme_.deposits[i].start_day, 80, "%d.%m.%Y", temp_date);
  }
  temp_date =
      localtime(&scheme_.deposits[scheme_.amount_of_periods].start_time);
  strftime(scheme_.deposits[scheme_.amount_of_periods].start_day, 80,
           "%d.%m.%Y", temp_date);
}

void s21::s21_deposit::deposit_duration_calculating() {
  int periods_counter = 0;
  struct tm *temp_date = NULL;
  if (scheme_.amount_of_periods == 1) {
    scheme_.deposits[periods_counter].days_of_deposit = scheme_.days_of_deposit;
    scheme_.deposits[periods_counter].months_of_deposit =
        scheme_.months_of_deposit;
    scheme_.deposits[periods_counter].quaters_of_deposit =
        scheme_.quaters_of_deposit;
  } else {
    while (periods_counter < scheme_.amount_of_periods) {
      if (scheme_.type == DAILLY || scheme_.type == SIMPLE) {
        scheme_.deposits[periods_counter].days_of_deposit =
            (int)((7200 +
                   difftime(scheme_.deposits[periods_counter + 1].start_time,
                            scheme_.deposits[periods_counter].start_time)) /
                  (DAY_IN_SEC));
      } else if (scheme_.type == MONTHY) {
        temp_date =
            localtime(&scheme_.deposits[periods_counter + 1].start_time);
        int temp_1 = temp_date->tm_year * 12 + temp_date->tm_mon;
        temp_date = localtime(&scheme_.deposits[periods_counter].start_time);
        int temp_2 = temp_date->tm_year * 12 + temp_date->tm_mon;
        scheme_.deposits[periods_counter].months_of_deposit = temp_1 - temp_2;
      } else if (scheme_.type == QUARTERLY) {
        temp_date =
            localtime(&scheme_.deposits[periods_counter + 1].start_time);
        int temp_1 = temp_date->tm_year * 12 + temp_date->tm_mon;
        temp_date = localtime(&scheme_.deposits[periods_counter].start_time);
        int temp_2 = temp_date->tm_year * 12 + temp_date->tm_mon;
        scheme_.deposits[periods_counter].quaters_of_deposit =
            (temp_1 - temp_2) / 3;
      }
      scheme_.deposits[periods_counter].type = scheme_.type;
      periods_counter++;
    }
  }
}

void s21::s21_deposit::deposit_scheme_prepairing() {
  struct tm *initial_date = NULL;
  time_t start_time = scheme_.start_time, adding_dates[DEPOS_AMOUNT],
         removing_dates[DEPOS_AMOUNT];
  initial_date = localtime(&start_time);
  int duration_in_days = duration_days_calculate(initial_date);
  int adding_number = 0, removing_number = 0;
  if (scheme_.type != SIMPLE) {
    if (scheme_.adding_type == DAILLY || scheme_.removing_type == DAILLY) {
      scheme_.type = DAILLY;
    } else if ((scheme_.adding_type == MONTHY ||
                scheme_.removing_type == MONTHY) &&
               scheme_.type == QUARTERLY) {
      scheme_.type = MONTHY;
    }
    next_adding_days_calculation(duration_in_days, adding_dates,
                                 &adding_number);
    next_removing_days_calculation(duration_in_days, removing_dates,
                                   &removing_number);
  }
  int deposit_counter = 0, adding_counter = 0, removing_counter = 0;
  scheme_.deposits[deposit_counter].summ = scheme_.start_summ;
  scheme_.deposits[deposit_counter].start_time = scheme_.start_time;
  scheme_.deposits[deposit_counter].percents = scheme_.percents;
  scheme_.deposits[deposit_counter].type = scheme_.type;
  scheme_.deposits[deposit_counter].tax_percents = scheme_.tax_percents;
  scheme_.amount_of_periods = 1;
  scheme_.addings[deposit_counter] = 0;
  scheme_.removings[deposit_counter] = 0;
  while (adding_number > 0 || removing_number > 0) {
    deposit_counter++;
    scheme_.amount_of_periods += 1;
    time_t next_adding = adding_dates[adding_counter],
           next_removing = removing_dates[removing_counter];
    if (adding_number > 0 && removing_number > 0) {
      if (next_adding == next_removing) {
        scheme_.deposits[deposit_counter].start_time = next_adding;
        scheme_.addings[deposit_counter] = scheme_.adding_summ;
        scheme_.removings[deposit_counter] = scheme_.removing_summ;
        adding_counter++;
        removing_counter++;
        adding_number--;
        removing_number--;
      } else if (next_adding < next_removing) {
        scheme_.deposits[deposit_counter].start_time = next_adding;
        scheme_.addings[deposit_counter] = scheme_.adding_summ;
        scheme_.removings[deposit_counter] = 0;
        adding_counter++;
        adding_number--;
      } else {
        scheme_.deposits[deposit_counter].start_time = next_removing;
        scheme_.addings[deposit_counter] = 0;
        scheme_.removings[deposit_counter] = scheme_.removing_summ;
        removing_counter++;
        removing_number--;
      }
    } else if (adding_number > 0 && removing_number == 0) {
      scheme_.deposits[deposit_counter].start_time = next_adding;
      scheme_.addings[deposit_counter] = scheme_.adding_summ;
      scheme_.removings[deposit_counter] = 0;
      adding_counter++;
      adding_number--;
    } else {
      scheme_.deposits[deposit_counter].start_time = next_removing;
      scheme_.addings[deposit_counter] = 0;
      scheme_.removings[deposit_counter] = scheme_.removing_summ;
      removing_counter++;
      removing_number--;
    }
    scheme_.deposits[deposit_counter].percents = scheme_.percents;
    scheme_.deposits[deposit_counter].type = scheme_.type;
    scheme_.deposits[deposit_counter].tax_percents = scheme_.tax_percents;
  }
  deposit_counter++;
  scheme_.deposits[deposit_counter].start_time =
      scheme_.start_time + (time_t)(24 * 60 * 60 * duration_in_days);
}

void s21::s21_deposit::next_removing_days_calculation(int duration_in_days,
                                                      time_t removing_dates[],
                                                      int *removing_number) {
  struct tm *initial_date = NULL;
  initial_date = localtime(&scheme_.start_time);
  int next_removing_in_days, number_of_removing_periods = 0, flag_end_month = 0;
  time_t current_time_1, current_time_2, current_time_3;
  char s0[40] = {0}, s1[40] = {0}, s2[40] = {0}, s3[40] = {0};
  strftime(s0, 80, "%d.%m.%Y %H:%M:%S ", initial_date);
  while (duration_in_days > 0) {
    strftime(s0, 80, "%d.%m.%Y %H:%M:%S ", initial_date);
    if (scheme_.removing_type == SIMPLE) {
      duration_in_days = 0;
      break;
    } else if (scheme_.removing_type == DAILLY) {
      current_time_1 = mktime(initial_date);
      current_time_2 = current_time_1 + scheme_.removing_periods * DAY_IN_SEC;
      initial_date = localtime(&current_time_2);
    } else if (scheme_.removing_type == MONTHY) {
      current_time_1 = mktime(initial_date);
      initial_date->tm_mon += scheme_.removing_periods;
    } else {
      current_time_1 = mktime(initial_date);
      initial_date->tm_mon += 3 * scheme_.removing_periods;
    }
    if (flag_end_month > 0) {
      initial_date->tm_mday += flag_end_month;
      flag_end_month = 0;
    }
    int temp_mon = initial_date->tm_mon;
    current_time_2 = mktime(initial_date);
    initial_date = localtime(&current_time_2);
    if (temp_mon != 12) {
      while (initial_date->tm_mon > temp_mon) {
        initial_date->tm_mday -= 1;
        flag_end_month++;
        current_time_2 = mktime(initial_date);
        initial_date = localtime(&current_time_2);
      }
    }
    next_removing_in_days =
        (int)((7200 + difftime(current_time_2, current_time_1)) / (DAY_IN_SEC));
    duration_in_days -= next_removing_in_days;
    if (duration_in_days < 0)
      break;
    removing_dates[number_of_removing_periods] = current_time_2;
    number_of_removing_periods += 1;
    strftime(s1, 80, "%d.%m.%Y %H:%M:%S ", initial_date);
  }
  *removing_number = number_of_removing_periods;
  if (duration_in_days == 0)
    *removing_number -= 1;
  strftime(s2, 80, "%d.%m.%Y %H:%M:%S ", initial_date);
  if (scheme_.removing_type == DAILLY) {
    initial_date->tm_yday -=
        number_of_removing_periods * scheme_.removing_periods;
    current_time_3 = mktime(initial_date);
    initial_date = localtime(&current_time_3);
  } else if (scheme_.removing_type == MONTHY) {
    initial_date->tm_mon -=
        number_of_removing_periods * scheme_.removing_periods;
    current_time_3 = mktime(initial_date);
    initial_date = localtime(&current_time_3);
  } else if (scheme_.removing_type == QUARTERLY) {
    initial_date->tm_mon -=
        number_of_removing_periods * 3 * scheme_.removing_periods;
    current_time_3 = mktime(initial_date);
    initial_date = localtime(&current_time_3);
  }
  strftime(s3, 80, "%d.%m.%Y %H:%M:%S ", initial_date);
}

void s21::s21_deposit::next_adding_days_calculation(int duration_in_days,
                                                    time_t adding_dates[],
                                                    int *adding_number) {
  struct tm *initial_date = NULL;
  initial_date = localtime(&scheme_.start_time);
  int next_adding_in_days, number_of_adding_periods = 0, flag_end_month = 0;
  time_t current_time_1, current_time_2, current_time_3;
  while (duration_in_days > 0) {
    if (scheme_.adding_type == SIMPLE) {
      duration_in_days = 0;
      break;
    } else if (scheme_.adding_type == DAILLY) {
      current_time_1 = mktime(initial_date);
      current_time_2 = current_time_1 + scheme_.adding_periods * DAY_IN_SEC;
      initial_date = localtime(&current_time_2);
    } else if (scheme_.adding_type == MONTHY) {
      current_time_1 = mktime(initial_date);
      initial_date->tm_mon += scheme_.adding_periods;
    } else {
      current_time_1 = mktime(initial_date);
      initial_date->tm_mon += 3 * scheme_.adding_periods;
    }
    if (flag_end_month > 0) {
      initial_date->tm_mday += flag_end_month;
      flag_end_month = 0;
    }
    int temp_mon = initial_date->tm_mon;
    current_time_2 = mktime(initial_date);
    initial_date = localtime(&current_time_2);
    if (temp_mon != 12) {
      while (initial_date->tm_mon > temp_mon) {
        initial_date->tm_mday -= 1;
        flag_end_month++;
        current_time_2 = mktime(initial_date);
        initial_date = localtime(&current_time_2);
      }
    }
    next_adding_in_days =
        (int)((7200 + difftime(current_time_2, current_time_1)) / (DAY_IN_SEC));
    duration_in_days -= next_adding_in_days;
    if (duration_in_days < 0)
      break;
    adding_dates[number_of_adding_periods] = current_time_2;
    number_of_adding_periods += 1;
  }
  *adding_number = number_of_adding_periods;
  if (duration_in_days == 0)
    *adding_number -= 1;
  if (scheme_.adding_type == DAILLY) {
    initial_date->tm_yday -= number_of_adding_periods * scheme_.adding_periods;
    current_time_3 = mktime(initial_date);
    initial_date = localtime(&current_time_3);
  } else if (scheme_.adding_type == MONTHY) {
    initial_date->tm_mon -= number_of_adding_periods * scheme_.adding_periods;
    current_time_3 = mktime(initial_date);
    initial_date = localtime(&current_time_3);
  } else if (scheme_.adding_type == QUARTERLY) {
    initial_date->tm_mon -=
        number_of_adding_periods * 3 * scheme_.adding_periods;
    current_time_3 = mktime(initial_date);
    initial_date = localtime(&current_time_3);
  }
}

int s21::s21_deposit::duration_days_calculate(struct tm *initial_date) {
  int duration_in_days;
  char s0[40] = {0}, s1[40] = {0};
  strftime(s0, 80, "%d.%m.%Y %H:%M:%S ", initial_date);
  if (scheme_.type == DAILLY) {
    duration_in_days = scheme_.days_of_deposit;
  } else if (scheme_.type == MONTHY || scheme_.type == QUARTERLY) {
    time_t current_time_1 = mktime(initial_date);
    initial_date->tm_mon +=
        scheme_.months_of_deposit + 3 * scheme_.quaters_of_deposit;
    time_t current_time_2 = mktime(initial_date);
    duration_in_days =
        (int)((7200 + difftime(current_time_2, current_time_1)) / (DAY_IN_SEC));
    initial_date->tm_mon -=
        scheme_.months_of_deposit + 3 * scheme_.quaters_of_deposit;
    time_t current_time_3 = mktime(initial_date);
    initial_date = localtime(&current_time_3);
  } else {
    duration_in_days = scheme_.days_of_deposit;
    if (duration_in_days == 0) {
      time_t current_time_1 = mktime(initial_date);
      initial_date->tm_mon +=
          scheme_.months_of_deposit + 3 * scheme_.quaters_of_deposit;
      time_t current_time_2 = mktime(initial_date);
      duration_in_days =
          (int)((7200 + difftime(current_time_2, current_time_1)) /
                (DAY_IN_SEC));
      initial_date->tm_mon -=
          scheme_.months_of_deposit + 3 * scheme_.quaters_of_deposit;
      time_t current_time_3 = mktime(initial_date);
      initial_date = localtime(&current_time_3);
      scheme_.days_of_deposit = duration_in_days;
    }
  }
  strftime(s1, 80, "%d.%m.%Y %H:%M:%S ", initial_date);
  return duration_in_days;
}
