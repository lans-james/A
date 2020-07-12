#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include<QtGui>
#include<QLabel>
#include<QTimer>
#include<QKeyEvent>
#include<item.h>
#include<mianer.h>
#include<map.h>
#include<QMediaPlayer>
#include<QMediaPlaylist>

#include <QThread>
namespace Ui {
class Playscene;
}

class Playscene : public QMainWindow
{
    Q_OBJECT

public:
//   explicit Playscene(QWidget *parent = 0);
  explicit Playscene(int level);
 int levelIndex;//记录所选关卡
      void keyPressEvent(QKeyEvent *);//键盘按压事件

      //重写事件
      void paintEvent(QPaintEvent *event);
      bool detection();//碰撞检测， 判断是否碰到物体
      void do_stop();//暂停
      void resume();//暂停后开始
      void init();//初始化

    ~Playscene();

private slots:
    void timereduce();//倒计时
    void rotate();//旋转
    void ss();//绳子伸展操作
    void mm();//随机生成石头的事件


    void on_toolButton_reset_clicked();
    void on_toolButton_ppause_clicked();

    void on_toolButton_restart_clicked();

    void on_toolButton_cancel_clicked();
    //上面全部为 按钮点击事件
  signals:
      void gameSceneBack();

private:
    Ui::Playscene *ui;
    //使用Ui::MainWindow定义一个指针，这个指针是用前面声明的namespace Ui里面的MainWindow类定义的，所以指针ui是一个指向Ui域中MainWindow的指针，后面需要访问界面上的组件，都需要通过这个指针ui
    QPixmap pix;//绘画
    QImage background,hook;//图片

    int interval_angle;
    int time_left;
    bool AmazingCrazy=false;

    int cur_item;
    double rad;//表示1弧度=多少度
    int angle_change;
    int k;//表示倍数

    mianer *miner;//类的指针
    Map *map;//类的指针

    //计时器
    QTimer timer_angle,timer_clock,timer_s;
    //int interval_angle;
    int interval_miner;
    //int time_left;
    int time;//表示已经进行了多久，每10秒随机产生一次矿石
    int time_up,time_down;//表示加速和减速的持续时间

    QLabel *lable[15];//前2个为大金矿，后4个为小金矿,6-9为随机产生的石头（可重复产生）
    //Item *item[10];
QMediaPlaylist *playlist=new QMediaPlaylist;
    QMediaPlayer *player =new QMediaPlayer;
    QMediaPlayer *player1=new QMediaPlayer;
    QMediaPlayer *player2=new QMediaPlayer;
    QMediaPlayer *player3=new QMediaPlayer;
    QMediaPlayer *player4=new QMediaPlayer;
    QMediaPlayer *player5=new QMediaPlayer;

    //新建 媒体控制对象
;
};

#endif // PLAYSCENE_H
