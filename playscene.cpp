#include "playscene.h"
#include "ui_playscene.h"
#include"QDebug"
#include"mybutton.h"
#include"QLabel"
#include"QPainter"
#include"QTimer"
#include"QPushButton"
#include<math.h>
#include<stdlib.h>
#include"QPen"
#include<QKeyEvent>
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include <QThread>

Playscene::Playscene(int level ):
    ui(new Ui::Playscene)
{
    ui->setupUi(this);
    QString str=QString("进入了第%1关").arg(level);
    qDebug()<<str;
    this->levelIndex=level;
    this->setFixedSize(1700,1000);
    this->setWindowIcon(QPixmap(":/rec/图标.jpg"));
    this->setWindowTitle("游戏界面");

    connect(ui->actionexit,&QAction::triggered,[=](){
        this->close();
    });
    //鼠标样式
    QPixmap pixmap(":/rec/pic/ccc.png");//自定义指针
    QCursor cursor= QCursor(pixmap,-1,-1);
    setCursor(cursor);

    ui->actionexit->setIcon(QIcon(":/rec/1.ico"));
    //返回按钮
    mybutton *closebtn=new mybutton(":/rec/pic/reset.png");
    closebtn->setParent(this);
    closebtn->move(this->width()-closebtn->width()-10,30);
    connect(closebtn,&mybutton::clicked,[=](){
        player->pause();
        qDebug()<<"返回了";
        closebtn-> zoom1();
        closebtn-> zoom2();
        QTimer::singleShot(500,this,[=](){
            this->hide();
            //告诉主场景
            emit this->gameSceneBack();
        });
    });
    //显示当前关卡
    QLabel *label=new QLabel;
    label->setParent(this);

    label->move(30,this->height()-55);
    label->setFixedSize(300,40);
    QFont font;
    font.setPointSize(20);
    font.setFamily("华文新魏");
    label->setFont(font);
    QString str1=QString("Level:%1").arg(this->levelIndex);
    label->setText(str1);

    if(levelIndex<=3)
    {
        interval_angle=18;
    }
    else if(levelIndex>3&&levelIndex<=6)
        interval_angle=15;
    else if (levelIndex>6&&levelIndex<=9)
        interval_angle=21-levelIndex;
    else
        interval_angle=9;
    interval_miner=200;
    miner=new mianer;
    map=new Map;
    pix.load(":/rec/pic/hook1.png");//设置钩子，60*50

    timer_angle.setInterval(interval_angle);//设置触发间隔为15ms
    connect(&timer_angle,&QTimer::timeout,this,&Playscene::rotate);//链接
    connect(&timer_angle,&QTimer::timeout,this,&Playscene::ss);

    timer_s.setInterval(interval_miner);//s控制矿工的运动
    connect(&timer_s,&QTimer::timeout,this,&Playscene::mm);

    timer_clock.setInterval(1000);
    connect(&timer_clock,&QTimer::timeout,this,&Playscene::timereduce);

    rad=180/3.1415926;//弧度
    angle_change=1;//角度转变量为1°

    lable[0]=ui->label_1;
    lable[1]=ui->label_2;
    lable[2]=ui->label_3;
    lable[3]=ui->label_4;
    lable[4]=ui->label_5;
    lable[5]=ui->label_6;
    lable[6]=ui->label_7;
    lable[7]=ui->label_8;
    lable[8]=ui->label_9;
    lable[9]=ui->label_10;
    lable[10]=ui->label_11;
    lable[11]=ui->label_12;
    lable[12]=ui->label_13;
    lable[13]=ui->label_14;
    lable[14]=ui->label_15;//随机物品
    init();
    do_stop();
    ui->label_pause->setVisible(true);//暂停图案
    ui->toolButton_ppause->setVisible(true);

}

