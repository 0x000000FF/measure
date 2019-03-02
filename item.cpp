#include "item.h"

item::item(QChar t)
{
    this->type = t;

    this->enable = 0;
    this->name = "--";
    this->unit = "--";
    this->min = 0;
    this->value = 0;
    this->max = 0;

    if(this->type == 'W')
    {
        this->enable = 1;
        this->name = "重量";
    }
    else if(this->type == 'D')
    {
        this->enable = 1;
        this->name = "密度";
    }
}
