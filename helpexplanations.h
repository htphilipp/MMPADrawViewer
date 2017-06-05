#ifndef HELPEXPLANATIONS_H
#define HELPEXPLANATIONS_H

#include <QWidget>

namespace Ui {
class helpExplanations;
}

class helpExplanations : public QWidget
{
    Q_OBJECT

public:
    explicit helpExplanations(QWidget *parent = 0);
    ~helpExplanations();

private slots:
    void on_pushButton_clicked();

private:
    Ui::helpExplanations *ui;
};

#endif // HELPEXPLANATIONS_H
