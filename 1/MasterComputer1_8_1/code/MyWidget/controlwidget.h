/*
 * 点动控制界面，包含+X，-X，+Y，-Y，+Z，-Z，+PZT，-PZT
*/

#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QByteArray>
#include <QVector>

class ControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlWidget(QWidget *parent = 0);
    void HideButton();
    void ShowButton();

signals:
    void ConToCom(QByteArray);

public slots:

private:
    QVector<QPushButton *> AllButton;
 /*   QPushButton *xPlus;
    QPushButton *xSub;
    QPushButton *yPlus;
    QPushButton *ySub;
    QPushButton *zPlus;
    QPushButton *zSub;
    QPushButton *pztPlus;
    QPushButton *pztSub;
*/
    QLabel *TittleLable;    //标题

    QByteArray *m_condata;  //传输的数据

    void CreateInit();
    void CreateLayout();

private slots:
    void HandleXPlusData();
    void HandleXSubData();
    void HandleYPlusData();
    void HandleYSubData();
    void HandleZPlusData();
    void HandleZSubData();
    void HandlePZTPlusData();
    void HandlePZTSubData();

};

#endif // CONTROLWIDGET_H
