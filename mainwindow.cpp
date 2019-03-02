#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "config.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QGroupBox * Group_box_item[MAX_ITEMS];
    QLineEdit * Line_edit_name[MAX_ITEMS];
    QLineEdit * Line_edit_unit[MAX_ITEMS];
    QLineEdit * Line_edit_min[MAX_ITEMS];
    QLineEdit * Line_edit_max[MAX_ITEMS];

//    QHBoxLayout *layout = new QHBoxLayout;

    ui->groupBox_setting = new QGroupBox(tr("setting"));

    for(int i = 0;i < MAX_ITEMS;i++)
    {
        Group_box_item[i] = new QGroupBox(tr("groupbox%1").arg(i+1));
//        Group_box_item[i]->show();
//        ui->Items_Layout->addWidget(Group_box_item[i],0,0);
//        ui->Items_Layout->addWidget(Group_box_item[i]);
//        ui->groupBox_setting->setLayout(ui->Items_Layout);
    }
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}
