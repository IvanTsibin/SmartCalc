#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "s21_smartcalc.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    cancel_clicked = 0; enter_clicked = 0; entered_number = 0; sign_pressed = 0; x_factor_clicked = 0;
    credit_duration = 12; credit_type = 1; deposit_duration = 365; deposit_type = 3;
    adding_type = 1; removing_type = 2; adding_periods = 1; removing_periods = 1;
    xMin = 0; xMax = 0; yMin = 0; yMax = 0; credit_sum = 1000000; credit_percents = 20; unremoveble = 0;
    deposit_sum = 1000000; deposit_percents = 20; adding_sum = 0; removing_sum = 0;
    ui->setupUi(this);

    connect(ui->PBnumber0,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->PBnumber1,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->PBnumber2,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->PBnumber3,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->PBnumber4,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->PBnumber5,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->PBnumber6,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->PBnumber7,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->PBnumber8,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->PBnumber9,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->PBplusAndMinus,SIGNAL(clicked()),this,SLOT(operations()));
    connect(ui->PBplus,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->PBminus,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->PBmultip,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->PBdiv,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->PBexp,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->PBequals,SIGNAL(clicked()),this,SLOT(on_PBequals_clicked()));
    connect(ui->PBcancle,SIGNAL(clicked()),this,SLOT(on_PBcancle_clicked()));
    connect(ui->PBleftBrace,SIGNAL(clicked()),this,SLOT(func_buttons_clicked()));
    connect(ui->PBrightBrace,SIGNAL(clicked()),this,SLOT(func_buttons_clicked()));
    connect(ui->PBsin,SIGNAL(clicked()),this,SLOT(func_buttons_clicked()));
    connect(ui->PBcos,SIGNAL(clicked()),this,SLOT(func_buttons_clicked()));
    connect(ui->PBtan,SIGNAL(clicked()),this,SLOT(func_buttons_clicked()));
    connect(ui->PBasin,SIGNAL(clicked()),this,SLOT(func_buttons_clicked()));
    connect(ui->PBacos,SIGNAL(clicked()),this,SLOT(func_buttons_clicked()));
    connect(ui->PBatan,SIGNAL(clicked()),this,SLOT(func_buttons_clicked()));
    connect(ui->PBln,SIGNAL(clicked()),this,SLOT(func_buttons_clicked()));
    connect(ui->PBlog,SIGNAL(clicked()),this,SLOT(func_buttons_clicked()));
    connect(ui->PBsqrt,SIGNAL(clicked()),this,SLOT(func_buttons_clicked()));
    connect(ui->PBmod,SIGNAL(clicked()),this,SLOT(func_buttons_clicked()));


    ui->PBplus->setCheckable(true);
    ui->PBminus->setCheckable(true);
    ui->PBmultip->setCheckable(true);
    ui->PBdiv->setCheckable(true);
    ui->PBcancle->setCheckable(true);
    ui->PBequals->setCheckable(true);
    ui->PBxFactor->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    check_enter_clicked();
    QString new_label;
    if (event->key() == Qt::Key_1 && !ui->PBxFactor->isChecked()) {
        if (ui->RezultShow->text() == "0") {
            ui->RezultShow->setText("1");
        } else {
            ui->RezultShow->setText(ui->RezultShow->text() + "1");
        }
        entered_number = 1; sign_pressed = 0;
    } else if (event->key() == Qt::Key_2 && !ui->PBxFactor->isChecked()) {
        if (ui->RezultShow->text() == "0") {
            ui->RezultShow->setText("2");
        } else {
            ui->RezultShow->setText(ui->RezultShow->text() + "2");
        }
        entered_number = 1; sign_pressed = 0;
    } else if (event->key() == Qt::Key_3 && !ui->PBxFactor->isChecked()) {
        if (ui->RezultShow->text() == "0") {
            ui->RezultShow->setText("3");
        } else {
            ui->RezultShow->setText(ui->RezultShow->text() + "3");
        }
        entered_number = 1; sign_pressed = 0;
    } else if (event->key() == Qt::Key_4 && !ui->PBxFactor->isChecked()) {
        if (ui->RezultShow->text() == "0") {
            ui->RezultShow->setText("4");
        } else {
            ui->RezultShow->setText(ui->RezultShow->text() + "4");
        }
        entered_number = 1; sign_pressed = 0;
    } else if (event->key() == Qt::Key_5 && !ui->PBxFactor->isChecked()) {
        if (ui->RezultShow->text() == "0") {
            ui->RezultShow->setText("5");
        } else {
            ui->RezultShow->setText(ui->RezultShow->text() + "5");
        }
        entered_number = 1; sign_pressed = 0;
    } else if (event->key() == Qt::Key_6 && !ui->PBxFactor->isChecked()) {
        if (ui->RezultShow->text() == "0") {
            ui->RezultShow->setText("6");
        } else {
            ui->RezultShow->setText(ui->RezultShow->text() + "6");
        }
        entered_number = 1; sign_pressed = 0;
    } else if (event->key() == Qt::Key_7 && !ui->PBxFactor->isChecked()) {
        if (ui->RezultShow->text() == "0") {
            ui->RezultShow->setText("7");
        } else {
            ui->RezultShow->setText(ui->RezultShow->text() + "7");
        }
        entered_number = 1; sign_pressed = 0;
    } else if (event->key() == Qt::Key_8 && !ui->PBxFactor->isChecked()) {
        if (ui->RezultShow->text() == "0") {
            ui->RezultShow->setText("8");
        } else {
            ui->RezultShow->setText(ui->RezultShow->text() + "8");
        }
        entered_number = 1; sign_pressed = 0;
    } else if (event->key() == Qt::Key_9 && !ui->PBxFactor->isChecked()) {
        if (ui->RezultShow->text() == "0") {
            ui->RezultShow->setText("9");
        } else {
            ui->RezultShow->setText(ui->RezultShow->text() + "9");
        }
        entered_number = 1; sign_pressed = 0;
    } else if (event->key() == Qt::Key_0 && !ui->PBxFactor->isChecked()) {
        if (ui->RezultShow->text() != "0") {
        ui->RezultShow->setText(ui->RezultShow->text() + "0");
        }
        entered_number = 1; sign_pressed = 0;
    } else if (event->key() == Qt::Key_Period) {
        if(!(ui->RezultShow->text().contains('.'))) {
            ui->RezultShow->setText(ui->RezultShow->text() + ".");
            entered_number = 1; sign_pressed = 0;
        }
    } else if (event->key() == Qt::Key_Plus && sign_pressed == 0) {
        if_entered_number_one();
        ui->TextShow->setText(ui->TextShow->text() + "+");
        ui->PBplus->setChecked(true); ui->PBxFactor->setChecked(false);
        ui->RezultShow->setText("");  entered_number = 0; sign_pressed = 1;
    } else if (event->key() == Qt::Key_Minus && sign_pressed == 0) {
        if (ui->RezultShow->text() == "0" && ui->TextShow->text() == "") {
            ui->RezultShow->setText("-");
        } else {
            if_entered_number_one();
            ui->TextShow->setText(ui->TextShow->text() + "-");
            ui->PBminus->setChecked(true); ui->PBxFactor->setChecked(false);
            ui->RezultShow->setText("");  entered_number = 0; sign_pressed = 1;
        }
    } else if (event->key() == Qt::Key_Asterisk && sign_pressed == 0) {
        if_entered_number_one();
        ui->TextShow->setText(ui->TextShow->text() + "*");
        ui->PBmultip->setChecked(true); ui->PBxFactor->setChecked(false);
        ui->RezultShow->setText("");  entered_number = 0; sign_pressed = 1;
    } else if (event->key() == Qt::Key_Slash && sign_pressed == 0) {
        if_entered_number_one();
        ui->TextShow->setText(ui->TextShow->text() + "/");
        ui->PBdiv->setChecked(true); ui->PBxFactor->setChecked(false);
        ui->RezultShow->setText("");  entered_number = 0; sign_pressed = 1;
    } else if (event->key() == Qt::Key_Enter && sign_pressed == 0) {
        ui->PBequals->setChecked(true); ui->PBxFactor->setChecked(false);
        on_PBequals_clicked();
    } else if (event->key() == Qt::Key_Escape) {
        ui->PBcancle->setChecked(true);
        entered_number = 0;
        on_PBcancle_clicked();
    } else if (event->key() == Qt::Key_E && sign_pressed == 0) {
        if_entered_number_one();
        ui->TextShow->setText(ui->TextShow->text() + "E");
        ui->RezultShow->setText("");  entered_number = 0;
    }
}

