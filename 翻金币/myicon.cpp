#include "myicon.h"
#include <QDebug>
#include <QTimer>
//MyIcon::MyIcon(QWidget *parent) :
//    QPushButton(parent)
//{
//}
MyIcon::MyIcon(QString btnImg)
{
    QPixmap pix;
    bool ret=pix.load(btnImg);
    if(!ret)
    {
       qDebug()<<"图片加载失败";
       return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px};");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    time1=new QTimer(this);
    time2=new QTimer(this);
    connect(time1,&QTimer::timeout,[=](){
       QPixmap pix;
       QString str=QString(":/res/Coin000%1.png").arg(this->min++);
       pix.load(str);
       this->setFixedSize(pix.width(),pix.height());
       this->setStyleSheet("QPushButton{border:0px};");
       this->setIcon(pix);
       this->setIconSize(QSize(pix.width(),pix.height()));
       if(this->min>this->max)
       {
           this->min=1;
           isAnimation=false;
           time1->stop();
       }
    });
    connect(time2,&QTimer::timeout,[=](){
       QPixmap pix;
       QString str=QString(":/res/Coin000%1.png").arg(this->max--);
       pix.load(str);
       this->setFixedSize(pix.width(),pix.height());
       this->setStyleSheet("QPushButton{border:0px};");
       this->setIcon(pix);
       this->setIconSize(QSize(pix.width(),pix.height()));
       if(this->max<this->min)
       {
           this->max=8;
           isAnimation=false;
           time2->stop();
       }
    });
}

void MyIcon::changeFlag()
{
    if(this->flag)
    {
        time1->start(30);
        isAnimation=true;
        this->flag=false;
    }
    else
    {
        time2->start(30);
         isAnimation=true;
        this->flag=true;
    }
}
void MyIcon::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation||this->isWin)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}
