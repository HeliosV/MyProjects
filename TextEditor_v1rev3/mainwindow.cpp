#include "MainWindow.h"
#include "textwindow.h"
#include "aboutwindow.h"
#include "settingswindow.h"
#include "findwindow.h"
#include <QMainWindow>
#include <QApplication>
#include <QTextStream>
#include <QApplication>
#include <QMdiSubWindow>
#include <QShortcut>
#include "webviewwindow.h"
#include "texttabwidget.h"


Window::Window() : fndwnd(NULL), newTab(NULL)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowIcon(QIcon(":images/main.png"));
    setMinimumSize(QSize(1024, 768));
    setWindowTitle("Text Editor");

    textTabWidget = new MyTabWidget;
    textTabWidget->setTabsClosable(true);
    textTabWidget->setMovable(true);
    setCentralWidget(textTabWidget);
    connect(textTabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));

    s = new SettingsWnd(*this);

    menuFile = menuBar()->addMenu(tr("&File"));
    menuEdit = menuBar()->addMenu(tr("&Edit"));
    menuSearch = menuBar()->addMenu(tr("&Search"));
    menuSettings = menuBar()->addMenu(tr("&Tools"));
    menuView = menuBar()->addMenu(tr("&View"));
    menuHelp = menuBar()->addMenu(tr("&Help"));
    //-------------------MENU FILE-------------------------------------------------------
    QAction* actionOpen = new QAction(QIcon(":images/openfile.png"),"Open", this);
    actionOpen->setShortcut(tr("Ctrl+O"));
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(openfile()));
    menuFile->addAction(actionOpen);
    QAction* actionSave = new QAction(QIcon(":images/save.png"),"Save", this);
    actionSave->setShortcut(tr("Ctrl+S"));
    connect(actionSave, SIGNAL(triggered()), this, SLOT(savefile()));
    menuFile->addAction(actionSave);
    QAction* actionSaveAs = new QAction(QIcon(":images/save.png"),"Save as...", this);
    connect(actionSaveAs, SIGNAL(triggered()), this, SLOT(savefileAs()));
    menuFile->addAction(actionSaveAs);

    menuHistoryList = new QMenu("Recently opened files", menuFile);
    menuFile->addMenu(menuHistoryList);
    menuHistoryList->setIcon(QIcon(":images/hist.png"));

    readConfigurationFile();
    menuFile->addSeparator();

    QAction* actionQuit = new QAction(QIcon(":images/close.png"),"Quit", this);
    actionQuit->setShortcut(tr("Ctrl+Q"));
    connect(actionQuit, SIGNAL(triggered()), this, SLOT(quitMain()));
    menuFile->addAction(actionQuit);
    //--------------------------MENU EDIT----------------------------------------------
    QAction* actionUndo = new QAction(QIcon(":images/undo.png"),"Undo", this);
    actionUndo->setShortcut(tr("Ctrl+Z"));
    connect(actionUndo, SIGNAL(triggered()), this, SLOT(undoAct()));
    menuEdit->addAction(actionUndo);
    QAction* actionRedo = new QAction(QIcon(":images/redo.png"),"Redo", this);
    actionRedo->setShortcut(tr("Ctrl+Y"));
    connect(actionRedo, SIGNAL(triggered()), this, SLOT(redoAct()));
    menuEdit->addAction(actionRedo);
    QAction* actionCut = new QAction(QIcon(":images/cut.png"),"Cut", this);
    actionCut->setShortcut(tr("Ctrl+X"));
    connect(actionCut, SIGNAL(triggered()), this, SLOT(cutAct()));
    menuEdit->addAction(actionCut);
    QAction* actionCopy = new QAction(QIcon(":images/copy.png"),"Copy", this);
    actionCopy->setShortcut(tr("Ctrl+C"));
    connect(actionCopy, SIGNAL(triggered()), this, SLOT(copyAct()));
    menuEdit->addAction(actionCopy);
    QAction* actionPaste = new QAction(QIcon(":images/paste.png"),"Paste", this);
    actionPaste->setShortcut(tr("Ctrl+V"));
    connect(actionPaste, SIGNAL(triggered()), this, SLOT(pasteAct()));
    menuEdit->addAction(actionPaste);

    menuEdit->addSeparator();

    menuConvertCase = new QMenu("Convert case", menuEdit);
    menuEdit->addMenu(menuConvertCase);
    menuConvertCase->setIcon(QIcon(":images/convert.png"));

    QAction* actionUpperCase = new QAction(QIcon(":images/lctouc.png"),"UPPERCASE", this);
    actionUpperCase->setShortcut(tr("Ctrl+Shift+U"));
    connect(actionUpperCase, SIGNAL(triggered()), this, SLOT(converttoUpper()));
    menuConvertCase->addAction(actionUpperCase);
    QAction* actionLowerCase = new QAction(QIcon(":images/uctolc.png"),"lowercase", this);
    actionLowerCase->setShortcut(tr("Ctrl+U"));
    connect(actionLowerCase, SIGNAL(triggered()), this, SLOT(converttoLower()));
    menuConvertCase->addAction(actionLowerCase);
    menuEdit->addSeparator();
    QAction* actionSort = new QAction(QIcon(":images/sort.png"),"Sort", this);
    connect(actionSort, SIGNAL(triggered()), this, SLOT(sortAct()));
    menuEdit->addAction(actionSort);
    //---------------------------MENU SEARCH--------------------------------------------------
    QAction* actionSearch = new QAction(QIcon(":images/find.png"),"Search...", this);
    actionSearch->setShortcut(tr("Ctrl+F"));
    connect(actionSearch, SIGNAL(triggered()), this, SLOT(findAct()));
    menuSearch->addAction(actionSearch);

    //-----------------------------MENU SETTINGS----------------------------------------------
    QAction* actionSettings = new QAction(QIcon(":images/settings.png"),"Settings", this);
    connect(actionSettings, SIGNAL(triggered()), this, SLOT(settingsAct()));
    menuSettings->addAction(actionSettings);
    //---------------------------MENU VIEW------------------------------------------------------
    QAction* actionFull = new QAction(QIcon(":images/full.png"),"Full/Normal Screen", this);
    actionFull->setShortcut(tr("Ctrl+Return"));
    connect(actionFull, SIGNAL(triggered()), this, SLOT(wndType()));
    menuView->addAction(actionFull);
    //----------------------------MENU HELP------------------------------------------------------
    actionAbout = new QAction(QIcon(":images/info.png"),"About", this);
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    menuHelp->addAction(actionAbout);
    QAction* actionHelp = new QAction(QIcon(":images/visit.png"),"Visit our site", this);
    connect(actionHelp, SIGNAL(triggered()), this, SLOT(visit()));
    menuHelp->addAction(actionHelp);


    statusBar()->showMessage("Ready");
    tbar = addToolBar(tr("File"));

    QToolButton *buttonOpen = new QToolButton;
    buttonOpen->setIcon(QIcon(":images/openfile.png"));
    connect(buttonOpen, SIGNAL(clicked()), this, SLOT(openfile()));
    QToolButton *buttonSave = new QToolButton;
    buttonSave->setIcon(QIcon(":images/save.png"));
    connect(buttonSave, SIGNAL(clicked()), this, SLOT(savefile()));
    QToolButton *buttonUndo = new QToolButton;
    buttonUndo->setIcon(QIcon(":images/undo.png"));
    connect(buttonUndo, SIGNAL(clicked()), this, SLOT(undoAct()));
    QToolButton *buttonRedo = new QToolButton;
    buttonRedo->setIcon(QIcon(":images/redo.png"));
    connect(buttonRedo, SIGNAL(clicked()), this, SLOT(redoAct()));
    QToolButton *buttonCut = new QToolButton;
    buttonCut->setIcon(QIcon(":images/cut.png"));
    connect(buttonCut, SIGNAL(clicked()), this, SLOT(cutAct()));
    QToolButton *buttonCopy = new QToolButton;
    buttonCopy->setIcon(QIcon(":images/copy.png"));
    connect(buttonCopy, SIGNAL(clicked()), this, SLOT(copyAct()));
    QToolButton *buttonPaste = new QToolButton;
    buttonPaste->setIcon(QIcon(":images/paste.png"));
    connect(buttonPaste, SIGNAL(clicked()), this, SLOT(pasteAct()));
    QToolButton *buttonFind = new QToolButton;
    buttonFind->setIcon(QIcon(":images/find.png"));
    connect(buttonFind, SIGNAL(clicked()), this, SLOT(findAct()));
    QToolButton *buttonVisit = new QToolButton;
    buttonVisit->setIcon(QIcon(":images/visit.png"));
    connect(buttonVisit, SIGNAL(clicked()), this, SLOT(visit()));
    QToolButton *buttonAbout = new QToolButton;
    buttonAbout->setIcon(QIcon(":images/info.png"));
    connect(buttonAbout, SIGNAL(clicked()), this, SLOT(about()));
    QToolButton *buttonClose = new QToolButton;
    buttonClose->setIcon(QIcon(":images/close.png"));
    connect(buttonClose, SIGNAL(clicked()), this, SLOT(quitMain()));

    buttonPrevious = new QToolButton;
    buttonPrevious->setIcon(QIcon(":images/previous.png"));
    connect(buttonPrevious, SIGNAL(clicked()), this, SLOT(findPreviousText()));
    buttonNext = new QToolButton;
    buttonNext->setIcon(QIcon(":images/next.png"));
    connect(buttonNext, SIGNAL(clicked()), this, SLOT(findNextText()));
    buttonReplace = new QToolButton;
    buttonReplace->setIcon(QIcon(":images/replace.png"));
    connect(buttonReplace, SIGNAL(clicked()), this, SLOT(replaceText()));

    findedit = new QLineEdit;
    replaceEdit = new QLineEdit;

    tbar->addWidget(buttonOpen);
    tbar->addSeparator();
    tbar->addWidget(buttonSave);
    tbar->addSeparator();
    tbar->addWidget(buttonUndo);
    tbar->addSeparator();
    tbar->addWidget(buttonRedo);
    tbar->addSeparator();
    tbar->addWidget(buttonCut);
    tbar->addSeparator();
    tbar->addWidget(buttonCopy);
    tbar->addSeparator();
    tbar->addWidget(buttonPaste);
    tbar->addSeparator();
    tbar->addWidget(buttonFind);
    tbar->addSeparator();
    tbar->addWidget(buttonVisit);
    tbar->addSeparator();
    tbar->addWidget(buttonAbout);
    tbar->addSeparator();
    tbar->addWidget(buttonClose);
    tbar->addSeparator();
    tbar->addWidget(findedit);
    tbar->addSeparator();
    tbar->addWidget(buttonPrevious);
    tbar->addSeparator();
    tbar->addWidget(buttonNext);
    tbar->addSeparator();
    tbar->addWidget(replaceEdit);
    tbar->addSeparator();
    tbar->addWidget(buttonReplace);
}


