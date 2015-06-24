#ifndef TEXTWINDOW
#define TEXTWINDOW

#include <QObject>
#include <iostream>
#include <QGuiApplication>
#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>
#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QStatusBar>
#include <QComboBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QFileDialog>
#include <QTextEdit>
#include <QSplitter>
#include <QWebView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolBar>
#include <QToolButton>
#include <QFileInfo>
#include <QScrollBar>
#include <QFileDialog>
#include <QSettings>
#include <QMdiArea>
#include "settingswindow.h"

class Widget: public QTextEdit
{
    Q_OBJECT
public:
    Widget();
    ~Widget(){}
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    bool loadFile(const QString& fileName);
    QString userFriendlyCurrentFile();
    QString currentFile() { return curFile; }
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void documentWasModified();
private:
    bool maybeSave();
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);
    QString curFile;
    bool isUntitled;
};

#endif // TEXTWINDOW

