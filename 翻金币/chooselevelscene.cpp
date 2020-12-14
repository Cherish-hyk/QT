#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QLabel>
#include <QTime>
#include <QTimer>
#include <QCoreApplication>
#include <QSound>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) :
    QMainWindow(parent)
{
    this->setFixedSize(350,588);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("选择关卡");
    QMenuBar*bar=menuBar();
    setMenuBar(bar);
    QMenu *startMenu=bar->addMenu("开始");
    QAction *quitAction=startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
       this->close();
    });
    QSound*chooseSound=new QSound(":/res/TapButtonSound.wav");
    QSound*backSound=new QSound(":/res/BackButtonSound.wav");
    MyPushButton*backbar=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backbar->setParent(this);
    backbar->move(this->width()-backbar->width(),this->height()-backbar->height());
    connect(backbar,&MyPushButton::clicked,[=](){
        backSound->play();
      emit this->chooseSceneBack();
    });
    for(int i=0;i<20;i++)
    {
        MyPushButton*menuBtn=new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(35+i%4*70,130+i/4*70);
        connect(menuBtn,&MyPushButton::clicked,[=](){
        chooseSound->play();
        sleep(200);
        this->hide();
        play=new PlayScene(i+1);
        play->setGeometry(this->geometry());
        play->show();
        connect(play,&PlayScene::playChooseSceneBack,this,[=](){
            this->setGeometry(play->geometry());
            sleep(300);
            this->show();
            delete play;
            play=NULL;
          });
        });
        QLabel*label=new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(35+i%4*70,130+i/4*70);
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}
void  ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
  //  pix.scaled(pix.width()*0.1,pix.height()*0.1);
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix);
}
void ChooseLevelScene::sleep(unsigned int msec)
{
    QTime reachTime=QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime()<reachTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}

