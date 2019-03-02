#include "tab_main.h"

Tab_main::Tab_main(config* cfg,Show_items* all_items,QWidget *parent) : QWidget(parent)
{
    this->cfg = cfg;
    this->all_items = all_items;
    this->port = new serial(this->cfg->serial_MT,this->cfg->serial_WKC);

    this->timer_measurre = new QTimer();
    this->timer_measurre->start(1000);

    this->cal = new calculator();

    this->Layout_main = new QHBoxLayout;
    this->Layout_L = new QVBoxLayout;
    this->Layout_R = new QVBoxLayout;

    this->Layout_main->addLayout(this->Layout_R);
    this->Layout_main->addLayout(this->Layout_L);

    this->Group_img = new QGroupBox();

    this->Lable_img = new QLabel();
    this->Lable_img->setStyleSheet("background-color:gray");
    this->Lable_img->setMinimumSize(IMG_WIDTH,IMG_HEIGHT);
    this->Lable_img->setMaximumSize(IMG_WIDTH,IMG_HEIGHT);

    this->Group_WVD = new QGroupBox();
    this->Group_WVD->setMaximumSize(550,350);
    this->Layout_WVD = new QGridLayout;

    for(int i = 0;i < 2;i++)
    {
        this->Layout_WVD->setRowMinimumHeight(i,70);

        this->Layout_WVD->addWidget(this->all_items->item[i]->name_main,i+1,0);
        this->Layout_WVD->addWidget(this->all_items->item[i]->min_main,i+1,1);
        this->Layout_WVD->addWidget(this->all_items->item[i]->offset_main,i+1,2);
        this->Layout_WVD->addWidget(this->all_items->item[i]->max_main,i+1,3);
        this->Layout_WVD->addWidget(this->all_items->item[i]->unit_main,i+1,4);
    }

    this->Label_density = new QLabel("密度");
    this->Label_density->setMaximumSize(300,45);
//    this->Label_density->setMinimumSize(300,45);
    this->Label_density->setStyleSheet(" \
                                      font-family:Microsoft YaHei UI; \
                                      font:bold;font-size:24px");

    this->Label_density_val = new QLabel("--");
    this->Label_density_val->setStyleSheet("qproperty-alignment: 'AlignBottom | AlignRight'; \
                                      font-family:Microsoft YaHei UI; \
                                      font:bold;font-size:36px");


    this->Button_reset = new QPushButton("校零");
    this->Button_reset->setMinimumSize(60,60);
    this->Button_reset->setMaximumSize(60,60);
    this->Button_reset->setStyleSheet("background-color:rgb(188,210,238);\
                                        border-radius:30px;\
                                        font-family:Microsoft YaHei UI; \
                                        font:bold;font-size:18px");
    this->Layout_WVD->addWidget(this->Button_reset,1,5,Qt::AlignCenter);

//    this->Label_com_state = new QLabel();
//    this->Label_com_state->setMaximumSize(16,16);
//    this->Label_com_state->setStyleSheet("background-color:red");
    this->Label_density_unit = new QLabel();
    this->Label_density_unit->setStyleSheet("text-align:right; \
                                      font-family:Microsoft YaHei UI; \
                                      font:bold;font-size:14px");


    this->Button_mea = new QPushButton("测量");
    this->Button_mea->setDisabled(true);
    this->Button_mea->setMinimumSize(80,80);
    this->Button_mea->setMaximumSize(80,80);
    this->Button_mea->setStyleSheet("{\
                                        border-radius:40px;\
                                        border:5px solid red;\
                                        font-family:Microsoft YaHei UI; \
                                        font:bold;font-size:24px}");

    this->Layout_connect = new QHBoxLayout;
    this->Button_connect = new QPushButton("连接");
    this->Button_connect->setStyleSheet(" \
                                      font-family:Microsoft YaHei UI; \
                                      font:bold;font-size:20px");
    this->Button_connect->setMinimumSize(40,40);
    this->Button_disconnect = new QPushButton("断开");
    this->Button_disconnect->setMinimumSize(40,40);

    this->Check_auto = new QCheckBox("实时测量");
    this->Check_auto->setDisabled(true);

    this->Layout_connect->addWidget(this->Check_auto);
    this->Layout_connect->addWidget(this->Button_connect);

//    this->Layout_WVD->addWidget(this->Label_com_state,2,3);
//    this->Layout_WVD->addWidget(this->Label_density_unit,2,3);
//    this->Layout_WVD->addWidget(this->Check_auto,1,4);
    this->Layout_WVD->addWidget(this->Button_mea,2,5,Qt::AlignCenter);

    this->Group_WVD->setLayout(this->Layout_WVD);
//    this->Layout_WVD->addWidget(this->Label_density,2,0);
//    this->Layout_WVD->addWidget(this->Label_density_val,2,1,1,2);

    this->Layout_number = new QHBoxLayout;

    this->Line_number = new QLineEdit();
    this->Line_number->setAttribute(Qt::WA_InputMethodEnabled,true);

    this->Line_number->setStyleSheet(" \
                                      font-family:Microsoft YaHei UI; \
                                      font:bold;font-size:20px");
    this->Line_number->setMaxLength(20);
    this->Line_number->setMinimumSize(120,36);
    this->Line_number->setMaximumSize(120,36);


    this->Line_number_1 = new QLineEdit("0");
    this->Line_number_1->setAttribute(Qt::WA_InputMethodEnabled,true);

    this->Line_number_1->setStyleSheet(" \
                                      font-family:Microsoft YaHei UI; \
                                      font:bold;font-size:20px");
    this->Line_number_1->setMaxLength(20);
    this->Line_number_1->setMinimumSize(120,36);
    this->Line_number_1->setMaximumSize(120,36);

    this->Button_save = new QPushButton("记录");
//    this->Button_save->setDisabled(true);
    this->Button_save->setMinimumSize(60,60);
    this->Button_save->setMaximumSize(60,60);
    this->Button_save->setStyleSheet("background-color:rgb(188,210,238);\
                                      border-radius:30px;\
                                      font-family:Microsoft YaHei UI; \
                                      font:bold;font-size:18px");

    this->Lable_number = new QLabel("编号");
    this->Lable_number->setMinimumSize(60,60);
    this->Lable_number->setMaximumSize(60,60);
    this->Lable_number->setAlignment(Qt::AlignCenter);
    this->Lable_number->setStyleSheet("background-color:rgb(255,255,255);\
                                        border-radius:30px;\
                                        font-family:Microsoft YaHei UI; \
                                        font:bold;font-size:24px");
//    this->Check_auto_clear = new QCheckBox("自动清除");

    this->Layout_WVD->addWidget(this->Lable_number,0,0);

    this->Layout_number->addWidget(this->Line_number);
    QLabel *bel = new QLabel("-");
    bel->setStyleSheet(" \
                  font-family:Microsoft YaHei UI; \
                  font:bold;font-size:24px");
    this->Layout_number->addWidget(bel);
    this->Layout_number->addWidget(this->Line_number_1);
    this->Layout_WVD->addLayout(this->Layout_number,0,2,1,2,Qt::AlignCenter);
//    this->Layout_WVD->addWidget(this->Check_auto_clear,3,4);
    this->Layout_WVD->addWidget(this->Button_save,0,5,Qt::AlignCenter);

    this->Layout_L->addWidget(this->Group_WVD);
    this->Layout_L->addWidget(this->Lable_img,0,Qt::AlignCenter);

    this->Group_item = new QGroupBox();
    this->Layout_item = new QGridLayout;
//    this->Layout_item->setSpacing(1);

    this->Layout_R->addWidget(Group_item);

    this->Group_item->setLayout(Layout_item);

    this->Group_item->setMaximumSize(500,650);
    this->Group_item->setMaximumSize(500,650);

    this->setLayout(this->Layout_main);

    for(int i = 2;i < SHOW_ITEMS;i++)
    {
        this->ret_values[i] = -9999;
//        this->items[i] = new item_show(this->cfg->all_items[i],i);

        this->Layout_item->setRowMinimumHeight(i,70);

        this->Layout_item->addWidget(this->all_items->item[i]->name_main,i,0);
        this->Layout_item->addWidget(this->all_items->item[i]->min_main,i,1);
        this->Layout_item->addWidget(this->all_items->item[i]->offset_main,i,2);
        this->Layout_item->addWidget(this->all_items->item[i]->max_main,i,3);
        this->Layout_item->addWidget(this->all_items->item[i]->unit_main,i,4);
    }
    this->Layout_item->setRowMinimumHeight(SHOW_ITEMS,70);
    this->Layout_item->addLayout(this->Layout_connect,SHOW_ITEMS,0,1,5,Qt::AlignBottom);

//    this->load_config(cfg);
    connect(this->Button_connect,SIGNAL(clicked(bool)),this,SLOT(open_port()));
    connect(this->Button_disconnect,SIGNAL(clicked(bool)),this,SLOT(close_port()));
    connect(this->Button_mea,SIGNAL(clicked(bool)),this,SLOT(get_data()));
    connect(this->Button_reset,SIGNAL(clicked(bool)),this,SLOT(set_offset()));
    connect(this->Button_save,SIGNAL(clicked(bool)),this,SLOT(record()));
    connect(this->port,SIGNAL(data(QStringList)),this,SLOT(update_value(QStringList)));
    connect(this->Check_auto,SIGNAL(stateChanged(int)),this,SLOT(auto_measure(int)));
    connect(this->Line_number,SIGNAL(returnPressed()),this,SLOT(record()));
    connect(this->port,SIGNAL(error(QSerialPort::SerialPortError)),this,SLOT(close_port(QSerialPort::SerialPortError)));

}

