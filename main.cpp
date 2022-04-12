#include "mainwindow.h"
#include <QApplication>

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#include "QFontDatabase"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    //printf ("%d\n", hack ());

    return a.exec();
}
