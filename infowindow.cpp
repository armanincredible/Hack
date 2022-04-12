#include "infowindow.h"
#include "ui_infowindow.h"
#include "QPixmap"

InfoWindow::InfoWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoWindow)
{
    ui->setupUi(this);

    this->setFixedSize(762,755);
    //this->statusBar()->setSizeGripEnabled(false);

    QPixmap pix (":/files/stream/dorabig.jpg");
    int w = ui->doraimage->width();
    int h = ui->doraimage->height();
    ui->doraimage->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
}

InfoWindow::~InfoWindow()
{
    delete ui;
}
