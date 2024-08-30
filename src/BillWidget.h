/*##################################################################################
#   File name:          BillWidget.h
#   Created on:         08/30/2024
#   Author:             stwomey
#   Description:        Header file for a BillWidget
#   Change History:     See https://github.com/SeanTwomey9/PersonalFinanceTool
#   Relative Location:  PersonalFinanceTool/src/
##################################################################################*/

#ifndef BILLWIDGET_H
#define BILLWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QDateTimeEdit>

class BillWidget : public QWidget
{

public:

    BillWidget(QObject *parent);
    ~BillWidget();

private:

    const QString m_WINDOW_TITLE = "Bill Entry";
    QLabel *m_nameLabel = nullptr;
    const QString m_NAME_LABEL_TEXT = "Bill Name:";
    QLineEdit m_NAME_INPUT;
    QLabel m_DUE_DATE_LABEL;
    const QString m_DUE_DATE_LABEL_TEXT = "Due Date:";
    QDateTimeEdit m_DUE_DATE_INPUT;
};

#endif // BILLWIDGET_H
