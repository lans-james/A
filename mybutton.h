#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class mybutton : public QPushButton
{
    Q_OBJECT
public:
    explicit mybutton(QWidget *parent = nullptr);
    QString mgpath;
    mybutton(QString path);
    void zoom1();//向上弹跳
    void zoom2();//向下弹跳
signals:

public slots:
};

#endif // MYBUTTON_H
