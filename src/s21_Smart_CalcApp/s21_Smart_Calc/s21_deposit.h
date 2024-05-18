#ifndef SRC_S21_BANKING_H_
#define SRC_S21_BANKING_H_

#include <ctime>

namespace s21 {

#define DEPOS_AMOUNT 4000
#define DAY_IN_SEC 86400

typedef enum {
  DAILLY = 0,
  MONTHY = 1,
  QUARTERLY = 2,
  SIMPLE = 3
} deposit_type_t;

class s21_deposit {
public:
  void deposit_full_calculating();

  s21_deposit();
  ~s21_deposit();

  void scheme_start_summ(double sum);
  void scheme_percents(double percents);
  void scheme_days_of_deposit(int days);
  void scheme_months_of_deposit(int months);
  void scheme_quaters_of_deposit(int quaters);
  void scheme_type(deposit_type_t type);
  void scheme_adding_type(deposit_type_t adding_type);
  void scheme_adding_periods(int adding_periods);
  void scheme_adding_summ(double adding_sum);
  void scheme_removing_type(deposit_type_t removing_type);
  void scheme_removing_periods(int removing_periods);
  void scheme_removing_summ(double removing_sum);
  void scheme_unremovble_summ(double unremovble_summ);
  void scheme_amount_of_periods(int amount_of_periods);
  void scheme_tax_percents(double tax_percents);
  void scheme_start_time();

  const time_t *return_start_time(int month_number);
  char *return_start_day(int month_number);
  double return_start_period_summ(int month_number);
  double return_addings(int month_number);
  double return_removings(int month_number);
  double return_summ(int month_number);
  double return_summ_in_deposit(int month_number);
  double return_percents_in_deposit(int month_number);
  double return_full_summ_in_deposit();
  double return_percents_for_all_in_deposit();
  double return_tax_summ_for_all();
  int return_amount_of_periods();

private:
  typedef struct deposit {
    double summ{};
    double percents{};
    int days_of_deposit{};
    int months_of_deposit{};
    int quaters_of_deposit{};
    double percents_for_all{};
    double summ_for_all{};
    double tax_percents{};
    double tax_summ{};
    deposit_type_t type;
    time_t start_time;
    char start_day[40];
  } deposit_t;

  typedef struct deposit_scheme {
    deposit_t deposits[DEPOS_AMOUNT];
    double start_period_summ[DEPOS_AMOUNT];
    double addings[DEPOS_AMOUNT];
    double removings[DEPOS_AMOUNT];
    double start_summ;
    double percents;
    double percents_for_all;
    double unremovble_summ;
    int days_of_deposit;
    int months_of_deposit;
    int quaters_of_deposit;
    deposit_type_t type;
    deposit_type_t adding_type;
    deposit_type_t removing_type;
    int adding_periods;
    int removing_periods;
    double adding_summ;
    double removing_summ;
    double tax_percents;
    double tax_summ_for_all;
    int amount_of_periods;
    time_t start_time;
  } deposit_scheme_t;

  void calculate_deposit(deposit_t *in_deposit);

  void dailly_deposit_calculate(deposit_t *in_deposit);
  void monthy_deposit_calculate(deposit_t *in_deposit);
  void quaterly_deposit_calculate(deposit_t *in_deposit);
  void simple_deposit_calculate(deposit_t *in_deposit);
  int year_in_days(int year_number);
  int year_in_days_for_date(struct tm *current_date);
  void deposit_scheme_calculating();
  void deposit_duration_calculating();
  void deposit_scheme_prepairing();
  int duration_days_calculate(struct tm *initial_date);
  void next_removing_days_calculation(int duration_in_days,
                                      time_t adding_dates[],
                                      int *adding_number);
  void next_adding_days_calculation(int duration_in_days, time_t adding_dates[],
                                    int *removing_number);

  deposit_scheme_t scheme_;
};
} // namespace s21

#endif // SRC_S21_BANKING_H_
