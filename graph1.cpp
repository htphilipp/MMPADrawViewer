#include "graph1.h"
#include "ui_graph1.h"

graph1::graph1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::graph1)
{
    ui->setupUi(this);
    ui->g1->addGraph();
    ui->g1->xAxis->setLabel("frame number");
    ui->g1->yAxis->setLabel("Average ROI");
    ui->g1->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    ui->g1->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
    //ui->g1->setRangeDrag(Qt::Horizontal|Qt::Vertical);
    //ui->g1->setRangeZoom(Qt::Horizontal|Qt::Vertical);

//    ui->g1->show();

}

graph1::~graph1()
{
    delete ui;
}


//void        graph1::setROIdat(QVector< double> *xx)
//{
//    double i=0;
//    QVector< double> j(xx->length());

//    int gcount=ui->g1->graphCount();
//    for(auto k=0;k<gcount;k++)
//    {
//        ui->g1->removeGraph(k);
//    }
//    //ui->setupUi(this);
//    ui->g1->addGraph();
//    ui->g1->xAxis->setLabel("frame number");
//    ui->g1->yAxis->setLabel("Average ROI");
//   // ui->g1->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
//    ui->g1->graph(0)->setPen(QPen(Qt::blue));


//    //ui->g1->graph(0)->setData(xdat,ydat);
//    for(auto b=0;b<xx->length();b++)
//    {
//       // ui->g1->graph(0)->addData(i,(*xx)[b]);
//       // i=i+1;
//        j[b]=b;
//    }

//    ui->g1->graph(0)->setData(j, *xx);
//    ui->g1->graph(0)->rescaleAxes();
//    ui->g1->replot();

//}

//void    graph1::setCOMdat(QVector< double>* xx, QVector< double>* yy)
//{
//    double i=0;
//    QVector< double> j(xx->length());

//    int gcount=ui->g1->graphCount();
//    for(auto k=0;k<gcount;k++)
//    {
//        ui->g1->removeGraph(k);
//    }
//    //ui->setupUi(this);
//    ui->g1->addGraph();
//    ui->g1->addGraph();
//    ui->g1->xAxis->setLabel("frame number");
//    ui->g1->yAxis->setLabel("Cent. of mass. (x=blue,y=red)");
//   // ui->g1->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
//   // ui->g1->graph(1)->setBrush(QBrush(QColor(255, 0, 0, 20)));
//    ui->g1->graph(0)->setPen(QPen(Qt::blue));
//    ui->g1->graph(1)->setPen(QPen(Qt::red));



//    //ui->g1->graph(0)->setData(xdat,ydat);
//    for(auto b=0;b<xx->length();b++)
//    {
//       // ui->g1->graph(0)->addData(i,(*xx)[b]);
//       // i=i+1;
//        j[b] = b;
//    }
//    i=0;
////    for(auto b=0;b<yy->length();b++)
////    {
////        ui->g1->graph(1)->addData(i,(*yy)[b]);
////       // ui->g1->graph(1)->addData(i,10);
////        i=i+1;
////    }

//    ui->g1->graph(0)->setData(j, *xx);
//    ui->g1->graph(1)->setData(j, *yy);

//    ui->g1->graph(0)->rescaleAxes();
//    ui->g1->graph(1)->rescaleAxes();
//    ui->g1->replot();


//}



void graph1::on_pushButton_clicked()
{
    this->hide();
}

void graph1::on_pushButton_2_clicked()
{
  //  double xll,xul,yll,yul;

    ui->g1->xAxis->setRange(ui->lineEdit_3->text().toDouble(),ui->lineEdit_4->text().toDouble());
    ui->g1->yAxis->setRange(ui->lineEdit->text().toDouble(),ui->lineEdit_2->text().toDouble());

    ui->g1->replot();
}


