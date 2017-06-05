#ifndef ENDVIEW_H
#define ENDVIEW_H

#include <QWidget>
#include "./qcustomplot.h"

namespace Ui {
class EndView;
}

class EndView : public QWidget
{
    Q_OBJECT

public:
     QCPColorMap        *colorMap;
     QCPRange            dataRange;
     long long           frameslice;
     long long           tpixmin, tpixmax;
     std::vector< double>      data;
     int                 step;
     int                 maxViewIndex;

     void                dataToMap();
     void                dataToMap(int);


    explicit EndView(QWidget *parent = 0);
    ~EndView();

signals:

    float getImdat(long long);
    int getNumFrames();
    int       getStep();


private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_comboBox_activated(const QString &arg1);

private:
    Ui::EndView *ui;
};

#endif // ENDVIEW_H
