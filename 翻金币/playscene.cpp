#include "playscene.h"
#include <QMenuBar>
#include <QPainter>
#include <QLabel>
#include "mypushbutton.h"
#include "myicon.h"
#include "dataconfig.h"
#include <QTime>
#include <QCoreApplication>
#include <QDebug>
#include <QPropertyAnimation>
#include <QSound>
//PlayScene::PlayScene(QWidget *parent) :
//    QMainWindow(parent)
//{
//}
PlayScene::PlayScene(int levelNum)
{
    this->levelIndex=levelNum;
    this->setFixedSize(350,588);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("游戏场景");
    QMenuBar*bar=menuBar();
    setMenuBar(bar);
    QMenu *startMenu=bar->addMenu("开始");
    QAction *quitAction=startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
       this->close();
    });
    QSound*backSound=new QSound(":/res/BackButtonSound.wav");
    QSound*flipSound=new QSound(":/res/ConFlipSound.wav");
    QSound*winSound=new QSound(":/res/LevelWinSound.wav");
    MyPushButton*backbar=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backbar->setParent(this);
    backbar->move(this->width()-backbar->width(),this->height()-backbar->height());
    connect(backbar,&MyPushButton::clicked,[=](){
        backSound->play();
      emit this->playChooseSceneBack();
    });
    QLabel*lable=new QLabel;
    lable->setParent(this);
    QFont font;
    font.setFamily("ScriptC");
    font.setPointSize(20);
    font.setBold(true);
    QString str=QString("Level:%1").arg(this->levelIndex);
    lable->setFont(font);
    lable->setText(str);
    lable->setGeometry(30,this->height()-50,120,50);
    dataConfig config;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->gameArray[i][j]=config.mData[this->levelIndex][i][j];
        }
    }
    QLabel*winLable=new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLable->setPixmap(tmpPix);
    winLable->setParent(this);
    winLable->move((this->width()-tmpPix.width())*0.5,-4*tmpPix.height());

    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            QLabel *lable=new QLabel;
            lable->setGeometry(0,0,50,50);
            lable->setPixmap(QPixmap(":/res/BoardNode(1).png"));
            lable->setParent(this);
            lable->move(72+i*50,200+j*50);
            QString str;
            if(this->gameArray[i][j]==1)
            {
                str=":/res/Coin0001.png";
            }
            else
            {
                str=":/res/Coin0008.png";
            }
            MyIcon *icon=new MyIcon(str);
            icon->setParent(this);
            icon->move(74+i*50,204+j*50);
            icon->posX=i;
            icon->posY=j;
            icon->flag=this->gameArray[i][j];
            btnicon[i][j]=icon;
            connect(icon,&MyIcon::clicked,[=](){
                flipSound->play();
              icon->changeFlag();
              this->gameArray[i][j]=this->gameArray[i][j]==0?1:0;
              sleep(300);
              if(icon->posX+1<=3)
              {
                  btnicon[icon->posX+1][icon->posY]->changeFlag();
                  this->gameArray[icon->posX+1][icon->posY]=this->gameArray[icon->posX+1][icon->posY]==0?1:0;
              }
              if(icon->posX-1>=0)
              {
                  btnicon[icon->posX-1][icon->posY]->changeFlag();
                  this->gameArray[icon->posX-1][icon->posY]=this->gameArray[icon->posX-1][icon->posY]==0?1:0;

              }
              if(icon->posY+1<=3)
              {
                  btnicon[icon->posX][icon->posY+1]->changeFlag();
                  this->gameArray[icon->posX][icon->posY+1]=this->gameArray[icon->posX][icon->posY+1]==0?1:0;
              }
              if(icon->posY-1>=0)
              {
                  btnicon[icon->posX][icon->posY-1]->changeFlag();
                  this->gameArray[icon->posX][icon->posY-1]=this->gameArray[icon->posX][icon->posY-1]==0?1:0;
              }
              this->isWin=true;
              for(int i=0;i<4;i++)
              {
                  for(int j=0;j<4;j++)
                  {
                      if(btnicon[i][j]->flag==false)
                      {
                          this->isWin=false;
                          break;
                      }
                  }
              }
              if(this->isWin==true)
              {
                  winSound->play();

                  qDebug()<<"游戏胜利";
                    for(int i=0;i<4;i++)
                     {
                       for(int j=0;j<4;j++)
                     {
                       btnicon[i][j]->isWin=true;
                     }
                    }
                    QPropertyAnimation *animation=new QPropertyAnimation(winLable,"geometry");
                    animation->setDuration(1000);
                    animation->setStartValue(QRect(winLable->x(),winLable->y(),winLable->width(),winLable->height()));
                    animation->setEndValue(QRect(winLable->x(),winLable->y()+180,winLable->width(),winLable->height()));
                    animation->setEasingCurve(QEasingCurve::OutBounce);
                    animation->start();
              }


            });
        }
    }
}
void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
    //pix.scaled(pix.width()*0.1,pix.height()*0.1);
    painter.drawPixmap(0,0,pix);

}
void PlayScene::sleep(unsigned int msec)
{
    QTime reachTime=QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime()<reachTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}
