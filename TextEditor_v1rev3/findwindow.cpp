#include "findwindow.h"
#include "findtab.h"
#include "replacetab.h"

FindWindow::FindWindow(Window& w) : QMainWindow(), mainwnd(w)
{
    setAttribute(Qt::WA_DeleteOnClose);

    setWindowTitle("Find");
    setMinimumSize(400, 220);
    setMaximumSize(400, 220);

    tabWidget = new QTabWidget(this);
    tabWidget->addTab(new FindTab(mainwnd, *this),"Find");
    tabWidget->addTab(new ReplaceTab(mainwnd, *this),"Replace");
    setCentralWidget(tabWidget);

    statusBar = new QStatusBar;
    statusBar->showMessage("In progress...");
    setStatusBar(statusBar);
}

FindWindow::~FindWindow()
{
    delete tabWidget;
    delete statusBar;
}


void FindWindow::closeEvent(QCloseEvent *event)
{
    if (event->type() == QEvent::Close)
    {
        mainwnd.fndwnd = NULL;
    }
}





