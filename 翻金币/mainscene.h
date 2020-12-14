#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include "chooselevelscene.h"
#include <QTime>
namespace Ui {
class MainScene;
}

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScene(QWidget *parent = 0);
    ~MainScene();
    void paintEvent(QPaintEvent *);
    ChooseLevelScene*chooseScene=NULL;
    void sleep(unsigned int msec);
private:
    Ui::MainScene *ui;
};

#endif // MAINSCENE_H