void Window::closeTab(int i_index)
{
    if (activeTab()->maybeSave())
        textTabWidget->removeTab(i_index);
}

void Window::findAct()
{
    if (fndwnd == NULL)
    {
        fndwnd = new FindWindow(*this);
        fndwnd->setWindowOpacity(0.95);
        fndwnd->show();
    }
    else
        fndwnd->activateWindow();
}

void Window::closeEvent(QCloseEvent *event)
{
    if (!activeTab() || activeTab()->maybeSave())
    {
        //std::cout << "Event accepted!" << std::endl;
        event->accept();
    }
    else
    {
        //std::cout << "Event ignored!" << std::endl;
        event->ignore();
    }
}

void Window::createGlobalShortcuts()
{
    shortcut = new QShortcut(QKeySequence(tr("Ctrl+O")), this);
    shortcut->setContext(Qt::ApplicationShortcut);
    connect(shortcut, SIGNAL(activated()), this, SLOT(openfile()));

    shortcut2 = new QShortcut(QKeySequence(tr("Ctrl+Return")), this);
    shortcut2->setContext(Qt::ApplicationShortcut);
    connect(shortcut2, SIGNAL(activated()), this, SLOT(wndType()));

    shortcut3 = new QShortcut(QKeySequence(tr("Ctrl+S")), this);
    shortcut3->setContext(Qt::ApplicationShortcut);
    connect(shortcut3, SIGNAL(activated()), this, SLOT(savefile()));

    shortcut4 = new QShortcut(QKeySequence(tr("Ctrl+Q")), this);
    shortcut4->setContext(Qt::ApplicationShortcut);
    connect(shortcut4, SIGNAL(activated()), this, SLOT(quitMain()));

}

