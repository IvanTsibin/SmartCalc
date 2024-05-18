#ifndef CREDIT_H
#define CREDIT_H

#include <QWidget>

namespace Ui {
class Credit;
}

class Credit : public QWidget
{
    Q_OBJECT

public:
    explicit Credit(QWidget *parent = nullptr);
    ~Credit();

private:
    Ui::Credit *ui;
    double credit_sum_1, credit_percents_1;
    int credit_duration_1, credit_type_1;

public slots:
    void get_CreditSum(double);
    void get_CreditDuration(int);
    void get_CreditType(int);
    void get_CreditPercents(double);
    void make_table();

};

#endif // CREDIT_H