void Playscene::init()//初始化 加载一些内容
{

    playlist->addMedia(QUrl("qrc:/rec/bgm/sound.mp3"));
    playlist->addMedia(QUrl("qrc:/rec/bgm/sound.mp3"));
    player->setPlaylist(playlist);
    player->setVolume(10);
    player->play();
    //加载音乐

        player1->setMedia(QUrl("qrc:/rec/bgm/ss.mp3"));
        player1->setVolume(180);
    //加载音效
    
    player2->setMedia(QUrl("qrc:/rec/bgm/get.mp3"));
    player2->setVolume(100);
    //加载音效
    
    player3->setMedia(QUrl("qrc:/rec/bgm/special.mp3"));
    player3->setVolume(100);
    //加载音效
    
    player4->setMedia(QUrl("qrc:/rec/bgm/money.mp3"));
    player4->setVolume(50);
    //加载音效
    
    player5->setMedia(QUrl("qrc:/rec/bgm/voice.mp3"));
    player5->setVolume(50);
    //加载音效


    ui->label_pause->setVisible(false);//暂停图案
    ui->toolButton_ppause->setVisible(false);
    ui->label_finish->setVisible(false);//结束图案
    ui->toolButton_reset->setVisible(false);
    ui->toolButton_cancel->setVisible(false);
    ui->toolButton_restart->setVisible(false);//重新开始图案
    ui->toolButton_restart->move(this->width()*0.5,this->height()*0.85);
    ui->toolButton_restart->setVisible(false);
    ui->label_final->setVisible(false);
    ui->lcdNumber_speed->setVisible(false);
    miner->init();//矿工初始化设置 实体类函数调用
    map->init();//地图初始化设置  实体类函数调用

    if(levelIndex<=3)
    {
        time_left=120-(levelIndex-1)*10;
    }
    else if(levelIndex>3&&levelIndex<=6)
    {
        time_left=100-(levelIndex-4)*10;
    }
    else if (levelIndex>6&&levelIndex<=9){
        time_left=80-(levelIndex-7)*5;
    }
    else
    {time_left=60;
   }
    for(int i=0;i<7;i++)
    {
        lable[i]->setVisible(true);
        lable[i]->move(map->get_point(i));
        if(i<2||i==6)
            lable[i]->resize(140,120);
        else
            lable[i]->resize(60,50);
    }
    for(int i=6;i<15;i++)//让随机矿石不可见
        lable[i]->setVisible(false);
    time=time_up=time_down=0;
    k=1;

    ui->toolButton->setStyleSheet("#toolButton{border-image:url(:/rec/pic/1.png);}");//设置矿工

    ui->lcdNumber->display(time_left);//显示剩余时间
    ui->lcdNumber_sum->display(miner->get_sum());//显示当前分数
    timer_angle.start();//计时器启动
    timer_clock.start();
    timer_s.start();
}
void Playscene::paintEvent(QPaintEvent *)//画线操作
{    QPainter painter(this);
     QPixmap pix2;
      pix2.load(":/rec/pic/background.jpg");
       painter.drawPixmap(0,0,this->width(),this->height(),pix2);

        painter.translate(850,150); //让图片的中心作为旋转的中心
         painter.rotate(miner->get_angle()); //顺时针旋转90度
          painter.translate(-850,-150); //使原点复原

           int length=miner->get_length();
            if(miner->isrotating()==false||miner->isstopped())
            {
                painter.drawPixmap(850-pix.width()*0.5,180+length,pix);//绘图的起点
                QPen pen;
                pen.setWidth(5);
                painter.setPen(pen);
                painter.setRenderHint(QPainter::Antialiasing, true);
                painter.drawLine(QPoint(850,140),QPoint(850,180+length));
                //qDebug()<<"划线了y";
            }
            else
            { QPen pen;
                pen.setWidth(5);
                painter.setPen(pen);
                painter.setRenderHint(QPainter::Antialiasing, true);
                painter.drawLine(QPoint(850,140),QPoint(850,180));
                painter.drawPixmap(850-pix.width()*0.5,180,pix);//绘图的起点
            }
             update();//强制程序重新绘制界面
}
void Playscene::keyPressEvent(QKeyEvent *e)//键盘事件操作
{
    int key=e->key();
    if (!miner->isstopped()&&key == Qt::Key_Down) // 按向下方向键时
    {
        if(miner->isrotating())//如果正在旋转
        {
            qDebug()<<"按下了下方向键";
            //停止旋转，进行下拉操作
            miner->set_is_rotating(false);
            ss();
        }
    }
    if(key == Qt::Key_Space)//空格键 暂停功能
    {
        if(miner->isstopped()&&time_left>0)
            resume();
        else{
            do_stop();
        }
    }
    if(key == Qt::Key_Up&&!miner->isgrab()){//方向键↑ 收钩
       player1->play();
        if(miner->get_length()>0&&miner->get_speed()>0){
            miner->set_speed(-1*(miner->get_speed()));
        }
    }
}
bool Playscene::detection()//碰撞和越界检测
{
    //定义临时变量angle和length
    int angle=miner->get_angle();
    int length=miner->get_length();

    if(fabs(angle)>45){
        if(length>(850/(sin(fabs(angle/rad)))))
            return true;
    }
    else if(length>(840/(cos(angle/rad))))
        return true;
    if(map->detection(850-length*sin(angle/rad),141+length*cos(angle/rad)))//如果map.碰撞检测返回为真
    {
        miner->set_is_grab(true);
        return true;
    }
  return false;
}
void Playscene::do_stop()
{
    player->pause();
    if(time_left>0){
        ui->label_pause->setVisible(true);//暂停图案
        ui->toolButton_restart->setVisible(true);
        ui->toolButton_ppause->setVisible(false);
    }
    miner->set_is_rotating(!(miner->isrotating()));
    timer_clock.stop();
    timer_angle.stop();
    timer_s.stop();

    miner->set_stopped(true);
}
void Playscene::resume()
{
    player->play();
    ui->label_pause->setVisible(false);//暂停图案
    ui->toolButton_restart->setVisible(false);
    ui->toolButton_ppause->setVisible(true);
    miner->set_is_rotating(!(miner->isrotating()));
    timer_clock.start();
    timer_angle.start();
    timer_s.start();
    miner->set_stopped(false);
}

