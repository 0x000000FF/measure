#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QSettings>
#include <QtWidgets>
#include <QDialog>
#include "item.h"
#include <QFile>

#define MAX_ITEMS  8
#define SHOW_ITEMS (MAX_ITEMS+2)

#define DEF_SETTING ("C:\\default.ini")
#define PASSWD ("E:\\pass.ini")

class config
{
public:
    QString ini_path;
    QFile *log_file;
    QTextStream *log_stream;

    QString img_path;
    QString log_path;
    QString formula;
    QString program_index;
    QString pswd;
    QString serial_MT;
    QString serial_WKC;

    QSettings *setting;
    QSettings *setting_pass;
    int items_sum;
    int decimal;

private:


public:
    item *all_items[SHOW_ITEMS];
    config();
    ~config();
    int load_ini(QString);
    int load_ini();
    int save_ini(QString);
    int save_ini();

    void logging(QString);
};

#endif // CONFIG_H
