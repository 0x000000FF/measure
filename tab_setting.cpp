#include "tab_setting.h"


Tab_setting::Tab_setting(config *cfg,QWidget *parent) : QWidget(parent)
{
    this->cfg = cfg;

    this->Layout_main = new QGridLayout;
    this->setLayout(this->Layout_main);

    this->Lable_log = new QLabel("记录文件:");
    this->Lable_log->setStyleSheet("font-family:Microsoft YaHei UI; \
                                        font:bold;font-size:24px");

    this->Line_log = new QLineEdit();
    this->Line_log->setMinimumSize(300,40);
    this->Button_log = new QPushButton("选择路径");
    this->Button_log->setMinimumSize(160,40);
    this->Button_log->setStyleSheet("font-family:Microsoft YaHei UI; \
                                        font:bold;font-size:20px");
    this->Button_apply = new QPushButton("载入配置");
    this->Button_apply->setMinimumSize(160,40);
    this->Button_apply->setStyleSheet("font-family:Microsoft YaHei UI; \
                                        font:bold;font-size:20px");
    this->Button_power_off = new QPushButton("关机");
    this->Button_apply->setMaximumSize(120,30);
    this->Button_power_off->setStyleSheet("background-color:rgb(255,20,20);\
                                          font-family:Microsoft YaHei UI; \
                                        font:bold;font-size:20px");

    this->Lable_img = new QLabel("没有图片");
    this->Lable_img->setAlignment(Qt::AlignCenter);
    this->Lable_img->setStyleSheet("background-color:gray");
    this->Lable_img->setMinimumSize(IMG_WIDTH,IMG_HEIGHT);
    this->Lable_img->setMaximumSize(IMG_WIDTH,IMG_HEIGHT);

    this->Layout_main->addWidget(this->Lable_img,0,2,1,4);
    this->Layout_main->addWidget(this->Lable_log,1,0,Qt::AlignCenter);
    this->Layout_main->addWidget(this->Line_log,1,1,1,4);
    this->Layout_main->addWidget(this->Button_log,1,5);
    this->Layout_main->addWidget(this->Button_apply,2,1);
    this->Layout_main->addWidget(this->Button_power_off,2,4);

    connect(this->Button_power_off,SIGNAL(clicked(bool)),this,SIGNAL(s_power_off()));

    connect(this->Button_log,SIGNAL(clicked(bool)),this,SLOT(set_log_path()));
    connect(this->Button_apply,SIGNAL(clicked(bool)),this,SLOT(on_Button_load_clicked()));
}

void Tab_setting::load_config(config *cfg)
{
    this->cfg = cfg;

    QString image_path = cfg->img_path;
    this->Line_log->setText(this->cfg->log_path);

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
}

void Tab_setting::on_Button_load_clicked()
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
        emit(this->cfg_changed());
    }
}


void Tab_setting::set_log_path()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                      ".//",
                                                   QFileDialog::ShowDirsOnly
                                                      | QFileDialog::DontResolveSymlinks);

    this->cfg->log_path = QString::fromLocal8Bit(dir.toLatin1().constData());
    this->Line_log->setText(dir);
    this->cfg->log_path = dir;
    this->cfg->save_ini();
}