void MainWindow::if_entered_number_one() {
    if (entered_number == 1) {
        if ((ui->RezultShow->text()).toDouble() < 0 && ui->TextShow->text() != "") {
            ui->TextShow->setText(ui->TextShow->text() + "(" + ui->RezultShow->text() + ")");
            ui->RezultShow->setText("");
        } else {
            ui->TextShow->setText(ui->TextShow->text() + ui->RezultShow->text());
            ui->RezultShow->setText("");
        }
    }
}

void MainWindow::digits_numbers() {
    if (!ui->PBxFactor->isChecked()) {
        check_enter_clicked();
        QPushButton *button = (QPushButton *) sender();
        if (ui->RezultShow->text() == "0") {
            ui->RezultShow->setText(button->text());
        } else {
            ui->RezultShow->setText(ui->RezultShow->text() + button->text());
        }
        entered_number = 1; sign_pressed = 0;
    }
}

void MainWindow::operations() {
    QPushButton *button = (QPushButton *) sender();
    double all_numbers;
    QString new_label;
    if(button->text() == "+-") {
    all_numbers = (ui->RezultShow->text()).toDouble();
    all_numbers = all_numbers * (-1);
    new_label = QString::number(all_numbers, 'g', 15);
    ui->RezultShow->setText(new_label);
    }
}

