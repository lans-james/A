#include "mybutton.h"
#include<QDebug>
#include"QPropertyAnimation"
mybutton::mybutton(QString path){
    mgpath=path;
    QPixmap pixmap;
    bool ret=pixmap.load(mgpath);
    if(!ret){
        qDebug()<<"图片加载错误";
    }
    //设置图片大小
    this->setFixedSize(pixmap.width(),pixmap.height());
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pixmap);
    //设置图标大小
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
}
void mybutton::zoom1(){
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    //设置时间间隔
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}
//向下弹跳
void mybutton::zoom2(){
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    //设置时间间隔
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}
