#include "item_show.h"

item_show::item_show(item *cfg,int index,QString style="rec")
{
    this->item_cfg = cfg;

    this->name_main = new QLabel(this->item_cfg->name);
    this->unit_main = new QLabel(this->item_cfg->unit);
//    this->value_main = new QLabel(this->item_cfg->value);
    this->min_main = new QLabel(QString::number(this->item_cfg->min));
    this->max_main = new QLabel(QString::number(this->item_cfg->max));
    this->offset_main = new QProgressBar();

    this->enable_setting = new QCheckBox();
    this->name_setting = new QLineEdit(this->item_cfg->name);
    this->unit_setting = new QLineEdit(this->item_cfg->unit);
    this->min_setting = new QDoubleSpinBox();
    this->max_setting = new QDoubleSpinBox();


    if(this->item_cfg->type == 'W')
    {
        this->enable_setting->setText("$W");
        this->enable_setting->setChecked(true);
        this->enable_setting->setEnabled(false);
        this->name_setting->setEnabled(false);

        this->min_setting->setSingleStep(0.0001);
        this->max_setting->setSingleStep(0.0001);
        this->min_setting->setRange(-100,100);
        this->max_setting->setRange(-100,100);
        this->min_setting->setDecimals(4);
        this->max_setting->setDecimals(4);
    }
    else if(this->item_cfg->type == 'D')
    {
        this->enable_setting->setText("$D");
        this->enable_setting->setChecked(true);
        this->enable_setting->setEnabled(false);
        this->name_setting->setEnabled(false);

        this->min_setting->setSingleStep(0.0001);
        this->max_setting->setSingleStep(0.0001);
        this->min_setting->setRange(-100,100);
        this->max_setting->setRange(-100,100);
        this->min_setting->setDecimals(4);
        this->max_setting->setDecimals(4);
    }
//    else if(this->item_cfg->type == 'D')
//    {
//        this->enable_setting->setText("$V");
//        this->enable_setting->setChecked(true);
//        this->enable_setting->setEnabled(false);
//        this->name_setting->setEnabled(false);

//        this->min_setting->setSingleStep(0.0001);
//        this->max_setting->setSingleStep(0.0001);
//        this->min_setting->setRange(-100,100);
//        this->max_setting->setRange(-100,100);
//        this->min_setting->setDecimals(4);
//        this->max_setting->setDecimals(4);
//    }
    else
    {
        this->enable_setting->setText("$"+QString::number(index));
        this->min_setting->setSingleStep(0.001);
        this->max_setting->setSingleStep(0.001);
        this->min_setting->setRange(-100,100);
        this->max_setting->setRange(-100,100);
        this->min_setting->setDecimals(3);
        this->max_setting->setDecimals(3);
    }

    if(style == "cir")
    {
        this->name_main->setMinimumSize(60,60);
        this->name_main->setMaximumSize(60,60);
        this->name_main->setAlignment(Qt::AlignCenter);
        this->name_main->setStyleSheet("background-color:rgb(255,255,255);\
                                      border-radius:30px;\
                                      font-family:Microsoft YaHei UI; \
                                      font:bold;font-size:24px");
    }
    else if (style == "rec")
    {
        this->name_main->setStyleSheet("\
                                      font-family:Microsoft YaHei UI; \
                                      font:bold;font-size:24px");
    }

    this->unit_main->setStyleSheet("text-align:right; \
                                      font-family:Microsoft YaHei UI; \
                                      font:bold;font-size:22px");

    this->min_main->setStyleSheet("qproperty-alignment: 'AlignBottom | AlignRight'; \
                                      font-family:Microsoft YaHei UI; \
                                      font:bold;font-size:14px");

    this->max_main->setStyleSheet("qproperty-alignment: 'AlignBottom | AlignLeft'; \
                                      font-family:Microsoft YaHei UI; \
                                      font:bold;font-size:14px");

    this->offset_main->setStyleSheet("QProgressBar{text-align:right; \
                                        background-color:rgb(70,130,180); \
                                        border:3px solid white; \
                                        border-radius:10px; \
                                        border-style:outset; \
                                        font-family:Microsoft YaHei UI; \
                                        font:bold;font-size:34px}"
                                     "QProgressBar::chunk{background-color:rgb(0,255,0);\
                                        }");

    this->offset_main->setMinimumSize(200,45);
    this->offset_main->setMaximumSize(200,45);
    this->offset_main->setFormat("--");
}

void item_show::reload_main(item *cfg)
{
    this->item_cfg = cfg;

    if(this->item_cfg->enable == 1)
    {
        int min = (int)(item_cfg->value*TIMES);
        int max = (int)(item_cfg->max*TIMES);
//        min = 0;
//        max = 100;
        this->offset_main->setRange(0,max-min);
        this->offset_main->setValue(0);

//        this->offset_main->setFormat(QString::number(item_cfg->value));
        this->offset_main->setFormat("--");

        this->name_main->setVisible(true);
        this->unit_main->setVisible(true);
        this->min_main->setVisible(true);
        this->max_main->setVisible(true);
        this->offset_main->setVisible(true);

        this->name_main->setText(this->item_cfg->name);
        this->unit_main->setText(this->item_cfg->unit);
    //    this->value_main->setText(this->item_cfg->value);
        this->min_main->setText(QString::number(this->item_cfg->min));
        this->max_main->setText(QString::number(this->item_cfg->max));
    }
    else
    {
        this->name_main->setVisible(false);
        this->unit_main->setVisible(false);
        this->min_main->setVisible(false);
        this->max_main->setVisible(false);
        this->offset_main->setVisible(false);
    }
}

