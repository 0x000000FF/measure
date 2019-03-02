#include "tab_para.h"



Tab_para::Tab_para(config *cfg,Show_items *all_items,QWidget *parent) : QWidget(parent)
{
    this->cfg = cfg;
    this->all_items = all_items;

    this->Group_setting = new QGroupBox();
    this->Group_setting->setMinimumSize(500,640);
    this->Group_setting->setMaximumSize(500,640);

    this->Group_img = new QGroupBox();
    this->Group_img->setMinimumSize(480,640);
    this->Group_img->setMaximumSize(480,640);

    this->Lable_img = new QLabel("没有图片");
    this->Lable_img->setAlignment(Qt::AlignCenter);
    this->Lable_img->setStyleSheet("background-color:gray;");
    this->Lable_img->setMinimumSize(IMG_WIDTH,IMG_HEIGHT);
    this->Lable_img->setMaximumSize(IMG_WIDTH,IMG_HEIGHT);

    this->Layout_setting = new QVBoxLayout;
    this->Layout_img = new QGridLayout;

    this->Group_item   = new QGroupBox();
    this->Layout_item = new QGridLayout;

//    this->Group_item->setMaximumSize(700,550);
//    this->Group_item->setMaximumSize(700,550);

    QLabel *Lable_num = new QLabel("编号");
    Lable_num->setMaximumHeight(24);
    this->Layout_item->addWidget(Lable_num,0,0);
    QLabel *Lable_name = new QLabel("名称");
    Lable_name->setMaximumHeight(24);
    this->Layout_item->addWidget(Lable_name,0,1);
    QLabel *Lable_unit = new QLabel("单位");
    Lable_unit->setMaximumHeight(24);
    this->Layout_item->addWidget(Lable_unit,0,2);
    QLabel *Lable_min = new QLabel("最小值");
    Lable_min->setMaximumHeight(24);
    this->Layout_item->addWidget(Lable_min,0,3);
    QLabel *Lable_max = new QLabel("最大值");
    Lable_max->setMaximumHeight(24);
    this->Layout_item->addWidget(Lable_max,0,4);

    this->Group_item->setLayout(Layout_item);
    this->Layout_setting->addWidget(Group_item);

    this->Group_formula = new QGroupBox();
    this->Layout_formula = new QHBoxLayout;
    this->Layout_setting->addLayout(this->Layout_formula);


    this->Layout_log = new QHBoxLayout;
    this->Lable_log = new QLabel("记录文件");
//    this->Button_log = new QPushButton("...");
//    this->Button_log->setMinimumSize(30,28);
//    this->Button_log->setMaximumSize(30,28);
//    this->Line_log = new QLineEdit();
//    this->Layout_log->addWidget(this->Lable_log);
//    this->Layout_log->addWidget(this->Line_log);
//    this->Layout_log->addWidget(this->Button_log);

    this->Button_power_off = new QPushButton("关机");
    this->Button_power_off->setMaximumSize(64,28);
    this->Button_power_off->setStyleSheet("QPushButton{\
                                              background-color:rgb(255,20,20); \
                                              color:rgb(0,0,0);\
                                              border-radius:5px;\
                                              border:3px solid white;\
                                              border-style:outset;}");

//    this->Group_serial = new QGroupBox();
//    this->Layout_serial = new QHBoxLayout;
//    this->Serial_MT = new QComboBox();
//    this->Serial_WKC = new QComboBox();
//    this->Lable_TM = new QLabel("TM-3000端口:");
//    this->Lable_TM->setMaximumWidth(100);
//    this->Lable_WKC = new QLabel("WKC端口:");
//    this->Lable_WKC->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
//    QStringList coms;
//    for(int i = 1;i<=30;i++)
//    {
//        coms.append("COM"+QString::number(i));
//    }
//    this->Serial_MT->addItems(coms);
//    this->Serial_WKC->addItems(coms);
//    this->Serial_MT->setCurrentText(this->cfg->serial_MT);
//    this->Serial_WKC->setCurrentText(this->cfg->serial_WKC);

    this->Group_buttons = new QGroupBox();
    this->Layout_buttons = new QHBoxLayout;

    this->Button_save = new QPushButton("保存");
    this->Button_save->setMaximumSize(80,36);
    this->Button_saveas = new QPushButton("另存");
    this->Button_saveas->setMaximumSize(80,36);
    this->Button_load = new QPushButton("载入");
    this->Button_load->setMaximumSize(80,36);
    this->Button_apply = new QPushButton("应用");
    this->Button_apply->setMaximumSize(80,36);

    this->Layout_buttons->addWidget(Button_save);
    this->Layout_buttons->addWidget(Button_saveas);
    this->Layout_buttons->addWidget(Button_load);
    this->Layout_buttons->addWidget(Button_apply);

    this->Layout_setting->addLayout(Layout_buttons);
    this->Group_setting->setLayout(Layout_setting);

//    this->Layout_img->addWidget(open_img);
    this->Group_img->setLayout(Layout_img);

    this->open_img = new QPushButton("更改图片");
    this->open_img->setMinimumSize(80,36);
    this->Line_img = new QLineEdit();
    this->Line_img->setMinimumSize(350,36);

    this->Lable_dec = new QLabel("密度位数:");
    this->Lable_dec->setMaximumSize(80,36);
    this->Lable_index = new QLabel("光幕编号:");
    this->Lable_index->setMaximumSize(80,36);
    this->Decimal = new QComboBox();
    this->Decimal->setMinimumSize(100,36);
    this->combo_index = new QComboBox();
    this->combo_index->setMinimumSize(100,36);

    for(int i = 0;i<5;i++)
    {
        this->Decimal->addItem(QString::number(i));
    }
    for(int i = 0;i<16;i++)
    {
        this->combo_index->addItem("PW,"+QString("%1").arg(i, 2, 10, QChar('0')));
    }

    this->Lable_formula = new QLabel("体积公式:");
    this->Text_formula = new QPlainTextEdit();
    this->Text_formula->setMinimumSize(350,90);
    this->Text_formula->setMaximumSize(350,90);

    this->Button_formula = new QPushButton("修改公式");
    this->Button_formula->setMinimumSize(80,36);

    this->Label_pswd = new QLabel("管理密码:");
    this->Line_pswd = new QLineEdit();
    this->Line_pswd->setMinimumSize(350,36);


    this->Button_keyboard = new QPushButton("键盘");
    this->Button_keyboard->setMinimumSize(80,36);
    this->Button_keyboard->setMaximumSize(80,36);

//this->Layout_img->set
    this->Layout_img->addWidget(this->Lable_img,0,1,4,4,Qt::AlignLeft);
    this->Layout_img->addWidget(this->Line_img,4,0,1,4,Qt::AlignCenter);
    this->Layout_img->addWidget(this->open_img,4,4,Qt::AlignCenter);
//    this->Layout_img->addWidget(this->Button_formula,5,4,Qt::AlignCenter);
    this->Layout_img->addWidget(this->Lable_dec,5,0,Qt::AlignCenter);
    this->Layout_img->addWidget(this->Decimal,5,1,1,4,Qt::AlignLeft);
    this->Layout_img->addWidget(this->Lable_index,6,0,Qt::AlignCenter);
    this->Layout_img->addWidget(this->combo_index,6,1,1,4,Qt::AlignLeft);
this->Layout_img->addWidget(this->Lable_formula,7,0,Qt::AlignCenter);
this->Layout_img->addWidget(this->Text_formula,7,1,1,4,Qt::AlignLeft);
    this->Layout_img->addWidget(this->Label_pswd,8,0,Qt::AlignCenter);
    this->Layout_img->addWidget(this->Line_pswd,8,1,1,4,Qt::AlignLeft);
    this->Layout_img->addWidget(this->Button_keyboard,9,4,Qt::AlignCenter);

    this->Layout_main = new QHBoxLayout;
    this->Layout_main->addWidget(Group_img);
    this->Layout_main->addWidget(Group_setting);
    this->Layout_main->addStretch(1);
    this->setLayout(Layout_main);

    for(int i = 0;i < SHOW_ITEMS;i++)
    {
//        this->items[i] = new item_show(this->cfg->all_items[i],i);
        this->Layout_item->setRowMinimumHeight(i,36);

        this->Layout_item->addWidget(this->all_items->item[i]->enable_setting,i+1,0);
        this->Layout_item->addWidget(this->all_items->item[i]->name_setting,i+1,1);
        this->Layout_item->addWidget(this->all_items->item[i]->unit_setting,i+1,2);
        this->Layout_item->addWidget(this->all_items->item[i]->min_setting,i+1,3);
        this->Layout_item->addWidget(this->all_items->item[i]->max_setting,i+1,4);


    }

    connect(this->open_img,SIGNAL(clicked(bool)),this,SLOT(on_open_img_clicked()));
    connect(this->Button_apply,SIGNAL(clicked(bool)),this,SLOT(on_Button_apply_clicked()));
    connect(this->Button_load,SIGNAL(clicked(bool)),this,SLOT(on_Button_load_clicked()));
    connect(this->Button_save,SIGNAL(clicked(bool)),this,SLOT(on_Button_save_clicked()));
    connect(this->Button_saveas,SIGNAL(clicked(bool)),this,SLOT(on_Button_saveas_clicked()));
//    connect(this->Button_log,SIGNAL(clicked(bool)),this,SLOT(set_log_path()));
//    connect(this->Button_power_off,SIGNAL(clicked(bool)),this,SLOT(on_Button_power_off_clicked()));
    connect(this->Button_keyboard,SIGNAL(clicked(bool)),this,SLOT(on_Button_keyboard_clicked()));
    connect(this->Button_formula,SIGNAL(clicked(bool)),this,SLOT(on_Button_formula_clicked()));
}