void MainWindow::on_PBdot_clicked()
{
    if (!ui->PBxFactor->isChecked()) {
        if(!(ui->RezultShow->text().contains('.')))
            ui->RezultShow->setText(ui->RezultShow->text() + ".");
    }
}

void MainWindow::on_PBequals_clicked()
{
    if (ui->TextShow->text() != "" && ui->TextShow->text() != "0") {
        if (ui->PBequals->isChecked() && enter_clicked == 0) {
            if (ui->RezultShow->text() != "" && ui->RezultShow->text() != "0") if_entered_number_one();
            if (x_factor_clicked == 0) {
                char cstr[255];
                QByteArray bytes = ui->TextShow->text().toLocal8Bit();
                strcpy (cstr, bytes.data ());
                s21::calculator temp;
                double labelNumber = temp.calculate_init_str(cstr);
                QString new_label = QString::number(labelNumber, 'g', 15);
                ui->TextShow->setText(ui->TextShow->text() + "=" + new_label);
                ui->RezultShow->setText("");
                ui->PBequals->setChecked(false);
            } else {
                on_PBxFunction_clicked();
                ui->PBequals->setChecked(false);
            }
            enter_clicked = 1;
        } else if (ui->PBequals->isChecked() && enter_clicked == 1) {
            ui->TextShow->setText("");
            ui->RezultShow->setText("0");
            ui->PBequals->setChecked(false);
            enter_clicked = 0;
            sign_pressed = 0;
        }
    }
}

void MainWindow::check_enter_clicked()
{
    if (enter_clicked == 1) {
        ui->TextShow->setText("");
        ui->RezultShow->setText("0");
        ui->PBequals->setChecked(false);
        enter_clicked = 0;
        sign_pressed = 0;
    }
}

