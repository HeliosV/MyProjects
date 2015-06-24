#include "settingswindow.h"
#include "mainwindow.h"

SettingsWnd::SettingsWnd(Window& w) : QDialog(), widget(w)
{
    setAttribute(Qt::WA_DeleteOnClose);
    settings = new QSettings("../historyfilepath.ini",QSettings::IniFormat);
    pathHistory = new QSettings("../pathhistory.ini",QSettings::IniFormat);
    setMinimumSize(QSize(500, 200));
    setWindowTitle("Settings");

    QGridLayout *mainLayout = new QGridLayout;

    QHBoxLayout *dialogLayout = new QHBoxLayout;

    okbtn = new QPushButton;
    okbtn->setText("OK");

    cancbtn = new QPushButton;
    cancbtn->setText("Cancel");

    applbtn = new QPushButton(this);
    applbtn->setText("Apply");

    dialogLayout->addWidget(okbtn);
    dialogLayout->addWidget(cancbtn);
    dialogLayout->addWidget(applbtn);

    QVBoxLayout *historyFileLayout = new QVBoxLayout;

    browse = new QPushButton(this);
    browse->setText("Browse history file");

    clearhist = new QPushButton(this);
    clearhist->setText("Clear history");

    historyFileLayout->addWidget(browse);
    historyFileLayout->addWidget(clearhist);

    connect(cancbtn, SIGNAL(clicked()), this, SLOT(reject()));
    connect(applbtn, SIGNAL(clicked()), this, SLOT(accept()));
    connect(okbtn, SIGNAL(clicked()), this, SLOT(close()));
    connect(browse, SIGNAL(clicked()), this, SLOT(browseFile()));
    connect(clearhist, SIGNAL(clicked()), this, SLOT(clearHistory()));

    mainLayout->addLayout(historyFileLayout, 0, 0);
    mainLayout->addLayout(dialogLayout, 1, 1);

    setLayout(mainLayout);
}

void SettingsWnd::quitSettings()
{
    close();
}

void SettingsWnd::clearHistory()
{
    QFile file(settings->value("Path/value").toString());
    file.resize(0);
    widget.readConfigurationFile();
}

void SettingsWnd::browseFile()
{
    histpath = QFileDialog::getOpenFileName(this, tr("Open File"), "../", tr("History Files (*.txt)"));
    settings->setValue("Path/value", histpath);
    settings->sync();
    widget.readConfigurationFile();
}

void SettingsWnd::accept()
{
    QMessageBox mess;
    mess.setText(histpath);
    mess.exec();
}

