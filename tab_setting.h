#ifndef TAB_SETTING_H
#define TAB_SETTING_H


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

class Tab_setting : public QWidget
{
    Q_OBJECT
public:
    config *cfg;
    QGridLayout *Layout_main;
    QLabel *Lable_img;
    QLabel *Lable_log;
    QLineEdit *Line_log;

    QPushButton *Button_log;
    QPushButton *Button_apply;
    QPushButton *Button_power_off;

public:
    explicit Tab_setting(config *,QWidget *parent = 0);

signals:
    void s_power_off();
    void s_keyboard();
    void cfg_changed();

private:
    void sync_setting();

public slots:
    void load_config(config*);
    void set_log_path();
    void on_Button_load_clicked();
};


#endif // TAB_SETTING_H
