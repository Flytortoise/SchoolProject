/*
 * 点动控制界面，包含+X，-X，+Y，-Y，+Z，-Z，+PZT，-PZT
*/

#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class ControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlWidget(QWidget *parent = 0);

signals:

public slots:

private:
    QPushButton *xPlus;
    QPushButton *xSub;
    QPushButton *yPlus;
    QPushButton *ySub;
    QPushButton *zPlus;
    QPushButton *zSub;
    QPushButton *pztPlus;
    QPushButton *pztSub;

    QLabel *TittleLable;    //标题

    void CreateInit();
    void CreateLayout();

};

#endif // CONTROLWIDGET_H
