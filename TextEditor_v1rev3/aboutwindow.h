#ifndef ABOUTWINDOW
#define ABOUTWINDOW

#include <QObject>
#include <iostream>
#include <QGuiApplication>
#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QDialog>

class AboutWnd : public QDialog
{
    Q_OBJECT
public:
    AboutWnd();
    ~AboutWnd(){ delete btn; }
public slots:
    void quitAbout();
private:
    QPushButton *btn;
};

#endif // ABOUTWINDOW

