#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QWidget>

namespace Ui {
class Deposit;
}

class Deposit : public QWidget
{
    Q_OBJECT

public:
    explicit Deposit(QWidget *parent = nullptr);
    ~Deposit();

private:
    Ui::Deposit *ui;
    int deposit_duration_1, deposit_type_1;
    int adding_type_1, removing_type_1, adding_periods_1, removing_periods_1;
    double  deposit_sum_1, deposit_percents_1, adding_sum_1, removing_sum_1, unremoveble_1;

public slots:
    void get_DepositSum(double);
    void get_DepositDuration(int);
    void get_DepositType(int);
    void get_DepositPercents(double);
    void get_AddingSum(double);
    void get_AddingPeriods(int);
    void get_AddingType(int);
    void get_RemovingSum(double);
    void get_RemovingPeriods(int);
    void get_RemovingType(int);
    void get_Unremoveble(double);
    void make_table();
};

#endif // DEPOSIT_H
