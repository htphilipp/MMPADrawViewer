#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    //initializing pointers to nullptr for memory tracking
    colorMap    =nullptr;
    roi         =nullptr;
    tempLine    =nullptr;
    paramWin    =nullptr;
    outg1       =nullptr;
    phist       =nullptr;

    // end initilizations




    N=0;
    dataRange.lower=-1.0;
    dataRange.upper=400;
    int height,width;
    paramWin = new viewParam(this);
    paramWin->show();

    outg1 = new graph1(this);

    phist = new pixHist();
    endv = new EndView();
    helpstuff = new helpExplanations();
    threshexp = new threshExport();

    //phist->datas = &ImDat;


    //outg1->show();
    outg1->setROIdat(&roisum);
    //outg1->ui->g1->xAxis->setLabel("frame number");


    // making connection between viewParam and main window so range can be set.
    connect(paramWin, SIGNAL(setRange(double,double)),this, SLOT(setRange(double,double)));
    connect(paramWin, SIGNAL(setRoi(double,double,double,double)),this, SLOT(setRoi(double,double,double,double)));
    connect(phist, SIGNAL(getImdat(long long)),this, SLOT(getImdat(long long)));
    connect(endv, SIGNAL(getImdat(long long)),this, SLOT(getImdat(long long)));
    connect(endv, SIGNAL(getNumFrames()),this, SLOT(getNumFrames()));
    connect(endv, SIGNAL(getStep()),this, SLOT(getStep()));

    connect(threshexp, SIGNAL(getImdat(long long)),this, SLOT(getImdat(long long)));
    connect(threshexp, SIGNAL(getNumFrames()),this, SLOT(getNumFrames()));


    ui->setupUi(this);
    ui->widget->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming

    ui->widget->axisRect()->setupFullAxesBox(true);
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");
    colorMap = new QCPColorMap(ui->widget->xAxis, ui->widget->yAxis);


    colorMap->data()->setSize(xdim, ydim); // we want the color map to have nx * ny data points
    colorMap->data()->setRange(QCPRange(0, xdim), QCPRange(0, ydim)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions

     colorMap->setGradient(QCPColorGradient::gpGrayscale);
     //colorMap->setGradient(QCPColorGradient::gpThermal);
     colorMap->rescaleDataRange();
     colorMap->setAntialiased(0);
     colorMap->setInterpolate(0);

     ui->widget->addGraph();
     connect(ui->widget,SIGNAL(mousePress(QMouseEvent*)),this,SLOT(showValue(QMouseEvent*)));
     connect(ui->widget,SIGNAL(mouseMove(QMouseEvent*)),this,SLOT(showValue(QMouseEvent*)));

     ui->widget->setMouseTracking(1);

     QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->widget);
     ui->widget->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

     ui->widget->setBackgroundScaled(true);

     height=ui->widget->height();
     width =ui->widget->width();

    ui->widget->rescaleAxes(false);
     ui->widget->replot();
     ui->label->setStyleSheet("background-color: rgba(255, 255, 255, 70);");

//     QCPItemRect *

     roi = new QCPItemRect(ui->widget);

     ui->widget->addLayer(QString("graphlayer"));
     tempLine = new QCPItemLine(ui->widget);


//test
//     colorMap->setVisible(0);
     //roi->setVisible(0);
     //roi->setLayer("linelayer");


     roi->setPen(QPen(Qt::red));

     setRoi(10,10,20,20);
//     roi->bottomRight->setCoords(10,10);
//     roi->topLeft->setCoords(100,100);
     ImDat=nullptr;



}

MainWindow::~MainWindow()
{

    if((mem_ifile.is_open()))
    {
            mem_ifile.close();
            ImDat = nullptr;
    }

    if(ImDat!=nullptr)
    {
            delete ImDat;
            ImDat = nullptr;
    }

//    if(colorMap!=nullptr)
//    {
//            delete colorMap;
//             colorMap=nullptr;
//    }

//    if(roi!=nullptr)
//    {
//            delete roi;
//            roi=nullptr;
//    }

//    if(tempLine!=nullptr)
//    {
//            delete tempLine;
//            tempLine=nullptr;
//    }

//    if(paramWin!=nullptr)
//    {
//            delete paramWin;
//    }

//    if(outg1!=nullptr)
//    {
//            delete outg1;
//    }
//    if(phist!=nullptr)
//    {
//            delete phist;
//    }
    /*
     *
     *
     *
     *
     *
     *
     *
     * */

    delete ui;
}

