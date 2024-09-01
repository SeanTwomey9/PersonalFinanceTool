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

    // Needed to make the widget appear without clicking the application icon
    this->setWindowModality(Qt::ApplicationModal);

    initializeWidget();
    createWidgetLayout();
    connect(m_enterAnotherButton, SIGNAL(clicked()), this, SLOT(createAndSendBill()), Qt::AutoConnection);
}

BillWidget::~BillWidget()
{
    if(m_nameLabel != nullptr)
    {
        delete m_nameLabel;
        m_nameLabel = nullptr;
    }
}

void BillWidget::initializeWidget()
{
    m_nameLabel = new QLabel(this);
    m_nameLabel->setText(m_NAME_LABEL_TEXT);
    m_nameInput = new QLineEdit(this);

    m_amountDueLabel = new QLabel(this);
    m_amountDueLabel->setText(m_AMOUNT_DUE_LABEL_TEXT);
    m_amountDueInput = new QLineEdit(this);

    m_dueDateLabel = new QLabel(this);
    m_dueDateLabel->setText(m_DUE_DATE_LABEL_TEXT);
    m_dueDateInput = new QDateEdit(this);
    m_dueDateInput->setCalendarPopup(true);
    m_dueDateInput->setDate(QDate::currentDate());

    m_closeButton = new QPushButton(this);
    m_closeButton->setText(m_CLOSE_BUTTON_TEXT);

    m_enterAnotherButton = new QPushButton(this);
    m_enterAnotherButton->setText(m_ENTER_ANOTHER_BUTTON_TEXT);

    m_doneButton = new QPushButton(this);
    m_doneButton->setText(m_DONE_BUTTON_TEXT);
}

void BillWidget::createWidgetLayout()
{
    m_gridLayout = new QGridLayout(this);
    m_gridLayout->addWidget(m_nameLabel, 0, 0, Qt::AlignmentFlag::AlignLeft);
    m_gridLayout->addWidget(m_nameInput, 0, 1);
    m_gridLayout->addWidget(m_amountDueLabel, 1, 0);
    m_gridLayout->addWidget(m_amountDueInput, 1, 1);
    m_gridLayout->addWidget(m_dueDateLabel, 2, 0);
    m_gridLayout->addWidget(m_dueDateInput, 2, 1);
    m_gridLayout->addWidget(m_closeButton, 3, 0);
    m_gridLayout->addWidget(m_enterAnotherButton, 3, 1);
    m_gridLayout->addWidget(m_doneButton, 3, 2);
}

QPushButton* BillWidget::getCloseButton()
{
    return m_closeButton;
}

QPushButton* BillWidget::getEnterAnotherButton()
{
    return m_enterAnotherButton;
}

QPushButton* BillWidget::getDoneButton()
{
    return m_doneButton;
}

void BillWidget::createAndSendBill()
{
    Bill *enteredBill = new Bill();
    enteredBill->setName(m_nameInput->text());
    enteredBill->setAmountDue(m_amountDueInput->text().toDouble());
    enteredBill->setDueDate(m_dueDateInput->dateTime());

    emit sendBill(enteredBill);
}

QLineEdit* BillWidget::getNameInput()
{
    return m_nameInput;
}

QLineEdit* BillWidget::getAmountDueInput()
{
    return m_amountDueInput;
}

QDateEdit* BillWidget::getDueDateInput()
{
    return m_dueDateInput;
}
