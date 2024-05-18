#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include "xfunction.h"
#include "credit.h"
#include "deposit.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;

private:
    Xfunction *x_function;
    Credit *credit;
    Deposit *deposit;
    int cancel_clicked, enter_clicked, entered_number, sign_pressed, x_factor_clicked;
    int credit_duration, credit_type, deposit_duration, deposit_type;
    int adding_type, removing_type, adding_periods, removing_periods;
    double xMin, xMax, yMin, yMax, credit_sum, credit_percents, unremoveble;
    double deposit_sum, deposit_percents, adding_sum, removing_sum;

signals:
//    void send_Xmin(double);
//    void send_Xmax(double);
//    void send_Ymin(double);
//    void send_Ymax(double);
//    void send_str(char*);
    void send_Credit_sum(double);
    void send_Credit_duration(int);
    void send_Credit_type(int);
    void send_Credit_percents(double);
    void send_Deposit_sum(double);
    void send_Deposit_duration(int);
    void send_Deposit_type(int);
    void send_Deposit_percents(double);
    void send_Adding_sum(double);
    void send_Adding_periods(int);
    void send_Adding_type(int);
    void send_Removing_sum(double);
    void send_Removing_periods(int);
    void send_Removing_type(int);
    void send_Unremoveble(double);

private slots:
    void if_entered_number_one();
    void digits_numbers();
    void on_PBdot_clicked();
    void operations();
    void math_operations();
    void on_PBequals_clicked();
    void check_enter_clicked();
    void on_PBcancle_clicked();
    void func_buttons_clicked();
    void on_PBxFactor_clicked();
    void on_PBxMin_clicked();
    void on_PBxMax_clicked();
    void on_PByMin_clicked();
    void on_PByMax_clicked();
    void on_PBxFunction_clicked();
    void on_PBCreditSum_clicked();
    void on_CBCreditType_currentTextChanged(const QString &arg1);
    void on_SBCreditDuration_valueChanged(int arg1);
    void on_PBCredit_clicked();
    void on_DSBPercents_valueChanged(double arg1);
    void on_PBDepositSum_clicked();
    void on_PBDepositAddingSum_clicked();
    void on_PBDepositRemovingSum_clicked();
    void on_DSBDepositPercents_valueChanged(double arg1);
    void on_CBDepositType_currentIndexChanged(const QString &arg1);
    void on_CBDepositAddingType_currentIndexChanged(const QString &arg1);
    void on_CBDepositRemovingType_currentIndexChanged(const QString &arg1);
    void on_SBDepositAddingPeriod_valueChanged(int arg1);
    void on_SBDepositRemovingPeriod_valueChanged(int arg1);
    void on_PBDeposit_clicked();
    void on_PBDepositSum_2_clicked();
    void on_SBDepositDuration_valueChanged(int arg1);
};
#endif // MAINWINDOW_H