void Playscene::timereduce()//计时器
{
    if(time_left>=0)
    {
        time++;
        ui->lcdNumber->display(time_left--);
        if(time_down==0&&time_up==0)
        {
            k=1;
            timer_s.setInterval(interval_miner);
            timer_angle.setInterval(interval_angle);
            ui->lcdNumber_speed->setVisible(false);
        }
        if(time_down)
        {
            k=1;
            --time_down;
            ui->lcdNumber_speed->setVisible(true);
            ui->lcdNumber_speed->display(time_down);
        }
        if(time_up)
        {
            --time_up;
            k=3;
            ui->lcdNumber_speed->setVisible(true);
            ui->lcdNumber_speed->display(time_up);
        }
        if(time%8==0)//每8秒，随机生成矿石一次
        {
            map->rrand(levelIndex);
            for(int i=6;i<15;i++)
                if(map->is_visible(i))//如果该物体可见
                {
                    lable[i]->setVisible(true);
                    lable[i]->move(map->get_point(i));

                }
        }

   }

    if(time_left<0)//剩余时间为0，则停止游戏
    {
        do_stop();
        for(int m=0;m<15;m++){
            lable[m]->setVisible(false);
        }
        player->stop();
        ui->label_finish->setVisible(true);

        ui->toolButton_reset->setVisible(true);
        ui->label_final->setVisible(true);

        if(levelIndex<=3)
        {if(miner->get_sum()<=4000)
               { QMediaPlayer *player7=new QMediaPlayer;
               player7->setMedia(QUrl("qrc:/rec/bgm/fail.mp3"));
               player7->setVolume(80);
               player7->play();
           }
        else if(miner->get_sum()>4000)
        {  QMediaPlayer *player6=new QMediaPlayer;
                player6->setMedia(QUrl("qrc:/rec/bgm/succeed.mp3"));
                player6->setVolume(80);
            player6->play();}}
         else if(levelIndex>3&&levelIndex<=6)
        {if(miner->get_sum()<=3500)
               { QMediaPlayer *player7=new QMediaPlayer;
               player7->setMedia(QUrl("qrc:/rec/bgm/fail.mp3"));
               player7->setVolume(80);
                   player7->play();
          }
        else if(miner->get_sum()>3500)
        {  QMediaPlayer *player6=new QMediaPlayer;
                player6->setMedia(QUrl("qrc:/rec/bgm/succeed.mp3"));
                player6->setVolume(80);
            player6->play();}}
        else if(levelIndex>6&&levelIndex<=10)
       {if(miner->get_sum()<=2500)
             {   QMediaPlayer *player7=new QMediaPlayer;
               player7->setMedia(QUrl("qrc:/rec/bgm/fail.mp3"));
               player7->setVolume(80);
                player7->play();}

       else if(miner->get_sum()>2500)
       {  QMediaPlayer *player6=new QMediaPlayer;
                player6->setMedia(QUrl("qrc:/rec/bgm/succeed.mp3"));
                player6->setVolume(80);
            player6->play();}}

        QString s = QString::number(miner->get_sum(), 10);
        ui->label_final->setText(s);
        QFont font("Microsoft YaHei",55,75);
        ui->label_final->setFont(font);        
        ui->toolButton_cancel->setVisible(true);
    }
}
void Playscene::rotate()//控制旋转
{
    if(miner->isrotating())//旋转时
    {
        miner->change_angle(angle_change);
        int angle=miner->get_angle();
        if(angle>=90||angle<=-90)
            angle_change*=-1;
    }
    update();
}
void Playscene::mm()//矿工动作设置
{
    if(!miner->isrotating())
    {
        if(miner->isfflag())//矿工的动作设置
            ui->toolButton->setStyleSheet("#toolButton{border-image:url(:/rec/pic/2.png);}");
        else
            ui->toolButton->setStyleSheet("#toolButton{border-image:url(:/rec/pic/3.png);}");
    }

}

