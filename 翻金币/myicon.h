#ifndef MYICON_H
#define MYICON_H
#include <QTimer>
#include <QPushButton>

class MyIcon : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyIcon(QWidget *parent = 0);
    MyIcon(QString btnImg);
    int posX;
    int posY;
    bool flag;
    void changeFlag();
    QTimer *time1;
    QTimer *time2;
    int min=1;
    int max=8;
    bool isAnimation=false;
    void mousePressEvent(QMouseEvent *e);
    bool isWin=false;

signals:

public slots:

};

#endif // MYICON_H
