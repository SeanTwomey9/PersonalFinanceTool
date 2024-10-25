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

/**
 * @brief Properly deletes a dynamically allocated label pointer, as long as it was created properly.
 * @param p_label - The label pointer to be deleted.
 */
void deleteLabelIfNonNull(QLabel *p_label);

/**
 * @brief Properly deletes a dynamically allocated line edit pointer, as long as it was created properly.
 * @param p_lineEdit - The line edit pointer to be deleted.
 */
void deleteLineEditIfNonNull(QLineEdit *p_lineEdit);

/**
 * @brief Properly deletes a dynamically allocated button pointer, as long as it was created properly.
 * @param p_button - The button pointer to be deleted.
 */
void deleteButtonIfNonNull(QPushButton *p_button);

/**
 * @brief The BillWidget class represents a pop-up widget which allows the user to enter a bill that they wish to track.
 */
class BillWidget : public QWidget
{
    Q_OBJECT

public:

    /**
     * @brief Constructs a widget allowing the user to enter their bills.
     * @param parent - Parent widget used for object tree tracking.
     */
    BillWidget(QObject *parent);

    /**
     * @brief Destructs the BillWidget by deleting objects which were dynamically allocated.
     */
    ~BillWidget();

    /**
     * @brief Creates the labels, input fields, and buttons of the BillWidget.
     */
    void initializeWidget();

    /**
     * @brief Adds the widgets of the BillWidget into a grid layout.
     */
    void createWidgetLayout();

    /**
     * @brief Returns the close push button pointer.
     * @return The close push button pointer.
     */
    QPushButton* getCloseButton();

    /**
     * @brief Returns the enter another push button pointer.
     * @return The enter another push button pointer.
     */
    QPushButton* getEnterAnotherButton();

    /**
     * @brief Returns the done push button pointer.
     * @return The done push button pointer.
     */
    QPushButton* getDoneButton();

    /**
     * @brief Returns the name line edit pointer.
     * @return The name line edit pointer.
     */
    QLineEdit* getNameInput();

    /**
     * @brief Returns the amount due line edit pointer.
     * @return The amount due line edit pointer.
     */
    QLineEdit* getAmountDueInput();

    /**
     * @brief Returns the due date date edit pointer.
     * @return The due date date edit pointer.
     */
    QDateEdit* getDueDateInput();

private:


    const QString m_WINDOW_TITLE = "Bill Entry"; //!< Title of the BillWidget window.

    // Name input fields
    QLabel *m_nameLabel = nullptr; //!< Label for the line edit used for entering the name of the bill.
    const QString m_NAME_LABEL_TEXT = "Bill Name:"; //!< Text for the label for the line edit used for entering the name of the bill.
    QLineEdit *m_nameInput = nullptr; //!< The line edit used for entering the name of the bill.

    // Amount due input fields
    QLabel *m_amountDueLabel = nullptr; //!< Label for the line edit used for entering the amount due of the bill.
    const QString m_AMOUNT_DUE_LABEL_TEXT = "Amount Due:"; //!< Text for the label for the line edit used for entering the amount due of the bill
    QLineEdit *m_amountDueInput = nullptr; //!< The line edit used for entering the amount due of the bill.

    // Due date input fields
    QLabel *m_dueDateLabel; //!< Label for the date edit used for entering the due date of the bill.
    const QString m_DUE_DATE_LABEL_TEXT = "Due Date:"; //!< Text for the label for the date edit used for entering the due date of the bill.
    QDateEdit *m_dueDateInput = nullptr; //!< The date edit used for entering the due date of the bill.

    QGridLayout *m_gridLayout = nullptr; //!< Grid layout used for organizing the labels, line edits, date edit, and push buttons of the BillWidget.

    // Button and button text variables
    QPushButton *m_closeButton = nullptr; //!< Push button used for closing the BillWidget.
    const QString m_CLOSE_BUTTON_TEXT = "Close"; //!< Text used for the Close push button.
    QPushButton *m_enterAnotherButton = nullptr; //!< Push button used for entering another bill.
    const QString m_ENTER_ANOTHER_BUTTON_TEXT = "Enter Another Bill"; //!< Text used for the Enter Another button.
    QPushButton *m_doneButton = nullptr; //!< Push button used for closing the BillWidget when finished entering bills.
    const QString m_DONE_BUTTON_TEXT = "Done"; //!< //!< Text used for the Done push button.
};

#endif // BILLWIDGET_H
