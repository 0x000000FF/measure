#include <QApplication>
#include "dialog.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setAutoSipEnabled(true);

    config *mycof = new config();
    mycof->load_ini();

    TabDialog * window = new TabDialog(mycof);
    window->show();


//    serial * device = new serial();

//    device->start_timer();

//    calculator *cal = new calculator();

//    cal->set_exp("2+123*2+45/3.12-111");
//    cal->do_cal();

    return app.exec();
}
