#ifndef SECONDSCENE_H
#define SECONDSCENE_H

#include <QMainWindow>
#include"playscene.h"
class secondscene : public QMainWindow
{
    Q_OBJECT
public:
    explicit secondscene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    //声明游戏场景对象
    Playscene *play=NULL;


signals:

    //写一个自定义信号，告诉主场景返回
    void gameSceneBack();
public slots:
};

#endif // SECONDSCENE_H
