/*
 * 极间电压
*/
#ifndef VOLTAGEWIDGET_H
#define VOLTAGEWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>

class VoltageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VoltageWidget(QWidget *parent = 0);

signals:

public slots:

private:
    QLineEdit *voltageInput;
    QLineEdit *voltageOutput;

    QLabel *TittleLabel;

    void CreateInit();
    void CreateLayout();
};

#endif // VOLTAGEWIDGET_H
