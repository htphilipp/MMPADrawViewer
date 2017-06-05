#include "viewparam.h"
#include "ui_viewparam.h"
#include "mainwindow.h"
#include <QThread>

viewParam::viewParam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::viewParam)
{
    ui->setupUi(this);
    // mom = parent;
    //range = span;
     ui->lineEdit->setText(QString::number(400));
     ui->lineEdit_2->setText(QString::number(-1));
}


viewParam::~viewParam()
{
    delete ui;
}


void viewParam::on_lineEdit_textChanged(const QString &arg1)
{

    setRange(ui->lineEdit_2->text().toDouble(),ui->lineEdit->text().toDouble());

}


void viewParam::on_lineEdit_2_textChanged(const QString &arg1)
{
    setRange(ui->lineEdit_2->text().toDouble(),ui->lineEdit->text().toDouble());
}

void viewParam::on_highUp_pressed()
{
    double val;

        val = ui->lineEdit->text().toDouble();
        val++;
        ui->lineEdit->setText(QString::number(val));
        QThread::msleep(50);

}

void viewParam::on_highDown_pressed()
{
    double val;
    val = ui->lineEdit->text().toDouble();
    val--;
    ui->lineEdit->setText(QString::number(val));
}

void viewParam::on_lowUp_pressed()
{
    double val;
    val = ui->lineEdit_2->text().toDouble();
    val++;
    ui->lineEdit_2->setText(QString::number(val));
}

void viewParam::on_lowDown_pressed()
{
    double val;
    val = ui->lineEdit_2->text().toDouble();
    val--;
    ui->lineEdit_2->setText(QString::number(val));
}

void viewParam::on_br_x_textChanged(const QString &arg1)
{
    double brx,bry,tlx,tly;
    brx=ui->br_x->text().toDouble();
    bry=ui->br_y->text().toDouble();
    tlx=ui->tl_x->text().toDouble();
    tly=ui->tl_y->text().toDouble();

    setRoi(brx,bry,tlx,tly);
}

void viewParam::on_br_y_textChanged(const QString &arg1)
{
    setRoi(ui->br_x->text().toDouble(),
           ui->br_y->text().toDouble(),
           ui->tl_x->text().toDouble(),
           ui->tl_y->text().toDouble()
           );
}

void viewParam::on_tl_x_textChanged(const QString &arg1)
{
    setRoi(ui->br_x->text().toDouble(),
           ui->br_y->text().toDouble(),
           ui->tl_x->text().toDouble(),
           ui->tl_y->text().toDouble()
           );
}

void viewParam::on_tl_y_textChanged(const QString &arg1)
{
    setRoi(ui->br_x->text().toDouble(),
           ui->br_y->text().toDouble(),
           ui->tl_x->text().toDouble(),
           ui->tl_y->text().toDouble()
           );

}
