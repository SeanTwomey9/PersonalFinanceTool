/*##################################################################################
#   File name:          Bill.cpp
#   Created on:         08/30/2024
#   Author:             stwomey
#   Description:        Source file for a Bill
#   Change History:     See https://github.com/SeanTwomey9/PersonalFinanceTool
#   Relative Location:  PersonalFinanceTool/src/
##################################################################################*/

#include "Bill.h"

QString Bill::getName()
{
    // Return the name of the bill
    return m_name;
}

void Bill::setName(QString p_updatedName)
{
    // Update the name of the bill
    m_name = p_updatedName;
}

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

QDate Bill::getDueDate()
{
    // Return the due date
    return m_dueDate;
}

void Bill::setDueDate(QDate p_updatedDueDate)
{
    // Update the due date
    m_dueDate = p_updatedDueDate;
}

bool Bill::isFunded()
{
    // Return the funded status
    return m_isFunded;
}

void Bill::setFundedStatus(bool p_updatedFundingStatus)
{
    // Update the funded status
    m_isFunded = p_updatedFundingStatus;
}


bool operator == (const Bill &p_firstBill, const Bill &p_secondBill)
{
    // If the two Bill objects have equivalent names, amounts due, due dates, and funded status, true is returned. False otherwise
    return (p_firstBill.m_name == p_secondBill.m_name && p_firstBill.m_amountDueDollars == p_secondBill.m_amountDueDollars
            && p_firstBill.m_dueDate == p_secondBill.m_dueDate && p_firstBill.m_isFunded == p_secondBill.m_isFunded);
}
