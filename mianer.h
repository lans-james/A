#ifndef MIANER_H
#define MIANER_H

#include <QWidget>

class mianer : public QWidget//矿工类 （钩子）
{
    Q_OBJECT
private:
    int angle;//角度
    double speed;//速度
    double length;
    double rlength;
    int sum;//得分

    bool is_rotating;
    bool is_grab;
    bool stopped;
    bool fflag;

public:
    explicit mianer(QWidget *parent = nullptr);

    //关于各项数值的更改
    void change_angle(const int &aangle);
    void change_length(const double &llength);
    void change_rlength(const double &rrlength);
    void change_sum(const double &ssum);

    //关于各项数值的设置
    void set_length(const double &llength);
    void set_rlength(const double &rrlength);
    void set_speed(const double &sspeed);

    //关于各布尔值的设置
    void set_is_rotating(bool c);
    void set_is_grab(bool c);
    void set_stopped(bool c);

    //get数值以及布尔值
    double get_speed(){return speed;}
    int get_angle(){return angle;}
    double get_length(){return length;}
    double get_rlength(){return rlength;}
    int get_sum(){return sum;}

    bool isrotating(){return is_rotating;}
    bool isgrab(){return is_grab;}
    bool isstopped(){return stopped;}
    bool isfflag()
    {
        fflag=!fflag;
        return fflag;
    }
    //初始化
    void init();


};





#endif // MIANER_H