void MainWindow::math_operations()
{
    check_enter_clicked();
    QPushButton *button = (QPushButton *) sender();
    if (entered_number == 1) ui->TextShow->setText(ui->TextShow->text() + ui->RezultShow->text());
    if((ui->PBplus->isChecked() || button->text() == "+") && sign_pressed == 0) {
        ui->TextShow->setText(ui->TextShow->text() + "+");
        ui->PBplus->setChecked(false); sign_pressed = 1;
    } else if ((ui->PBminus->isChecked() || button->text() == "-") && sign_pressed == 0) {
        ui->TextShow->setText(ui->TextShow->text() + "-");
        ui->PBminus->setChecked(false); sign_pressed = 1;
    } else if ((ui->PBmultip->isChecked() || button->text() == "*") && sign_pressed == 0) {
        ui->TextShow->setText(ui->TextShow->text() + "*");
        ui->PBmultip->setChecked(false); sign_pressed = 1;
    } else if ((ui->PBdiv->isChecked() || button->text() == "/") && sign_pressed == 0) {
       ui->TextShow->setText(ui->TextShow->text() + "/");
       ui->PBdiv->setChecked(false); sign_pressed = 1;
    } else if ((ui->PBexp->isChecked() || button->text() == "^") && sign_pressed == 0) {
       ui->TextShow->setText(ui->TextShow->text() + "^");
       ui->PBexp->setChecked(false); sign_pressed = 1;
    }
    ui->RezultShow->setText("");
    button->setChecked(false);  ui->PBxFactor->setChecked(false);
}

void MainWindow::on_PBcancle_clicked()
{
    if (enter_clicked == 1) {
        ui->TextShow->setText("");
        ui->RezultShow->setText("0");
        ui->PBcancle->setChecked(false);
        ui->PBequals->setChecked(false);
        enter_clicked = 0;
    } else if (ui->PBcancle->isChecked() && cancel_clicked == 1) {
        ui->TextShow->setText("");
        ui->PBcancle->setChecked(false);
        cancel_clicked = 0;
        x_factor_clicked = 0;
    } else if (ui->PBcancle->isChecked() && cancel_clicked == 0){
        ui->RezultShow->setText("0");
        ui->PBcancle->setChecked(false);
         ui->PBxFactor->setChecked(false);
        cancel_clicked = 1;
    }
}

void MainWindow::func_buttons_clicked()
{
    check_enter_clicked();
    QPushButton *button = (QPushButton *) sender();
     if (button->text() == "(") {
        ui->TextShow->setText(ui->TextShow->text() + "(");
     } else if (button->text() == ")") {
        ui->TextShow->setText(ui->TextShow->text() + ui->RezultShow->text());
        ui->TextShow->setText(ui->TextShow->text() + ")");
     } else if (button->text() == "sin") {
        ui->TextShow->setText(ui->TextShow->text() + "sin(");
     } else if (button->text() == "cos") {
        ui->TextShow->setText(ui->TextShow->text() + "cos(");
     } else if (button->text() == "tan") {
        ui->TextShow->setText(ui->TextShow->text() + "tan(");
     } else if (button->text() == "asin") {
        ui->TextShow->setText(ui->TextShow->text() + "asin(");
     } else if (button->text() == "acos") {
        ui->TextShow->setText(ui->TextShow->text() + "acos(");
     } else if (button->text() == "atan") {
        ui->TextShow->setText(ui->TextShow->text() + "atan(");
     } else if (button->text() == "ln") {
        ui->TextShow->setText(ui->TextShow->text() + "ln(");
     } else if (button->text() == "log") {
        ui->TextShow->setText(ui->TextShow->text() + "log(");
     } else if (button->text() == "sqrt") {
        ui->TextShow->setText(ui->TextShow->text() + "sqrt(");
     } else if (button->text() == "mod") {
        ui->TextShow->setText(ui->TextShow->text() + ui->RezultShow->text() + "mod");
     } else if (button->text() == "^") {
         ui->TextShow->setText(ui->TextShow->text() + ui->RezultShow->text() + "^");
      }
    entered_number = 0;
    ui->RezultShow->setText("");
    ui->PBxFactor->setChecked(false);
}



