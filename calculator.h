#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QString>
#include <QByteArray>
#include <QStack>
#include <QStringList>

class calculator
{

public:
    calculator();

    //把中缀表达式转换成后缀表达式
    QStringList mid2end(const QString);
//    //计算后缀表达式的值并返回
    double calculate(const QStringList);

    ~calculator();
private:
    QString exp;

    double result;
public:
    double do_cal(QString);
};

#endif // CALCULATOR_H
