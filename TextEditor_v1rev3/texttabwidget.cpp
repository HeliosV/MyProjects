#include <texttabwidget.h>
#include <iostream>

TextTabWidget::TextTabWidget() : QTextEdit()
{
    setWindowTitle("File name"); // need to path text file parameter
    setAttribute(Qt::WA_DeleteOnClose);
    isUntitled = true;
}

bool TextTabWidget::loadFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
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

//void TextTabWidget::closeEvent(QCloseEvent *event)
//{
//    if (maybeSave())
//        event->accept();
//    else
//        event->ignore();
//}


void TextTabWidget::setCurrentFile(const QString &fileName)
{
    curFile = QFileInfo(fileName).canonicalFilePath();
    isUntitled = false;
    document()->setModified(false);
    setWindowModified(false);
    setWindowTitle(userFriendlyCurrentFile() + "[*]");
}

QString TextTabWidget::userFriendlyCurrentFile()
{
    return strippedName(curFile);
}

QString TextTabWidget::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void TextTabWidget::documentWasModified()
{
    setWindowModified(document()->isModified());
}

bool TextTabWidget::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), curFile);
    if (fileName.isEmpty())
        return false;
    return saveFile(fileName);
}

bool TextTabWidget::save()
{
    return saveFile(curFile);
}

bool TextTabWidget::maybeSave()
{
    if (document()->isModified())
    {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Text Editor"),tr("'%1' has been modified.\n"
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

bool TextTabWidget::saveFile(const QString &fileName)
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
