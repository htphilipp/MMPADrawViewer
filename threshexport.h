#ifndef THRESHEXPORT_H
#define THRESHEXPORT_H

#include <QDialog>
#include <fstream>
#include <QFileDialog>
#include <boost/iostreams/device/mapped_file.hpp>

namespace Ui {
class threshExport;
}

class threshExport : public QDialog
{
    Q_OBJECT

public:
    explicit threshExport(QWidget *parent = 0);
    void threshold();

    ~threshExport();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

signals:

    float getImdat(long long);
    int   getNumFrames();

private:
    Ui::threshExport *ui;
};

#endif // THRESHEXPORT_H
