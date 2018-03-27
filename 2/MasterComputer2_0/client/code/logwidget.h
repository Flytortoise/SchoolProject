#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "registerdialog.h"

class LogWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LogWidget(QWidget *parent = 0);

signals:

public slots:

private:
    void CreateInit();
    void CreateLayout();

private:
    QLabel *UserNameLabel;
    QLineEdit *UserNameLineEdit;
    QLabel *PassWdLabel;
    QLineEdit *PassWdLineEdit;
    QPushButton *OkBtn;

    QPushButton *RegisterBtn;
    RegisterDialog *m_RegisterDialog;

};

#endif // LOGWIDGET_H
