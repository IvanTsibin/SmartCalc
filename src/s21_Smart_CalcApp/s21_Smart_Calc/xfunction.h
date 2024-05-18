#ifndef XFUNCTION_H
#define XFUNCTION_H

#include <QWidget>

namespace Ui {
class Xfunction;
}

class Xfunction : public QWidget
{
    Q_OBJECT

public:
    explicit Xfunction(QWidget *parent = nullptr);
    ~Xfunction();

private:
    Ui::Xfunction *ui;
    double xMin1, xMax1, yMin1, yMax1;
    char str1[255];
    int N, steps_amount;

public slots:
//    void get_Xmax(double);
//    void get_Xmin(double);
//    void get_Ymax(double);
//    void get_Ymin(double);
//    void get_str(char*);
    void make_graph(char*, double, double, double, double);

private slots:

};

#endif // XFUNCTION_H
