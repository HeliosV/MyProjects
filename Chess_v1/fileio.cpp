#include "fileio.h"
#include <QFile>
#include <iostream>


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
    if (!file.open(QFile::WriteOnly | QIODevice::Text | QIODevice::Append))
        return false;

    QTextStream out(&file);
    out << data;
    out << endl;

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

QString FileIO::readCurrentLine(int i_index)
{
    if (mSource.isEmpty()){
        emit error("source is empty");
        return QString();
    }

    int count = 0;
    QFile file(mSource);
    QString fileContent;
    if ( file.open(QIODevice::ReadOnly) ) {
        QString line;
        QTextStream t( &file );
        do
        {
            line = t.readLine();
            ++count;
            if (count == i_index)
            {
                fileContent += line;
                break;
            }

        }
        while (!line.isNull());

        file.close();
    } else {
        emit error("Unable to open the file");
        return QString();
    }
    return fileContent;
}

int FileIO::moveCount()
{
    if (mSource.isEmpty()){
        emit error("source is empty");
        return 0;
    }

    int count = 0;

    QFile file(mSource);

    if ( file.open(QIODevice::ReadOnly) ) {
        QString line;
        QTextStream t( &file );
        do
        {
            line = t.readLine();
            ++count;
        }
        while (!line.isNull());

        file.close();
    } else {
        emit error("Unable to open the file");
        return 0;
    }
    return count;
}
