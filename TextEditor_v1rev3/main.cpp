#include <iostream>
#include "mainwindow.h"
#include <QApplication>
#include <crtdbg.h>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    {
        Window *wid = new Window();
        wid->show();
    }
    if (_CrtDumpMemoryLeaks())
        std::cout << "Leaks!!!!" << std::endl;
    else
        std::cout << "Memory OK!" << std::endl;

    application.exec();
    return 0;
}

