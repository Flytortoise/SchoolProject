#include "socketwidget.h"
#include "logwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SocketWidget w1;
   // LogWidget w2;
    w1.show();
   // w2.show();

    return a.exec();
}
