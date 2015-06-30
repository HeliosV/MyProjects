#include "fileio.h"
#include <QFile>


FileIO::FileIO(QObject *parent) :
    QObject(parent)
{

}

QString FileIO::read()
{
    if (mSource.isEmpty()){
        emit error("source is empty");
        return QString();
    }

    QFile file(mSource);
    QString fileContent;
    if ( file.open(QIODevice::ReadOnly) ) {
        QString line;
        QTextStream t( &file );
        do {
            line = t.readLine();
            fileContent += line;
         } while (!line.isNull());

        file.close();
    } else {
        emit error("Unable to open the file");
        return QString();
    }
    return fileContent;
}

bool FileIO::write(const QString& data)
{
    if (mSource.isEmpty())
        return false;

    QFile file(mSource);
    if (!file.open(QFile::WriteOnly | QFile::Append))
        return false;

    QTextStream out(&file);
    out << data;

    file.close();

    return true;
}

bool FileIO::clear()
{
    if (mSource.isEmpty())
        return false;

    QFile file(mSource);
    if (!file.open(QFile::ReadWrite| QFile::Truncate))
        return false;

    QTextStream out(&file);
    out << "";

    file.close();

    return true;
}
