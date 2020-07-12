#include "mianer.h"

mianer::mianer(QWidget *parent) : QWidget(parent)
{

}
//关于各项数值的更改
void mianer::change_angle(const int &aangle)
{
    angle+=aangle;
}
void mianer::change_length(const double &llength)
{
    length+=llength;
}
void mianer::change_rlength(const double &rrlength)
{
    rlength+=rrlength;
}
void mianer::change_sum(const double &ssum)
{
    sum+=ssum;
}
//关于各项数值的设置
void mianer::set_speed(const double &sspeed)
{
    speed=sspeed;
}
void mianer::set_length(const double &llength)
{
    length=llength;
}
void mianer::set_rlength(const double &rrlength)
{
    rlength=rrlength;
}

//关于各布尔值的设置
void mianer::set_is_rotating(bool c)
{
    is_rotating=c;
}
void mianer::set_is_grab(bool c)
{
    is_grab=c;
}
void mianer::set_stopped(bool c)
{
    stopped=c;
}

//初始化
void  mianer::init()
{
    angle=0;//起始旋转角度为0
    speed=4;//钩子初始速度为2
    length=0;
    rlength=0;
    sum=0;

    is_rotating=true;//判断是否正在进行旋转
    is_grab=false;//当前没有抓取任何物体
    stopped=false;
    fflag=true;
}
