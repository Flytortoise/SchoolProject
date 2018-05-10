#ifndef PROMPTMESSAGE_H
#define PROMPTMESSAGE_H

#include <QDialog>
#include <QLabel>

//串口发送信息时的提示窗口

class PromptMessage : public QDialog
{
    Q_OBJECT
public:
    PromptMessage(QWidget *parent = 0);

private:
    void CreateInit();
    void CreateLayout();

    QLabel *MessageLabel;

};

#endif // PROMPTMESSAGE_H