void MainWindow::on_actionLoad_File_triggered()
{
    QFileDialog filedialog;
    std::size_t size = 0;
//    if(mem_ifile.is_open())
//    {

//        mem_ifile.close();
//    }


  //  QCPColorMapData fdat;
    filedialog.setFileMode(QFileDialog::AnyFile);
    try
    {
        QString fileName = filedialog.getOpenFileName(NULL, "Open File","","");

        if(!fileName.isEmpty())
        {
                        if((ImDat)&&(mem_ifile.is_open()))
                        {
                                mem_ifile.close();
                                ImDat = nullptr;
                        }
                        else if(ImDat!=nullptr)
                        {
                            delete ImDat;
                            ImDat = nullptr;
                        }



                        std::ifstream is(fileName.toStdString());
                        //****modiftying read in of file


                        if(is.is_open())
                        {
//                            if(ImDat!=nullptr)
//                            {
//                                delete ImDat;
//                                ImDat = nullptr;
//                            }

                            is.seekg(0, std::ios_base::end);
                            size=is.tellg();
                            is.seekg(0, std::ios_base::beg);
                            // Create a vector to store the data
                            //ImDat.reserve(size/sizeof(float));
                            // can I not use resize? No
                            //ImDat.resize(size/sizeof(float));
                            ImDat = new float[size/sizeof(float)];
                            is.read((char*) &ImDat[0], size);
                            // Close the file
                            is.close();
                        }


                        //THIS DOESN'T SEEM TO WORK <BELOW>
                //        std::ifstream is(fileName.toStdString(),std::ios::binary);
                //        is.unsetf(std::ios::skipws);
                //        if(is.is_open())
                //        {
                //            is.unsetf(std::ios::skipws);
                //            is.seekg(0, std::ios_base::end);
                //            std::size_t size=is.tellg();
                //            is.seekg(0, std::ios_base::beg);
                //            ImDat.reserve(size/sizeof(float));
                //            ImDat.insert(ImDat.begin(),std::istream_iterator< float>(is),std::istream_iterator< float>());
                //        }



                        NumFrames = (size/sizeof(float))/(xdim*ydim);
                        double x, y, z;
                        for(int i=0;i<266;i++)
                        {
                            for(int j=0;j<396;j++)
                            {
                                colorMap->data()->cellToCoord(j*1, i*1, &x, &y);
                                colorMap->data()->setCell(j, i, ImDat[N*266*396+i*396+j]);
                            }
                        }

                        colorMap->setDataRange(dataRange);

                        ui->widget->replot();

                        this->setWindowTitle(fileName);

                    //colorMap->setData();
                   // fdat.

                    //delete file;


        }
    }
    catch(std::bad_alloc)//const char* msg)
    {
        ui->label_3->setText("Ouch. Too Big.");
        //ui->messageOut->setText(QString::QString(msg));
        // ui->messageOut->setText(QString(msg));
    }

    //phist->datas = &ImDat;

}

void MainWindow::showValue(QMouseEvent *event)
{
    //if(event->button()==Qt::RightButton)
    //{
            QString mes("");
            ui->label->setText(" ");
            curx = ui->widget->xAxis->pixelToCoord(event->pos().x());
            cury = ui->widget->yAxis->pixelToCoord(event->pos().y());

            double z = colorMap->data()->data(curx,cury);

            mes.append(" x=");
            mes.append(QString::number(round(curx)));
            mes.append("\n y=");
            mes.append(QString::number(round(cury)));
            mes.append("\n pix=");
            mes.append(QString::number( z));
            mes.append("\n frame=");
            mes.append(QString::number( N));
            ui->label->move(event->pos());

            //ui->label->move(x,y);
            ui->label->setText(mes);
            //ui->label->setText(QString("hey"));
   // }
}

void MainWindow::update()
{
    colorMap->setDataRange(dataRange);
    ui->widget->replot();
}


