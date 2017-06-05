#include "pixhist.h"
#include "ui_pixhist.h"

pixHist::pixHist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pixHist)
{
    ui->setupUi(this);

    ui->widget->xAxis->setLabel("Value");
    ui->widget->yAxis->setLabel("Frequency");

    ui->widget->addGraph();
    ui->widget->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    ui->widget->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

   // datas = imd;

 //   freq    =   new std::vector< double>();
 //   binp    =   new std::vector< double>();


}

pixHist::~pixHist()
{
    delete ui;
}

void pixHist::on_pushButton_clicked()
{

    int gcount=ui->widget->graphCount();
    for(auto k=0;k<gcount;k++)
    {
        ui->widget->removeGraph(k);
    }
    ui->widget->addGraph();

    blow    = ui->lineEdit->text().toFloat();
    bhigh   = ui->lineEdit_2->text().toFloat();
    db      = ui->lineEdit_3->text().toFloat();

    long long fn,x,y;
    int i = 1;
    double te;
//    std::vector< double> *freq;
//    std::vector< double> *binp;
    //QVector<double> freq;
    //QVector<double> binp;

//    freq    =   new std::vector< double>();
//    binp    =   new std::vector< double>();

    ui->widget->graph(0)->setPen(QPen(Qt::blue));

    binp.clear();
    freq.clear();

    binp.push_back(blow);

    while(binp[binp.size()-1]<bhigh)
    {
        binp.push_back(blow+(i)*db);
        i++;
    }

     freq.resize(binp.size());

    for(i=0;i<int(binp.size());i++)
    {
        freq[i]=0;
    }

    for( fn = 0;fn<NumFrames;fn++)
    {
        for( x=xlow;x<=xhigh;x++)
        {
            for( y=ylow;y<=yhigh;y++)
            {

                te = double(getImdat(fn*266*396+y*396+x));
                i=0;

                while((binp[i]<te)&&(i<int(binp.size())))
                {
                    i++;
                }

                if(i<int(freq.size()))
                {
                    freq[i] = freq[i]+1.0;
                }

            }
        }

    }

    for(auto k = 0;k<binp.size();k++)
    {
        binp[k] -= db/2;
    }
    //centering display
//    for(i=0;i<binp.size();i++)
//    {
//        binp[i]-=0.5*db;
//    }

    te=0;
   // freq[2]=10;

      this->ui->widget->graph(0)->setData(QVector< double>::fromStdVector(binp),QVector< double>::fromStdVector(freq));
   // ui->widget->graph(0)->setData()

    ui->widget->graph(0)->rescaleAxes();
//    ui->widget->xAxis->setRange(xlow,xhigh);
    ui->widget->replot();


}

void pixHist::on_pushButton_2_clicked()
{
    ui->widget->yAxis->setScaleType(QCPAxis::stLogarithmic);
    ui->widget->replot();
}

void pixHist::on_pushButton_3_clicked()
{
    ui->widget->yAxis->setScaleType(QCPAxis::stLinear);
    ui->widget->replot();
}

void pixHist::on_pushButton_4_clicked()
{
    ui->widget->xAxis->setRange(ui->xlow->text().toDouble(),ui->xhigh->text().toDouble());
    ui->widget->yAxis->setRange(ui->ylow->text().toDouble(),ui->yhigh->text().toDouble());

    ui->widget->replot();
}

void pixHist::on_saveData_clicked()
{
    QFileDialog filedialog;


  //  QCPColorMapData fdat;
    filedialog.setFileMode(QFileDialog::AnyFile);
    try
    {
        QString fileName = filedialog.getSaveFileName(NULL, "Save File","","");
        std::ofstream outf(fileName.toStdString(),std::ios::out);
        if(outf)
        {
            outf<<"energy, occupancy"<<std::endl;
            if(binp.size() == freq.size())
            {
                    for(auto j=0;j<binp.size();j++)
                    {
                        outf<<binp[j]<<", "<<freq[j]<<std::endl;
                    }
            }
        }
        outf.close();
    }
    catch(const char* msg)
    {

    }

}

void pixHist::on_savePlot_clicked()
{
    QFileDialog filedialog;


  //  QCPColorMapData fdat;
    filedialog.setFileMode(QFileDialog::AnyFile);
    QString fileName = filedialog.getSaveFileName(NULL, "Save Plot","","*.png");

    ui->widget->savePng(fileName);
}
