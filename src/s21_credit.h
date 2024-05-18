#ifndef SRC_S21_CREDIT_H_
#define SRC_S21_CREDIT_H_

#include <ctime>

namespace s21 {

typedef enum { DIFF = 0, ANUN = 1 } credit_type_t;

class s21_credit {
public:
  s21_credit();
  ~s21_credit();
  void calculate_credit();
  void start_credit_summ(double sum);
  void start_credit_type(credit_type_t type);
  void start_credit_month_time(int time_in_month);
  void start_credit_percents(double percents);
  double return_payment_per_month(int month_number);
  double return_summ_per_month(int month_number);
  double return_percents_per_month(int month_number);
  double return_summ_for_all();
  double return_percents_for_all();
  int return_month_amount();

private:
  typedef struct credit {
    double payment_per_month[360];
    double summ_per_month[360];
    double percents_per_month[360];
    double percents;
    double percents_for_all;
    double summ_for_all;
    int month_time;
    double summ;
    struct tm time;
    credit_type_t type;
  } credit_t;

  void diff_credit_calculate();
  void anun_credit_calculate();

  credit_t in_credit_;
};
} // namespace s21

#endif // SRC_S21_CREDIT_H_