void MainWindow::keyPressEvent(QKeyEvent* e)
{

    double x,y,z;

    //--------------

    //----
    long long step;

    step = ui->lineEdit->text().toLongLong();


    if(e->key() == Qt::Key_Right)
    {
        if(N<(NumFrames-1))
        {
            N++;
            for(long long i=0;i<266;i++)
            {
                for(long long j=0;j<396;j++)
                {
                   // colorMap->data()->cellToCoord(j*1, i*1, &x, &y);
                    colorMap->data()->setCell(j, i, ImDat[N*266*396+i*396+j]);
                }
            }
            colorMap->setDataRange(dataRange);
            ui->widget->replot();
        }
        else
        {
            N=0;

            for(long long i=0;i<266;i++)
            {
                for(long long j=0;j<396;j++)
                {
                    //colorMap->data()->cellToCoord(j*1, i*1, &x, &y);
                    colorMap->data()->setCell(j, i, ImDat[N*266*396+i*396+j]);
                }
            }
            colorMap->setDataRange(dataRange);
            ui->widget->replot();
        }
    }


    if(e->key() == Qt::Key_Up)
    {
        if(N<(NumFrames-step))
        {
            N+=step;
            for(long long i=0;i<266;i++)
            {
                for(long long j=0;j<396;j++)
                {
                    //colorMap->data()->cellToCoord(j*1, i*1, &x, &y);
                    colorMap->data()->setCell(j, i, ImDat[N*266*396+i*396+j]);
                }
            }
            colorMap->setDataRange(dataRange);
            ui->widget->replot();
        }
        else if(NumFrames>2*step)
        {
            N=N+step-NumFrames;

            for(long long i=0;i<266;i++)
            {
                for(long long j=0;j<396;j++)
                {
                    //colorMap->data()->cellToCoord(j*1, i*1, &x, &y);
                    colorMap->data()->setCell(j, i, ImDat[N*266*396+i*396+j]);
                }
            }
            colorMap->setDataRange(dataRange);
            ui->widget->replot();
        }
    }





    if(e->key() == Qt::Key_Left)
    {
        if(N>0)
        {
            N--;
            for(long long i=0;i<266;i++)
            {
                for(long long j=0;j<396;j++)
                {
                    //colorMap->data()->cellToCoord(j*1, i*1, &x, &y);
                    colorMap->data()->setCell(j, i, ImDat[N*266*396+i*396+j]);
                }
            }
            colorMap->setDataRange(dataRange);
            ui->widget->replot();
        }
        else
        {
            N=NumFrames-1;

            for(long long i=0;i<266;i++)
            {
                for(long long j=0;j<396;j++)
                {
                   // colorMap->data()->cellToCoord(j*1, i*1, &x, &y);
                    colorMap->data()->setCell(j, i, ImDat[N*266*396+i*396+j]);
                }
            }
            colorMap->setDataRange(dataRange);
            ui->widget->replot();
        }
    }

    if(e->key() == Qt::Key_Down)
    {
        if(N>=step)
        {
            N-=step;
            for(long long i=0;i<266;i++)
            {
                for(long long j=0;j<396;j++)
                {
                   // colorMap->data()->cellToCoord(j*1, i*1, &x, &y);
                    colorMap->data()->setCell(j, i, ImDat[N*266*396+i*396+j]);
                }
            }
            colorMap->setDataRange(dataRange);
            ui->widget->replot();
        }
        else if(NumFrames>2*step)
        {
            N=NumFrames-(step-N);

            for(long long i=0;i<266;i++)
            {
                for(long long j=0;j<396;j++)
                {
                   // colorMap->data()->cellToCoord(j*1, i*1, &x, &y);
                    colorMap->data()->setCell(j, i, ImDat[N*266*396+i*396+j]);
                }
            }
            colorMap->setDataRange(dataRange);
            ui->widget->replot();
        }
    }




    QString mes("");
    ui->label->setText(" ");

//    x = ui->widget->xAxis->pixelToCoord(QCursor::pos().x());
//    y = ui->widget->xAxis->pixelToCoord(QCursor::pos().y());

    z = colorMap->data()->data(curx,cury);

    mes.append(" x=");
    mes.append(QString::number(round(curx)));
    mes.append("\n y=");
    mes.append(QString::number(round(cury)));
    mes.append("\n pix=");
    mes.append(QString::number( z));
    mes.append("\n frame=");
    mes.append(QString::number( N));
    //ui->label->move(QCursor::pos());
    //ui->label->move(x,y);
    ui->label->setText(mes);
    //ui->label->setText(QString("hey"));

}

void MainWindow::setRange(double low,double high)
{
    dataRange.lower = low;
    dataRange.upper = high;
    update();
}

void    MainWindow::setRoi(double brX,double brY,double tlX, double tlY)
{
        roi->bottomRight->setCoords(brX,brY);
        roi->topLeft->setCoords(tlX,tlY);

        brx=brX;
        bry=brY;
        tlx=tlX;
        tly=tlY;
}


//void MainWindow::on_actionTrack_ROI_sum_triggered()
//{

//}

