#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QSound>
MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);
    setFixedSize(350,588);
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    setWindowTitle("翻金币");
    connect(ui->actionExit,&QAction::triggered,[=](){
        this->close();
    });
    QSound*startSound=new QSound(":/res/TapButtonSound.wav");
    MyPushButton*startBtn=new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);
    chooseScene=new ChooseLevelScene;
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,this,[=](){
       this->setGeometry(chooseScene->geometry());
        sleep(300);
       chooseScene->hide();
       this->show();
    });
    connect(startBtn,&MyPushButton::clicked,[=](){
        startSound->play();
     startBtn->zoom1();
     startBtn->zoom2();
     //QTimer::singleShot(500,this);
     sleep(300);
     chooseScene->setGeometry(this->geometry());
     this->hide();

     chooseScene->show();


    });
}
void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
    //pix.scaled(pix.width()*0.1,pix.height()*0.1);
    painter.drawPixmap(0,0,pix);

}
void MainScene::sleep(unsigned int msec)
{
    QTime reachTime=QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime()<reachTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}
MainScene::~MainScene()
{
    delete ui;
}
