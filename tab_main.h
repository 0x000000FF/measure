#ifndef TAB_MAIN_H
#define TAB_MAIN_H


#include <QDialog>
#include "config.h"
#include "item_show.h"
#include <QObject>
#include "serial.h"
#include "calculator.h"
#include "QList"
#include "QTimer"
#include <QtSerialPort/QSerialPort>
#include "define.h"

class Tab_main : public QWidget
{
    Q_OBJECT

public:
    double weight_offset = 0;
    double ret_values[SHOW_ITEMS];
    double volume;
    double density = -9999;

    QTimer *timer_measurre;
    QString serial_number;

    calculator *cal;
    serial * port;

    config *cfg;
    Show_items *all_items;

    QGroupBox *Group_img;
    QLabel *Lable_img;

    QGroupBox *Group_item;
    QGridLayout *Layout_item;

//    item_show *items[SHOW_ITEMS];

    QGroupBox *Group_mea;
    QHBoxLayout *Layout_mea;
    QPushButton *Button_mea;

    QHBoxLayout *Layout_connect;
    QPushButton *Button_connect;
    QPushButton *Button_disconnect;

    QCheckBox *Check_auto;
    QPushButton *Button_reset;
    QLabel *Label_com_state;
    QLabel *Label_density_unit;

    QGroupBox *Group_number;
    QHBoxLayout *Layout_number;
    QLabel *Lable_number;
    QLineEdit *Line_number;
    QLineEdit *Line_number_1;
    QPushButton *Button_save;
    QCheckBox *Check_auto_clear;

    QGroupBox *Group_WVD;
    QGridLayout *Layout_WVD;

    QLabel *Label_density;
    QLabel *Label_density_val;

    QVBoxLayout *Layout_L;
    QVBoxLayout *Layout_R;
    QHBoxLayout *Layout_main;

private:
    double calcul_volume();

public:
    explicit Tab_main(config*,Show_items*,QWidget *parent = 0);

public slots:
    void load_config(config*,Show_items*);
    void set_offset();
    void update_value(QStringList);
    void record();
    void auto_measure(int);
    void open_port();
    void close_port();
    void close_port(QSerialPort::SerialPortError);
    void get_data();


signals:
    void do_measur();

};


#endif // TAB_MAIN_H