void MainWindow::on_PBxFactor_clicked()
{
    ui->PBxFactor->setChecked(true);
    ui->TextShow->setText(ui->TextShow->text() + "x");
    ui->RezultShow->setText("");
    x_factor_clicked = 1;
    entered_number = 1;
    sign_pressed = 0;
}

void MainWindow::on_PBxMin_clicked()
{
    ui->XminRezult->setText(ui->RezultShow->text());
    ui->RezultShow->setText("0");
}

void MainWindow::on_PBxMax_clicked()
{
    ui->XmaxRezult->setText(ui->RezultShow->text());
    ui->RezultShow->setText("0");
}

void MainWindow::on_PByMin_clicked()
{
    ui->YminRezult->setText(ui->RezultShow->text());
    ui->RezultShow->setText("0");
}

void MainWindow::on_PByMax_clicked()
{
    ui->YmaxRezult->setText(ui->RezultShow->text());
    ui->RezultShow->setText("0");
}

void MainWindow::on_PBxFunction_clicked()
{
    if (ui->RezultShow->text() == "0") ui->RezultShow->setText("");
    if (ui->RezultShow->text() != "") {
        ui->TextShow->setText(ui->TextShow->text() + ui->RezultShow->text());
    }
    ui->RezultShow->setText("0");
    x_function = new Xfunction();
    yMax = (ui->YmaxRezult->text()).toDouble();
    yMin = (ui->YminRezult->text()).toDouble();
    xMax = (ui->XmaxRezult->text()).toDouble();
    xMin = (ui->XminRezult->text()).toDouble();
    char cstr[255];
    QByteArray bytes = ui->TextShow->text().toLocal8Bit();
    strcpy (cstr, bytes.data ());
    x_function->show();
    x_function->make_graph(cstr, xMax, xMin, yMax, yMin);
}

void MainWindow::on_PBCreditSum_clicked()
{
    credit_sum = (ui->RezultShow->text()).toDouble();
    QString new_lable;
    int temp = (int)credit_sum;
    new_lable = QString::number(temp, 'd', 0);
    ui->CreditSum->setText(new_lable);
    ui->RezultShow->setText("0");
}

void MainWindow::on_CBCreditType_currentTextChanged(const QString &arg1)
{
    if (arg1 == "ANUITENT") {
        credit_type = 1;
    } else {
        credit_type = 0;
    }
}

void MainWindow::on_SBCreditDuration_valueChanged(int arg1)
{
    credit_duration = arg1;
}

void MainWindow::on_PBCredit_clicked()
{
    credit = new Credit();

    connect(this, &MainWindow::send_Credit_sum, credit, &Credit::get_CreditSum);
    connect(this, &MainWindow::send_Credit_duration, credit, &Credit::get_CreditDuration);
    connect(this, &MainWindow::send_Credit_type, credit, &Credit::get_CreditType);
    connect(this, &MainWindow::send_Credit_percents, credit, &Credit::get_CreditPercents);

    emit send_Credit_sum(credit_sum);
    emit send_Credit_duration(credit_duration);
    emit send_Credit_type(credit_type);
    emit send_Credit_percents(credit_percents);

    credit->show();
    credit->make_table();
}


void MainWindow::on_DSBPercents_valueChanged(double arg1)
{
    credit_percents = arg1;
}

void MainWindow::on_PBDepositSum_clicked()
{
    deposit_sum = (ui->RezultShow->text()).toDouble();
    QString new_lable;
    int temp = (int)deposit_sum;
    new_lable = QString::number(temp, 'd', 0);
    ui->DepositSum->setText(new_lable);
    ui->RezultShow->setText("0");
}


void MainWindow::on_PBDepositAddingSum_clicked()
{
    adding_sum = (ui->RezultShow->text()).toDouble();
    QString new_lable;
    int temp = (int)adding_sum;
    new_lable = QString::number(temp, 'd', 0);
    ui->DepositAddingSum->setText(new_lable);
    ui->RezultShow->setText("0");
}

