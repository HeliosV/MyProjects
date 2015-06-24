#include "findtab.h"

FindTab::FindTab(Window& w, FindWindow &fwnd) : QWidget(), mainwnd(w), findw(fwnd)
{
    setAttribute(Qt::WA_DeleteOnClose);
    QGridLayout *mainLayout = new QGridLayout;
    QHBoxLayout *findlayout = new QHBoxLayout;
    editwhat = new QLineEdit;
    findNextButton = new QPushButton(tr("Search next"));
    connect(findNextButton, SIGNAL(clicked()), this, SLOT(findNextText()));

    QLabel *findlab = new QLabel;
    findlab->setText("Find: ");

    findlayout->addWidget(findlab);
    findlayout->addWidget(editwhat);
    findlayout->addWidget(findNextButton);

    QHBoxLayout *settingsLayout = new QHBoxLayout;

    QGroupBox *propertyBox = new QGroupBox(tr("Properties"));
    checkLoop = new QCheckBox("L&oop search", this);
    checkRegister = new QCheckBox("C&ase sensitive", this);
    checkWholeWord = new QCheckBox("O&nly whole words", this);
    QVBoxLayout *propVBox = new QVBoxLayout;
    propVBox->addWidget(checkLoop);
    propVBox->addWidget(checkRegister);
    propVBox->addWidget(checkWholeWord);
    propertyBox->setLayout(propVBox);


    QGroupBox *directionBox = new QGroupBox(tr("Direction"));
    radioUp = new QRadioButton(tr("U&p"));
    QRadioButton *radioDown = new QRadioButton(tr("D&own"));
    radioDown->setChecked(true);

    QVBoxLayout *directVBox = new QVBoxLayout;
    directVBox->addWidget(radioUp);
    directVBox->addWidget(radioDown);
    directionBox->setLayout(directVBox);

    settingsLayout->addWidget(propertyBox);
    settingsLayout->addWidget(directionBox);

    mainLayout->addLayout(findlayout, 0, 0);
    mainLayout->addLayout(settingsLayout, 1, 0);

    setLayout(mainLayout);
}

void FindTab::findNextText()
{ 
    QFlags<QTextDocument::FindFlag> flags;
    QTextCursor::MoveOperation moveOpFlag = QTextCursor::Start;

    if (mainwnd.activeTab())
    {
        QPalette p = mainwnd.activeTab()->palette();
        p.setColor(QPalette::Inactive, QPalette::Highlight, p.color(QPalette::Active, QPalette::Highlight));
        p.setColor(QPalette::Inactive, QPalette::HighlightedText, p.color(QPalette::Active, QPalette::HighlightedText));
        mainwnd.activeTab()->setPalette(p);
        mainwnd.activeTab()->setFocus();
        if (checkRegister->isChecked())
            flags |= QTextDocument::FindCaseSensitively;
        if (checkWholeWord->isChecked())
            flags |= QTextDocument::FindWholeWords;
        if (radioUp->isChecked())
        {
            flags |= QTextDocument::FindBackward;
            moveOpFlag = QTextCursor::End;
        }

        if (!mainwnd.activeTab()->find(editwhat->text(), flags))
        {
            if (checkLoop->isChecked())
            {
                QTextCursor tmpCursor = mainwnd.activeTab()->textCursor();
                tmpCursor.movePosition(moveOpFlag, QTextCursor::MoveAnchor, 0);
                mainwnd.activeTab()->setTextCursor(tmpCursor);
                mainwnd.activeTab()->find(editwhat->text(), flags);
            }
            else
                findw.statusBar->showMessage("You've reached the end of document");
        }
    }
}

