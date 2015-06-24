#ifndef SETTINGSWINDOW
#define SETTINGSWINDOW

#include <QObject>
#include <iostream>
#include <QGuiApplication>
#include <QPushButton>
#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QStatusBar>
#include <QComboBox>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolBar>
#include <QToolButton>
#include <QFileInfo>
#include <QScrollBar>
#include <QFileDialog>
#include <QSettings>
#include <QDialogButtonBox>

class Window;

class SettingsWnd: public QDialog
{
    Q_OBJECT
public:
    SettingsWnd(Window& w);
    ~SettingsWnd(){}
public slots:
    void quitSettings();
    void browseFile();
    void clearHistory();
    void accept();
public:
    QPushButton *okbtn;
    QPushButton *cancbtn;
    QPushButton *applbtn;
    QPushButton *browse;
    QPushButton *clearhist;
    QString fname;
    QString histpath;
    QString pathHist;
    QSettings *settings;
    QSettings *pathHistory;
    Window& widget;
    QDialogButtonBox *buttonBox;
};

#endif // SETTINGSWINDOW

