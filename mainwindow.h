#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./qcustomplot.h"
#include "vector"
#include <sstream>
#include <QTextStream>
#include <cmath>
#include <fstream>
#include <QKeyEvent>
#include "./viewparam.h"
#include "graph1.h"
#include "pixhist.h"
#include "endview.h"
#include "helpexplanations.h"
#include "threshexport.h"
#include <boost/iostreams/device/mapped_file.hpp>




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
   // QVector< float>    ImDat;      // raw data
    long long                 NumFrames;  // Total Number of Frames
    long long                 N;          // present frame
    int                 xdim = 396;    // number of pixels in x direction
    int                 ydim = 266;     // number of pixels in y direction
//    QVector< double>    roisum;
//    QVector< double>    comx;
//    QVector< double>    comy;

    std::vector< double>    roisum;
    std::vector< double>    comx;
    std::vector< double>    comy;
    std::vector< double>    timeStamps;
    friend  class   pixHist;
    double                  comx_offset;
    double                  comy_offset;
    boost::iostreams::mapped_file_source mem_ifile;

   // float           getImdat(long long index);

    QCPColorMap *colorMap;
    //QCPColorMapData framedat;
    QCPRange            dataRange;
   // bool eventFilter(QObject *watched, QEvent *event);
    //void setRange(double,double);

    QCPItemRect *roi;
    //void    setRoi(double brX,double brY,double tlX,double tlY);
    QVector< QCPItemLine> com_follow;
    QCPItemLine *tempLine;

    viewParam           *paramWin;
   // connect(this, SIGNAL(setRange(double,double)), separateClass, SLOT(setRange(double,double)));
    // this is not done here... connecting in header does not work.  Must connect specific instances.

    graph1              *outg1;
    pixHist             *phist;
    EndView             *endv;
    helpExplanations    *helpstuff;
    threshExport         *threshexp;

    QPen myPen;


    double curx,cury;

    void update();
    void keyPressEvent(QKeyEvent*);

   // std::vector< float>    ImDat;

    ~MainWindow();

private slots:
    void on_actionLoad_File_triggered();
     void showValue(QMouseEvent*);
    // void on_actionTrack_ROI_sum_triggered();

     void on_actionTrack_ROI_sum_triggered();

     void on_actionTrack_ROI_COM_triggered();

     void on_actionGray_triggered();

     void on_actionThermal_triggered();

     void on_actionSpectrum_triggered();

     void on_actionJet_triggered();

     void on_actionIon_triggered();

     void on_actionPolar_triggered();

     void on_actionNight_triggered();

     void on_actionGeography_triggered();

     void on_actionCandy_triggered();

     void on_actionTrack_ROI_COM_ave_triggered();

     void on_actionTrack_ROI_sum_COM_triggered();

     void on_actionTime_Stamps_triggered();

     void on_actionHistogram_ROI_triggered();

     void on_pushButton_clicked();

     void on_pushButton_2_clicked();


     void on_actionCollapse_Max_triggered();

     void on_actionCollapse_Mean_triggered();

     void on_actionSave_Image_png_triggered();

     void on_actionShow_ROI_Path_triggered();

     void on_actionView_triggered();

     void on_actionExport_PNGs_triggered();

     void on_actionLoad_File_mem_map_triggered();

     void on_actionClear_Plot_Overlays_triggered();

     void on_actionTheta_Omega_triggered();

     void on_actionGeneral_Explanations_triggered();

     void on_actionExport_Thresholded_Stack_triggered();

     void on_actionExport_ROI_stack_triggered();

public slots:
     void setRange(double,double);
     void setRoi(double brX,double brY,double tlX,double tlY);
     float           getImdat(long long index);
     int       getNumFrames();
     int       getStep();


private:
    Ui::MainWindow *ui;
    //std::vector< float>    ImDat;
    
    
    float *ImDat;
    //trying unique_ptr
//    std::unique_ptr <float> ImDat;  
    
    //QVector< float>    ImDat;      // raw data
     double              brx,bry,tlx,tly;



};

#endif // MAINWINDOW_H
