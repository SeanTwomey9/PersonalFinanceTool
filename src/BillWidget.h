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

#include "Bill.h"

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QGridLayout>
#include <QPushButton>

class BillWidget : public QWidget
{
    Q_OBJECT

public:

    BillWidget(QObject *parent);
    ~BillWidget();

    void initializeWidget();
    void createWidgetLayout();
    QPushButton* getCloseButton();
    QPushButton* getEnterAnotherButton();
    QPushButton* getDoneButton();

signals:

    void sendBill(Bill *p_sentBill);

public slots:

    void createAndSendBill();

private:


    const QString m_WINDOW_TITLE = "Bill Entry";

    // Name input fields
    QLabel *m_nameLabel = nullptr;
    const QString m_NAME_LABEL_TEXT = "Bill Name:";
    QLineEdit *m_nameInput = nullptr;

    // Amount due input fields
    QLabel *m_amountDueLabel = nullptr;
    const QString m_AMOUNT_DUE_LABEL_TEXT = "AmountDue:";
    QLineEdit *m_amountDueInput = nullptr;

    // Due date input fields
    QLabel *m_dueDateLabel;
    const QString m_DUE_DATE_LABEL_TEXT = "DueDate:";
    QDateEdit *m_dueDateInput = nullptr;

    QGridLayout *m_gridLayout = nullptr;

    QPushButton *m_closeButton = nullptr;
    const QString m_CLOSE_BUTTON_TEXT = "Close";
    QPushButton *m_enterAnotherButton = nullptr;
    const QString m_ENTER_ANOTHER_BUTTON_TEXT = "Enter another bill";
    QPushButton *m_doneButton = nullptr;
    const QString m_DONE_BUTTON_TEXT = "Done";
};

#endif // BILLWIDGET_H
