#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QList>
#include <QPushButton>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QSlider>
#include <QLabel>
#include <QToolBar>
#include <QTableWidget>
#include <QLCDNumber>
#include <QListWidget>
#include <QDir>
#include <QToolButton>
#include "Server.h"


class Server;

 class MainWindow : public QMainWindow
 {
     Q_OBJECT

 public:
     MainWindow();

 private slots:
     void addFile();
     void addDir();
     void shuffle();
     void objectClicked(QListWidgetItem* item);
     void checkAv();
     void shuffleOff();
     void clearPl();
     void positionChanged(qint64 position);
     void setDuration();
     void setPosition(int position);
     void checkPlItems();
     void runServer();
 public slots:
     void play();
     void pause();
     void stop();
     void next();
     void previous();

 public:
     QMediaPlayer *player;
     QMediaPlaylist *playlist;
     QPushButton *btnPlay;
     QPushButton *btnPause;
     QMenu* menuFile;
     QMenu* menuEdit;
     QMenu* menuSettings;
     QMenu* menuHelp;
     QMenu* menuView;
     QVBoxLayout *layout;
     //QProgressBar *progressBar;
     QSlider *progressSlider;
     QSlider *volumeSlider;
     QLabel *volumeLabel;
     QLabel *durationLabel;
     QLabel *nowPlayingLabel;
     QToolBar *tbar;
     QToolBar *barProgress;
     QListWidget *tableWidget;
     QStringList horHeader;
     QList <QMediaContent> media;
     QStringList files;
     qint64 time;
     QString directory;
     QStringList fileName;
     QString f1;
     QToolButton *buttonPlay;
     QToolButton *buttonPause;
     QToolButton *buttonStop;
     QToolButton *buttonNext;
     QToolButton *buttonPrevious;
     QToolButton *buttonShuffle;
     QToolButton *buttonShuffleOff;
     QToolButton *buttonClearPl;
     QAction* actionPlay;
     QAction* actionPause;
     QAction* actionStop;
     Server *serv;
 };


#endif // MAINWINDOW_H
