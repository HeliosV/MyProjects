#ifndef MAINWINDOW
#define MAINWINDOW

#include <QMainWindow>
#include <QMdiArea>
#include <QTextEdit>
#include <QWebView>
#include <QShortcut>
#include <QLineEdit>
#include <QToolButton>
#include "settingswindow.h"
#include "findwindow.h"
#include "texttabwidget.h"
#include <typeinfo>
#include "mytabwidget.h"

class Widget;
class FindWindow;
class TextTabWidget;
//class MyTabWidget;

class Window : public QMainWindow
{
    Q_OBJECT
public:
    Window();
    ~Window(){}
public slots:
    //TextTabWidget* createTab(const QString& fileName);
    TextTabWidget* activeTab();
    void openfile();
    void loadFile(QString &fileName);
    void savefile();
    void quitMain();
    void getCursorPosition();
    void copyAct();
    void pasteAct();
    void cutAct();
    void visit();
    void undoAct();
    void redoAct();
    void findAct();
    void readConfigurationFile();
    void saveConfiguration();
    void loadFileintoTextEdit();
    void about();
    void settingsAct();
    void findPreviousText();
    void findNextText();
    void replaceText();
    void converttoUpper();
    void converttoLower();
    void wndType();
    void savefileAs();
    void createGlobalShortcuts();
    void deleteGlobalShortcuts();
    void sortAct();
    void writePathHistory();
    void closeTab(int i_index);
private:
    void closeEvent(QCloseEvent *event);
    //MyTabWidget *textTabWidget;
public:
    QMainWindow *window;
    QMdiArea *mdiArea;
    QMenu* menuFile;
    QMenu* menuEdit;
    QMenu *menuSearch;
    QMenu* menuSettings;
    QMenu* menuHelp;
    QMenu* menuView;
    QToolBar *tbar;
    QScrollBar *txtscr;
    QString fileName;
    QMenu* menuHistoryList;
    QMenu* menuConvertCase;
    QAction* actionFile1;
    QTextCursor c;
    QString line;
    QAction* action;
    QAction* actionAbout;
    QList<QAction*> listaction;
    SettingsWnd* s;
    QToolButton *buttonPrevious;
    QToolButton *buttonNext;
    QToolButton *buttonReplace;
    QLineEdit *findedit;
    QLineEdit *replaceEdit;
    QShortcut *shortcut;
    QShortcut *shortcut2;
    QShortcut *shortcut3;
    QShortcut *shortcut4;
    QString str;
    QStringList list;
    FindWindow *fndwnd;
    TextTabWidget *newTab;
    QTabWidget *textTabWidget;
};

#endif // MAINWINDOW

