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
    this->setGeometry(0, 0, 300, 200);

    // Create the BillWidget
    m_billWidget = new BillWidget(this);
    connect(m_billWidget->getCloseButton(), SIGNAL(clicked()), this, SLOT(terminateApplication()), Qt::AutoConnection);
    connect(m_billWidget->getEnterAnotherButton(), SIGNAL(clicked()), this, SLOT(saveBillAndDisplayBillWidget()), Qt::AutoConnection);
    connect(m_billWidget->getDoneButton(), SIGNAL(clicked()), this, SLOT(saveBillAndDisplayDashboard()), Qt::AutoConnection);

    m_billTableWidget = new QTableWidget(this);
    m_billTableWidget->setGeometry(0, 0, 300, 200);
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
    // Create a message box with appropriate displayed text
    QMessageBox configFileFailBox;
    configFileFailBox.setText(m_CONFIG_FILE_GENERATE_FAIL_BOX_TITLE);
    configFileFailBox.setInformativeText(m_CONFIG_FILE_GENERATE_FAIL_BOX_INFO_TEXT);
    configFileFailBox.setStandardButtons(QMessageBox::Ok);

    int configFileFailBoxSelection = configFileFailBox.exec();

    switch(configFileFailBoxSelection)
    {
        // If the user presses "Ok", terminate the application
        case QMessageBox::Button::Ok :
        {
            emit conditionToTerminateMet();
            break;
        }

        default :
        {
            // Terminate the application by default
            emit conditionToTerminateMet();
            break;
        }
    }
}

void MainWindow::createInvalidKeyBox()
{
    // Create the invalid key message box
    QMessageBox invalidKeyBox;
    invalidKeyBox.setText(m_INVALID_KEY_BOX_TEXT);
    invalidKeyBox.setInformativeText(m_INVALID_KEY_BOX_INFO_TEXT);
    invalidKeyBox.setStandardButtons(QMessageBox::Ok);

    int invalidKeyBoxSelection = invalidKeyBox.exec();

    switch(invalidKeyBoxSelection)
    {
        // If the user presses the "Ok" button
        case QMessageBox::Button::Ok :
        {
            // Terminate the application
            emit conditionToTerminateMet();
            break;
        }

        default :
        {
            // Terminate the application in the default case
            emit conditionToTerminateMet();
            break;
        }
    }
}

void MainWindow::createTableWidgetUsingMap()
{
    // Set the number of rows in the table widget to be the number of bills stored in the bill map
    m_billTableWidget->setRowCount(m_billMap.size());

    // Set the number of columns to the number of fields which each Bill displays
    m_billTableWidget->setColumnCount(3);

    // Set the table widget headers to the appropriate fields each Bill displays
    m_billTableWidget->setHorizontalHeaderLabels(QString("Bill Name;Amount Due;Due Date").split(";"));

    // Initialize the row we're setting to zero
    int row = 0;

    // Create an iterator to iterate over the bill map
    QMap<QString, Bill>::iterator billMapIterator;

    for(billMapIterator = m_billMap.begin(); billMapIterator != m_billMap.end(); ++billMapIterator)
    {
        // Retrieve the current Bill being checked
        Bill currentBill = *billMapIterator;

        // Set the columns appropriately to the Bill's attributes
        m_billTableWidget->setItem(row, 0, new QTableWidgetItem(currentBill.getName()));
        m_billTableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(currentBill.getAmountDue())));
        m_billTableWidget->setItem(row, 2, new QTableWidgetItem(currentBill.getDueDate().toString()));

        // Increment the row for the next Bill
        row++;
    }

    // Resize the table widget's columns to fit the contents
    m_billTableWidget->resizeColumnsToContents();
}