void Playscene::ss()//伸展操作
{player1->play();
    if(!miner->isrotating())
    {
        if(miner->isgrab())//物体的移动
        {

            miner->change_rlength(k*fabs(miner->get_speed()));
            int rlength=miner->get_rlength();
            int angle=miner->get_angle();
            QPoint p=map->get_point(map->get_cur_item());//获取当前物体的坐标
            QPoint temp(rlength*sin(angle/rad),-rlength*cos(angle/rad));//temp为位移大小
            lable[map->get_cur_item()]->move((p+temp));
        }
        if(miner->isgrab()||detection())//如果已经抓到物体了或碰撞检测返回为true
        {
            if(miner->isgrab())
            {
                player2->play();//抓住物体后音效
                miner->set_speed(map->get_cur_speed());
            }
            else
            {
                miner->set_speed(-1*(miner->get_speed()));//速度相反，往反向拉
            }
        }

        miner->change_length(k*miner->get_speed());
        if(miner->get_length()<=0)//如果钩子回到了起点
        {
            if(miner->isgrab())//如果抓到了东西
            {
                player4->play();
                map->invisible();//令当前物体不可见
                lable[map->get_cur_item()]->setVisible(false);//令当前物体不可见
                miner->change_sum(map->get_cur_price());
                miner->set_rlength(0);
                miner->set_is_grab(false);
                if(map->get_cur_kind())//如果抓到了特殊物品
                {
                    player3->play();
                    int kind=map->get_cur_kind();
                    if(kind==1)
                    {
                        time_up=10;
                        time_down=0;//不能叠加，所以把另一个的时间归零
                        timer_s.setInterval(30);
                        k=2;
                    }else if(kind==2)
                    {
                        time_down=10;
                        time_up=0;//不能叠加，所以把另一个的时间归零
                        timer_s.setInterval(interval_miner*2);
                        timer_angle.setInterval(interval_angle*2);
                        k=1;
                    }
                    else if(kind==3){
                        time_left+=15;
                    }
                    else {
                        time_up+=10;
                        time_down=0;//不能叠加，所以把另一个时间归零
                        timer_s.setInterval(30);
                        k=3;
                        miner->change_sum(map->get_cur_price());
                    }
                }
            }
            miner->set_is_rotating(true);
            miner->set_speed(4);
        }
    }
    ui->lcdNumber_sum->display(miner->get_sum());
    update();
}
void Playscene::on_toolButton_reset_clicked()//重新开始
{
    player5->play();
    QTimer::singleShot(300,this,[=](){
        this->hide();
        //告诉主场景
        emit this->gameSceneBack();
    });
}

void Playscene::on_toolButton_restart_clicked()//继续游戏
{

    QTimer::singleShot(300,this,[=](){
        resume();
    });

}


void Playscene::on_toolButton_ppause_clicked()
{
    QTimer::singleShot(300,this,[=](){
        do_stop();
    });

}
void Playscene::on_toolButton_cancel_clicked()//退出游戏
{
    player5->play();
    QTimer::singleShot(300,this,[=](){
        qApp->quit();
        ui->label_finish->setVisible(false);
        ui->toolButton_cancel->setVisible(false);
        ui->toolButton_restart->setVisible(false);
    });

}


Playscene::~Playscene()
{

    delete ui;
}
