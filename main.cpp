#include "mainwindow.h"
#include <QApplication>
#include <iostream>


int main( int argc, char ** argv )
{
    QApplication app(argc,argv);
    MainWindow *w = new MainWindow();
    w->show();
    app.exec();

    qDebug("App done");
}

