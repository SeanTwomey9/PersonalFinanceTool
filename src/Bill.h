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

#include <QDate>

/**
 * @brief The Bill class represents a bill which a user needs to pay.
 */
class Bill
{

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
     * @brief Allows for the comparison of Bill objects for equality
     * @param p_firstBill - The first Bill object to compare.
     * @param p_secondBill - The second Bill object to compare.
     * @return True if the Bill objects are equal based on their name, amount due, due date, and funded status. False otherwise.
     */
    friend bool operator == (const Bill &p_firstBill, const Bill &p_secondBill);

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
    QDate getDueDate();

    /**
     * @brief Returns the funded status of the bill.
     * @return m_isFunded - Represents whether or not the bill has been funded.
     */
    bool getFundedStatus();

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
    void setDueDate(QDate p_updatedDueDate);

    /**
     * @brief Updates the bill's funded status.
     * @param p_updatedFundedStatus - Updated funded status.
     */
    void setFundedStatus(bool p_updatedFundedStatus);

private:

    QString m_name = ""; //!< The name of the bill, defaulted to an empty string.
    double m_amountDueDollars = 0.00; //!< The amount of money owed for the bill in dollars and cents, defaulted to zero.
    QDate m_dueDate; //!< The date that the bill is due, no default for now.
    bool m_isFunded = false; //!< Whether or not the bill has been funded yet, defaulted to false.

signals:
};

#endif // BILL_H