void MainWindow::on_actionTrack_ROI_sum_triggered()
{
    //QVector< double> roisum;
    //int framnum;
    int xlow,xhigh,ylow,yhigh;
    int c=0;
    int nn=0;
    long long fn;
    long long x,y;

    xlow=0;
    xhigh=0;
    ylow=0;
    yhigh=0;

    roisum.clear();

    roisum.resize(NumFrames);

    if(brx<tlx)
    {
        xlow = brx;
        xhigh = tlx;
    }
    else
    {
        xlow = tlx;
        xhigh = brx;
    }

    if(bry<tly)
    {
        ylow = bry;
        yhigh = tly;
    }
    else
    {
        ylow = tly;
        yhigh = bry;
    }

    c=(xhigh-xlow+1)*(yhigh-ylow+1);

    for(fn = 0;fn<NumFrames;fn++)
    {
        nn=0;
        roisum[fn]=0;
        for(x=xlow;x<=xhigh;x++)
        {
            for(y=ylow;y<=yhigh;y++)
            {
                roisum[fn]+=ImDat[fn*266*396+y*396+x];
                nn++;
                ui->label_2->setText(QString::number(c));

            }
        }

        roisum[fn]=roisum[fn]/c;
    }

    outg1->setROIdat(&roisum);
    outg1->setROIdat(&roisum);

    outg1->show();


}

void MainWindow::on_actionTrack_ROI_COM_triggered()
{
    //QVector< double> comx;
    //QVector< double> comy;
    //int framnum;
    int xlow,xhigh,ylow,yhigh;
    int c=0;
    int nn=0;

    long long fn,x,y;


    xlow=0;
    xhigh=0;
    ylow=0;
    yhigh=0;

    double temp;
    comx.clear();
    comy.clear();

    comx.resize(NumFrames);
    comy.resize(NumFrames);


    if(brx<tlx)
    {
        xlow = brx;
        xhigh = tlx;
    }
    else
    {
        xlow = tlx;
        xhigh = brx;
    }

    if(bry<tly)
    {
        ylow = bry;
        yhigh = tly;
    }
    else
    {
        ylow = tly;
        yhigh = bry;
    }

    c=(xhigh-xlow+1)*(yhigh-ylow+1);

    for(fn = 0;fn<NumFrames;fn++)
    {
        nn=0;
        temp=0;
        comx[fn]=0;
        comy[fn]=0;
        for(x=xlow;x<=xhigh;x++)
        {
            for(y=ylow;y<=yhigh;y++)
            {
                temp+=ImDat[fn*266*396+y*396+x];
                comx[fn]+=x*ImDat[fn*266*396+y*396+x];
                comy[fn]+=y*ImDat[fn*266*396+y*396+x];
            }
        }
        comx[fn]=comx[fn]/temp;
        comy[fn]=comy[fn]/temp;
    }

    outg1->setCOMdat(&comx,&comy);
    outg1->setCOMdat(&comx,&comy);

    comx_offset =0;
    comy_offset =0;

    outg1->show();

}

void MainWindow::on_actionGray_triggered()
{
    colorMap->setGradient(QCPColorGradient::gpGrayscale);
    ui->widget->replot();

}

void MainWindow::on_actionThermal_triggered()
{
    colorMap->setGradient(QCPColorGradient::gpThermal);
    ui->widget->replot();
    //QCPColorGradient::gp
}

void MainWindow::on_actionSpectrum_triggered()
{
    colorMap->setGradient(QCPColorGradient::gpSpectrum);
    ui->widget->replot();
}

void MainWindow::on_actionJet_triggered()
{
    colorMap->setGradient(QCPColorGradient::gpJet);
    ui->widget->replot();
}

void MainWindow::on_actionIon_triggered()
{
    colorMap->setGradient(QCPColorGradient::gpIon);
    ui->widget->replot();
}

void MainWindow::on_actionPolar_triggered()
{
    colorMap->setGradient(QCPColorGradient::gpPolar);
    ui->widget->replot();
}

void MainWindow::on_actionNight_triggered()
{
    colorMap->setGradient(QCPColorGradient::gpNight);
    ui->widget->replot();
}

void MainWindow::on_actionGeography_triggered()
{
    colorMap->setGradient(QCPColorGradient::gpGeography);
    ui->widget->replot();
}

void MainWindow::on_actionCandy_triggered()
{
    colorMap->setGradient(QCPColorGradient::gpCandy);
    ui->widget->replot();
}