void item_show::reload_setting(item *cfg)
{
    this->item_cfg = cfg;

    if(this->item_cfg->enable == 1)
    {
        this->name_setting->setEnabled(true);
        this->unit_setting->setEnabled(true);
        this->min_setting->setEnabled(true);
        this->max_setting->setEnabled(true);

        this->enable_setting->setChecked(true);
        this->name_setting->setText(this->item_cfg->name);
        this->unit_setting->setText(this->item_cfg->unit);
        this->min_setting->setValue(this->item_cfg->min);
        this->max_setting->setValue(this->item_cfg->max);

    }
    else
    {
        this->enable_setting->setChecked(false);
        this->name_setting->setEnabled(false);
        this->unit_setting->setEnabled(false);
        this->min_setting->setEnabled(false);
        this->max_setting->setEnabled(false);
    }

    connect(this->enable_setting,SIGNAL(toggled(bool)),this->name_setting,SLOT(setEnabled(bool)));
    connect(this->enable_setting,SIGNAL(toggled(bool)),this->unit_setting,SLOT(setEnabled(bool)));
    connect(this->enable_setting,SIGNAL(toggled(bool)),this->min_setting,SLOT(setEnabled(bool)));
    connect(this->enable_setting,SIGNAL(toggled(bool)),this->max_setting,SLOT(setEnabled(bool)));
}


void item_show::sync_setting()
{
    if(this->enable_setting->isChecked() == true)
    {
        this->item_cfg->enable = 1;
    }
    else
    {
        this->item_cfg->enable = 0;
    }

    this->item_cfg->name = this->name_setting->text().toUtf8();
    this->item_cfg->unit = this->unit_setting->text().toLocal8Bit();
    this->item_cfg->min  = this->min_setting->value();
    this->item_cfg->max  = this->max_setting->value();
    this->item_cfg->value= (this->item_cfg->min + this->item_cfg->max)/2;

}

void item_show::update_value(double value,int len,QString state)
{
//    len = 4;
    QString num = QString::number(value,'f',len);
    if (value == -9999)
    {
        num = "--";
    }
//    qDebug()<<"+++"<<value<<"::"<<num;

    qDebug()<<this->offset_main->minimum()<<":"<<this->offset_main->maximum()<<"::"<<value;
    if(state == "S S")
    {
        this->offset_main->setStyleSheet("QProgressBar{text-align:right; \
                                            background-color:rgb(70,130,180);\
                                            border:3px solid white;\
                                            border-radius:10px;\
                                            border-style:outset; \
                                            font-family:Microsoft YaHei UI; \
                                            font:bold;font-size:34px}"
                                         "QProgressBar::chunk{background-color:rgb(0,255,0);\
                                            }");
    }
    else if(state == "S D")
    {
        this->offset_main->setStyleSheet("QProgressBar{text-align:right; \
                                         background-color:rgb(70,130,180);\
                                         border:3px solid white;\
                                         border-radius:10px;\
                                         border-style:outset; \
                                         font-family:Microsoft YaHei UI; \
                                         font:bold;font-size:34px}"
                                      "QProgressBar::chunk{background-color:rgb(255,127,36);\
                                         }");
    }

    if(value > this->item_cfg->max || value < this->item_cfg->min)
    {
        this->offset_main->setStyleSheet("QProgressBar{text-align:right; \
                                         background-color:rgb(70,130,180);\
                                         border:3px solid white;\
                                         border-radius:10px;\
                                         border-style:outset; \
                                         font-family:Microsoft YaHei UI; \
                                         font:bold;font-size:34px}"
                                      "QProgressBar::chunk{background-color:rgb(255,0,0);\
                                         }");

        this->offset_main->setValue((int)((this->item_cfg->max-this->item_cfg->value)*TIMES));
        this->offset_main->setFormat(num);
    }
    else
    {
        if(value >= this->item_cfg->value)
        {
            this->offset_main->setInvertedAppearance(false);
            int val = (int)((value-this->item_cfg->value)*TIMES);
            qDebug()<<val;

            this->offset_main->setValue(val);
        }
        else if(value < this->item_cfg->value)
        {
            this->offset_main->setInvertedAppearance(true);
            int val = (int)((this->item_cfg->value-value)*TIMES);
            qDebug()<<val;

            this->offset_main->setValue(val);
        }
    //        this->offset_main->setFormat(QString::number(item_cfg->value));
        this->offset_main->setFormat(num);
    }
}
