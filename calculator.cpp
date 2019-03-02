#include "calculator.h"
#include <QDebug>




calculator::calculator()
{

}

//中缀表达式转为后缀表达式的实现
QStringList calculator::mid2end(const QString mid)
{
    QStringList list_end;
    QString ele;
    QStack <QString> mystack;

    foreach (QChar c, mid)
    {

        if((c>='0'&&c<='9') || c == '.')
        {
            ele += c;
        }
        else
        {
            list_end.append(ele);
            ele = "";

            if(c=='-'||c=='+')
            {
                if(!mystack.isEmpty())
                {
                    while((!mystack.isEmpty()) && (mystack.top()=="+"||mystack.top()=="-"||mystack.top()=='*'||mystack.top()=='/'))
                    {
                        //只要是加号或者减号 栈中的无论是什么，出干净
                        list_end.append(mystack.pop());
                    }
                }
                mystack.push(QString(c));
            }
            else if(c=='*'||c=='/')
            {
                if(!mystack.isEmpty())
                {
                    while((!mystack.isEmpty()) && (mystack.top()=="*"||mystack.top()=="/"))
                    {
                        list_end.append(mystack.pop());
                    }
                }
                mystack.push(QString(c));
            }
            else if('('==c)
            {
                mystack.push(QString(c));
            }
            else if(')'==c)
            {
                //遇到）将（之前的所有数据输出之后将（出栈
                if(!mystack.isEmpty())
                {
                    while((!mystack.isEmpty()) && mystack.top()!='(')
                    {
                        list_end.append(mystack.pop());
                    }
                }//当前的）直接输出
                mystack.pop();
            }
        }
    }
    list_end.append(ele);

    while(!mystack.isEmpty())
    {
        list_end.append(mystack.pop());
    }
    qDebug()<<list_end;

    return list_end;
}

////======计算表达式的和==================================================================================
double calculator::calculate(const QStringList list_end)
{
    if(list_end.isEmpty())
    {
        return 0;
    }

    double a,b;
    QStack <double> mystack;

    foreach (QString ele, list_end)
    {

        if(ele == "+")
        {
            b = mystack.pop();
            a = mystack.pop();
            mystack.push(a+b);
            qDebug()<<a<<"+"<<b<<"="<<mystack.top()<<endl;
        }
        else if(ele == "-")
        {
            b = mystack.pop();
            a = mystack.pop();
            mystack.push(a-b);
            qDebug()<<a<<"-"<<b<<"="<<mystack.top()<<endl;
        }
        else if(ele == "*")
        {
            b = mystack.pop();
            a = mystack.pop();
            mystack.push(a*b);
            qDebug()<<a<<"*"<<b<<"="<<mystack.top()<<endl;
        }
        else if(ele == "/")
        {
            b = mystack.pop();
            a = mystack.pop();
            mystack.push(a/b);
            qDebug()<<a<<"/"<<b<<"="<<mystack.top()<<endl;
        }
        else
        {
            mystack.push(ele.toDouble());
        }

    }
    return mystack.top();
}
////=====================================================================================================
double calculator::do_cal(QString exp)
{
    this->exp = exp;

    this->result = calculate(this->mid2end(this->exp));
    qDebug()<<"result:"<<result;

    return this->result;
}


calculator::~calculator()
{

}
