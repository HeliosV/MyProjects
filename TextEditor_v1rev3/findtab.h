#ifndef FINDTAB
#define FINDTAB

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QRadioButton>
#include "mainwindow.h"

class FindTab : public QWidget
{
    Q_OBJECT
public:
    FindTab(Window& w, FindWindow& fwnd);
    ~FindTab(){}
private:
    QLineEdit *editwhat;
    QPushButton *findNextButton;
    QCheckBox *checkLoop;
    QCheckBox *checkRegister;
    QCheckBox *checkWholeWord;
    QRadioButton *radioUp;
    Window& mainwnd;
    FindWindow& findw;
public slots:
    void findNextText();
};


#endif // FINDTAB