void MainWindow::on_actionTrack_ROI_COM_ave_triggered()
{
    //QVector< double> comx;
    //QVector< double> comy;
    //int framnum;
    int xlow,xhigh,ylow,yhigh;
    int c=0;
    int nn=0;

    long long fn,x,y;

    xlow=0;
    xhigh=0;
    ylow=0;
    yhigh=0;

    double temp,xsum,ysum;
    xsum = 0;
    ysum = 0;
    comx.clear();
    comy.clear();

    comx.resize(NumFrames);
    comy.resize(NumFrames);


    if(brx<tlx)
    {
        xlow = brx;
        xhigh = tlx;
    }
    else
    {
        xlow = tlx;
        xhigh = brx;
    }

    if(bry<tly)
    {
        ylow = bry;
        yhigh = tly;
    }
    else
    {
        ylow = tly;
        yhigh = bry;
    }

    c=(xhigh-xlow+1)*(yhigh-ylow+1);

    for( fn = 0;fn<NumFrames;fn++)
    {
        nn=0;
        temp=0;
        comx[fn]=0;
        comy[fn]=0;
        for( x=xlow;x<=xhigh;x++)
        {
            for( y=ylow;y<=yhigh;y++)
            {
                temp+=ImDat[fn*266*396+y*396+x];
                comx[fn]+=double(x)*double(ImDat[fn*266*396+y*396+x]);
                comy[fn]+=double(y)*double(ImDat[fn*266*396+y*396+x]);
            }
        }
        comx[fn]=comx[fn]/temp;
        comy[fn]=comy[fn]/temp;
        xsum+=comx[fn];
        ysum+=comy[fn];

    }

    xsum/=NumFrames; //computing avergaes
    ysum/=NumFrames; // for subtracting off

    for( fn = 0;fn<NumFrames;fn++)
    {
        comx[fn]-=xsum;
        comy[fn]-=ysum;
    }
    outg1->setCOMdat(&comx,&comy);
   // outg1->setCOMdat(&comx,&comy);

    comx_offset=xsum;
    comy_offset=ysum;

    outg1->show();

}


void MainWindow::on_actionTrack_ROI_sum_COM_triggered()
{


    int xlow,xhigh,ylow,yhigh;
    int c=0;
    int xd,yd;
    int nn=0;
    int frtosum;
    int fcount=0;
   // QVector< double> imsum;

    std::vector< double> imsum;
    long long fn,x,y;

    frtosum = ui->lineEdit->text().toInt();


    xlow=0;
    xhigh=0;
    ylow=0;
    yhigh=0;

    double temp,xsum,ysum;
    xsum = 0;
    ysum = 0;
    comx.clear();
    comy.clear();

    comx.resize((NumFrames/frtosum));
    comy.resize((NumFrames/frtosum));


    if(brx<tlx)
    {
        xlow = brx;
        xhigh = tlx;
    }
    else
    {
        xlow = tlx;
        xhigh = brx;
    }

    if(bry<tly)
    {
        ylow = bry;
        yhigh = tly;
    }
    else
    {
        ylow = tly;
        yhigh = bry;
    }



    c=(xhigh-xlow+1)*(yhigh-ylow+1);
    xd = (xhigh-xlow+1);
    yd = (yhigh-ylow+1);

    imsum.resize(c);

    for( fn = 0;fn<NumFrames;fn++)
    {
        if(((fn%frtosum) == 0) && (fcount< (comx.size())))
        {
                nn=0;
                temp=0;
                comx[fcount]=0;
                comy[fcount]=0;
                for(auto jj=0;jj<xd;jj++)
                {
                    for(auto kk=0;kk<yd;kk++)
                    {
                        imsum[kk*xd+jj]=0;
                    }
                }
        }

        for( x=xlow;x<=xhigh;x++)
                {
                    for( y=ylow;y<=yhigh;y++)
                    {
                        temp+=ImDat[fn*266*396+y*396+x];
                        if(fcount< (comx.size()))
                        {
                            imsum[(y-ylow)*xd + (x - xlow)] +=ImDat[fn*266*396+y*396+x];
                        }
                    }
                }

        if((((fn+1)%frtosum) == 0) && (fcount< (comx.size())))
                {
                    for( x=xlow;x<=xhigh;x++)
                    {
                                for( y=ylow;y<=yhigh;y++)
                                {
                                    comx[fcount]+=double(x)*imsum[(y-ylow)*xd + (x - xlow)];
                                    comy[fcount]+=double(y)*imsum[(y-ylow)*xd + (x - xlow)];
                                }
                    }


                    comx[fcount]=comx[fcount]/temp;
                    comy[fcount]=comy[fcount]/temp;
                    xsum+=comx[fcount];
                    ysum+=comy[fcount];
                    fcount++;
                }




    }

//    for( fn = 0;fn<NumFrames;fn++)
//    {
//        if(((fn%frtosum) == 0) && (fcount< (comx.size())))
//        {
//        nn=0;
//        temp=0;
//        comx[fcount]=0;
//        comy[fcount]=0;
//        }

//        for( x=xlow;x<=xhigh;x++)
//        {
//            for( y=ylow;y<=yhigh;y++)
//            {
//                temp+=ImDat[fn*266*396+y*396+x];
//                if(fcount< (comx.size()))
//                {
//                    comx[fcount]+=double(x)*double(ImDat[fn*266*396+y*396+x]);
//                    comy[fcount]+=double(y)*double(ImDat[fn*266*396+y*396+x]);
//                }
//            }
//        }

//        if((((fn+1)%frtosum) == 0) && (fcount< (comx.size())))
//        {
//            comx[fcount]=comx[fcount]/temp;
//            comy[fcount]=comy[fcount]/temp;
//            xsum+=comx[fcount];
//            ysum+=comy[fcount];
//            fcount++;
//        }
//    }

    xsum/=(NumFrames/frtosum); //computing avergaes
    ysum/=(NumFrames/frtosum); // for subtracting off

    for( fn = 0;fn<comx.size();fn++)
    {
        comx[fn]-=xsum;
        comy[fn]-=ysum;
    }
    outg1->setCOMdat(&comx,&comy);
   // outg1->setCOMdat(&comx,&comy);

    comx_offset=xsum;
    comy_offset=ysum;

    outg1->show();

}

