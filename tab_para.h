#ifndef TAB_PARA_H
#define TAB_PARA_H


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

class Tab_para : public QWidget
{
    Q_OBJECT
public:

    config *cfg;
    Show_items *all_items;

    QHBoxLayout *Layout_main;

    QGroupBox *Group_setting;
    QVBoxLayout *Layout_setting;

    QGroupBox *Group_item;
    QGridLayout *Layout_item;

//    item_show *items[SHOW_ITEMS];

    QGroupBox *Group_serial;
    QHBoxLayout *Layout_serial;
    QComboBox *Serial_MT;
    QComboBox *Serial_WKC;
    QLabel *Lable_TM;
    QLabel *Lable_WKC;

    QComboBox *Decimal;
    QComboBox *combo_index;
    QLabel *Lable_dec;
    QLabel *Lable_index;

    QLabel *Label_pswd;
    QLineEdit *Line_pswd;

    QGroupBox *Group_buttons;
    QHBoxLayout *Layout_buttons;

    QPushButton *Button_save;
    QPushButton *Button_saveas;
    QPushButton *Button_load;
    QPushButton *Button_apply;

    QGroupBox *Group_img;
    QGridLayout *Layout_img;

    QLabel *Lable_img;
    QHBoxLayout *Layout_img_btn;
    QLineEdit *Line_img;
    QPushButton *open_img;

    QGroupBox *Group_formula;
    QHBoxLayout *Layout_formula;
    QPlainTextEdit *Text_formula;
    QLabel *Lable_formula;
    QPushButton *Button_formula;

    QHBoxLayout *Layout_log;
    QLabel *Lable_log;

    QHBoxLayout *Layout_sys;
    QPushButton *Button_power_off;
    QPushButton *Button_keyboard;

public:
    explicit Tab_para(config *,Show_items*,QWidget *parent = 0);

private:
    void sync_setting();

public slots:
    void load_config(config*,Show_items*);
    void on_open_img_clicked();
    void on_Button_save_clicked();
    void on_Button_saveas_clicked();
    void on_Button_load_clicked();
    void on_Button_apply_clicked();
    void on_Button_keyboard_clicked();
    void on_Button_formula_clicked();
    void set_log_path();

signals:
    void cfg_changed();
    void load();
    void save();
    void apply();
};

#endif // TAB_PARA_H
