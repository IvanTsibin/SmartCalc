#include "credit.h"
#include "ui_credit.h"
#include "s21_credit.h"

Credit::Credit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Credit)
{
    credit_sum_1 = 0; credit_percents_1 = 0.5;
    credit_duration_1 = 1; credit_type_1 = 0;
    ui->setupUi(this);
}

Credit::~Credit()
{
    delete ui;
}



void Credit::get_CreditSum(double value) {
    credit_sum_1 = value;
}


void Credit::get_CreditDuration(int value) {
    credit_duration_1 = value;
}


void Credit::get_CreditType(int value) {
    credit_type_1 = value;
}

void Credit::get_CreditPercents(double value) {
    credit_percents_1 = value;
}


void Credit::make_table() {
    ui->TBCredit->setRowCount(credit_duration_1);

    s21::s21_credit temp;
    temp.start_credit_summ(credit_sum_1);
    temp.start_credit_type((s21::credit_type_t)credit_type_1);
    temp.start_credit_month_time(credit_duration_1);
    temp.start_credit_percents(credit_percents_1);
    temp.calculate_credit();
    QString total_percents_str = QString::number(temp.return_percents_for_all(), 'd', 2);
    ui->TotalPercentsSum->setText(total_percents_str);
    QString total_sum_str = QString::number(temp.return_summ_for_all(), 'd', 2);
    ui->TotalSum->setText(total_sum_str);
    ui->TBCredit->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (int i = 0; i < credit_duration_1; i++) {
        QTableWidgetItem *month = new QTableWidgetItem();
        QString month_str = QString::number( i + 1, 'd', 0);
        month->setText(month_str);
        QTableWidgetItem *month_payment = new QTableWidgetItem();
        QString total_summ_str = QString::number(temp.return_payment_per_month(i), 'd', 2);
        month_payment->setText(total_summ_str);
        QTableWidgetItem *month_base_payment = new QTableWidgetItem();
        QString base_summ_str = QString::number(temp.return_summ_per_month(i), 'd', 2);
        month_base_payment->setText(base_summ_str);
        QTableWidgetItem *percents_for_month = new QTableWidgetItem();
        QString percents_str = QString::number(temp.return_percents_per_month(i), 'd', 2);
        percents_for_month->setText(percents_str);

        ui->TBCredit->setItem(i, 0, month);
        ui->TBCredit->setItem(i, 1, month_payment);
        ui->TBCredit->setItem(i, 2, month_base_payment);
        ui->TBCredit->setItem(i, 3, percents_for_month);
        ui->TBCredit->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        ui->TBCredit->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        ui->TBCredit->item(i, 2)->setTextAlignment(Qt::AlignCenter);
        ui->TBCredit->item(i, 3)->setTextAlignment(Qt::AlignCenter);
    }

    ui->TBCredit->show();
}

