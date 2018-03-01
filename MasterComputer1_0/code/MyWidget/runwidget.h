#ifndef RUNWIDGET_H
#define RUNWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPushButton>

class RunWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RunWidget(QWidget *parent = 0);

signals:

public slots:

private:
    enum {
        mmSize = 6,
        mm_sSize = 3,
        umSize = 2,
        setSizeData = 4,
        speedSizeData = 3
    };

    QLabel *xLocationLabel;
    QLabel *yLocationLabel;
    QLabel *zLocationLabel;
    QLabel *pztLocationLabel;
    QLabel *setLabel[setSizeData];
    QLabel *speedLabel[speedSizeData];
    QLabel *mmUnitLabel[mmSize];
    QLabel *mm_sUnitLabel[mm_sSize];
    QLabel *umUnitLabel[umSize];

    QLineEdit *xLocationEdit;
    QLineEdit *yLocationEdit;
    QLineEdit *zLocationEdit;
    QLineEdit *pztLocationEdit;
    QLineEdit *setEdit[setSizeData];
    QLineEdit *speedEdit[speedSizeData];

    QPushButton *setOk;

    QLabel *TittleLabel;

    void CreateInit();  //初始化控件
    void CreateLayout();    //布局

};

#endif // RUNWIDGET_H











