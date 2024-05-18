#include "deposit.h"
#include "ui_deposit.h"
#include "s21_deposit.h"

Deposit::Deposit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Deposit)
{
    deposit_duration_1 = 1; deposit_type_1 = 3;
    adding_type_1 = 1; removing_type_1 = 2; adding_periods_1 = 1; removing_periods_1 = 1;
    deposit_sum_1 = 0; deposit_percents_1 = 0.5; adding_sum_1 = 0; removing_sum_1 = 0; unremoveble_1 = 0;
    ui->setupUi(this);
}

Deposit::~Deposit()
{
    delete ui;
}

void Deposit::get_DepositSum(double value) {
    deposit_sum_1 = value;
}
void Deposit::get_DepositDuration(int value) {
    deposit_duration_1 = value;
}
void Deposit::get_DepositType(int value) {
    deposit_type_1 = value;
}
void Deposit::get_DepositPercents(double value) {
    deposit_percents_1 = value;
}
void Deposit::get_AddingSum(double value) {
    adding_sum_1 = value;
}
void Deposit::get_AddingPeriods(int value) {
    adding_periods_1 = value;
}
void Deposit::get_AddingType(int value) {
    adding_type_1 = value;
}
void Deposit::get_RemovingSum(double value) {
    removing_sum_1 = value;
}
void Deposit::get_RemovingPeriods(int value) {
    removing_periods_1 = value;
}
void Deposit::get_RemovingType(int value) {
    removing_type_1 = value;
}

void Deposit::get_Unremoveble(double value) {
    unremoveble_1 = value;
}

void Deposit::make_table() {
using namespace s21;
        s21::s21_deposit temp;
        temp.scheme_start_summ(deposit_sum_1);
        temp.scheme_percents(deposit_percents_1);
        if (deposit_type_1 == 0) {
            temp.scheme_type(DAILLY);
            temp.scheme_days_of_deposit(deposit_duration_1);
        } else if (deposit_type_1 == 1) {
            temp.scheme_type(MONTHY);
            temp.scheme_months_of_deposit(deposit_duration_1);
        } else if (deposit_type_1 == 2) {
            temp.scheme_type(QUARTERLY);
            temp.scheme_quaters_of_deposit(deposit_duration_1);
        } else {
            temp.scheme_type(SIMPLE);
            temp.scheme_days_of_deposit(deposit_duration_1);
        }
        if (adding_sum_1 == 0) {
            temp.scheme_adding_type((s21::deposit_type_t)deposit_type_1);
            temp.scheme_adding_periods(1);
            temp.scheme_adding_summ(0);
        } else {
            temp.scheme_adding_type((s21::deposit_type_t)adding_type_1);
            temp.scheme_adding_periods(adding_periods_1);
            temp.scheme_adding_summ(adding_sum_1);
        }
        if (removing_sum_1 == 0) {
            temp.scheme_removing_type((s21::deposit_type_t)deposit_type_1);
            temp.scheme_removing_periods(1);
            temp.scheme_removing_summ(0);
        } else {
            temp.scheme_removing_type((s21::deposit_type_t)removing_type_1);
            temp.scheme_removing_periods(removing_periods_1);
            temp.scheme_removing_summ(removing_sum_1);
        }
        temp.scheme_unremovble_summ(unremoveble_1);
        temp.scheme_tax_percents(13);
        temp.deposit_full_calculating();

    ui->TWDeposit->setRowCount(temp.return_amount_of_periods() + 1);
    for (int i = 0; i < temp.return_amount_of_periods() + 1; i++) {
        QTableWidgetItem *step = new QTableWidgetItem();
        QString month_str = QString::number( i + 1, 'd', 0);
        step->setText(month_str);
        QTableWidgetItem *date = new QTableWidgetItem();
        QString date_str = QString::fromStdString(temp.return_start_day(i));
        date->setText(date_str);
        QTableWidgetItem *start_sum = new QTableWidgetItem();
        QString start_sum_str = QString::number( temp.return_start_period_summ(i), 'd', 0);
        start_sum->setText(start_sum_str);
        QTableWidgetItem *adding_sum = new QTableWidgetItem();
        QTableWidgetItem *removing_sum = new QTableWidgetItem();
        if (i < temp.return_amount_of_periods()) {
            QString adding_sum_str = QString::number(temp.return_addings(i), 'd', 0);
            adding_sum->setText(adding_sum_str);
            QString removing_sum_str = QString::number(temp.return_removings(i), 'd', 0);
            removing_sum->setText(removing_sum_str);
        } else {
            QString removing_sum_str = QString::number(0, 'd', 0);
            removing_sum->setText(removing_sum_str);
            QString adding_sum_str = QString::number(0, 'd', 0);
            adding_sum->setText(adding_sum_str);
        }
        QTableWidgetItem *summ = new QTableWidgetItem();
        QString summ_str = QString::number(temp.return_summ(i), 'd', 0);
        summ->setText(summ_str);
        QTableWidgetItem *rezult_sum = new QTableWidgetItem();
        QTableWidgetItem *percents_sum = new QTableWidgetItem();
        if (i < temp.return_amount_of_periods()) {
            QString rezult_sum_str = QString::number(temp.return_summ_in_deposit(i), 'd', 0);
            rezult_sum->setText(rezult_sum_str);
            QString percents_sum_str = QString::number(temp.return_percents_in_deposit(i), 'd', 0);
            percents_sum->setText(percents_sum_str);
        } else {
            QString rezult_sum_str = QString::number(0, 'd', 0);
            rezult_sum->setText(rezult_sum_str);
            QString percents_sum_str = QString::number(0, 'd', 0);
            percents_sum->setText(percents_sum_str);
        }
        ui->TWDeposit->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->TWDeposit->setItem(i, 0, step);
        ui->TWDeposit->setItem(i, 1, date);
        ui->TWDeposit->setItem(i, 2, start_sum);
        ui->TWDeposit->setItem(i, 3, adding_sum);
        ui->TWDeposit->setItem(i, 4, removing_sum);
        ui->TWDeposit->setItem(i, 5, summ);
        ui->TWDeposit->setItem(i, 6, rezult_sum);
        ui->TWDeposit->setItem(i, 7, percents_sum);
        ui->TWDeposit->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        ui->TWDeposit->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        ui->TWDeposit->item(i, 2)->setTextAlignment(Qt::AlignCenter);
        ui->TWDeposit->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        ui->TWDeposit->item(i, 4)->setTextAlignment(Qt::AlignCenter);
        ui->TWDeposit->item(i, 5)->setTextAlignment(Qt::AlignCenter);
        ui->TWDeposit->item(i, 6)->setTextAlignment(Qt::AlignCenter);
        ui->TWDeposit->item(i, 7)->setTextAlignment(Qt::AlignCenter);
    }
    QString rezult_sum_str = QString::number(temp.return_full_summ_in_deposit(), 'd', 0);
    ui->FinalSumOnAccaunt->setText(rezult_sum_str);
    QString percents_sum_str = QString::number(temp.return_percents_for_all_in_deposit(), 'd', 0);
    ui->TotalSumOfPercents->setText(percents_sum_str);
    QString tax_sum_for_percents_str = QString::number(temp.return_tax_summ_for_all(), 'd', 0);
    ui->TaxSumForPercents->setText(tax_sum_for_percents_str);
    ui->TWDeposit->show();
}
