#ifndef PIXHIST_H
#define PIXHIST_H

#include <QDialog>
#include "./qcustomplot.h"
#include <fstream>

namespace Ui {
class pixHist;
}

class pixHist : public QDialog
{
    Q_OBJECT



public:
    explicit pixHist(QWidget *parent = 0);
    //std::vector< float> *datas;
    QCPGraphData data;
    long long xlow,ylow,xhigh,yhigh;
    float   blow,bhigh,db;
    long long NumFrames;

    std::vector< double> freq;
    std::vector< double> binp;

    ~pixHist();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_saveData_clicked();

    void on_savePlot_clicked();

signals:

    float getImdat(long long);

private:
    Ui::pixHist *ui;
};

#endif // PIXHIST_H