void Tab_para::load_config(config *cfg,Show_items *all_items)
{
    this->cfg = cfg;
    this->all_items = all_items;
    //image_path = QFileDialog::getOpenFileName(this,tr("选择图片"),"",tr("Images(*.png *.bmp *.jpg *.tif *.gif)"));
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
//            QMessageBox::information(this,tr("打开失败"),tr("打开图片失败！"));
            delete img;
        }
        this->Lable_img->setPixmap(QPixmap::fromImage(*img).scaled(IMG_WIDTH,IMG_HEIGHT,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    }
    for(int i = 0;i < SHOW_ITEMS;i++)
    {
        this->all_items->item[i]->reload_setting(this->cfg->all_items[i]);
    }
    this->Text_formula->setPlainText(cfg->formula);
    this->Line_img->setText(this->cfg->img_path);
    this->Line_pswd->setText(this->cfg->pswd);
    this->combo_index->setCurrentText(this->cfg->program_index);
}

void Tab_para::on_Button_formula_clicked()
{
    bool isOK;

//    QString formula = QInputDialog::getText(NULL,tr("密码验证"),tr("请输入密码:"),QPlainTextEdit::Panel,"",&isOK);
//    QInputDialog *input = new QInputDialog();
//    input->resize(800,600);
//    input->
//    input->show();


}

