#include "aboutwindow.h"

AboutWnd::AboutWnd() : QDialog()
{
    setAttribute(Qt::WA_DeleteOnClose);
    move(500, 500);
    resize(200,100);
    setWindowTitle("About");
    QLabel *lab = new QLabel(this);
    lab->setText("ABOUT");
    btn = new QPushButton(this);
    btn->setText("Ok");
    btn->move(50,50);
    connect(btn, SIGNAL(clicked()), this, SLOT(quitAbout()));
}

void AboutWnd::quitAbout()
{
    close();
}

