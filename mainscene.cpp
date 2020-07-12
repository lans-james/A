#include "mainscene.h"
#include "ui_mainscene.h"
#include"QPainter"
#include"mybutton.h"
#include"QTimer"
#include"QLabel"
#include"QPropertyAnimation"
#include"QDebug"
#include"QDialog"
#include"QPushButton"
#include<QMediaPlayer>
#include<QMediaPlaylist>//多媒体模块下的音效
MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);
    this->setFixedSize(1700,1000);
    this->setWindowIcon(QPixmap(":/rec/图标.jpg"));
    this->setWindowTitle("黄金矿工");
    connect(ui->actionexit,&QAction::triggered,[=](){
        this->close();
    });
    ui->actionexit->setIcon(QIcon(":/rec/1.ico"));
    //鼠标样式
    QPixmap pixmap(":/rec/pic/ccc.png");//自定义指针
    QCursor cursor= QCursor(pixmap,-1,-1);
    setCursor(cursor);

    //准备开始音效

    //创建按钮
    mybutton *start=new mybutton(":/rec/pic/start2.png");
    mybutton *introduction=new mybutton(":/rec/pic/introduction2.png");
    mybutton *about=new mybutton(":/rec/pic/about2.png");
    mybutton *exit=new mybutton(":/rec/pic/quit2.png");
    start->setParent(this);
    introduction->setParent(this);
    about->setParent(this);
    exit->setParent(this);
    start->move(50,this->height()-introduction->height()-60-start->height());
    introduction->move(introduction->width() +40,this->height()-exit->height()-about->height()-60);
    about->move(50,this->height()-introduction->height()-30);
    exit->move(introduction->width() +40,this->height()-exit->height()-30);
    //监听选择关卡的选择按钮信号
    connect(gamescene,&secondscene::gameSceneBack,[=](){
        gamescene->hide();
        this->show();
    });//特效
    //开始按钮
    connect(start,&mybutton::clicked,[=](){
        //播放开始音效
        QMediaPlayer *player8=new QMediaPlayer;
         player8->setMedia(QUrl("qrc:/rec/bgm/voice1.mp3"));
         player8->setVolume(80);
        player8->play();
        qDebug()<<"播放";
        //弹跳
        start-> zoom1();
        start-> zoom2();
        //延时进入选择关卡场景
        QTimer::singleShot(1000,this,[=](){
            //自身隐藏
            this->hide();
            //进入到选择关卡的场景
            gamescene->show();

        });
    });
    //创建返回按钮
    mybutton *closebtn=new mybutton(":/rec/pic/reset.png");
    closebtn->setParent(this);
    closebtn->move(this->width()-closebtn->width()-10,30);
    //introduction按钮设置
    connect(introduction,&mybutton::clicked,[=](){
        QMediaPlayer *player8=new QMediaPlayer;
         player8->setMedia(QUrl("qrc:/rec/bgm/voice1.mp3"));
         player8->setVolume(80);
        player8->play();
        introduction-> zoom1();
        introduction-> zoom2();
        QTimer::singleShot(500,this,[=](){
            QPixmap map1;
            map1.load(":/rec/pic/capture_20200705090320661.bmp");
            ui->intro->setGeometry(0,0,map1.width(),map1.height());
            ui->intro->setPixmap(map1);
            ui->intro->setParent(this);
            ui->intro->move(this->width()*0.5-map1.width()*0.5,-map1.height()*0.5);

            QPropertyAnimation * animation1 =  new QPropertyAnimation(ui->intro,"geometry");
            animation1->setDuration(1000);
            animation1->setStartValue(QRect(ui->intro->x(),ui->intro->y(),ui->intro->width(),ui->intro->height()));
            animation1->setEndValue(QRect(ui->intro->x(),ui->intro->y()+500,ui->intro->width(),ui->intro->height()));
            animation1->setEasingCurve(QEasingCurve::OutBounce);
            animation1->start();
            ui->intro->show();
            connect(closebtn,&mybutton::clicked,[=](){
                closebtn-> zoom1();
                closebtn-> zoom2();
                if(closebtn->y()>30){
                    closebtn->move(this->width()-closebtn->width()-10,30);
                }
                QTimer::singleShot(500,this,[=](){
                    ui->intro->close();
                });

            });
        });});

    //about按钮设置
    connect(about,&mybutton::clicked,[=](){
        QMediaPlayer *player8=new QMediaPlayer;
         player8->setMedia(QUrl("qrc:/rec/bgm/voice1.mp3"));
         player8->setVolume(80);
        player8->play();
        about-> zoom1();
        about-> zoom2();
        QTimer::singleShot(500,this,[=](){
            QPixmap map2;
            map2.load(":/rec/pic/about3");
            ui->intro1->setGeometry(0,0,map2.width(),map2.height());
            ui->intro1->setPixmap(map2);
            ui->intro1->setParent(this);
            ui->intro1->move(this->width()*0.5-map2.width()*0.5,-map2.height()*0.5);
            QPropertyAnimation * animation1 =  new QPropertyAnimation(ui->intro1,"geometry");
            animation1->setDuration(1000);
            animation1->setStartValue(QRect(ui->intro1->x(),ui->intro1->y(),ui->intro1->width(),ui->intro1->height()));
            animation1->setEndValue(QRect(ui->intro1->x(),ui->intro1->y()+500,ui->intro1->width(),ui->intro1->height()));
            animation1->setEasingCurve(QEasingCurve::OutBounce);
            animation1->start();
            ui->intro1->show();
            connect(closebtn,&mybutton::clicked,[=](){
                closebtn-> zoom1();
                closebtn-> zoom2();
                if(closebtn->y()>30){
                    closebtn->move(this->width()-closebtn->width()-10,30);
                }
                QTimer::singleShot(500,this,[=](){
                    ui->intro1->close();
                });
            });
        });});

    //exit按钮设置
    connect(exit,&mybutton::clicked,[=](){
        QMediaPlayer *player8=new QMediaPlayer;
         player8->setMedia(QUrl("qrc:/rec/bgm/voice1.mp3"));
         player8->setVolume(80);
        player8->play();
        exit-> zoom1();
        exit-> zoom2();
        QTimer::singleShot(500,this,[=](){
            this->close();
        });
    });

}


MainScene::~MainScene()
{
    delete ui;
}
//绘制背景
void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap map;
    map.load(":/rec/pic/开始界面.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),map);
}
