#include <QApplication>
#include <QQmlApplicationEngine>
#include "fileio.h"
#include <QtQml>

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<FileIO, 1>("FileIO", 1, 0, "FileIO");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
