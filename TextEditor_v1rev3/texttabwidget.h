#ifndef TEXTTABWIDGET
#define TEXTTABWIDGET

#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QApplication>
#include <QFileInfo>
#include <QFileDialog>
#include <QCloseEvent>
#include <iostream>

class TextTabWidget : public QTextEdit
{
    Q_OBJECT
public:
    TextTabWidget();
    ~TextTabWidget(){std::cout << "Tab widget destroyed" << std::endl;}
private:
    bool isUntitled;
    QString curFile;
    QString strippedName(const QString &fullFileName);   
private slots:
    void documentWasModified();
public slots:
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    bool loadFile(const QString& fileName);
    void setCurrentFile(const QString &fileName);
    QString userFriendlyCurrentFile();
    QString currentFile() { return curFile; }
    bool maybeSave();
};

#endif // TEXTTABWIDGET

