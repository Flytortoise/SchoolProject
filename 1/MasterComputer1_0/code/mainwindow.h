#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "powerwidget.h"
#include "runwidget.h"
#include "voltagewidget.h"
#include "controlwidget.h"
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    PowerWidget *powerwidget;
    RunWidget *runwidget;
    VoltageWidget *voltagewidget;
    ControlWidget *controlwidget;

    QPushButton *exitButton;

    void CreateInit();
    void CreateLayout();
};

#endif // MAINWINDOW_H
