#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "config.h"
#include "item_show.h"
#include <QObject>
#include "serial.h"
#include "calculator.h"
#include "QList"
#include "QTimer"
#include <QtSerialPort/QSerialPort>
#include "tab_main.h"
#include "tab_setting.h"
#include "tab_para.h"
#include "sys.h"

class TabDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TabDialog(config*,QWidget *parent = 0);

public:
    config *cfg;
    QVBoxLayout *Layout_V;

    QTabWidget *tabWidget;
    Tab_main *main_tab;
    Tab_setting *setting_tab;
    Tab_para *para_tab;
    sys *sys_func;

public:
    Show_items *all_items;
    bool eventFilter(QObject *watched, QEvent *event);

signals:
    void s_power_off();
    void s_keyboard();

private slots:
    void reload();
    void check_pswd(int);
};

#endif // DIALOG_H
