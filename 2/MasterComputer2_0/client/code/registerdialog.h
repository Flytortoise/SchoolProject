#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>



class RegisterDialog : public QDialog
{
    Q_OBJECT
public:
    explicit RegisterDialog(QWidget *parent = 0);
signals:

public slots:

private:
    void CreateInit();
    void CreateLayout();

private:
    QLabel *UserNameLabel;
    QLabel *PassWdLabel1;
    QLabel *PassWdLabel2;
    QLineEdit *UserNameLineEdit;
    QLineEdit *PassWdLineEdit1;
    QLineEdit *PassWdLineEdit2;

    QPushButton *OkBtn;

};

#endif // REGISTERDIALOG_H