void    graph1::setCOMdat(std::vector< double>* xx, std::vector< double>* yy)
{
    double i=0;
    QVector< double> j(xx->size());

    int gcount=ui->g1->graphCount();
    for(auto k=0;k<gcount;k++)
    {
        ui->g1->removeGraph(k);
    }
    //ui->setupUi(this);
    ui->g1->addGraph();
    ui->g1->addGraph();
    ui->g1->xAxis->setLabel("frame number");
    ui->g1->yAxis->setLabel("Cent. of mass. (x=blue,y=red)");
   // ui->g1->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
   // ui->g1->graph(1)->setBrush(QBrush(QColor(255, 0, 0, 20)));
    ui->g1->graph(0)->setPen(QPen(Qt::blue));
    ui->g1->graph(1)->setPen(QPen(Qt::red));



    //ui->g1->graph(0)->setData(xdat,ydat);
    for(auto b=0;b<xx->size();b++)
    {
       // ui->g1->graph(0)->addData(i,(*xx)[b]);
       // i=i+1;
        j[b] = b;
    }
    i=0;
//    for(auto b=0;b<yy->length();b++)
//    {
//        ui->g1->graph(1)->addData(i,(*yy)[b]);
//       // ui->g1->graph(1)->addData(i,10);
//        i=i+1;
//    }

    ui->g1->graph(0)->setData(j,QVector<double>::fromStdVector(*xx));
    ui->g1->graph(1)->setData(j,QVector<double>::fromStdVector(*yy));

    ui->g1->graph(0)->rescaleAxes();
    ui->g1->graph(1)->rescaleAxes();
    ui->g1->replot();

}

void        graph1::setROIdat(std::vector< double> *xx)
{
    double i=0;
    QVector< double> j(xx->size());

    int gcount=ui->g1->graphCount();
    for(auto k=0;k<gcount;k++)
    {
        ui->g1->removeGraph(k);
    }
    //ui->setupUi(this);
    ui->g1->addGraph();
    ui->g1->xAxis->setLabel("frame number");
    ui->g1->yAxis->setLabel("Average ROI");
   // ui->g1->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    ui->g1->graph(0)->setPen(QPen(Qt::blue));


    //ui->g1->graph(0)->setData(xdat,ydat);
    for(auto b=0;b<xx->size();b++)
    {
       // ui->g1->graph(0)->addData(i,(*xx)[b]);
       // i=i+1;
        j[b]=b;
    }

    ui->g1->graph(0)->setData(j, QVector<double>::fromStdVector(*xx));
    ui->g1->graph(0)->rescaleAxes();
    ui->g1->replot();

}

void        graph1::setTIMEdat(std::vector< double> *xx)
{
    double i=0;
    QVector< double> j(xx->size());

    int gcount=ui->g1->graphCount();
    for(auto k=0;k<gcount;k++)
    {
        ui->g1->removeGraph(k);
    }
    //ui->setupUi(this);
    ui->g1->addGraph();
    ui->g1->xAxis->setLabel("frame number");
    ui->g1->yAxis->setLabel("Time stamp running difference (us)");
   // ui->g1->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    ui->g1->graph(0)->setPen(QPen(Qt::blue));


    //ui->g1->graph(0)->setData(xdat,ydat);
    for(auto b=0;b<xx->size();b++)
    {
       // ui->g1->graph(0)->addData(i,(*xx)[b]);
       // i=i+1;
        j[b]=b;
    }

    ui->g1->graph(0)->setData(j, QVector<double>::fromStdVector(*xx));
    ui->g1->graph(0)->rescaleAxes();
    ui->g1->replot();

}



void graph1::on_pushButton_3_clicked()
{
    if(ui->g1->graphCount()>=1)
    {
        if(ui->g1->graph(0)->visible())
        {
            ui->g1->graph(0)->setVisible(0);
        }
        else
        {
            ui->g1->graph(0)->setVisible(1);
        }
        ui->g1->replot();
    }
}

void graph1::on_pushButton_4_clicked()
{
    if(ui->g1->graphCount()>=2)
    {
        if(ui->g1->graph(1)->visible())
        {
            ui->g1->graph(1)->setVisible(0);
        }
        else
        {
            ui->g1->graph(1)->setVisible(1);
        }
        ui->g1->replot();
    }

}

void graph1::on_pushButton_5_clicked()
{
    QFileDialog filedialog;


  //  QCPColorMapData fdat;
    filedialog.setFileMode(QFileDialog::AnyFile);
    QString fileName = filedialog.getSaveFileName(NULL, "Save Plot","","*.png");

    ui->g1->savePng(fileName);
}
