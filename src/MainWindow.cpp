/*##################################################################################
#   File name:          MainWindow.cpp
#   Created on:         08/30/2024
#   Author:             stwomey
#
#   Description:        Header file for the MainWindow
#
#   Change History:     See https://github.com/SeanTwomey9/PersonalFinanceTool
#   Relative Location:  PersonalFinanceTool/src/
#
##################################################################################*/

#include "MainWindow.h"

#include <QFile>
#include <QMessageBox>
#include <QInputDialog>
#include <QApplication>

MainWindow::MainWindow()
{
    connect(this, SIGNAL(conditionToTerminateMet()), this, SLOT(terminateApplication()), Qt::QueuedConnection);

    if(QFile::exists(m_CONFIG_FILE_DIRECTORY))
    {
        // Read config file and create UI
        this->setWindowTitle(m_APP_NAME);
    }

    else
    {
        // Prompt user for financial information
        welcomeFirstTimeUser();
    }

}

MainWindow::~MainWindow()
{

}

void MainWindow::terminateApplication()
{
    QCoreApplication::quit();
}

void MainWindow::welcomeFirstTimeUser()
{
    // Create a welcome message box with appropriate title and title
    QMessageBox welcomeBox;
    welcomeBox.setText(m_WELCOME_BOX_PRIMARY_TEXT);
    welcomeBox.setInformativeText(m_WELCOME_BOX_INFO_TEXT);

    // Allow options for advancing to the next screen or closing the application
    welcomeBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Close);

    // Save the user's selection
    int welcomeBoxSelection = welcomeBox.exec();

    switch(welcomeBoxSelection)
    {
        // If the user selects "Ok"
        case QMessageBox::Ok:
        {
            // Ask for total funds available
            askForTotalAmountAvailable();
            break;
        }

        // If the user selects "Close"
        case QMessageBox::Close:
        {
            // Exit application
            qDebug() << "USER PRESSED CLOSE";
            emit conditionToTerminateMet();
            break;
        }

        default:
        {
            break;
        }
    }
}

void MainWindow::askForTotalAmountAvailable()
{
    // Variable which is set to true if user pressed ok, false if user pressed cancel
    bool isTotalAmountAvailableRecorded;

    // Set up the input dialog box with appropriate text and input restrictions and store the result
    double amountAvailable = QInputDialog::getDouble(this, m_ASK_FOR_AMOUNT_AVAILABLE_TITLE, m_ASK_FOR_AMOUNT_AVAILABLE_TEXT, m_DEFAULT_AMOUNT_AVAILABLE, m_MIN_AMOUNT_AVAILABLE, m_MAX_AMOUNT_AVAILABLE, m_NUM_DECIMAL_PLACES,
                                                                  &isTotalAmountAvailableRecorded, Qt::WindowFlags(), m_AMOUNT_AVAILABLE_STEP_SIZE);

    // If the user pressed ok
    if(isTotalAmountAvailableRecorded)
    {
        // Store the total amount available entered, if nothing was entered this defaults to $0.00
        m_amountAvailable = amountAvailable;
    }

    else
    {
        // Exit application
        emit conditionToTerminateMet();
    }
}
