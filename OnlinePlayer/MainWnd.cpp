
#include <iostream>
#include <QtGui>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QMessageBox>
#include <QMediaPlaylist>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QMediaContent>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QToolButton>
#include <QTableWidget>
#include <QMediaObject>
#include <QMediaMetaData>
#include <QListWidget>
#include "MainWnd.h"
#include "Server.h"

 MainWindow::MainWindow()
 {
     //serv = new Server(*this);

     setWindowTitle("Music Player");

     menuFile = menuBar()->addMenu(tr("&File"));
     actionPlay = new QAction(QIcon(":images/play.png"),"Play", this);
     connect(actionPlay, SIGNAL(triggered()), this, SLOT(play()));
     menuFile->addAction(actionPlay);
     actionPause = new QAction(QIcon(":images/pause.png"),"Pause", this);
     connect(actionPause, SIGNAL(triggered()), this, SLOT(pause()));
     menuFile->addAction(actionPause);
     actionStop = new QAction(QIcon(":images/stop.png"),"Stop", this);
     connect(actionStop, SIGNAL(triggered()), this, SLOT(stop()));
     menuFile->addAction(actionStop);

     tbar = addToolBar(tr("Control Bar"));

     buttonPlay = new QToolButton;
     buttonPlay->setIcon(QIcon(":images/play.png"));
     connect(buttonPlay, SIGNAL(clicked()), this, SLOT(play()));
     buttonPause = new QToolButton;
     buttonPause->setIcon(QIcon(":images/pause.png"));
     connect(buttonPause, SIGNAL(clicked()), this, SLOT(pause()));
     buttonStop = new QToolButton;
     buttonStop->setIcon(QIcon(":images/stop.png"));
     connect(buttonStop, SIGNAL(clicked()), this, SLOT(stop()));
     buttonPrevious = new QToolButton;
     buttonPrevious->setIcon(QIcon(":images/prev.png"));
     connect(buttonPrevious, SIGNAL(clicked()), this, SLOT(previous()));
     buttonNext = new QToolButton;
     buttonNext->setIcon(QIcon(":images/next.png"));
     connect(buttonNext, SIGNAL(clicked()), this, SLOT(next()));
     buttonShuffle = new QToolButton;
     buttonShuffle->setIcon(QIcon(":images/shuffle.png"));
     connect(buttonShuffle, SIGNAL(clicked()), this, SLOT(shuffle()));
     buttonShuffleOff = new QToolButton;
     buttonShuffleOff->setIcon(QIcon(":images/shuffleoff.png"));
     connect(buttonShuffleOff, SIGNAL(clicked()), this, SLOT(shuffleOff()));
     buttonClearPl = new QToolButton;
     buttonClearPl->setIcon(QIcon(":images/clearpl.png"));
     connect(buttonClearPl, SIGNAL(clicked()), this, SLOT(clearPl()));
     QToolButton *addDir = new QToolButton;
     addDir->setIcon(QIcon(":images/addfolder.png"));
     connect(addDir, SIGNAL(clicked()), this, SLOT(addDir()));
     QToolButton *addFile = new QToolButton;
     addFile->setIcon(QIcon(":images/addfiles.png"));
     connect(addFile, SIGNAL(clicked()), this, SLOT(addFile()));
     QToolButton *runServer = new QToolButton;
     runServer->setIcon(QIcon(":images/server.png"));
     connect(runServer, SIGNAL(clicked()), this, SLOT(runServer()));

     progressSlider = new QSlider(Qt::Horizontal, this);
     volumeSlider = new QSlider(Qt::Horizontal, this);
     volumeLabel = new QLabel(this);
     durationLabel = new QLabel(this);
     nowPlayingLabel = new QLabel(this);
     volumeLabel->setText("Volume");
     tbar->addWidget(buttonPlay);
     tbar->addSeparator();
     tbar->addWidget(buttonPause);
     tbar->addSeparator();
     tbar->addWidget(buttonStop);
     tbar->addSeparator();
     tbar->addWidget(buttonPrevious);
     tbar->addSeparator();
     tbar->addWidget(buttonNext);
     tbar->addSeparator();
     tbar->addWidget(buttonShuffle);
     tbar->addSeparator();
     tbar->addWidget(buttonShuffleOff);
     tbar->addSeparator();
     tbar->addWidget(buttonClearPl);
     tbar->addSeparator();
     tbar->addWidget(addFile);
     tbar->addSeparator();
     tbar->addWidget(addDir);
     tbar->addSeparator();
     tbar->addWidget(runServer);
     tbar->addSeparator();
     tbar->addWidget(volumeLabel);
     tbar->addWidget(volumeSlider);
     tbar->addSeparator();
     barProgress = addToolBar(tr("Progress Bar"));
     barProgress->addWidget(progressSlider);
     barProgress->addSeparator();
     barProgress->addWidget(durationLabel);
     insertToolBarBreak(barProgress);
     statusBar()->addWidget(nowPlayingLabel);
     player = new QMediaPlayer;
     playlist = new QMediaPlaylist(player);
     playlist->setCurrentIndex(0);
     playlist->setPlaybackMode(QMediaPlaylist::Loop);
     tableWidget = new QListWidget(this);
     setCentralWidget(tableWidget);
     player->setPlaylist(playlist);
     player->setVolume(100);
     volumeSlider->setTickPosition(QSlider::TicksRight);
     volumeSlider->setValue(100);
     connect(volumeSlider, SIGNAL(valueChanged(int)), player, SLOT(setVolume(int)));
     connect(player,SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
     connect(player,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(setDuration()));
     connect(player,SIGNAL(positionChanged(qint64)), this, SLOT(setDuration()));
     connect(progressSlider,SIGNAL(sliderMoved(int)), this, SLOT(setPosition(int)));
     connect(playlist, SIGNAL(currentMediaChanged(QMediaContent)), this, SLOT(checkAv()));
     connect(tableWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(objectClicked(QListWidgetItem*)));
     checkPlItems();

 }


 void MainWindow::runServer()
 {
     Server *serv = new Server(*this);
     //serv->show();
 }


 void MainWindow::setDuration()
 {
     if (player->mediaStatus() == 6)
     {
         QTime displayDur(0, (player->duration() / 60000) % 60, (player->duration() / 1000) % 60);
         QTime displayPos(0, (player->position() / 60000) % 60, (player->position() / 1000) % 60);
         durationLabel->setText(displayPos.toString("mm:ss")+"/"+displayDur.toString("mm:ss"));
     }
 }

 void MainWindow::setPosition(int position)
 {
    player->setPosition(qint64(position));
 }

 void MainWindow::checkPlItems()
 {
     if (!playlist->isEmpty())
     {
         buttonPlay->setEnabled(true);
         buttonPause->setEnabled(true);
         buttonStop->setEnabled(true);
         buttonPrevious->setEnabled(true);
         buttonNext->setEnabled(true);
         buttonShuffle->setEnabled(true);
         buttonShuffleOff->setEnabled(true);
         buttonClearPl->setEnabled(true);
         actionPlay->setEnabled(true);
         actionPause->setEnabled(true);
         actionStop->setEnabled(true);
     }
     else
     {
         buttonPlay->setEnabled(false);
         buttonPause->setEnabled(false);
         buttonStop->setEnabled(false);
         buttonPrevious->setEnabled(false);
         buttonNext->setEnabled(false);
         buttonShuffle->setEnabled(false);
         buttonShuffleOff->setEnabled(false);
         buttonClearPl->setEnabled(false);
         actionPlay->setEnabled(false);
         actionPause->setEnabled(false);
         actionStop->setEnabled(false);
     }
 }

 void MainWindow::positionChanged(qint64 position)
 {
     progressSlider->setRange(0, player->duration());
     progressSlider->setValue(qBound(qint64(0),  position, player->position()));
 }

 void MainWindow::checkAv()
 {
    tableWidget->setCurrentRow(playlist->currentIndex());
    if (!playlist->isEmpty())
        nowPlayingLabel->setText("Now Palying:  "+ tableWidget->currentItem()->text());
    else
    {
        nowPlayingLabel->setText("Empty Playlist");
        durationLabel->setText("00:00/00:00");
    }
 }

 void MainWindow::objectClicked(QListWidgetItem* item)
 {
     playlist->setCurrentIndex(tableWidget->currentRow());
     nowPlayingLabel->setText("Now Palying:  "+item->text());
     play();
 }

 void MainWindow::addFile()
 {
     fileName = QFileDialog::getOpenFileNames(this, tr("Open File"), "D:/", tr("Music Files (*.mp3)"));
     if(fileName.isEmpty())
         return;
     QList<QMediaContent> content;
     for(int i=0; i<fileName.count(); i++)
     {
         f1 = fileName.at(i);
         QFileInfo fi(f1);
         content.push_back(QUrl::fromLocalFile(fi.filePath()));
         tableWidget->addItem(fi.fileName());
     }
     playlist->addMedia(content);
     checkPlItems();
 }

 void MainWindow::addDir()
 {
     directory = QFileDialog::getExistingDirectory(this,tr("Select dir for files to import"));
     if(directory.isEmpty())
         return;
     QDir dir(directory);
     files = dir.entryList(QStringList() << "*.mp3",QDir::Files);
     QList<QMediaContent> content;

     for(int i=0; i<files.count(); i++)
     {
         QString f = files.at(i);
         content.push_back(QUrl::fromLocalFile(dir.path()+"/" + f));
         QFileInfo fi(f);
         tableWidget->addItem(fi.fileName());
     }
     playlist->addMedia(content);
     tableWidget->setCurrentRow(playlist->currentIndex() != -1? playlist->currentIndex():0);
     checkPlItems();
 }


 void MainWindow::play()
 {
    player->play();
    nowPlayingLabel->setText("Now Palying:  "+ tableWidget->currentItem()->text());
 }

 void MainWindow::pause()
 {
    player->pause();
 }


 void MainWindow::stop()
 {
    player->stop();
 }

 void MainWindow::previous()
 {
    playlist->previous();
    if(tableWidget->currentRow()<0)
    {
        tableWidget->setCurrentRow(tableWidget->count()-1);
        playlist->setCurrentIndex(playlist->mediaCount()-1);
        play();
    }
    nowPlayingLabel->setText("Now Palying:  "+ tableWidget->currentItem()->text());
    if(playlist->playbackMode() == 4)
    {
        tableWidget->setCurrentRow(playlist->currentIndex());
        nowPlayingLabel->setText("Now Palying:  "+ tableWidget->currentItem()->text());
    }
    else
        return;
 }

 void MainWindow::next()
 {
    playlist->next();
    if(tableWidget->currentRow()<0)
    {
        tableWidget->setCurrentRow(0);
        playlist->setCurrentIndex(0);
        play();
    }
    nowPlayingLabel->setText("Now Palying:  "+ tableWidget->currentItem()->text());
    if(playlist->playbackMode() == 4)
    {
        tableWidget->setCurrentRow(playlist->currentIndex());
        nowPlayingLabel->setText("Now Palying:  "+ tableWidget->currentItem()->text());
    }
    else
        return;
 }

 void MainWindow::shuffle()
 {
     playlist->setPlaybackMode(QMediaPlaylist::Random);
 }

 void MainWindow::shuffleOff()
 {
     playlist->setPlaybackMode(QMediaPlaylist::Sequential);
 }

 void MainWindow::clearPl()
 {
     playlist->clear();
     tableWidget->clear();
     checkPlItems();
 }








