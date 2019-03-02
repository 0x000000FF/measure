#ifndef INPUT_H
#define INPUT_H

#include <QObject>
#include <QString>

class input:public QObject
{
    Q_OBJECT
public:
    input();

    QString get_text();
private:
//    QPlainTextEdit *mytext;
public slots:
    void quit();
};

#endif // INPUT_H
