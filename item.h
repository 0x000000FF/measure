#ifndef ITEM_H
#define ITEM_H
#include <QString>

class item
{
public:
    int enable;
    QString name;
    QString unit;
    double min;
    double max;
    double value;

    QChar type;

    item(QChar);
};

#endif // ITEM_H
