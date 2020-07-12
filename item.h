#ifndef ITEM_H
#define ITEM_H

#include <QWidget>

class Item : public QWidget
{
    Q_OBJECT
private:
    int x,y;//该物体的坐标
    int height,width;//物体的尺寸，用来判断是否体积碰撞从而是否抓取
    int price;//物体的价值
    int kind;//0表示普通物质，1为加速，2为减速
    double speed;//抓取物体后的速度
    bool visible;//物体是否可见
public:
    Item(){//构造函数
        visible=true;
    }
    //设置中心位置
    void set_position(const int &xx,const int &yy);
    //设置尺寸
    void set_size(const int &wwidth,const int &hheight);
    //设置价格
    void set_price(const int &pprice);
    //设置抓取后速度
    void set_speed(const double &sspeed);
    //设置抓取物体种类
    void set_kind(const int &kkind);
    //设置为可见
    void set_visible();
    //设置为不可见
    void set_invisible();
    //初始化函数
    void init();
    //碰撞检测
    bool detection(const int &xx,const int &yy);
    int get_kind(){return kind;}//获取种类
    int get_price(){return price;}//获取价格
    int get_x(){return x;}//获取X坐标
    int get_y(){return y;}//获取y坐标
    double get_speed(){return speed;}//获取抓取后速度
    bool is_visible(){return visible;}//获取是否可见
};


#endif // ITEM_H