void Tab_para::on_Button_keyboard_clicked()
{
    PVOID OldValue;
    BOOL bRet = Wow64DisableWow64FsRedirection (&OldValue);
    QString csProcess="C:\\Windows\\System32\\osk.exe";
    csProcess="C:\\Program Files\\Common Files\\microsoft shared\\ink\\TabTip.exe";
    QString params="";
    ShellExecute(NULL, L"open", (LPCWSTR)csProcess.utf16(), (LPCWSTR)params.utf16(), NULL, SW_SHOWNORMAL);
    if ( bRet )
    {
        Wow64RevertWow64FsRedirection(OldValue);
    }
}

void Tab_para::sync_setting()
{
    this->cfg->formula = this->Text_formula->toPlainText();
//    this->cfg->serial_MT = this->Serial_MT->currentText();
//    this->cfg->serial_WKC = this->Serial_WKC->currentText();

//    this->cfg->log_path = this->Line_log->text();
    this->cfg->img_path = this->Line_img->text();
    this->cfg->pswd = this->Line_pswd->text();
    this->cfg->program_index = this->combo_index->currentText();
    this->cfg->decimal = this->Decimal->currentText().toInt();

    for(int i = 0;i < SHOW_ITEMS;i++)
    {
        this->all_items->item[i]->sync_setting();

        this->all_items->item[i]->reload_main(this->cfg->all_items[i]);
        this->all_items->item[i]->reload_setting(this->cfg->all_items[i]);
    }
    emit(this->cfg_changed());
}

void Tab_para::on_open_img_clicked()
{
    QString image_path = "";
    image_path = QFileDialog::getOpenFileName(this,tr("选择图片"),"",tr("Images(*.png *.bmp *.jpg *.tif *.gif)"));

    if(image_path.isEmpty())
    {
        return;
    }
    else
    {
        QImage * img = new QImage;
        if(!(img->load(image_path)))
        {
            QMessageBox::information(NULL,tr("打开失败"),tr("打开图片失败！"));
            delete img;
            return;
        }
        this->Lable_img->setPixmap(QPixmap::fromImage(*img).scaled(IMG_WIDTH,IMG_HEIGHT,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        this->Line_img->setText(image_path);
    }
}

void Tab_para::on_Button_save_clicked()
{
    this->sync_setting();

    this->cfg->save_ini(this->cfg->ini_path);

    qDebug()<<"saved";
}

void Tab_para::on_Button_saveas_clicked()
{
    QString dir = QFileDialog::getSaveFileName(this,tr("选择文件"),"",tr("配置(*.ini)"));
    qDebug()<<dir;

    this->sync_setting();

    this->cfg->save_ini(dir);
}

void Tab_para::on_Button_apply_clicked()
{
    this->sync_setting();

    this->cfg->save_ini();
}


void Tab_para::on_Button_load_clicked()
{
    QString path = "";
    path = QFileDialog::getOpenFileName(this,tr("选择文件"),"",tr("配置(*.ini)"));

    if(path.isEmpty())
    {
        return;
    }
    else
    {
        this->cfg->ini_path = path;
        this->cfg->load_ini(path);
//        this->sync_setting();
        for(int i = 0;i < SHOW_ITEMS;i++)
        {
            this->all_items->item[i]->reload_main(this->cfg->all_items[i]);
            this->all_items->item[i]->reload_setting(this->cfg->all_items[i]);
        }

        emit(this->cfg_changed());
//        this->Group_item->setTitle(path);
    }
}

void Tab_para::set_log_path()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                      ".//",
                                                   QFileDialog::ShowDirsOnly
                                                      | QFileDialog::DontResolveSymlinks);

    this->cfg->log_path = QString::fromLocal8Bit(dir.toLatin1().constData());
//    this->Line_log->setText(dir);
    this->cfg->log_path=dir;
//    this->cfg->save_ini();
}
