/*##################################################################################
#   File name:          MainWindow.cpp
#   Created on:         08/30/2024
#   Author:             stwomey
#   Description:        Header file for the MainWindow
#   Change History:     See https://github.com/SeanTwomey9/PersonalFinanceTool
#   Relative Location:  PersonalFinanceTool/src/
##################################################################################*/

#include "MainWindow.h"
#include "BillWidget.h"

#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QInputDialog>
#include <QApplication>

MainWindow::MainWindow()
{
    // Connection to terminate application when certain conditions are met
    connect(this, SIGNAL(conditionToTerminateMet()), this, SLOT(terminateApplication()), Qt::QueuedConnection);
    this->setWindowTitle(m_APP_NAME);

    // Create the BillWidget
    m_billWidget = new BillWidget(this);
    connect(m_billWidget->getCloseButton(), SIGNAL(clicked()), this, SLOT(terminateApplication()), Qt::AutoConnection);
    connect(m_billWidget->getEnterAnotherButton(), SIGNAL(clicked()), this, SLOT(saveBillAndDisplayBillWidget()), Qt::AutoConnection);
    connect(m_billWidget->getDoneButton(), SIGNAL(clicked()), this, SLOT(saveBillAndDisplayDashboard()), Qt::AutoConnection);

    attemptConfigFileGeneration();


}

MainWindow::~MainWindow()
{

}

void MainWindow::terminateApplication()
{
    // Terminate the application
    QCoreApplication::quit();
}

void MainWindow::createConfigFileGenerateFailureBox()
{
    QMessageBox configFileFailBox;
    configFileFailBox.setText(m_CONFIG_FILE_GENERATE_FAIL_BOX_TITLE);
    configFileFailBox.setInformativeText(m_CONFIG_FILE_GENERATE_FAIL_BOX_INFO_TEXT);
    configFileFailBox.setStandardButtons(QMessageBox::Ok);

    int configFileFailBoxSelection = configFileFailBox.exec();

    switch(configFileFailBoxSelection)
    {
    case QMessageBox::Button::Ok :
    {
        emit conditionToTerminateMet();
        break;
    }

    default :
    {
        emit conditionToTerminateMet();
        break;
    }
    }
}

void MainWindow::attemptConfigFileGeneration()
{
    QDir configParentFolder;

    // If the config file path could not be generated
    if(!configParentFolder.mkpath(m_CONFIG_PARENT_FOLDER))
    {
        // Display a message box to alert the user
        createConfigFileGenerateFailureBox();
    }

    // The config file was found in the expected path
    else if(QFile::exists(m_CONFIG_FILE_DIRECTORY))
    {
        // Read config file and create UI
    }

    // The config file path exists but the file is not in it
    else
    {
        // Prompt user for financial information
        welcomeFirstTimeUser();
    }
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
        case QMessageBox::Ok :
        {
            // Ask for total funds available
            askForTotalAmountAvailable();
            break;
        }

        // If the user selects "Close"
        case QMessageBox::Close :
        {
            // Exit application
            emit conditionToTerminateMet();
            break;
        }

        default:
        {
            break;
        }
    }
}

void MainWindow::createCorruptConfigFileBox()
{
    QMessageBox corruptBox;
    corruptBox.setText(m_CONFIG_CORRUPT_FILE_BOX_TITLE);
    corruptBox.setInformativeText(m_CONFIG_CORRUPT_FILE_BOX_INFO_TEXT);

    corruptBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Close);

    int corruptBoxSelection = corruptBox.exec();

    switch(corruptBoxSelection)
    {
        case QMessageBox::Ok :
        {
            welcomeFirstTimeUser();
            break;
        }

        case QMessageBox::Close :
        {
            emit conditionToTerminateMet();
            break;
        }

        default:
        {
            break;
        }
    }
}

void MainWindow::saveBillAndDisplayBillWidget()
{
    QSettings m_settings(m_CONFIG_FILE_DIRECTORY, QSettings::IniFormat);

    if(m_settings.status() != QSettings::NoError)
    {
        createCorruptConfigFileBox();
    }

    else
    {
        Bill *enteredBill = new Bill();
        enteredBill->setName(m_billWidget->getNameInput()->text());
        enteredBill->setAmountDue(m_billWidget->getAmountDueInput()->text().toDouble());
        enteredBill->setDueDate(m_billWidget->getDueDateInput()->dateTime());

        m_settings.beginGroup(m_billWidget->getNameInput()->text());
        m_settings.setValue(m_BILL_AMOUNT_DUE_KEY, m_billWidget->getAmountDueInput()->text().toDouble());
        m_settings.setValue(m_BILL_DUE_DATE_KEY, m_billWidget->getDueDateInput()->dateTime().toString());
        m_settings.endGroup();
        m_settings.sync();

        m_billWidget->getNameInput()->clear();
        m_billWidget->getAmountDueInput()->clear();
        m_billWidget->getDueDateInput()->setDate(QDate::currentDate());
    }
}

void MainWindow::saveBillAndDisplayDashboard()
{
    QSettings m_settings(m_CONFIG_FILE_DIRECTORY, QSettings::IniFormat);

    if(m_settings.status() != QSettings::NoError)
    {
        createCorruptConfigFileBox();
    }

    else
    {
        m_settings.beginGroup(m_billWidget->getNameInput()->text());
        m_settings.setValue(m_BILL_AMOUNT_DUE_KEY, m_billWidget->getAmountDueInput()->text());
        m_settings.setValue(m_BILL_DUE_DATE_KEY, m_billWidget->getDueDateInput()->date().toString());
        m_settings.endGroup();
        m_settings.sync();

        m_billWidget->hide();
        this->show();
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

        QSettings m_settings(m_CONFIG_FILE_DIRECTORY, QSettings::IniFormat);

        if(m_settings.status() != QSettings::NoError)
        {
            createCorruptConfigFileBox();
        }

        else
        {
            m_settings.beginGroup(m_FUNDS_INFORMATION_GROUP_LABEL);
            m_settings.setValue(m_TOTAL_FUNDS_AVAILABLE_KEY, m_amountAvailable);
            m_settings.endGroup();
            m_settings.sync();
            m_billWidget->show();
        }

    }

    else
    {
        // Exit application
        emit conditionToTerminateMet();
    }
}
