#ifndef REPLACETAB
#define REPLACETAB

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QRadioButton>
#include "mainwindow.h"

class ReplaceTab : public QWidget
{
    Q_OBJECT
public:
    ReplaceTab(Window& w, FindWindow& fwnd);
    ~ReplaceTab(){}
private:
    QLineEdit *editwhat;
    QPushButton *findNextButton;
    QLineEdit *editfor;
    QPushButton *replaceButton;
    QCheckBox *checkLoop;
    QCheckBox *checkRegister;
    QCheckBox *checkWholeWord;
    QRadioButton *radioUp;
    Window& mainwnd;
    FindWindow& findw;
public slots:
    void replaceText();
    void findNextText();
};

#endif // REPLACETAB