void Tab_main::auto_measure(int state)
{
    if(state == 0)
    {
//        disconnect(this->timer_measurre,SIGNAL(timeout()),this->port,SLOT(get_TM()));
//        disconnect(this->timer_measurre,SIGNAL(timeout()),this->port,SLOT(get_WKC()));
        disconnect(this->timer_measurre,SIGNAL(timeout()),this,SLOT(get_data()));
    }
    else if(state == 2)
    {
//        connect(this->timer_measurre,SIGNAL(timeout()),this->port,SLOT(get_TM()));
//        connect(this->timer_measurre,SIGNAL(timeout()),this->port,SLOT(get_WKC()));
        connect(this->timer_measurre,SIGNAL(timeout()),this,SLOT(get_data()));
    }
}

void Tab_main::load_config(config *cfg,Show_items *all_items)
{
    this->cfg = cfg;
    this->all_items = all_items;

    this->close_port();
    this->port->set_ports(this->cfg->serial_MT,this->cfg->serial_WKC);
    this->port->set_program(this->cfg->program_index);

    this->Label_density_unit->setText(this->cfg->all_items[0]->unit+"/"+this->cfg->all_items[1]->unit);
//    this->open_port();

    qDebug()<<"load main config";
    qDebug()<<cfg->all_items;
    QString image_path = cfg->img_path;
    if(image_path.isEmpty())
    {
//        return;
    }
    else
    {
        QImage * img = new QImage;
        if(!(img->load(image_path)))
        {
            this->Lable_img->setText("图片打开失败！");
            delete img;
        }
        else
        {
            this->Lable_img->setPixmap(QPixmap::fromImage(*img).scaled(IMG_WIDTH,IMG_HEIGHT,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        }
    }

    for(int i = 0;i < SHOW_ITEMS;i++)
    {
        this->all_items->item[i]->reload_main(this->cfg->all_items[i]);
    }
}

void Tab_main::update_value(QStringList slist)
{
    QString str;
    for(int i = 1;i < slist.count();i++)
    {
        str = slist.at(i);
        if(str == "-FFFFFFF")
        {
            this->ret_values[i-1] = -9999;
        }
        else
        {
            this->ret_values[i-1] = str.toDouble();
        }
    }
    this->ret_values[0] -= this->weight_offset;

    qDebug()<<this->ret_values;

    this->all_items->item[0]->update_value(this->ret_values[0],4,slist[0]);

    this->volume = this->calcul_volume();
    this->density = this->ret_values[0]/this->volume;
    this->all_items->item[1]->update_value(this->density,this->cfg->decimal,"S S");

    for(int i = 2;i < SHOW_ITEMS;i++)
    {
        this->all_items->item[i]->update_value(this->ret_values[i-1],3,"S S");
    }

}

void Tab_main::set_offset()
{

    this->weight_offset += this->ret_values[0];
    this->ret_values[0] = 0.0;
    this->all_items->item[0]->update_value(this->ret_values[0],4,"S S");
}

double Tab_main::calcul_volume()
{
    if(this->cfg->formula.isEmpty())
    {
        return -9999;
    }
    QString exp = this->cfg->formula;

    exp.replace("$W",QString::number(this->ret_values[0]));

    for(int i = 1;i<SHOW_ITEMS;i++)
    {
        exp.replace("$"+QString::number(i),QString::number(this->ret_values[i]));
    }

    qDebug()<<exp;

    return this->cal->do_cal(exp);
}

void Tab_main::open_port()
{
    if(this->port->open_ports())
    {
        qDebug()<<"OPEN";

        this->Button_connect->setText("断开");
        this->Check_auto->setEnabled(true);
        this->Button_save->setEnabled(true);
        this->Button_mea->setEnabled(true);
//        this->Label_com_state->setStyleSheet("background-color:rgb(0,255,0)");
        this->Button_mea->setStyleSheet("border:5px solid green;");


        disconnect(this->Button_connect,SIGNAL(clicked(bool)),this,SLOT(open_port()));
        connect(this->Button_connect,SIGNAL(clicked(bool)),this,SLOT(close_port()),Qt::UniqueConnection);
    }
}

void Tab_main::close_port()
{
    qDebug()<<"CLOSE";
    this->port->close_ports();

    this->Button_connect->setText("连接");
    this->Check_auto->setDisabled(true);
//    this->Button_save->setDisabled(true);
    this->Button_mea->setDisabled(true);
//    this->Label_com_state->setStyleSheet("background-color:red");
    this->Button_mea->setStyleSheet("border-radius:40px;\
                                        border:5px solid red;\
                                        font-family:Microsoft YaHei UI; \
                                        font:bold;font-size:24px");

    disconnect(this->Button_connect,SIGNAL(clicked(bool)),this,SLOT(close_port()));
    connect(this->Button_connect,SIGNAL(clicked(bool)),this,SLOT(open_port()),Qt::UniqueConnection);
}


void Tab_main::close_port(QSerialPort::SerialPortError err)
{
    if(err != QSerialPort::NoError)
    {
        this->close_port();

        QMessageBox::critical(NULL, "错误", "打开串口失败", QMessageBox::Yes);
    }
}

void Tab_main::get_data()
{
    if(this->port->is_open())
    {
        qDebug()<<"GET";
        this->port->get_TM();
        this->port->get_WKC();
    }
}

QString str_format(QString str,int len)
{
    QString ret = str;
    int l = str.length();
    for (l;l<len;l++)
    {
        ret += " ";
    }
    return ret;
}
//extern str_format(QString ,int );

void Tab_main::record()
{
    this->serial_number = this->Line_number->text();
    if(this->serial_number.isEmpty())
    {
        QMessageBox::warning(NULL, "错误", "请输入编号！", QMessageBox::Yes);

        return;
    }

    if(this->Line_number_1->text().isEmpty())
    {
        this->Line_number_1->setText("0");
    }

    bool ok;
    int num = this->Line_number_1->text().toInt(&ok);
    if(!ok)
    {
        QMessageBox::warning(NULL, "错误", "序号必须为数字！", QMessageBox::Yes);
        return;
    }

    this->serial_number += "-";
    this->serial_number += this->Line_number_1->text();

    ++num;
    this->Line_number_1->setText(QString::number(num));
//    if(this->density == -9999)
//    {
//        return;
//    }

    this->serial_number = str_format(this->serial_number,16);

    QString str = "<"+this->serial_number+">";

    str += " ";
    this->ret_values[0] < -9 ? str += "--------":str += str_format(QString::number(this->ret_values[0],'g',8),8);

    str += " ";
    this->volume < 0 ? str += "--------":str += str_format(QString::number(this->volume,'g',8),8);

    str += " ";
    this->density < 0 ? str += "--------":str += str_format(QString::number(this->density,'g',8),8);

    for(int i=2;i<SHOW_ITEMS;i++)
    {
        str += " ";
        this->ret_values[i-1] < 0 ? str += "--------":str += str_format(QString::number(this->ret_values[i-1],'g',8),8);

    }
    this->Line_number->selectAll();
//    QMessageBox::information(NULL,tr("成功"),tr("数据记录成功！"));

    this->cfg->logging(str);
//    if(this->Check_auto_clear->isChecked())
//    {
//        this->Line_number->clear();
//    }
}