void MainWindow::on_actionTime_Stamps_triggered()
{
    timeStamps.clear();

    double tn,tnp,diff,offset;

    offset=0;


    for(long long i=0;i<(NumFrames-1);i++)
    {

        tn = ImDat[i*266*396+65];
        tnp= ImDat[(i+1)*266*396+65];
        diff = tnp-tn;
        if( diff < 0)
        {
            diff+=1000000.0;
        }

        timeStamps.push_back(diff);
    }

    outg1->setTIMEdat(&timeStamps);
    outg1->show();

}


void MainWindow::on_actionHistogram_ROI_triggered()
{

    long long x,y,fn;
    int xlow,xhigh,ylow,yhigh;
   // std::vector< double> toHist;

    if(brx<tlx)
    {
        xlow = brx;
        xhigh = tlx;
    }
    else
    {
        xlow = tlx;
        xhigh = brx;
    }

    if(bry<tly)
    {
        ylow = bry;
        yhigh = tly;
    }
    else
    {
        ylow = tly;
        yhigh = bry;
    }

//    toHist.clear();

//    for( fn = 0;fn<NumFrames;fn++)
//    {
//        for( x=xlow;x<=xhigh;x++)
//        {
//            for( y=ylow;y<=yhigh;y++)
//            {
//                toHist.push_back(ImDat[fn*266*396+y*396+x]);
//            }
//        }

//    }

    phist->xlow = xlow;
    phist->xhigh = xhigh;
    phist->ylow = ylow;
    phist->yhigh = yhigh;
    phist->NumFrames = NumFrames;

    phist->show();
}


void MainWindow::on_pushButton_clicked()
{
    colorMap->setDataScaleType(QCPAxis::stLogarithmic);
    ui->widget->rescaleAxes();
    //colorMap->dataScaleTypeChanged(QCPAxis::stLogarithmic);
    ui->widget->replot();
}



void MainWindow::on_pushButton_2_clicked()
{

    colorMap->setDataScaleType(QCPAxis::stLinear);
    ui->widget->rescaleAxes();
    ui->widget->replot();
}

float MainWindow::getImdat(long long kk)
{
    return ImDat[kk];

}

int MainWindow::getNumFrames()
{
    return int(NumFrames);
}

int MainWindow::getStep()
{
    return int(ui->lineEdit->text().toInt());
}

void MainWindow::on_actionCollapse_Max_triggered()
{
    long long fn,x,y;
   // double xx,yy;



    std::vector< float> tempim;
    //tempim.resize(396*266);

    for( x=0;x<xdim;x++)
    {
                for( y=0;y<ydim;y++)
                {
                    tempim.push_back(0);
                }
    }

    //tempim.resize(396*266);


    for( fn = 0;fn<NumFrames;fn++)
    {
        for( x=0;x<xdim;x++)
        {
                    for( y=0;y<ydim;y++)
                    {
                        if(ImDat[fn*266*396+y*396+x]>tempim[y*396+x])
                        {
                            tempim[y*396+x] = ImDat[fn*266*396+y*396+x];
                        }
                    }
        }
    }

    for(long long i=0;i<266;i++)
    {
        for(long long j=0;j<396;j++)
        {
            //colorMap->data()->cellToCoord(j*1, i*1, &xx, &yy);
            colorMap->data()->setCell(j, i, tempim[i*396+j]);
        }
    }
    colorMap->setDataRange(dataRange);
    ui->widget->replot();


}

void MainWindow::on_actionCollapse_Mean_triggered()
{
    long long fn,x,y;
   // double xx,yy;




    std::vector< double> tempim;
    //tempim.resize(396*266);

    for( x=0;x<xdim;x++)
    {
                for( y=0;y<ydim;y++)
                {
                    tempim.push_back(0);
                }
    }

    //tempim.resize(396*266);


    for( fn = 0;fn<NumFrames;fn++)
    {
        for( x=0;x<xdim;x++)
        {
                    for( y=0;y<ydim;y++)
                    {

                            tempim[y*396+x] += ImDat[fn*266*396+y*396+x];

                    }
        }
    }

    for( x=0;x<xdim;x++)
    {
                for( y=0;y<ydim;y++)
                {
                        tempim[y*396+x]/=  NumFrames;
                }
    }


    for(long long i=0;i<266;i++)
    {
        for(long long j=0;j<396;j++)
        {
            //colorMap->data()->cellToCoord(j*1, i*1, &xx, &yy);
            colorMap->data()->setCell(j, i, tempim[i*396+j]);
        }
    }
    colorMap->setDataRange(dataRange);
    ui->widget->replot();


}

