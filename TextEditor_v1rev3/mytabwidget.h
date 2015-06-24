#ifndef MYTABWIDGET
#define MYTABWIDGET


#include <iostream>
#include <QTabWidget>

class MyTabWidget : public QTabWidget
{
public:
    MyTabWidget();
    ~MyTabWidget(){}
private:
    void closeEvent(QCloseEvent *event);
public slots:

};


#endif // MYTABWIDGET

