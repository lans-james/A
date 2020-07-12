#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include"secondscene.h"
namespace Ui {
class MainScene;
}

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScene(QWidget *parent = 0);
    ~MainScene();
    void paintEvent(QPaintEvent *event);
    secondscene *gamescene=new secondscene;


private:
    Ui::MainScene *ui;
};

#endif // MAINSCENE_H