void MainWindow::on_actionSave_Image_png_triggered()
{
    QFileDialog filedialog;
    filedialog.setFileMode(QFileDialog::AnyFile);
    QString fileName = filedialog.getSaveFileName(NULL, "Save Image","","*.png");

    ui->widget->savePng(fileName);

}

void MainWindow::on_actionShow_ROI_Path_triggered()
{

    std::vector< double> comxtemp;
    std::vector< double> comytemp;

    for(auto i=0; i<comx.size();i++)
    {
        comxtemp.push_back(comx[i]+comx_offset);
        comytemp.push_back(comy[i]+comy_offset);

    }


  //     tempLine->start->setCoords(double(10),double(10));
  //     tempLine->end->setCoords(double(100), double(100));
  //     tempLine->setVisible(1);
 //      tempLine->setLayer("linelayer");
 //      tempLine->setHead(QCPLineEnding::esLineArrow);
  //     tempLine->setPen(QPen(Qt::yellow));
       //com_follow.push_back(tempLine);
        //QCPItemLine tLine(ui->widget);
//
//

//       for(auto i=1;i<comx.size();i++)
//       {
          // com_follow[i].setParent(ui->widget);

//          tempLine->start->setCoords(comx[i-1]+comx_offset,comy[i-1]+comy_offset);
//          tempLine->end->setCoords(comx[i]+comx_offset,comy[i]+comy_offset);
//          tempLine->setHead(QCPLineEnding::esLineArrow);
//          tempLine->setPen(QPen(Qt::yellow));
          //com_follow.append(*tempLine);
//       }
//       ui->widget->replot();
    ui->widget->addGraph();
    ui->widget->graph(ui->widget->graphCount()-1)->setData(QVector<double>::fromStdVector(comxtemp),QVector<double>::fromStdVector(comytemp));
    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QPen(Qt::yellow));
    //ui->widget->graph(ui->widget->graphCount()-1)->pen().setWidth(30);
   // kluge because pen width is not working directly
    myPen = ui->widget->graph(ui->widget->graphCount()-1)->pen();
    myPen.setWidth(5);
    ui->widget->graph(ui->widget->graphCount()-1)->setPen(myPen);
   // end kluge



    ui->widget->graph(ui->widget->graphCount()-1)->setVisible(1);
    ui->widget->graph(ui->widget->graphCount()-1)->setLayer("graphlayer");
    ui->widget->layer("graphlayer")->setVisible(1);

    ui->widget->replot();
}

void MainWindow::on_actionView_triggered()
{
    //double x,y,z;

    //--------------

    //----
    long long step;


    step = ui->lineEdit->text().toInt();

    long long startframe = N%step;

    for(long long k = startframe;k<(NumFrames-step);k+=step)
    {

            for(long long i=0;i<266;i++)
            {
                for(long long j=0;j<396;j++)
                {
                    //colorMap->data()->cellToCoord(j*1, i*1, &x, &y);
                    colorMap->data()->setCell(j, i, ImDat[k*266*396+i*396+j]);
                }
            }
            colorMap->setDataRange(dataRange);
            ui->widget->replot();
     }

}

void MainWindow::on_actionExport_PNGs_triggered()
{
    QFileDialog filedialog;
    filedialog.setFileMode(QFileDialog::AnyFile);
    QString rootfileName = filedialog.getSaveFileName(NULL, "Save Many Images","","*.png");

    long long step;

    if(!rootfileName.isEmpty())
    {

            step = ui->lineEdit->text().toInt();

            long long startframe = N%step;

            for(long long k = startframe;k<(NumFrames-step);k+=step)
            {

                    for(long long i=0;i<266;i++)
                    {
                        for(long long j=0;j<396;j++)
                        {
                            //colorMap->data()->cellToCoord(j*1, i*1, &x, &y);
                            colorMap->data()->setCell(j, i, ImDat[k*266*396+i*396+j]);
                        }
                    }
                    colorMap->setDataRange(dataRange);
                    ui->widget->replot();
                    ui->widget->savePng(rootfileName+QString::number(k).rightJustified(6, '0')+".png");
             }

    }


}

