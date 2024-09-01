/*##################################################################################
#   File name:          Bill.h
#   Created on:         08/30/2024
#   Author:             stwomey
#   Description:        Header file for a Bill
#   Change History:     See https://github.com/SeanTwomey9/PersonalFinanceTool
#   Relative Location:  PersonalFinanceTool/src/
##################################################################################*/

#ifndef BILL_H
#define BILL_H

#include <QObject>
#include <QDateTime>

/**
 * @brief The Bill class represents a bill which a user needs to pay.
 */
class Bill : public QObject
{
    Q_OBJECT

public:

    /**
     * @brief Constructs a Bill.
     */
    Bill() {};

    /**
     * Destructs a Bill.
     */
    ~Bill() {};

    /**
     * @brief Returns the bill's name.
     * @return m_name - Represents the name of the bill.
     */
    QString getName();

    /**
     * @brief Returns the bill's amount due.
     * @return m_amountDueDollars - Represents the amount of money due for the bill.
     */
    double getAmountDue();

    /**
     * @brief Returns the bill's due date.
     * @return m_dueData - Represents the due date of the bill.
     */
    QDateTime getDueDate();

    /**
     * @brief Returns the payment status of the bill.
     * @return m_isPaid - Represents whether or not the bill has been paid.
     */
    bool getPaymentStatus();

    /**
     * @brief Updates the bill's name.
     * @param p_updatedName  Updated bill name.
     */
    void setName(QString p_updatedName);

    /**
     * @brief Updates the bill's amount due.
     * @param p_updatedAmountDue - Updated amount due.
     */
    void setAmountDue(double p_updatedAmountDue);

    /**
     * @brief Updates the bill's due date.
     * @param p_updatedDueDate - Updated due date.
     */
    void setDueDate(QDateTime p_updatedDueDate);


private:

    /**
     * @brief Updates the bill's payment status.
     * @param p_updatedPaymentStatus - Updated payment status.
     */
    void setPaymentStatus(bool p_updatedPaymentStatus);
    QString m_name = ""; //!< The name of the bill, defaulted to an empty string.
    double m_amountDueDollars = 0.00; //!< The amount of money owed for the bill in dollars and cents, defaulted to zero.
    QDateTime m_dueDate; //!< The date that the bill is due, no default for now.
    bool m_isPaid = false; //!< Whether or not the bill has been paid yet, defaulted to false.

signals:
};

#endif // BILL_H
