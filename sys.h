#ifndef SYS_H
#define SYS_H
#include <Windows.h>
#pragma comment(lib, "user32.lib")
#include <QStringList>
#include <QObject>
#include <QtWidgets>

class sys:public QObject
{
    Q_OBJECT
public:
    sys();

signals:
    void cfg_changed();

public slots:
    void power_off();
    void call_keyboard();
    void save();
    void load();
    void apply();
};

#endif // SYS_H
