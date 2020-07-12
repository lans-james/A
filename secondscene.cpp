#include "secondscene.h"
#include"QMenuBar"
#include"QPainter"
#include"mybutton.h"
#include"QTimer"
#include"QLabel"
#include"QFont"
#include"QDebug"
#include<QMediaPlayer>
#include<QMediaPlaylist>
secondscene::secondscene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(1700,1000);
    this->setWindowIcon(QPixmap(":/rec/图标.jpg"));
    this->setWindowTitle("");
    //创建菜单
    QMenuBar *bar=this->menuBar();
    this->setMenuBar(bar);
    QMenu *startMenu=bar->addMenu("开始");
    QAction *quit=startMenu->addAction("退出");
    quit->setIcon(QIcon(":/rec/1.ico"));
    connect(quit,&QAction::triggered,[=](){
        this->close();});

    //鼠标样式
    QPixmap pixmap(":/rec/pic/ccc.png");//自定义指针
    QCursor cursor= QCursor(pixmap,-1,-1);
    setCursor(cursor);

    //返回按钮
    mybutton *closebtn=new mybutton(":/rec/pic/reset.png");
    closebtn->setParent(this);
    closebtn->move(this->width()-closebtn->width()-10,30);
    connect(closebtn,&mybutton::clicked,[=](){
        closebtn-> zoom1();
        closebtn-> zoom2();
        QTimer::singleShot(500,this,[=](){
            this->hide();
            //告诉主场景
            emit this->gameSceneBack();
        });
    });
    //创建关卡选择按钮
    for(int i=0;i<10;i++){

        mybutton *menubtn=new mybutton(":/rec/pic/LevelIcon.png");

        menubtn->setParent(this);
        menubtn->move(i%5*300+155,i/5*250+400);

        //创建接口
        connect(menubtn,&mybutton::clicked,[=](){
            QMediaPlayer *player9=new QMediaPlayer;
               player9->setMedia(QUrl("qrc:/rec/bgm/voice2.mp3"));
               player9->setVolume(80);
            player9->play();
            QString str=QString("您选择的是第%1关").arg(i+1);
            qDebug()<<str;
            //进入到游戏场景
            menubtn-> zoom1();
            menubtn-> zoom2();
            QTimer::singleShot(2000,this,[=](){
                this->hide();
                play=new Playscene(i+1);
                play->show();//显示游戏场景
                play->resume();
                //监听关卡的选择按钮信号
                connect(play,&Playscene::gameSceneBack,[=](){
                    this->show();
                    delete play;
                    play=NULL;
                });
            });
        });
        //设置按钮上的字
        QLabel *label=new QLabel;
        label->setParent(this);
        label->setFixedSize(menubtn->width(),menubtn->height());
        label->setText(QString::number(i+1));
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        label->move(i%5*300+155,i/5*250+380);
        label->setAttribute(Qt::WA_TransparentForMouseEvents,true);
        //字体
        QFont font("Microsoft YaHei",20,75);
        QPalette pa;
        pa.setColor(QPalette::WindowText,Qt::yellow);
        label->setFont(font);
        label->setPalette(pa);
    }
}
void secondscene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap map;
    map.load(":/rec/pic/second.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),map);
}
