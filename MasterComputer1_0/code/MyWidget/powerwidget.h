#ifndef POWERWIDGET_H
#define POWERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class PowerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PowerWidget(QWidget *parent = 0);

signals:

public slots:

private:
    QLabel *PulseWidthLable;
    QLabel *PulseRateLabel;
    QLabel *PowerLabel;
    QLabel *PowerCheckLabel;
    QLineEdit *PulseWidthEidt;
    QLineEdit *PulseRateEdit;
    QLineEdit *PowerEdit;
    QLineEdit *PowerCheckEdit;
    QPushButton *setOk;

    QLabel *TittleLabel;

    void CreateInit();
    void CreateLayout();

};

#endif // POWERWIDGET_H
