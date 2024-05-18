#include "xfunction.h"
#include "ui_xfunction.h"
#include "s21_smartcalc.h"
#include <QVector>
#include <math.h>


Xfunction::Xfunction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Xfunction)
{
    steps_amount = 1000;
    ui->setupUi(this);
}

Xfunction::~Xfunction()
{
    delete ui;
}

void Xfunction::make_graph(char *str, double xMax, double xMin, double yMax, double yMin) {
    strcpy(str1, str); xMin1 = xMin, xMax1 = xMax, yMin1 = yMin, yMax1 = yMax;
    QCustomPlot *p = ui->widget;
    QVector<double> x1(steps_amount + 1);
    QVector<double> y1(steps_amount + 1);
    p->clearPlottables();
    s21::calculator temp;
    int graph_counter = 0, graph_steps_amount[steps_amount + 1], steps_amount_counter = 0;
    for (int i = 0; i < steps_amount + 1; i++) {
        graph_steps_amount[i] = 0;
    }
    double temp_x_axis = xMax1, temp_y_axis = yMax1;
    if (xMax1 < xMin1) {
        xMax1 = xMin1;
        xMin1 = temp_x_axis;
    }
    if (yMax1 < yMin1) {
        yMax1 = yMin1;
        yMin1 = temp_y_axis;
    }
    double x_step = (xMax1 - xMin1)/(double)steps_amount;
    double temp_x = xMin1, temp_y_now;
    int flag = 1, initial_counter = 0;
    for (int i = 0; i < steps_amount + 1; i++) {
        x1[initial_counter] = temp_x;
        y1[initial_counter] = temp.calculate_x_factor(str1, temp_x);
         temp_y_now = temp.calculate_x_factor(str1, temp_x);
        if (temp_y_now < yMax1 * 2 && temp_y_now > yMin1 * 2) {
            flag = 1;
            graph_steps_amount[graph_counter] += 1;
            initial_counter++;
        }
        if (flag == 1 && (temp_y_now > yMax1 * 2 || temp_y_now < yMin1 * 2)) {
            graph_counter++;
            flag = 0;
        }  
        temp_x +=x_step;
    }
    graph_counter++;
    p->xAxis->setRange(xMin1*1.05, xMax1*1.05);
    p->yAxis->setRange(yMin1*1.05, yMax1*1.05);
    for (int i = 0; i < graph_counter; i++) {
        QVector<double> x2(graph_steps_amount[i]);
        QVector<double> y2(graph_steps_amount[i]);
        QCPGraph *graph2 = p->addGraph();
        for (int j = 0; j < graph_steps_amount[i]; j++) {
            if (steps_amount_counter > steps_amount + 1) break;
            x2[j] = x1[steps_amount_counter];
            y2[j] = y1[steps_amount_counter];
            steps_amount_counter++;
        }
        if (steps_amount_counter > steps_amount + 1) break;
        graph2->setData(x2,y2);
    }
    p->xAxis->setLabel("X");
    p->yAxis->setLabel("Y");
    p->replot();
}