void Window::deleteGlobalShortcuts()
{
    delete shortcut;
    shortcut = NULL;
    delete shortcut2;
    shortcut2 = NULL;
    delete shortcut3;
    shortcut3 = NULL;
    delete shortcut4;
    shortcut4 = NULL;
}


//Change recently opened files list length(<=10)
void Window::readConfigurationFile()
{
    s->histpath = s->settings->value("Path/value").toString();
    if (s->histpath.isEmpty()){
        QMessageBox *messnopath = new QMessageBox;
        messnopath->setText("No history file specified\nPlease select it or create a new one");
        messnopath->exec();
        s->browseFile();
    }
    QFile file(s->histpath);
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream ReadFile(&file);
    listaction.clear();
    menuHistoryList->clear();
    while (!ReadFile.atEnd())
    {
        line = ReadFile.readLine();
        QAction* action = new QAction(line, this);
        listaction.append(action);
        connect(listaction.last(), SIGNAL(triggered()), this, SLOT(loadFileintoTextEdit()));
        menuHistoryList->addAction(action);
    }
    QString stringFileName(ReadFile.readAll());
    if (!stringFileName.isEmpty())
    {
        loadFile(stringFileName);
    }
    file.close();
}

void Window::saveConfiguration()
{
    QFile file(s->histpath);
    file.open(QFile::WriteOnly | QFile::Text);
    QTextStream out(&file);
    QList<QAction*>::iterator i;
    for (i = listaction.begin(); i != listaction.end(); ++i){
        (*i)->text();
        out << (*i)->text() << "\n";
    }
    file.close();
}

