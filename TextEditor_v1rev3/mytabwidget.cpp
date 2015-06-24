#include <mytabwidget.h>
#include <QCloseEvent>

MyTabWidget::MyTabWidget()
{

}

void MyTabWidget::closeEvent(QCloseEvent *event)
{
    if (true)
    {
      std::cout << "Hello cruel world!" << std::endl;
      event->accept();
    }
    else
    {
        std::cout << "bye cruel world!" << std::endl;
        event->ignore();
    }
}