void MainWindow::on_PBDepositRemovingSum_clicked()
{
    removing_sum = (ui->RezultShow->text()).toDouble();
    QString new_lable;
    int temp = (int)removing_sum;
    new_lable = QString::number(temp, 'd', 0);
    ui->DepositRemovingSum->setText(new_lable);
    ui->RezultShow->setText("0");
}

void MainWindow::on_DSBDepositPercents_valueChanged(double arg1)
{
    deposit_percents = arg1;
}

void MainWindow::on_CBDepositType_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "DAILLY") {
        deposit_type = 0;
    } else if (arg1 == "MONTHY") {
        deposit_type = 1;
    } else if (arg1 == "QUATERLY") {
        deposit_type = 2;
    } else {
        deposit_type = 3;
    }
}

void MainWindow::on_CBDepositAddingType_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "DAILLY") {
        adding_type = 0;
    } else if (arg1 == "MONTHY") {
        adding_type = 1;
    } else if (arg1 == "QUATERLY") {
        adding_type = 2;
    }
}



void MainWindow::on_CBDepositRemovingType_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "DAILLY") {
        removing_type = 0;
    } else if (arg1 == "MONTHY") {
        removing_type = 1;
    } else if (arg1 == "QUATERLY") {
        removing_type = 2;
    }
}

void MainWindow::on_SBDepositAddingPeriod_valueChanged(int arg1)
{
    adding_periods = arg1;
}

void MainWindow::on_SBDepositRemovingPeriod_valueChanged(int arg1)
{
    removing_periods = arg1;
}

void MainWindow::on_PBDeposit_clicked()
{
    deposit = new Deposit();

    connect(this, &MainWindow::send_Deposit_sum, deposit, &Deposit::get_DepositSum);
    connect(this, &MainWindow::send_Deposit_duration, deposit, &Deposit::get_DepositDuration);
    connect(this, &MainWindow::send_Deposit_type, deposit, &Deposit::get_DepositType);
    connect(this, &MainWindow::send_Deposit_percents, deposit, &Deposit::get_DepositPercents);
    connect(this, &MainWindow::send_Adding_sum, deposit, &Deposit::get_AddingSum);
    connect(this, &MainWindow::send_Adding_periods, deposit, &Deposit::get_AddingPeriods);
    connect(this, &MainWindow::send_Adding_type, deposit, &Deposit::get_AddingType);
    connect(this, &MainWindow::send_Removing_sum, deposit, &Deposit::get_RemovingSum);
    connect(this, &MainWindow::send_Removing_periods, deposit, &Deposit::get_RemovingPeriods);
    connect(this, &MainWindow::send_Removing_type, deposit, &Deposit::get_RemovingType);
    connect(this, &MainWindow::send_Unremoveble, deposit, &Deposit::get_Unremoveble);

    emit send_Deposit_sum(deposit_sum);
    emit send_Deposit_duration(deposit_duration);
    emit send_Deposit_type(deposit_type);
    emit send_Deposit_percents(deposit_percents);
    emit send_Adding_sum(adding_sum);
    emit send_Adding_periods(adding_periods);
    emit send_Adding_type(adding_type);
    emit send_Removing_sum(removing_sum);
    emit send_Removing_periods(removing_periods);
    emit send_Removing_type(removing_type);
    emit send_Unremoveble(unremoveble);

    deposit->show();
    deposit->make_table();
}

void MainWindow::on_PBDepositSum_2_clicked()
{
    unremoveble = (ui->RezultShow->text()).toDouble();
    QString new_lable;
    int temp = (int)unremoveble;
    new_lable = QString::number(temp, 'd', 0);
    ui->UnremovebleSum->setText(new_lable);
    ui->RezultShow->setText("0");
}

void MainWindow::on_SBDepositDuration_valueChanged(int arg1)
{
    deposit_duration = arg1;
}

