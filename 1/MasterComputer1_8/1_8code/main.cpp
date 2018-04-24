#include "mainwindow.h"
#include <QApplication>
#include "promptmessage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
  //  ComPortWidget w;
   // PromptMessage w;
    w.show();

    return a.exec();
}
