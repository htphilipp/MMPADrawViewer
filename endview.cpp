#include "endview.h"
#include "ui_endview.h"

EndView::EndView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EndView)
{
    ui->setupUi(this);

    ui->endViewColorMap->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming

    ui->endViewColorMap->axisRect()->setupFullAxesBox(true);
    ui->endViewColorMap->xAxis->setLabel("Omega");
    ui->endViewColorMap->yAxis->setLabel("Azi");
    colorMap = new QCPColorMap(ui->endViewColorMap->xAxis, ui->endViewColorMap->yAxis);
    //colorMap->setGradient(QCPColorGradient::gpThermal);
    colorMap->setGradient(QCPColorGradient::gpGrayscale);

    colorMap->rescaleDataRange();
    colorMap->setAntialiased(0);
    colorMap->setInterpolate(0);

    ui->endViewColorMap->setMouseTracking(1);

    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->endViewColorMap);
    ui->endViewColorMap->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    ui->endViewColorMap->setBackgroundScaled(true);
    ui->endViewColorMap->rescaleAxes(false);
    dataRange.lower = ui->lineEdit_3->text().toDouble();
    dataRange.upper = ui->lineEdit_4->text().toDouble();
    colorMap->setDataRange(dataRange);
    //dataToMap();

    //data.resize(266*getStep());
    //step = getStep();
    //maxViewIndex = getNumFrames()/step;

}

EndView::~EndView()
{
    delete ui;
}

void EndView::on_pushButton_2_clicked()
{
    this->hide();
}

void EndView::on_pushButton_clicked()
{
    step = getStep();
    //ui->horizontalSlider->setRange(0,getNumFrames()/step);

    data.resize(266*step);

    maxViewIndex = getNumFrames()/step;
    colorMap->data()->setSize(step, 266);
    //colorMap->data()->setRange(QCPRange(0, step), QCPRange(0, 266));
    //colorMap->rescaleAxes();
   // colorMap->rescaleDataRange();
    //colorMap->setDataRange();
   // ui->widget->replot();
    dataRange.lower = ui->lineEdit_3->text().toDouble();
    dataRange.upper = ui->lineEdit_4->text().toDouble();
    colorMap->setDataRange(dataRange);
    ui->endViewColorMap->replot();
    ui->horizontalSlider->setRange(0,getNumFrames()/step);

    dataToMap();

}

void EndView::dataToMap()
{
    long long nI = ui->horizontalSlider->value();  // this is the index number  nI*step gives frame offset.
    //data.clear();
    for(auto nn=0;nn<data.size();nn++)
    {
        data[nn]=0;
    }

    bool thrq = ui->checkBox->isChecked();
    double thresh = ui->lineEdit_7->text().toDouble();

    long long minPix,maxPix;
    double temp;
    minPix = ui->lineEdit->text().toInt();
    maxPix = ui->lineEdit_2->text().toInt();

    //colorMap->data()->setCell(j, i, ImDat[N*266*396+i*396+j]);

    if(!ui->radioButton->isChecked())
    {
            for(long long k=minPix;k<=maxPix;k++)  //this will be long dimension in collected data - summed or maxed over this
            {
                for(auto i = 0; i<266;i++)
                {
                    for(auto j = 0; j<step; j++)  //this is width of the view/ colormap in EndView
                    {
                        temp = getImdat((long long)((nI*step+j)*266*396+i*396+k));
                        if(!thrq)
                        {
                            data[i*step+j] += temp;
                        }
                        else
                        {
                            if(temp>=thresh)
                            {
                                data[i*step+j] += temp;
                            }
                        }
                    }
                }
            }
      ui->lframe->setText(QString::number((nI*step+step)));
      ui->sval->setText(QString::number(nI));
     }
     else
     {
            for(auto k=minPix;k<=maxPix;k++)  //this will be long dimension in collected data - summed or maxed over this
            {
                for(auto i = 0; i<266;i++)
                {
                    for(auto j = 0; j<step; j++)  //this is width of the view/ colormap in EndView
                    {
                        temp = getImdat((long long)((nI*step+j)*266*396+i*396+k));
                        if(!thrq)
                        {
                                if(data[i*step+j] < temp)
                                {
                                    data[i*step+j] = temp;
                                }
                        }
                        else
                        {
                            if(temp>=thresh)
                            {
                                if(data[i*step+j] < temp)
                                {
                                    data[i*step+j] = temp;
                                }
                            }
                        }


                        }
                }
            }
        ui->lframe->setText(QString::number((nI*step+step)));
        ui->sval->setText(QString::number(nI));
     }

    for(auto i = 0;i<266;i++)
    {
        for( auto j = 0; j<step;j++)
        {
            colorMap->data()->setCell(j, i,data[i*step+j]);
        }
    }

    ui->endViewColorMap->replot();
    //ui->endViewColorMap->repaint();
   // qApp->processEvents();


}