void MainWindow::readConfigAndCreateUI()
{
    // Attempt to open the pre-existing config file
    QSettings m_settings(m_CONFIG_FILE_DIRECTORY, QSettings::IniFormat);

    // If attempting to open the config file resulted in an error
    if(m_settings.status() != QSettings::NoError)
    {
        // Alert the user with an appropriate message box
        createCorruptConfigFileBox();
    }

    // If the config file was opened successfully
    else
    {
        // Store all the keys from the config file in a list
        QStringList configFileKeys = m_settings.allKeys();

        // Iterate over each key
        foreach(QString key, configFileKeys)
        {
            // The keys are stored in "Group label/key" format so they need to be separated
            QStringList keyValues = m_settings.value(key).toStringList();

            // Split the keys at the "/" to isolate the current group label and key
            QStringList splitKeys = key.split(QLatin1Char('/'));

            // If splitting the key did not result in both a group label and key
            if(splitKeys.size() < 2)
            {
                // Alert the user with an invalid key message box
                createInvalidKeyBox();
            }

            else
            {
                // Save both the group label and value
                QString groupLabel = splitKeys.at(0);
                QString valueLabel = splitKeys.at(1);

                // If the group label is the funds information section
                if(groupLabel == m_FUNDS_INFORMATION_GROUP_LABEL)
                {
                    // If their is no total amount of money available currently stored in the config file
                    if(keyValues.at(0).isEmpty())
                    {
                        // Default the amount available to zero
                        m_amountAvailable = 0.00;
                    }

                    // If an amount available was found
                    else
                    {
                        // Update the amount available to the config file's contents
                        m_amountAvailable = keyValues.at(0).toDouble();
                    }
                }

                // If the group label is a bill
                else
                {
                    // If the bill being checked has not been inserted into the bill map yet
                    if(!m_billMap.contains(groupLabel))
                    {
                        // Create a new Bill object
                        Bill readBill;

                        // Set the Bill's name
                        readBill.setName(groupLabel);

                        // Since the amount due will be read before the due date, set the amount due of the Bill
                        readBill.setAmountDue(keyValues.at(0).toDouble());

                        // Insert the Bill into the map mapped to the name of the bill
                        m_billMap.insert(groupLabel, readBill);
                    }

                    // If the bill being checked already exists in the bill map, then we're checking its due date
                    else
                    {
                        // Adjust the due date string to only have single spaces within it
                        QString dateNoSpaces = keyValues.at(0).simplified();

                        // Remove spaces from due date string, this results in the due date string being in the form "dddMMMddyyyy" or "SatSep142024" for example
                        dateNoSpaces.replace(" ", "");

                        // Convert the due date string into a date object
                        QDate readDate = QDate::fromString(dateNoSpaces,"dddMMMddyyyy");

                        // Set the appropriate Bill's due date from the bill map
                        m_billMap[groupLabel].setDueDate(readDate);
                    }
                }
            }
        }

        // Create the table widget using the bill map's contents
        createTableWidgetUsingMap();

        // Display the main window
        this->show();
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
        readConfigAndCreateUI();

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
    // Create the corrupt confile file QMessageBox with appropriate displayed text
    QMessageBox corruptBox;
    corruptBox.setText(m_CONFIG_CORRUPT_FILE_BOX_TITLE);
    corruptBox.setInformativeText(m_CONFIG_CORRUPT_FILE_BOX_INFO_TEXT);

    // Give the user the options of "Ok'ing" the error or closing the application
    corruptBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Close);

    int corruptBoxSelection = corruptBox.exec();

    switch(corruptBoxSelection)
    {
        // If the user selected Ok
        case QMessageBox::Ok :
        {
            // Kick off the welcome sequence to have the user re-enter their financial information to get back to a functional state
            welcomeFirstTimeUser();
            break;
        }

        // If the user selected Close
        case QMessageBox::Close :
        {
            // Terminate the application
            emit conditionToTerminateMet();
            break;
        }

        default:
        {
            // Default to have the user re-enter their information
            welcomeFirstTimeUser();
            break;
        }
    }
}

void MainWindow::openConfigForBillCreation()
{
    // Attempt to access the config file
    QSettings m_settings(m_CONFIG_FILE_DIRECTORY, QSettings::IniFormat);

    // If the attempt to open the config file results in an error
    if(m_settings.status() != QSettings::NoError)
    {
        // Alert the user with a message box
        createCorruptConfigFileBox();
    }

    // Otherwise if the config file was opened successfully
    else
    {
        // Create a new Bill object for the bill information inputted into the BillWidget
        Bill enteredBill;
        enteredBill.setName(m_billWidget->getNameInput()->text());
        enteredBill.setAmountDue(m_billWidget->getAmountDueInput()->text().toDouble());
        enteredBill.setDueDate(m_billWidget->getDueDateInput()->date());

        // Insert the Bill object into the map with a key of the name of the bill
        m_billMap.insert(m_billWidget->getNameInput()->text(), enteredBill);

        // Write the Bill information out to the config file
        m_settings.beginGroup(m_billWidget->getNameInput()->text());
        m_settings.setValue(m_BILL_AMOUNT_DUE_KEY, m_billWidget->getAmountDueInput()->text().toDouble());
        m_settings.setValue(m_BILL_DUE_DATE_KEY, m_billWidget->getDueDateInput()->date().toString());
        m_settings.endGroup();
        m_settings.sync();
    }
}

void MainWindow::saveBillAndDisplayBillWidget()
{
    // Attempt to open the config file, if successful create a new Bill object and store contents in the config file
    openConfigForBillCreation();

    // Clear the BillWidget for entry of another bill
    m_billWidget->getNameInput()->clear();
    m_billWidget->getAmountDueInput()->clear();
    m_billWidget->getDueDateInput()->setDate(QDate::currentDate());
}

void MainWindow::saveBillAndDisplayDashboard()
{
    // Attempt to open the config file, if successful create a new Bill object and store contents in the config file
    openConfigForBillCreation();

    // Hide the BillWidget as no more bills need to be entered since the Done button was pressed
    m_billWidget->hide();

    // Create the bill table widget using the bill map
    createTableWidgetUsingMap();

    // Show the window
    this->show();

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

        // Attempt to open the config file
        QSettings m_settings(m_CONFIG_FILE_DIRECTORY, QSettings::IniFormat);

        // If attempting to open the config file resulted in an error
        if(m_settings.status() != QSettings::NoError)
        {
            // Alert the user with an appropriate message box
            createCorruptConfigFileBox();
        }

        // If the config file was opened without issue
        else
        {
            // Create the funds information group
            m_settings.beginGroup(m_FUNDS_INFORMATION_GROUP_LABEL);

            // Write the total funds available out to the config file
            m_settings.setValue(m_TOTAL_FUNDS_AVAILABLE_KEY, m_amountAvailable);
            m_settings.endGroup();
            m_settings.sync();

            // Show the BillWidget for bill entry
            m_billWidget->show();
        }

    }

    else
    {
        // Exit application
        emit conditionToTerminateMet();
    }
}
