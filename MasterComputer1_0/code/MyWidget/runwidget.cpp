#include "runwidget.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <QGridLayout>

RunWidget::RunWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle(tr("运动设置"));

    CreateInit();
    CreateLayout();


}

void RunWidget::CreateInit()
{
    QRegExp regexp("[0-9]{0,2}");

    xLocationLabel = new QLabel(tr("X坐标:"));
    xLocationEdit = new QLineEdit;
    xLocationEdit->setText(tr("0"));
    xLocationEdit->setReadOnly(true);
    xLocationEdit->setEnabled(false);
    xLocationLabel->setBuddy(xLocationEdit);

    yLocationLabel = new QLabel(tr("Y坐标:"));
    yLocationEdit = new QLineEdit;
    yLocationEdit->setText(tr("0"));
    yLocationEdit->setReadOnly(true);
    yLocationEdit->setEnabled(false);
    yLocationLabel->setBuddy(yLocationEdit);

    zLocationLabel = new QLabel(tr("Z坐标:"));
    zLocationEdit = new QLineEdit;
    zLocationEdit->setText(tr("0"));
    zLocationEdit->setReadOnly(true);
    zLocationEdit->setEnabled(false);
    zLocationLabel->setBuddy(zLocationEdit);

    pztLocationLabel = new QLabel(tr("PZT坐标:"));
    pztLocationEdit = new QLineEdit;
    pztLocationEdit->setText(tr("0"));
    pztLocationEdit->setReadOnly(true);
    pztLocationEdit->setEnabled(false);
    pztLocationLabel->setBuddy(pztLocationEdit);

    for(int i = 0 ; i < setSizeData; i++)
    {
        setLabel[i] = new QLabel(tr("设定:"));
        setEdit[i] = new QLineEdit;
        setEdit[i]->setText(tr("0"));
        setEdit[i]->setValidator(new QRegExpValidator(regexp, this));
        setLabel[i]->setBuddy(setEdit[i]);
    }

    for(int i = 0; i < speedSizeData; i++)
    {
        speedLabel[i] = new QLabel(tr("速度:"));
        speedEdit[i] = new QLineEdit;
        speedEdit[i]->setText(tr("0"));
        speedEdit[i]->setValidator(new QRegExpValidator(regexp, this));
        speedLabel[i]->setBuddy(speedEdit[i]);

    }

    for(int i = 0; i < mmSize; i++)
        mmUnitLabel[i] = new QLabel(tr("mm"));

    for(int i = 0; i < mm_sSize; i++)
        mm_sUnitLabel[i] = new QLabel(tr("mm/s"));

    for(int i = 0; i < umSize; i++)
        umUnitLabel[i] = new QLabel(tr("um"));

    setOk = new QPushButton(tr("参数设定"));
    TittleLabel = new QLabel(tr("运动设定:"));
}

void RunWidget::CreateLayout()
{
    int mmIndex, mm_sIndex, umIndex;
    int setLabelIndex, speedLabelIndex;
    int setEditIndex, speedEditIndex;
    mmIndex = mm_sIndex = umIndex = 0;
    setLabelIndex = speedLabelIndex = 0;
    setEditIndex = speedEditIndex = 0;


    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setHorizontalSpacing(10);
    mainLayout->setVerticalSpacing(10);
    mainLayout->addWidget(TittleLabel, 0, 0);
    mainLayout->addWidget(xLocationLabel, 1, 0);
    mainLayout->addWidget(xLocationEdit, 1, 1, 1, 2);
    mainLayout->addWidget(mmUnitLabel[mmIndex++], 1, 3);
    mainLayout->addWidget(setLabel[setLabelIndex++], 1, 4);
    mainLayout->addWidget(setEdit[setEditIndex++], 1, 5, 1, 2);
    mainLayout->addWidget(mmUnitLabel[mmIndex++], 1, 7);
    mainLayout->addWidget(speedLabel[speedLabelIndex++], 1, 8);
    mainLayout->addWidget(speedEdit[speedEditIndex++], 1, 9, 1, 2);
    mainLayout->addWidget(mm_sUnitLabel[mm_sIndex++], 1, 11);

    mainLayout->addWidget(yLocationLabel, 2, 0);
    mainLayout->addWidget(yLocationEdit, 2, 1, 1, 2);
    mainLayout->addWidget(mmUnitLabel[mmIndex++], 2, 3);
    mainLayout->addWidget(setLabel[setLabelIndex++], 2, 4);
    mainLayout->addWidget(setEdit[setEditIndex++], 2, 5, 1, 2);
    mainLayout->addWidget(mmUnitLabel[mmIndex++], 2, 7);
    mainLayout->addWidget(speedLabel[speedLabelIndex++], 2, 8);
    mainLayout->addWidget(speedEdit[speedEditIndex++], 2, 9, 1, 2);
    mainLayout->addWidget(mm_sUnitLabel[mm_sIndex++], 2, 11);

    mainLayout->addWidget(zLocationLabel, 3, 0);
    mainLayout->addWidget(zLocationEdit, 3, 1, 1, 2);
    mainLayout->addWidget(mmUnitLabel[mmIndex++], 3, 3);
    mainLayout->addWidget(setLabel[setLabelIndex++], 3, 4);
    mainLayout->addWidget(setEdit[setEditIndex++], 3, 5, 1, 2);
    mainLayout->addWidget(mmUnitLabel[mmIndex++], 3, 7);
    mainLayout->addWidget(speedLabel[speedLabelIndex++], 3, 8);
    mainLayout->addWidget(speedEdit[speedEditIndex++], 3, 9, 1, 2);
    mainLayout->addWidget(mm_sUnitLabel[mm_sIndex++], 3, 11);

    mainLayout->addWidget(pztLocationLabel, 4, 0);
    mainLayout->addWidget(pztLocationEdit, 4, 1, 1, 2);
    mainLayout->addWidget(umUnitLabel[umIndex++], 4, 3);
    mainLayout->addWidget(setLabel[setLabelIndex++], 4, 4);
    mainLayout->addWidget(setEdit[setEditIndex++], 4, 5, 1, 2);
    mainLayout->addWidget(umUnitLabel[umIndex++], 4, 7);
    mainLayout->addWidget(setOk, 4, 9);

    this->setLayout(mainLayout);
}