void Window::loadFileintoTextEdit()
{
    QObject *s = sender();
    QAction* action = (QAction*)s;
    QString tempName = action->text();
    loadFile(tempName);
}


void Window::writePathHistory()
{
    QFileInfo info(fileName);
    s->pathHistory->setValue("Path/value", info.path());
    s->pathHistory->sync();
}


void Window::openfile()
{
    s->pathHist = s->pathHistory->value("Path/value").toString();
    if (s->pathHist.isNull())
        s->pathHist = "../";
    this->fileName = QFileDialog::getOpenFileName(this, tr("Open File"), s->pathHist, tr("Text Files (*.txt)"));
    loadFile(fileName);
    writePathHistory();
    if (fileName != NULL)
    {
        QAction* lastAction = new QAction(fileName, this);
        listaction.prepend(lastAction);
    }
    saveConfiguration();
    readConfigurationFile();
}

void Window::loadFile(QString& fileName)
{
    newTab = new TextTabWidget;
    newTab->loadFile(fileName);
    connect(newTab ,SIGNAL(cursorPositionChanged()), this, SLOT(getCursorPosition()));
    this->fileName = fileName;
    QFileInfo info(fileName);
    textTabWidget->addTab(newTab,info.fileName());
    textTabWidget->setCurrentWidget(newTab);
}


