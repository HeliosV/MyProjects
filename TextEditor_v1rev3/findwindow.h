#ifndef FINDWINDOW
#define FINDWINDOW

#include <QObject>
#include <QGuiApplication>
#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QDialog>
#include <QLineEdit>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QDebug>
#include <QStatusBar>
#include <QCloseEvent>
#include "textwindow.h"
#include "mainwindow.h"

class FindWindow : public QMainWindow
{
    Q_OBJECT
public:
    FindWindow(Window& w);
    ~FindWindow();
private:
    QTabWidget *tabWidget;
public slots:
    void closeEvent(QCloseEvent *event);
public:
    Window& mainwnd;
    QStatusBar *statusBar;
};

#endif // FINDWINDOW

