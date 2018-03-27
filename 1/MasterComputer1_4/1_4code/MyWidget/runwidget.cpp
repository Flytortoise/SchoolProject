#include "runwidget.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <QGridLayout>
#include "transmitdata.h"
#include "datahandle.h"

const char *RunWidget::REGEXP = "^[0]|((-?[0-9]{1,4})(\\.\\d{0,3}))$";
//正则表达式

RunWidget::RunWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle(tr("运动设置"));

    CreateInit();
    CreateLayout();


}

void RunWidget::CreateInit()
{
    QRegExp regexp(REGEXP);
    //范围 [-9999.999,9999.999]

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

    setOkButton = new QPushButton(tr("参数设定"));
    connect(setOkButton, SIGNAL(clicked(bool)),
            this, SLOT(HandleRunData()));

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
    mainLayout->addWidget(xLocationEdit, 1, 1);
    mainLayout->addWidget(mmUnitLabel[mmIndex++], 1, 3);
    mainLayout->addWidget(setLabel[setLabelIndex++], 1, 4);
    mainLayout->addWidget(setEdit[setEditIndex++], 1, 5);
    mainLayout->addWidget(mmUnitLabel[mmIndex++], 1, 7);
    mainLayout->addWidget(speedLabel[speedLabelIndex++], 1, 8);
    mainLayout->addWidget(speedEdit[speedEditIndex++], 1, 9);
    mainLayout->addWidget(mm_sUnitLabel[mm_sIndex++], 1, 11);

    mainLayout->addWidget(yLocationLabel, 2, 0);
    mainLayout->addWidget(yLocationEdit, 2, 1);
    mainLayout->addWidget(mmUnitLabel[mmIndex++], 2, 3);
    mainLayout->addWidget(setLabel[setLabelIndex++], 2, 4);
    mainLayout->addWidget(setEdit[setEditIndex++], 2, 5);
    mainLayout->addWidget(mmUnitLabel[mmIndex++], 2, 7);
    mainLayout->addWidget(speedLabel[speedLabelIndex++], 2, 8);
    mainLayout->addWidget(speedEdit[speedEditIndex++], 2, 9);
    mainLayout->addWidget(mm_sUnitLabel[mm_sIndex++], 2, 11);

    mainLayout->addWidget(zLocationLabel, 3, 0);
    mainLayout->addWidget(zLocationEdit, 3, 1);
    mainLayout->addWidget(mmUnitLabel[mmIndex++], 3, 3);
    mainLayout->addWidget(setLabel[setLabelIndex++], 3, 4);
    mainLayout->addWidget(setEdit[setEditIndex++], 3, 5);
    mainLayout->addWidget(mmUnitLabel[mmIndex++], 3, 7);
    mainLayout->addWidget(speedLabel[speedLabelIndex++], 3, 8);
    mainLayout->addWidget(speedEdit[speedEditIndex++], 3, 9);
    mainLayout->addWidget(mm_sUnitLabel[mm_sIndex++], 3, 11);

    mainLayout->addWidget(pztLocationLabel, 4, 0);
    mainLayout->addWidget(pztLocationEdit, 4, 1);
    mainLayout->addWidget(umUnitLabel[umIndex++], 4, 3);
    mainLayout->addWidget(setLabel[setLabelIndex++], 4, 4);
    mainLayout->addWidget(setEdit[setEditIndex++], 4, 5);
    mainLayout->addWidget(umUnitLabel[umIndex++], 4, 7);
    mainLayout->addWidget(setOkButton, 4, 9);

    this->setLayout(mainLayout);
}

void RunWidget::HandleRunData()
{
    int PositionIndex = 0;
    int SpeedIndex = 0;
    m_data.xData[RunToHandleData::ShowPositon] = xLocationEdit->text();
    m_data.xData[RunToHandleData::SetPositon] = setEdit[PositionIndex++]->text();
    m_data.xData[RunToHandleData::SetSpeed] = speedEdit[SpeedIndex++]->text();
    m_OrgData[XIndex] = m_data.xData[RunToHandleData::ShowPositon].toDouble();

    m_data.yData[RunToHandleData::ShowPositon] = yLocationEdit->text();
    m_data.yData[RunToHandleData::SetPositon] = setEdit[PositionIndex++]->text();
    m_data.yData[RunToHandleData::SetSpeed] = speedEdit[SpeedIndex++]->text();
    m_OrgData[YIndex] = m_data.yData[RunToHandleData::ShowPositon].toDouble();

    m_data.zData[RunToHandleData::ShowPositon] = zLocationEdit->text();
    m_data.zData[RunToHandleData::SetPositon] = setEdit[PositionIndex++]->text();
    m_data.zData[RunToHandleData::SetSpeed] = speedEdit[SpeedIndex++]->text();
    m_OrgData[ZIndex] = m_data.zData[RunToHandleData::ShowPositon].toDouble();

    m_data.pztData[RunToHandleData::ShowPositon] = pztLocationEdit->text();
    m_data.pztData[RunToHandleData::SetPositon] = setEdit[PositionIndex]->text();
    m_OrgData[PZTIndex] = m_data.pztData[RunToHandleData::ShowPositon].toDouble();

    emit SendRunData(m_data);
}

void RunWidget::GetRecvData(ComToRunData comdata)
{
    if(comdata.isOk)
    {
        m_OrgData[XIndex] = xLocationEdit->text().toDouble();
        m_OrgData[YIndex] = yLocationEdit->text().toDouble();
        m_OrgData[ZIndex] = zLocationEdit->text().toDouble();
        m_OrgData[PZTIndex] = pztLocationEdit->text().toDouble();
    }

    //X
    if(comdata.isPlus[ComToRunData::XIndex])
        xLocationEdit->setText(QString::number(m_OrgData[XIndex] + comdata.PositionData[ComToRunData::XIndex],
                               10, 3)); //10进制，小数点3位
    else
        xLocationEdit->setText(QString::number(m_OrgData[XIndex] - comdata.PositionData[ComToRunData::XIndex],
                               10, 3));

    //Y
    if(comdata.isPlus[ComToRunData::YIndex])
        yLocationEdit->setText(QString::number(m_OrgData[YIndex] + comdata.PositionData[ComToRunData::YIndex],
                               10, 3));
    else
        yLocationEdit->setText(QString::number(m_OrgData[YIndex] - comdata.PositionData[ComToRunData::YIndex],
                               10, 3));

    //Z
    if(comdata.isPlus[ComToRunData::ZIndex])
        zLocationEdit->setText(QString::number(m_OrgData[ZIndex] + comdata.PositionData[ComToRunData::ZIndex],
                               10, 3));
    else
        zLocationEdit->setText(QString::number(m_OrgData[ZIndex] - comdata.PositionData[ComToRunData::ZIndex],
                               10, 3));
    //PZT
    pztLocationEdit->setText(QString::number(m_OrgData[PZTIndex] + comdata.PositionData[ComToRunData::PZTIndex],
                           10, 3));

}