//TextTabWidget* Window::createTab(const QString& fileName)
//{
//   TextTabWidget *tabWidget = new TextTabWidget;
//   textTabWidget->addTab(tabWidget, fileName);
//   return tabWidget;
//}

TextTabWidget* Window::activeTab()
{
    if(TextTabWidget *curWidget = static_cast<TextTabWidget *>(textTabWidget->currentWidget()))
        return curWidget;
    return 0;
}


//Widget *Window::activeMdiChild()
//{
//    if (QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow())
//        return qobject_cast<Widget *>(activeSubWindow->widget());
//    return 0;
//}



void Window::sortAct()
{
    if (activeTab())
    {
        c = activeTab()->textCursor();
        str = c.selectedText();
        list = str.split(QRegExp("\\W+"), QString::SkipEmptyParts);
        list.sort();
        for (int i = 0; i < list.size(); ++i)
        {
            c.insertText(list.value(i));
            c.insertText("\n");
        }
    }
}

void Window::savefile()
{
    if (activeTab() && activeTab()->save())
        statusBar()->showMessage(tr("File saved"), 2000);
}

void Window::savefileAs()
{
    if (activeTab() && activeTab()->saveAs())
        statusBar()->showMessage(tr("File saved"), 2000);
}

void Window::visit()
{
    Webview *qtWindow = new Webview;
    qtWindow->setAttribute(Qt::WA_DeleteOnClose);
    qtWindow->load(QUrl("http://qt.digia.com/"));
    qtWindow->show();
}

void Window::about()
{
    AboutWnd *wndAb = new AboutWnd();
    wndAb->exec();
    //QApplication::aboutQt();
}

void Window::settingsAct()
{
    SettingsWnd *wndSet = new SettingsWnd(*this);
    wndSet->exec();
}

void Window::quitMain()
{
    std::cout << "Exiting Program";
    QApplication::quit();
}


void Window::copyAct()
{
    if (activeTab())
        activeTab()->copy();
}

void Window::pasteAct()
{
    if (activeTab())
        activeTab()->paste();
}

void Window::cutAct()
{
    if (activeTab())
        activeTab()->cut();
}

void Window::undoAct()
{
    if (activeTab())
        activeTab()->undo();
}

void Window::redoAct()
{
    if (activeTab())
        activeTab()->redo();
}

void Window::wndType()
{
    isFullScreen() ? showNormal() : showFullScreen();
    if (isFullScreen()){
        createGlobalShortcuts();
        menuBar()->hide();
        tbar->hide();
        statusBar()->hide();
    }
    else
    {
        deleteGlobalShortcuts();
        menuBar()->show();
        tbar->show();
        statusBar()->show();
    }
}

void Window::converttoUpper()
{
    if (activeTab())
    {
        c = activeTab()->textCursor();
        c.insertText(c.selectedText().toUpper());
    }
}

void Window::converttoLower()
{
    if (activeTab())
    {
        c = activeTab()->textCursor();
        c.insertText(c.selectedText().toLower());
    }
}

void Window::findPreviousText()
{
    if (activeTab())
    {
        activeTab()->setFocus();
        activeTab()->find(findedit->text(),QTextDocument::FindBackward);
    }
}

void Window::findNextText()
{
    if (activeTab())
    {
        activeTab()->setFocus();
        activeTab()->find(findedit->text());
    }
}

void Window::replaceText()
{
    if (activeTab())
    {
        activeTab()->setFocus();
        activeTab()->insertPlainText(replaceEdit->text());
    }
}

void Window::getCursorPosition()
{
    c = activeTab()->textCursor();
    statusBar()->showMessage("Ln:"+QString::number(c.blockNumber()+1)+ " " + "|" + " " + "Col:"+QString::number(c.columnNumber()+1), 0);
}










