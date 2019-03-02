#ifndef ITEM_SHOW_H
#define ITEM_SHOW_H

#include "config.h"
#include <QString>
#include <QObject>

#define TIMES (100000.0)

class item_show : public QWidget
{
    Q_OBJECT

private:
    item *item_cfg;

public:
    QLabel *name_main;
    QLabel *unit_main;
    QLabel *value_main;
    QLabel *min_main;
    QLabel *max_main;
    QProgressBar *offset_main;

    QCheckBox *enable_setting;
    QLineEdit *name_setting;
    QLineEdit *unit_setting;
    QDoubleSpinBox *min_setting;
    QDoubleSpinBox *max_setting;

public:
    item_show(item *,int,QString);
    void reload_main(item *);
    void reload_setting(item *);
    void sync_setting();

    void update_value(double, int len, QString);
};


class Show_items : public QWidget
{
public:
    item_show *item[SHOW_ITEMS];
private:
    config *cfg;

public:
    Show_items(config *);
};



#endif // ITEM_SHOW_H
