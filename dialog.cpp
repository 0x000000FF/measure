#include "dialog.h"
#include <QtWidgets>
#include "config.h"
#include <QDebug>
#include <QTextCodec>
#include <QStringList>
#include "sys.h"

Show_items::Show_items(config* cfg)
{
    this->cfg = cfg;

    for(int i = 0;i < SHOW_ITEMS;i++)
    {
        if(i < 2)
        {
            this->item[i] = new item_show(this->cfg->all_items[i],i-1,"cir");

        }
        else
        {
            this->item[i] = new item_show(this->cfg->all_items[i],i-1,"rec");
        }
    }
}

TabDialog::TabDialog(config* cfg,QWidget *parent): QDialog(parent)
{
    QString sty = "*{\
                    background-color:rgb(135,206,250);\
                    font-family:Microsoft YaHei UI; \
                    font:normal;\
                    font-size:14px;}\
                QTabBar::tab{\
                    background-color:rgb(155,226,250);} \
                QTabBar::tab::selected{\
                    background-color:rgb(135,206,250);} \
                QDialog{\
                    background-color:rgb(30,144,255);\
                    border-radius:5px;\
                    border:3px solid white;\
                    border-style:outset;} \
                QPushButton{\
                    background-color:rgb(188,210,238); \
                    color:rgb(0,0,0);\
                    border-radius:5px;\
                    border:3px solid white;\
                    border-style:outset;}\
                QPushButton:hover{\
                    background-color:rgb(108,166,205);}\
                QPushButton:pressed{\
                    border:3px solid gray;}\
                QPushButton:disabled{\
                    color:rgb(160,160,160);\
                    background-color:rgb(188,210,238)}\
                QGroupBox{\
                    border-radius:5px;\
                    border:3px solid white;\
                    border-style:inset;}\
                QLineEdit{\
                    background-color:rgb(70,130,180);\
                    border-radius:5px;\
                    border:3px solid white;\
                    border-style:inset;}\
                QLineEdit:disabled{\
                    background-color:rgb(135,206,255);\
                    border-radius:5px;\
                    border:3px solid white;\
                    border-style:inset;}\
                QPlainTextEdit{\
                    background-color:rgb(70,130,180);\
                    border-radius:5px;\
                    border:3px solid white;\
                    border-style:inset;}\
                QLabel{}\
                QComboBox{\
                    background-color:rgb(70,130,180);\
                    border-radius:5px;\
                    border:3px solid white;\
                    border-style:inset;}\
                QComboBox:disabled{\
                    background-color:rgb(135,206,255);\
                    border-radius:5px;\
                    border:3px solid white;\
                    border-style:inset;}\
                QDoubleSpinBox{\
                    background-color:rgb(70,130,180);\
                    border-radius:5px;\
                    border:3px solid white;\
                    border-style:inset;}\
                QDoubleSpinBox:disabled{\
                    background-color:rgb(135,206,255);\
                    border-radius:5px;\
                    border:3px solid white;\
                    border-style:inset;}\
                    ";
    this->setStyleSheet(sty);

    this->cfg = cfg;

    this->all_items = new Show_items(this->cfg);

    tabWidget = new QTabWidget;
    tabWidget->resize(WIN_WIDTH-20,WIN_HEIGHT-20);
    tabWidget->setMinimumSize(WIN_WIDTH-20,WIN_HEIGHT-80);
    tabWidget->setMaximumSize(WIN_WIDTH-20,WIN_HEIGHT-80);
    this->main_tab = new Tab_main(this->cfg,this->all_items);
//    this->main_tab->setMinimumSize(WIN_WIDTH-20,WIN_HEIGHT-150);
//    this->main_tab->setMaximumSize(WIN_WIDTH-20,WIN_HEIGHT-150);
    this->para_tab = new Tab_para(this->cfg,this->all_items);
//    this->para_tab->setMinimumSize(WIN_WIDTH-20,WIN_HEIGHT-150);
//    this->para_tab->setMaximumSize(WIN_WIDTH-20,WIN_HEIGHT-150);
    this->setting_tab = new Tab_setting(this->cfg);
//    this->setting_tab->setMinimumSize(WIN_WIDTH-20,WIN_HEIGHT-150);
//    this->setting_tab->setMaximumSize(WIN_WIDTH-20,WIN_HEIGHT-150);

    this->main_tab->Line_number->installEventFilter(this);
    this->main_tab->Line_number_1->installEventFilter(this);
//    this->para_tab->Text_formula->installEventFilter(this);
//    this->para_tab->Line_img->installEventFilter(this);
//    this->para_tab->Line_log->installEventFilter(this);

//    for (int i = 0;i < SHOW_ITEMS; i++)
//    {
//        this->para_tab->all_items->item[i]->name_setting->installEventFilter(this);
//        this->para_tab->all_items->item[i]->unit_setting->installEventFilter(this);
//        this->para_tab->all_items->item[i]->min_setting->installEventFilter(this);
//        this->para_tab->all_items->item[i]->max_setting->installEventFilter(this);
//    }

    tabWidget->addTab(this->main_tab, tr("测量"));
    tabWidget->addTab(this->setting_tab, tr("配置"));
    tabWidget->addTab(this->para_tab, tr("参数"));

    QVBoxLayout *Layout_main = new QVBoxLayout;

    QLabel *Lable_logo = new QLabel();
    Lable_logo->setMaximumSize(1000,46);
    QString image_path = QCoreApplication::applicationDirPath() + "//logo.jpg";
    qDebug()<<image_path;
    if(image_path.isEmpty())
    {
//        return;
    }
    else
    {
        QImage * img = new QImage;
        if(!(img->load(image_path)))
        {

        }
        else
        {
            Lable_logo->setPixmap(QPixmap::fromImage(*img).scaled(1000,46,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        }
    }
    Layout_main->setSpacing(0);
    Layout_main->setStretch(0,0);
    Layout_main->setStretch(1,0);
    Layout_main->addWidget(Lable_logo,Qt::AlignTop);
    Layout_main->addWidget(tabWidget,Qt::AlignTop);
    this->setLayout(Layout_main);

    this->sys_func = new sys();

    connect(this->setting_tab,SIGNAL(s_power_off()),this->sys_func,SLOT(power_off()));
    connect(this->setting_tab,SIGNAL(cfg_changed()),this,SLOT(reload()));
    connect(this->para_tab,SIGNAL(cfg_changed()),this,SLOT(reload()));
    connect(this->para_tab,SIGNAL(load()),this->sys_func,SLOT(load()));
    connect(this->para_tab,SIGNAL(save()),this->sys_func,SLOT(save()));
    connect(this->para_tab,SIGNAL(apply()),this->sys_func,SLOT(apply()));
    connect(this->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(check_pswd(int)));

    setWindowTitle(tr("化工材料研究所"));
    setWindowState(Qt::WindowFullScreen);
    setWindowIcon(QIcon());

    this->reload();
}

void TabDialog::check_pswd(int i)
{
    if(i == 2)
    {
        bool isOK;
        this->para_tab->hide();
        this->sys_func->call_keyboard();

        QString pswd = QInputDialog::getText(NULL,tr("密码验证"),tr("请输入密码:"),QLineEdit::Password,"",&isOK);

        if(isOK)
        {
            if (pswd == this->cfg->pswd)
            {
                this->para_tab->show();
            }
            else
            {
                QMessageBox::warning(NULL,"密码错误","你输入的密码有误!",QMessageBox::Cancel);
            }
        }
    }
}

bool TabDialog::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        emit (s_keyboard());
    }
    return QWidget::eventFilter(watched,event);
}

void TabDialog::reload()
{
    this->main_tab->load_config(this->cfg,this->all_items);
    this->para_tab->load_config(this->cfg,this->all_items);
    this->setting_tab->load_config(this->cfg);
}
