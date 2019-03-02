#include "input.h"

input::input()
{
//    QDialog *dialog = new QDialog(this);
//    dialog->resize(800,600);
//    dialog->setWindowTitle("请输入公式");
//    QVBoxLayout *lay = new QVBoxLayout;
//    dialog->setLayout(lay);
//    this->mytext = new QPlainTextEdit();
//    this->mytext->setStyleSheet("background-color:rgb(135,206,255);\
//                            font-family:Microsoft YaHei UI; \
//                            font:bold;\
//                            font-size:20px");
//    lay->addWidget(this->mytext);
//    QPushButton *btn = new QPushButton("确定");
//    btn->setMaximumSize(80,36);
//    btn->setMinimumSize(80,36);
//    lay->addWidget(btn);

//    connect(btn,SIGNAL(clicked(bool)),this,SLOT(quit()));
//    dialog->show();
}

void input::quit()
{
    this->deleteLater();
}

QString input::get_text()
{
//    return (this->text);
}
