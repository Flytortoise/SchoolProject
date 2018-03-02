/*
 *串口调试窗口
 */

#ifndef COMPORTWIDGET_H
#define COMPORTWIDGET_H


#include <QWidget>
#include <QLabel>
#include <QTextEdit>    //文编编辑框
#include <QPushButton>  //按钮
#include <QComboBox>    //下拉框
#include <QCheckBox>    //复选框

class ComPortWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ComPortWidget(QWidget *parent = 0);

signals:

public slots:
     void MySendData();

private slots:
    void MyOpenCom();
    void MyCloseCom();
    void MyClearText();

private:
   // QLabel *TittleLabel;
    QLabel *RecvDataLable;
    QLabel *SendDataLabel;
    QLabel *SelectComLabel;
    QLabel *SelectBPSLabel;

    QPushButton *OpenComButton;
    QPushButton *CloseComButton;
    QPushButton *SendDataButton;
    QPushButton *ClearTextButton;

    QComboBox *SelectComComboBox;
    QComboBox *SelectBPSComboBox;

    QCheckBox *RecvHexShowCheckBox;
    QCheckBox *SendHexShowCheckBox;

    QTextEdit *RecvDataTextEdit;
    QTextEdit *SendDataTextEdit;

    void CreateInit();
    void CreateLayout();

};

#endif // COMPORTWIDGET_H
