#ifndef PLAYSCENE_H
#define PLAYSCENE_H
#include <myicon.h>
#include <QMainWindow>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = 0);
    PlayScene(int levelNum);
    int levelIndex;
     void paintEvent(QPaintEvent *);
     int gameArray[4][4];
     MyIcon*btnicon[4][4];
      void sleep(unsigned int msec);
      bool isWin;
signals:
     void playChooseSceneBack();

public slots:

};

#endif // PLAYSCENE_H
