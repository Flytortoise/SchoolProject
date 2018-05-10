#ifndef PROCESSWIDGET_H
#define PROCESSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class ProcessWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProcessWidget(QWidget *parent = nullptr);
    void HideButton();
    void ShowButton();

signals:
    void SendProcessData(bool);

public slots:

private:
    void CreateInit();
    void CreateLayout();

private:
    //QLabel *TittleLabel;
    QPushButton *BeginBtn;
    QPushButton *EndBtn;
};

#endif // PROCESSWIDGET_H
