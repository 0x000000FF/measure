#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QString>
#include <QList>

class serial:public QObject
{
    Q_OBJECT

private:
    QSerialPort *port_TM;
    QSerialPort *port_WKC;

    QString com_TM;
    QString com_WKC;

    QString program;

    bool ready_TM = false;
    bool ready_WKC = false;

    QString buffer_TM;
    QString buffer_WKC;

    QString msg_TM;
    QString msg_WKC;
//    config *cfg;
public:
    serial();
    serial(QString,QString);

    void send_data();
    bool is_open();
    bool open_ports();
    void close_ports();
    void set_ports(QString,QString);
    void set_program(QString);

signals:
    void data(QStringList);
    void error(QSerialPort::SerialPortError);

public slots:
    void get_TM();
    void get_WKC();
    void send_error(QSerialPort::SerialPortError);

    QStringList handle_TM();
    QStringList handle_WKC();
};

#endif // SERIAL_H
