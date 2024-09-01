/*##################################################################################
#   File name:          BillWidget.cpp
#   Created on:         08/30/2024
#   Author:             stwomey
#   Description:        Source file for a BillWidget
#   Change History:     See https://github.com/SeanTwomey9/PersonalFinanceTool
#   Relative Location:  PersonalFinanceTool/src/
##################################################################################*/

#include "BillWidget.h"

BillWidget::BillWidget(QObject *p_parent)
{
    this->setWindowTitle(m_WINDOW_TITLE);
    this->setGeometry(50, 50, 200, 200);
    m_nameLabel = new QLabel(this);
    m_nameLabel->setText(m_NAME_LABEL_TEXT);
    m_nameLabel->setGeometry(0, 0, 100, 100);
    this->setWindowModality(Qt::ApplicationModal);
    this->raise();
    this->activateWindow();
}

BillWidget::~BillWidget()
{
    if(m_nameLabel != nullptr)
    {
        delete m_nameLabel;
        m_nameLabel = nullptr;
    }
}
