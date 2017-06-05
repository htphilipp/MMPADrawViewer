#ifndef GRAPH1_H
#define GRAPH1_H

#include <QDialog>
#include "./qcustomplot.h"

namespace Ui {
class graph1;
}

class graph1 : public QDialog
{
    Q_OBJECT

public:
    explicit graph1(QWidget *parent = 0);
    QVector< float> xdat;
    QVector< float> ydat;
    QCPGraphData data;



 //   void        setROIdat(QVector< double>*);
//    void        setCOMdat(QVector< double>*,QVector< double>*);

    void        setROIdat(std::vector< double>*);
    void        setTIMEdat(std::vector< double>*);
    void        setCOMdat(std::vector< double>*,std::vector< double>*);

    ~graph1();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::graph1 *ui;
};

#endif // GRAPH1_H