void EndView::dataToMap(int vv)
{
    //int nI = ui->horizontalSlider->value();  // this is the index number  nI*step gives frame offset.
    //data.clear();

    long long nI = vv;
    bool thrq = ui->checkBox->isChecked();
    double thresh = ui->lineEdit_7->text().toDouble();

    for(auto nn=0;nn<data.size();nn++)
    {
        data[nn]=0;
    }


    long long minPix,maxPix;
    double temp;
    minPix = ui->lineEdit->text().toInt();
    maxPix = ui->lineEdit_2->text().toInt();

    //colorMap->data()->setCell(j, i, ImDat[N*266*396+i*396+j]);

    if(!ui->radioButton->isChecked())
    {
            for(long long k=minPix;k<=maxPix;k++)  //this will be long dimension in collected data - summed or maxed over this
            {
                for(auto i = 0; i<266;i++)
                {
                    for(auto j = 0; j<step; j++)  //this is width of the view/ colormap in EndView
                    {
                        temp = getImdat((long long)((nI*step+j)*266*396+i*396+k));
                        if(!thrq)
                        {
                            data[i*step+j] += temp;
                        }
                        else
                        {
                            if(temp>=thresh)
                            {
                                data[i*step+j] += temp;
                            }
                        }
                    }
                }
            }
      ui->lframe->setText(QString::number((nI*step+step)));
      ui->sval->setText(QString::number(nI));
     }
     else
     {
            for(auto k=minPix;k<=maxPix;k++)  //this will be long dimension in collected data - summed or maxed over this
            {
                for(auto i = 0; i<266;i++)
                {
                    for(auto j = 0; j<step; j++)  //this is width of the view/ colormap in EndView
                    {
                        temp = getImdat((long long)((nI*step+j)*266*396+i*396+k));
                        if(!thrq)
                        {
                                if(data[i*step+j] < temp)
                                {
                                    data[i*step+j] = temp;
                                }
                        }
                        else
                        {
                            if(temp>=thresh)
                            {
                                if(data[i*step+j] < temp)
                                {
                                    data[i*step+j] = temp;
                                }
                            }
                        }


                }
            }
        ui->lframe->setText(QString::number((nI*step+step)));
        ui->sval->setText(QString::number(nI));
            }
     }




//    if(!ui->radioButton->isChecked())
//    {
//            for(long long k=minPix;k<=maxPix;k++)  //this will be long dimension in collected data - summed or maxed over this
//            {
//                for(auto i = 0; i<266;i++)
//                {
//                    for(auto j = 0; j<step; j++)  //this is width of the view/ colormap in EndView
//                    {
//                        data[i*step+j] += getImdat((long long)((nI*step+j)*266*396+i*396+k));
//                    }
//                }
//            }
//            ui->lframe->setText(QString::number((nI*step+step)));
//            ui->sval->setText(QString::number(nI));
//     }
//     else
//     {
//            for(auto k=minPix;k<=maxPix;k++)  //this will be long dimension in collected data - summed or maxed over this
//            {
//                for(auto i = 0; i<266;i++)
//                {
//                    for(auto j = 0; j<step; j++)  //this is width of the view/ colormap in EndView
//                    {
//                        temp = getImdat((long long)((nI*step+j)*266*396+i*396+k));
//                        if(data[i*step+j] < temp)
//                        {
//                            data[i*step+j] = temp;
//                        }
//                    }
//                }
//            }
//            ui->lframe->setText(QString::number((nI*step+step)));
//            ui->sval->setText(QString::number(nI));

//     }

    for(auto i = 0;i<266;i++)
    {
        for( auto j = 0; j<step;j++)
        {
            colorMap->data()->setCell(j, i,data[i*step+j]);
        }
    }

    ui->endViewColorMap->replot();
    //ui->endViewColorMap->repaint();
   // qApp->processEvents();


}



void EndView::on_horizontalSlider_valueChanged(int value)
{
    if(value<(maxViewIndex))
    {
        dataToMap();
    }
}

void EndView::on_pushButton_3_clicked()
{
    long long maxv;
    long long minv;

    maxv=ui->lineEdit_6->text().toLongLong();
    minv=ui->lineEdit_5->text().toLongLong();

    if((minv>maxViewIndex) || (minv<0))
    {
        minv=0;
    }

    if((maxv>maxViewIndex) || (maxv<0))
    {
        maxv=maxViewIndex;
    }


    for(auto i = minv;i<(maxv);i++)
    {
        dataToMap(i);
    }
}

void EndView::on_pushButton_4_clicked()
{
    QFileDialog filedialog;
    filedialog.setFileMode(QFileDialog::AnyFile);
    QString rootfileName = filedialog.getSaveFileName(NULL, "Save Many Images","","*.png");
    long long maxv;
    long long minv;
    maxv=ui->lineEdit_6->text().toLongLong();
    minv=ui->lineEdit_5->text().toLongLong();


    if(!rootfileName.isEmpty())
    {
        if((minv>maxViewIndex) || (minv<0))
        {
            minv=0;
        }

        if((maxv>maxViewIndex) || (maxv<0))
        {
            maxv=maxViewIndex;
        }


        for(auto i = minv;i<(maxv);i++)
        {
            dataToMap(i);
            ui->endViewColorMap->savePng(rootfileName+QString::number(i).rightJustified(6, '0')+".png");
        }


    }
}

void EndView::on_comboBox_activated(const QString &arg1)
{
    if(!(QString::compare("Gray",arg1)))
    {
        colorMap->setGradient(QCPColorGradient::gpGrayscale);
    }

    if(!(QString::compare("Jet",arg1)))
    {
        colorMap->setGradient(QCPColorGradient::gpJet);
    }

    if(!(QString::compare("Ion",arg1)))
    {
        colorMap->setGradient(QCPColorGradient::gpIon);
    }

    if(!(QString::compare("Candy",arg1)))
    {
        colorMap->setGradient(QCPColorGradient::gpCandy);
    }

    if(!(QString::compare("Spectrum",arg1)))
    {
        colorMap->setGradient(QCPColorGradient::gpSpectrum);
    }

    if(!(QString::compare("Polar",arg1)))
    {
        colorMap->setGradient(QCPColorGradient::gpPolar);
    }

    if(!(QString::compare("Night",arg1)))
    {
        colorMap->setGradient(QCPColorGradient::gpNight);
    }

    if(!(QString::compare("Geography",arg1)))
    {
        colorMap->setGradient(QCPColorGradient::gpGeography);
    }

    if(!(QString::compare("Thermal",arg1)))
    {
        colorMap->setGradient(QCPColorGradient::gpThermal);
    }


}
