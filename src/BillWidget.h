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

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QGridLayout>
#include <QPushButton>

class BillWidget : public QDialog
{

public:

    BillWidget(QObject *parent);
    ~BillWidget();

    void initializeWidget();
    void createWidgetLayout();
    QPushButton* getCloseButton();
    QPushButton* getEnterAnotherButton();
    QPushButton* getDoneButton();

private:

    const QString m_WINDOW_TITLE = "Bill Entry";

    // Name input fields
    QLabel *m_nameLabel = nullptr;
    const QString m_NAME_LABEL_TEXT = "Bill Name:";
    QLineEdit *m_nameInput = nullptr;

    // Due date input fields
    QLabel *m_dueDateLabel;
    const QString m_DUE_DATE_LABEL_TEXT = "Due Date:";
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