void MainWindow::on_actionLoad_File_mem_map_triggered()
{
    QFileDialog filedialog;
    std::size_t size = 0;

    long long filesize;


//    if(mem_ifile.is_open())
//    {

//        mem_ifile.close();
//    }


  //  QCPColorMapData fdat;
    filedialog.setFileMode(QFileDialog::AnyFile);
    try
    {
        QString fileName = filedialog.getOpenFileName(NULL, "Open File","","");

        if(!fileName.isEmpty())
        {

                    if((ImDat!=nullptr)&&(mem_ifile.is_open()))
                    {
                            mem_ifile.close();
                            ImDat = nullptr;
                    }
                    else if(ImDat!=nullptr)
                    {
                           delete ImDat;
                           ImDat = nullptr;
                    }

                    mem_ifile.open(fileName.toStdString());
                    filesize = mem_ifile.size();

                        NumFrames = (filesize/sizeof(float))/(xdim*ydim);
                        ImDat = (float *)mem_ifile.data();

                        double x, y, z;
                        if(NumFrames>0)
                        {
                            for(long long i=0;i<266;i++)
                            {
                                for(long long j=0;j<396;j++)
                                {
                                    colorMap->data()->cellToCoord(j*1, i*1, &x, &y);
                                    colorMap->data()->setCell(j, i, ImDat[N*266*396+i*396+j]);
                                }
                            }
                        }
                        colorMap->setDataRange(dataRange);

                        ui->widget->replot();



                    //colorMap->setData();
                   // fdat.
                    this->setWindowTitle(fileName);
                    //delete file;

        }
    }
    catch(std::bad_alloc)//const char* msg)
    {
        ui->label_3->setText("Ouch. Too Big.");
        //ui->messageOut->setText(QString::QString(msg));
        // ui->messageOut->setText(QString(msg));
    }

}

void MainWindow::on_actionClear_Plot_Overlays_triggered()
{
    int gcount=ui->widget->graphCount();
    for(auto k=0;k<gcount;k++)
    {
        ui->widget->removeGraph(k);
    }
}

void MainWindow::on_actionTheta_Omega_triggered()
{
    endv->show();
    endv->frameslice = ui->lineEdit->text().toInt();



}

void MainWindow::on_actionGeneral_Explanations_triggered()
{
    helpstuff->show();
}

void MainWindow::on_actionExport_Thresholded_Stack_triggered()
{
    threshexp->show();

}

void MainWindow::on_actionExport_ROI_stack_triggered()
{
    int xlow,xhigh,ylow,yhigh;
    if(brx<tlx)
    {
        xlow = brx;
        xhigh = tlx;
    }
    else
    {
        xlow = tlx;
        xhigh = brx;
    }

    if(bry<tly)
    {
        ylow = bry;
        yhigh = tly;
    }
    else
    {
        ylow = tly;
        yhigh = bry;
    }

    // boost::iostreams::mapped_file_sink *mem_ofile;
     boost::iostreams::mapped_file_sink mem_ofile;
     boost::iostreams::mapped_file_params params;



     float *outdat;
     long long numfr = getNumFrames();
     long long fn,x,y;
     QFileDialog filedialog;
     long long fsize = (xhigh-xlow+1)*(yhigh-ylow+1)*4*numfr;
     long long fnumpix = (xhigh-xlow+1)*(yhigh-ylow+1);
     long long xpixels= (xhigh-xlow+1);

     filedialog.setFileMode(QFileDialog::AnyFile);
     params.new_file_size = (long long)(fsize);;
     params.length = (long long)(fsize);
     params.offset =0;
     //params.mode = std::ios::out;
     params.flags = boost::iostreams::mapped_file::readwrite;
     //params.


     try
     {
         //QString fileName = filedialog.getOpenFileName(NULL, "Open File","","");
         QString fileName = filedialog.getSaveFileName(NULL, "File to Save to:","","");
         params.path = fileName.toStdString();
        // mem_ofile = new boost::iostreams::mapped_file_sink();
        // mem_ofile->open(params);
        // mem_ofile.open(mapped_file_sink(fileName.toStdString()));
         mem_ofile.open(params);


         outdat = (float *)(mem_ofile.data());

        // for( fn = 0;fn<numfr;fn++)
         for( fn = 0;fn<numfr;fn++)
         {
             for( x=xlow;x<=xhigh;x++)
             {
                 for( y=ylow;y<=yhigh;y++)
                 {
                         *(outdat+fn*fnumpix+(y-ylow)*(xpixels)+(x-xlow))=ImDat[fn*266*396+y*396+x];
                 }
             }
         }

         mem_ofile.close();
         //delete mem_ofile;
     }
     catch(std::bad_alloc)
     {

     }

}
