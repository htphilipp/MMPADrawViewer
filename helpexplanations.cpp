#include "helpexplanations.h"
#include "ui_helpexplanations.h"

helpExplanations::helpExplanations(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::helpExplanations)
{
    ui->setupUi(this);
}

helpExplanations::~helpExplanations()
{
    delete ui;
}

void helpExplanations::on_pushButton_clicked()
{
    hide();
}
