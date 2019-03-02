#include "config.h"
#include <QDebug>
#include <QMessageBox>
#include <QDate>
#include <QTime>



QString string_format(QString str,int len)
{
    QString ret = str;
    int l = str.length();
    for (l;l<len;l++)
    {
        ret += " ";
    }
    return ret;
}



config::config()
{
    this->ini_path = DEF_SETTING;
}

config::~config()
{
    if(this->log_file->isOpen())
    {
        this->log_file->close();
    }
}

int config::load_ini(QString path)
{
    QFile *f = new QFile(path);
    if(!f->exists())
    {
        QMessageBox::warning(NULL, "警告", "无法载入默认配置", QMessageBox::Yes, QMessageBox::Yes);
//        return -1;
    }

    this->setting_pass = new QSettings(PASSWD,QSettings::IniFormat);
    this->pswd = setting_pass->value("/info/password").toString();
qDebug()<<this->pswd;
    this->ini_path = path;

    this->setting = new QSettings(path,QSettings::IniFormat);

    this->setting->setIniCodec(QTextCodec::codecForName("UTF-8"));

    this->decimal = this->setting->value("/info/decimal").toInt();
    this->program_index = this->setting->value("/info/program").toString();
    this->img_path = this->setting->value("/info/img").toString();
    this->log_path = this->setting->value("/info/log").toString();
    this->formula = this->setting->value("/info/formula").toString();
    this->items_sum = this->setting->value("/info/items").toInt();
    this->serial_MT = this->setting->value("/info/serial_MT").toString();
    this->serial_WKC = this->setting->value("/info/serial_WKC").toString();

    QString log_name = QDate().currentDate().toString("yyyy-MM-dd");
    qDebug()<<this->setting->allKeys();

    QDir dir(this->log_path);
    if(!dir.exists())
    {
        QMessageBox::warning(NULL, "警告", "路径无效", QMessageBox::Yes, QMessageBox::Yes,QIODevice::Unbuffered);
        this->log_path = ".";
    }

    this->log_file = new QFile(this->log_path+"/"+log_name+".txt");
    if(!this->log_file->open(QIODevice::Append | QIODevice::Text))
    {
        QMessageBox::warning(NULL, "警告", "路径无效", QMessageBox::Yes, QMessageBox::Yes,QIODevice::Unbuffered);
    }


    this->log_stream = new QTextStream(this->log_file);
    QString str = "编号";
    str = string_format(str,16);
    *(this->log_stream)<<str;

    for(int i = 0;i < SHOW_ITEMS;i++)
    {       
        QString tmp;
        if(i == 0)
        {
            this->all_items[i] = new item('W');
            this->all_items[i]->name = "重量";
            this->all_items[i]->enable = 1;
        }
        else if(i == 1)
        {
            this->all_items[i] = new item('D');
            this->all_items[i]->name = "密度";
            this->all_items[i]->enable = 1;
        }
        else
        {
            this->all_items[i] = new item('L');
            this->all_items[i]->name = this->setting->value("/item"+QString::number(i)+"/name").toString();
            this->all_items[i]->enable = this->setting->value("/item"+QString::number(i)+"/enable").toInt();
        }

        this->all_items[i]->unit = QString::fromLocal8Bit(this->setting->value("/item"+QString::number(i)+"/unit").toByteArray());
        this->all_items[i]->min = this->setting->value("/item"+QString::number(i)+"/min").toDouble();
        this->all_items[i]->max = this->setting->value("/item"+QString::number(i)+"/max").toDouble();
        this->all_items[i]->value = (this->all_items[i]->max + this->all_items[i]->min)/2.0;

        tmp = this->all_items[i]->name;
        tmp += "(";
        tmp += this->all_items[i]->unit;
        tmp += ")";

        tmp = string_format(tmp,9);
        *(this->log_stream)<<tmp;
    }
    *(this->log_stream)<<endl;
}

int config::load_ini()
{
    this->load_ini(DEF_SETTING);
}

void config::logging(QString str)
{
//    QString now = QTime().currentTime().toString("hh:mm:ss");
    *(this->log_stream)<<str<<endl;
}

int config::save_ini(QString path)
{
    this->ini_path = path;

//    QFile *f = new QFile(path);
//    this->log_file->open(QIODevice::WriteOnly);
//    f->close();

//    this->setting->clear();
    this->setting = new QSettings(path,QSettings::IniFormat);

    this->setting_pass->setValue("/info/password",this->pswd);

    this->setting->setValue("/info/program",this->program_index);
    this->setting->setValue("/info/decimal",this->decimal);
    this->setting->setValue("/info/log",this->log_path);
    this->setting->setValue("/info/img",this->img_path);
    this->setting->setValue("/info/formula",this->formula);
    this->setting->setValue("/info/items",this->items_sum);
    this->setting->setValue("/info/serial_MT",this->serial_MT);
    this->setting->setValue("/info/serial_WKC",this->serial_WKC);

    QString item_node;
    for(int i = 0;i < SHOW_ITEMS;i++)
    {
        item_node = "item"+QString::number(i);

        this->setting->setValue(item_node+"/enable",this->all_items[i]->enable);
        this->setting->setValue(item_node+"/name",this->all_items[i]->name);
        this->setting->setValue(item_node+"/unit",this->all_items[i]->unit);
        this->setting->setValue(item_node+"/min",this->all_items[i]->min);
        this->setting->setValue(item_node+"/max",this->all_items[i]->max);
    }

    this->setting->sync();
    return 0;
}

int config::save_ini()
{
    this->save_ini(DEF_SETTING);
}
