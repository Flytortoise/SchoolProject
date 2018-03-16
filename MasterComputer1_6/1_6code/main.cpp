#include "mainwindow.h"
#include <QApplication>
#include "transmitdata.h"
#include <QMetaType>

void mainInit()
{
    qRegisterMetaType<HandleToComData>("HandleToComData");
    qRegisterMetaType<ComToRunData>("ComToRunData");
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    mainInit();

    MainWindow w;
    w.show();

    return a.exec();
}
