#include <iostream>
#include <QGuiApplication>
#include <QApplication>
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
#include <QTextStream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolBar>
#include <QToolButton>
#include <QScrollBar>
#include <QFileInfo>
#include <QSettings>
#include <QFileDialog>
#include <QShortcut>
#include <QMdiArea>
#include <QSignalMapper>
#include <QCloseEvent>
#include "textwindow.h"
#include "aboutwindow.h"
#include "settingswindow.h"
#include "mainwindow.h"

Widget::Widget() : QTextEdit()
{
    setAttribute(Qt::WA_DeleteOnClose);
    isUntitled = true;
}

bool Widget::loadFile(const QString &fileName)
 {
     QFile file(fileName);
     if (!file.open(QFile::ReadOnly | QFile::Text)) {
         QMessageBox::warning(this, tr("Text Editor"),
                              tr("Cannot read file %1:\n%2.")
                              .arg(fileName)
                              .arg(file.errorString()));
         return false;
     }
     QTextStream in(&file);
     QApplication::setOverrideCursor(Qt::WaitCursor);
     setPlainText(in.readAll());
     QApplication::restoreOverrideCursor();
     setCurrentFile(fileName);
     connect(document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));
     return true;
 }

void Widget::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void Widget::setCurrentFile(const QString &fileName)
 {
     curFile = QFileInfo(fileName).canonicalFilePath();
     isUntitled = false;
     document()->setModified(false);
     setWindowModified(false);
     setWindowTitle(userFriendlyCurrentFile() + "[*]");
 }

void Widget::documentWasModified()
 {
     setWindowModified(document()->isModified());
 }

QString Widget::userFriendlyCurrentFile()
 {
     return strippedName(curFile);
 }

QString Widget::strippedName(const QString &fullFileName)
 {
     return QFileInfo(fullFileName).fileName();
 }

bool Widget::save()
 {
    return saveFile(curFile);
 }

bool Widget::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), curFile);
    if (fileName.isEmpty())
        return false;
    return saveFile(fileName);
}

bool Widget::maybeSave()
{
    if (document()->isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Text Editor"),
                     tr("'%1' has been modified.\n"
                        "Do you want to save your changes?")
                     .arg(userFriendlyCurrentFile()),
                     QMessageBox::Save | QMessageBox::Discard
                     | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return saveAs();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

bool Widget::saveFile(const QString &fileName)
 {
     QFile file(fileName);
     if (!file.open(QFile::WriteOnly | QFile::Text)) {
         QMessageBox::warning(this, tr("Text Editor"),
                              tr("Cannot write file %1:\n%2.")
                              .arg(fileName)
                              .arg(file.errorString()));
         return false;
     }
     QTextStream out(&file);
     QApplication::setOverrideCursor(Qt::WaitCursor);
     out << toPlainText();
     QApplication::restoreOverrideCursor();
     setCurrentFile(fileName);
     return true;
 }


























