#ifndef VIEWPARAM_H
#define VIEWPARAM_H

#include <QDialog>
#include "./qcustomplot.h"
//#include "mainwindow.h"
#include <QTextStream>
#include <functional>

namespace Ui {
class viewParam;
}

class viewParam : public QDialog
{
    Q_OBJECT

public:
    explicit viewParam(QWidget *parent = 0);

    ~viewParam();

   // QWidget* mom;
    //QCPRange *range;

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    //void on_pushButton_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);

   // void setRange(double,double);

    void on_highUp_pressed();

    void on_highDown_pressed();

    void on_lowUp_pressed();

    void on_lowDown_pressed();

    void on_br_x_textChanged(const QString &arg1);

    void on_br_y_textChanged(const QString &arg1);

    void on_tl_x_textChanged(const QString &arg1);

    void on_tl_y_textChanged(const QString &arg1);

signals:
    void setRange(double,double);
    void setRoi(double ,double ,double ,double );

private:
    Ui::viewParam *ui;
};

#endif // VIEWPARAM_H
