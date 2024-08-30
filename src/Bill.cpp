/*##################################################################################
#   File name:          Bill.cpp
#   Created on:         08/30/2024
#   Author:             stwomey
#
#   Description:        Source file for a Bill
#
#   Change History:     See https://github.com/SeanTwomey9/PersonalFinanceTool
#   Relative Location:  PersonalFinanceTool/src/
#
##################################################################################*/

#include "Bill.h"

double Bill::getAmountDue()
{
    // Return the amount due
    return m_amountDueDollars;
}

void Bill::setAmountDue(double p_updatedAmountDue)
{
    // Update the amount due
    m_amountDueDollars = p_updatedAmountDue;
}

QDateTime Bill::getDueDate()
{
    // Return the due date
    return m_dueDate;
}

void Bill::setDueDate(QDateTime p_updatedDueDate)
{
    // Update the due date
    m_dueDate = p_updatedDueDate;
}

bool Bill::getPaymentStatus()
{
    // Return the payment status
    return m_isPaid;
}

void Bill::setPaymentStatus(bool p_updatedPaymentStatus)
{
    // Update the payment status
    m_isPaid = p_updatedPaymentStatus;
}
