#include "serial.h"
#include <QDebug>
#include <QTime>

serial::serial()
{}
serial::serial(QString com_TM,QString com_WKC)
{
    this->com_TM = com_TM;
    this->com_WKC = com_WKC;

    this->port_TM = new QSerialPort();
    this->port_WKC = new QSerialPort();

    connect(this->port_TM,SIGNAL(readyRead()),this,SLOT(handle_TM()));
    connect(this->port_WKC,SIGNAL(readyRead()),this,SLOT(handle_WKC()));

    connect(this->port_TM,SIGNAL(errorOccurred(QSerialPort::SerialPortError)),this,SLOT(send_error(QSerialPort::SerialPortError)));
    connect(this->port_WKC,SIGNAL(errorOccurred(QSerialPort::SerialPortError)),this,SLOT(send_error(QSerialPort::SerialPortError)));
}

void serial::set_ports(QString com_TM,QString com_WKC)
{
    this->close_ports();
    this->com_TM = com_TM;
    this->com_WKC = com_WKC;
}

void serial::set_program(QString pr)
{
    this->program = pr;
}

bool serial::open_ports()
{
    qDebug()<<"TM begin..."<<this->com_TM;
    if(!this->port_TM->isOpen())
    {
        this->port_TM->setPortName(this->com_TM);  //打开COM1
        this->port_TM->open(QIODevice::ReadWrite);
        this->port_TM->setBaudRate(9600);
        this->port_TM->setDataBits(QSerialPort::Data8);
        this->port_TM->setParity(QSerialPort::NoParity);
        this->port_TM->setStopBits(QSerialPort::OneStop);
        this->port_TM->setFlowControl(QSerialPort::NoFlowControl);
    }

    if (this->port_TM->isOpen())
    {
        QByteArray buf = this->program.toLatin1();
        buf.append(0x0d);
        buf.append(0x0a);
        this->port_TM->write(buf);
    }
    else
    {
        qDebug()<<"TM3000 open failed";
        return false;
    }

    if(!this->port_WKC->isOpen())
    {
        qDebug()<<"WKC begin..."<<this->com_WKC;
        this->port_WKC->setPortName(this->com_WKC);  //打开COM1
        this->port_WKC->open(QIODevice::ReadWrite);
        this->port_WKC->setBaudRate(9600);
        this->port_WKC->setDataBits(QSerialPort::Data8);
        this->port_WKC->setParity(QSerialPort::NoParity);
        this->port_WKC->setStopBits(QSerialPort::OneStop);
        this->port_WKC->setFlowControl(QSerialPort::NoFlowControl);
    }

    if (this->port_WKC->isOpen())
    {
        qDebug()<<"WKC open successed";
    }
    else
    {
        qDebug()<<"WKC open failed";
        return false;
    }
    return true;
}

void serial::close_ports()
{
    if(this->port_TM->isOpen())
    {
        this->port_TM->close();
    }
    if(this->port_WKC->isOpen())
    {
        this->port_WKC->close();
    }
}

bool serial::is_open()
{
    return (this->port_TM->isOpen() && this->port_WKC->isOpen());
}

void serial::send_error(QSerialPort::SerialPortError err)
{
    if(err != QSerialPort::NoError)
    {
        qDebug()<<err;
        if(this->port_TM->isOpen())
        {
            this->port_TM->close();
        }
        if(this->port_WKC->isOpen())
        {
            this->port_WKC->close();
        }
        this->port_TM->clearError();
        this->port_WKC->clearError();
    }

    emit(this->error(err));
}

void serial::get_TM()
{
    QByteArray buf("MA");
    buf.append(0x0d);
    buf.append(0x0a);
    this->port_TM->write(buf);
    qDebug()<<"TM>>>>>";
}

void serial::get_WKC()
{
    QByteArray buf("SI");
//    buf.append(0x0d);
    buf.append(0x0a);
    this->port_WKC->write(buf);
    qDebug()<<"WKC>>>>>";
}

QStringList serial::handle_TM()
{
    qDebug()<<"TM<<<<<<<<";
    QStringList ret;
    QString msg;
    this->buffer_TM.append(this->port_TM->readAll());
    qDebug()<<this->buffer_TM;

    if(this->buffer_TM.contains("\r"))//\r
    {
        if(!this->buffer_TM.startsWith("MA"))
        {
            this->ready_TM = false;
            this->ready_WKC = false;

            this->port_TM->clear();
            this->port_WKC->clear();
            this->buffer_WKC.clear();
            this->buffer_TM.clear();

            this->get_TM();
            this->get_TM();

        }

        msg = this->buffer_TM.section("\r",0,0);
        this->buffer_TM = this->buffer_TM.section("\r",1,-1);
        qDebug()<<"mag:"<< msg;
        qDebug()<<"buffer:"<< this->buffer_TM;
        this->msg_TM = msg;
        this->ready_TM = true;

        this->send_data();
    }

    return ret;
}

QStringList serial::handle_WKC()
{
    qDebug()<<"WKC<<<<<<<<";
    QStringList ret;
    QString msg;
    this->buffer_WKC.append(this->port_WKC->readAll());
    qDebug()<<this->buffer_WKC;

    if(this->buffer_WKC.contains("\r\n"))//\r
    {
        if(!this->buffer_WKC.startsWith("S"))
        {
            this->ready_TM = false;
            this->ready_WKC = false;

            this->port_TM->clear();
            this->port_WKC->clear();
            this->buffer_WKC.clear();
            this->buffer_TM.clear();

            this->get_TM();
            this->get_TM();

        }
        msg = this->buffer_WKC.section("\r\n",0,0);
        this->buffer_WKC = this->buffer_WKC.section("\r\n",1,-1);
        qDebug()<<"mag:"<< msg;
        qDebug()<<"buffer:"<< this->buffer_WKC;
        this->msg_WKC = msg;
        this->ready_WKC = true;

        this->send_data();
    }
    return ret;
}

void serial::send_data()
{
    if(this->ready_TM && this->ready_WKC)
    {
        qDebug()<<"*************";
//
        QStringList ret;

        ret.append(this->msg_WKC.mid(0,3));
        ret.append(this->msg_WKC.mid(7,7));
        ret.append(this->msg_TM.split(","));

        ret.removeAt(2);
        qDebug()<<ret;

        emit(this->data(ret));

        this->ready_TM = false;
        this->ready_WKC = false;

        this->port_TM->clear();
        this->port_WKC->clear();

        this->buffer_TM.clear();
        this->buffer_WKC.clear();
    }
    else
    {
        return;
    }
}

