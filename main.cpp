#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    //get displays connected
    QList<QScreen *> screenList=QGuiApplication::screens();
    //set display to show program
    QRect rect=screenList[1]->geometry();
    w.setGeometry(rect);

    w.showFullScreen();
    return a.exec();
}
