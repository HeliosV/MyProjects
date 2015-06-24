#include <iostream>
#include <QtGui>
#include <QApplication>
#include "MainWnd.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    MainWindow *window = new MainWindow();
    //window.showNormal();
    window->show();
    application.setApplicationName("Music Player");
    application.exec();

}

