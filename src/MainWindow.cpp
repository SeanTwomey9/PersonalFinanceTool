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
#include <QMessageBox>
#include <QInputDialog>
#include <QApplication>
#include <QComboBox>

MainWindow::MainWindow()
{
    // Set the title of the MainWindow
    this->setWindowTitle(m_APP_NAME);

    // Size the MainWindow appropriately
    this->setGeometry(0, 0, 500, 520);

    // Create the BillWidget
    m_billWidget = new BillWidget(this);

    // Connection to terminate application when certain conditions are met
    connect(this, SIGNAL(conditionToTerminateMet()), this, SLOT(terminateApplication()), Qt::QueuedConnection);

    // When the BillWidget's Close button is clicked, terminate the application
    connect(m_billWidget->getCloseButton(), SIGNAL(clicked()), this, SLOT(terminateApplication()), Qt::AutoConnection);

    // When the BillWidget's Enter Another Bill button is clicked, save the currently entered bill information to the config file and re-display the widget
    connect(m_billWidget->getEnterAnotherButton(), SIGNAL(clicked()), this, SLOT(saveBillAndDisplayBillWidget()), Qt::AutoConnection);

    // When the BillWidget's Done button is clicked, save the currently entered bill information to the config file and display the bill table widget
    connect(m_billWidget->getDoneButton(), SIGNAL(clicked()), this, SLOT(saveBillAndDisplayBillTableWidget()), Qt::AutoConnection);

    // Create the amount available label and set its location and text
    m_amountAvailableLabel = new QLabel(this);
    m_amountAvailableLabel->setGeometry(0, 0, 150, 20);
    m_amountAvailableLabel->setText(m_TOTAL_AMOUNT_AVAILABLE_STRING);

    // Create the amount available line edit and set its location
    m_amountAvailableEdit = new QLineEdit(this);
    m_amountAvailableEdit->setGeometry(155, 0, 75, 20);

    // Create the bill table widget and set its location
    m_billTableWidget = new QTableWidget(this);
    m_billTableWidget->setGeometry(0, 100, 500, 500);

    // Create the save button
    m_saveButton = new QPushButton(this);
    m_saveButton->setText(m_SAVE_BUTTON_TEXT);

    // When the Save button is clicked, update the bill map and config file to match the contents of the bill table widget
    connect(m_saveButton, SIGNAL(clicked()), this, SLOT(updateConfigFromUI()), Qt::AutoConnection);

    // Create the Add Another Bill button
    m_addBillButton = new QPushButton(this);
    m_addBillButton->setText(m_ADD_BILL_BUTTON_TEXT);

    // When the Add Another Bill button is clicked, clear the BillWidget and display it for entry of another bill
    connect(m_addBillButton, SIGNAL(clicked()), this, SLOT(showBillWidget()), Qt::AutoConnection);

    // Create the Delete button
    m_deleteBillButton = new QPushButton(this);
    m_deleteBillButton->setText(m_DELETE_BUTTON_TEXT);

    // When the Delete button is clicked, make sure to update the amount available and funded bill lists if the deleted bill was funded, and then remove from the bill table widget
    connect(m_deleteBillButton, SIGNAL(clicked()), this, SLOT(deleteBillOnClick()), Qt::AutoConnection);

    // Create the Fund Bill button
    m_fundBillButton = new QPushButton(this);
    m_fundBillButton->setText(m_FUND_BILL_BUTTON_TEXT);

    // When the Fund Bill button is clicked, switch the selected bill's funding status to Funded
    connect(m_fundBillButton, SIGNAL(clicked()), this, SLOT(fundBillOnClick()), Qt::AutoConnection);

    // Create the Defund Bill button
    m_defundBillButton = new QPushButton(this);
    m_defundBillButton->setText(m_DEFUND_BILL_BUTTON_TEXT);

    // When the Defund Bill button is clicked, switch the selected bill's funding status to Not Funded
    connect(m_defundBillButton, SIGNAL(clicked()), this, SLOT(defundBillOnClick()), Qt::AutoConnection);

    // Create the Reset Bills button
    m_resetBillsButton = new QPushButton(this);
    m_resetBillsButton->setText(m_RESET_BILLS_BUTTON_TEXT);

    // When the Reset Bills button is clicked, remove the existing configuration file and launch the initialization sequence
    connect(m_resetBillsButton, SIGNAL(clicked()), this, SLOT(createResetBillsConfirmationBox()), Qt::AutoConnection);

    // Organize the buttons into a grid layout
    createButtonGridLayout();

    // Kick off the start sequence where we check for the existence of the config file
    attemptConfigFileGeneration();
}

MainWindow::~MainWindow()
{
    // If the BillWidget has been created successfully
    if(m_billWidget != nullptr)
    {
        // Delete it and set it to be null
        delete m_billWidget;
        m_billWidget = nullptr;
    }

    // Properly delete the amount available label
    deleteLabelIfNonNull(m_amountAvailableLabel);

    // Properly delete the amount available line edit
    deleteLineEditIfNonNull(m_amountAvailableEdit);

    // Properly delete the all buttons
    deleteButtonIfNonNull(m_saveButton);
    deleteButtonIfNonNull(m_addBillButton);
    deleteButtonIfNonNull(m_deleteBillButton);
    deleteButtonIfNonNull(m_fundBillButton);
    deleteButtonIfNonNull(m_defundBillButton);
    deleteButtonIfNonNull(m_resetBillsButton);

    // If the bill table widget has been created successfully
    if(m_billTableWidget != nullptr)
    {
        // Clear the widget so widget pointers within are deleted
        m_billTableWidget->clear();

        // Delete it and set it to be null
        delete m_billTableWidget;
        m_billTableWidget = nullptr;
    }
}

void MainWindow::createButtonGridLayout()
{
    // Organize the buttons into a grid layout
    m_buttonGridLayout = new QGridLayout(this);
    m_buttonGridLayout->addWidget(m_addBillButton, 0, 0, Qt::AlignmentFlag::AlignLeft);
    m_buttonGridLayout->addWidget(m_deleteBillButton, 0, 1);
    m_buttonGridLayout->addWidget(m_fundBillButton, 1, 0);
    m_buttonGridLayout->addWidget(m_defundBillButton, 1, 1);
    m_buttonGridLayout->addWidget(m_saveButton, 2, 0);
    m_buttonGridLayout->addWidget(m_resetBillsButton, 2, 1);

    // Ensure there is sufficient spacing between the buttons so they do not overlap
    m_buttonGridLayout->setHorizontalSpacing(5);

    // Position the grid layout in the top right corner of the MainWindow
    m_buttonGridLayout->setGeometry(QRect(250, -5, 250, 100));
}

void MainWindow::terminateApplication()
{
    // Terminate the application
    QCoreApplication::quit();
}

void MainWindow::createTableWidgetUsingMap()
{
    // Set the number of rows in the table widget to be the number of bills stored in the bill map
    m_billTableWidget->setRowCount(m_billMap.size());

    // Set the number of columns to the number of fields which each Bill displays
    m_billTableWidget->setColumnCount(4);

    // Set the table widget headers to the appropriate fields each Bill displays
    m_billTableWidget->setHorizontalHeaderLabels(QString(m_BILL_NAME_COLUMN_HEADER_STRING + ";" + m_BILL_AMOUNT_DUE_COLUMN_HEADER_STRING + ";" + m_BILL_DUE_DATE_COLUMN_HEADER_STRING + ";" + m_BILL_FUNDING_STATUS_COLUMN_HEADER_STRING).split(";"));

    // Initialize the row we're setting to zero
    int row = 0;

    // Create an iterator to iterate over the bill map
    QMap<QString, Bill>::iterator billMapIterator;


    for(billMapIterator = m_billMap.begin(); billMapIterator != m_billMap.end(); ++billMapIterator)
    {
        // Retrieve the current Bill being checked
        Bill currentBill = *billMapIterator;

        // Create a date edit for displaying and allowing the editing of the bill's due date
        QDateEdit *dateEdit = new QDateEdit(this);

        // Allow the display of a calendar for editing purposes
        dateEdit->setCalendarPopup(true);

        // Set the date edit based on the bill's due date
        dateEdit->setDate(currentBill.getDueDate());

        // Create a combo box to hold the funding status of the bill
        QComboBox *fundedStatusBox = new QComboBox(this);
        fundedStatusBox->addItem(m_NOT_FUNDED_STRING);
        fundedStatusBox->addItem(m_FUNDED_STRING);
        currentBill.isFunded() ? fundedStatusBox->setCurrentIndex(1) : fundedStatusBox->setCurrentIndex(0);

        // Set the columns appropriately to the Bill's attributes
        m_billTableWidget->setItem(row, 0, new QTableWidgetItem(currentBill.getName()));
        m_billTableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(currentBill.getAmountDue(), 'f', 2)));
        m_billTableWidget->setCellWidget(row, 2, dateEdit);
        m_billTableWidget->setCellWidget(row, 3, fundedStatusBox);

        // Increment the row for the next Bill
        row++;
    }
}

QDate MainWindow::convertDateStringToDate(QString p_dateString)
{
    // Convert the due date string into a date object and return it
    return QDate::fromString(removeSpaces(p_dateString), m_DATE_STRING_FORMAT);
}

void MainWindow::parseConfigContents(QString p_groupLabel, QString p_key, QString p_value)
{
    // If the group label is the funds information section
    if(p_groupLabel == m_FUNDS_INFORMATION_GROUP_LABEL)
    {
        // If there is no total amount of money available currently stored in the config file
        if(p_value.isEmpty())
        {
            // Default the amount available to zero
            m_totalAmountAvailable = 0.00;
        }

        // If an amount available was found
        else
        {
            // Update the amount available to the config file's contents
            m_totalAmountAvailable = p_value.toDouble();
        }
    }

    // If the group label is a bill
    else
    {
        // If the bill being checked has not been inserted into the bill map yet
        if(!m_billMap.contains(p_groupLabel))
        {
            // Create a new Bill object
            Bill readBill;

            // Set the Bill's name
            readBill.setName(p_groupLabel);

            // Since the amount due will be read before the due date and the funding status, set the amount due of the Bill
            readBill.setAmountDue(p_value.toDouble());

            // Insert the Bill into the map mapped to the name of the bill
            m_billMap[p_groupLabel] = readBill;
        }

        // If the bill being checked already exists in the bill map, then we're checking its due date
        else
        {
            // If the key label is the due date key
            if(p_key == m_BILL_DUE_DATE_KEY)
            {
                // Set the appropriate Bill's due date from the bill map by converting the date string to a date object
                m_billMap[p_groupLabel].setDueDate(convertDateStringToDate(p_value));
            }

            // Otherwise, the key label is the funding status
            else
            {
                // Set the appropriate Bill's funding status in the bill map by converting the funding status string to a boolean
                m_billMap[p_groupLabel].setFundedStatus(fundingStatusStringToBoolean(p_value));

                // If the Bill is currently funded
                if(m_billMap[p_groupLabel].isFunded())
                {
                    // Add the Bill's name to the funded list to assist with updating the total amount available
                    m_fundedBillsList.append(m_billMap[p_groupLabel].getName());
                }
            }
        }
    }
}

void MainWindow::readConfigAndCreateUI()
{
    // Attempt to open the pre-existing config file
    QSettings m_settings(m_CONFIG_FILE_DIRECTORY_NAME, QSettings::IniFormat);

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
            // Split the keys at the "/" to isolate the current group label and key
            QStringList splitKeys = key.split(QLatin1Char('/'));

            // If splitting the key did not result in both a group label and key
            if(splitKeys.size() < 2)
            {
                // TODO: Pass the invalid key to the box to display to the user
                // TODO: The box appears once for each incorrect pair, should the app just terminate after a single incorrect pair is found?
                // Alert the user with an invalid key message box
                createFatalErrorBox(m_INVALID_KEY_BOX_PRIMARY_TEXT, m_INVALID_KEY_BOX_INFO_TEXT);
            }

            else
            {
                // Save both the group label, key, and value
                QString groupLabel = splitKeys.at(0);
                QString keyLabel = splitKeys.at(1);

                // The keys are stored in "Group label/key" format so they need to be separated
                QString keyValue = m_settings.value(key).toString();

                // Use group labels, keys, and values from config file to update the bill map and funded bills list
                parseConfigContents(groupLabel, keyLabel, keyValue);
            }
        }

        // Set the amount avaiable line edit to the amount available amount in the config file, rounded to two decimal places
        m_amountAvailableEdit->setText(QString::number(m_totalAmountAvailable, 'f', 2));

        // Create the table widget using the bill map's contents
        createTableWidgetUsingMap();

        // Display the main window
        this->show();
    }
}

void MainWindow::attemptConfigFileGeneration()
{
    // If the config file path could not be generated
    if(!m_configFileDirectory.mkpath(m_CONFIG_PARENT_FOLDER))
    {
        // Display a message box to alert the user
        createFatalErrorBox(m_CONFIG_FILE_GENERATE_FAIL_BOX_PRIMARY_TEXT, m_CONFIG_FILE_GENERATE_FAIL_BOX_INFO_TEXT);
    }

    // The config file was found in the expected path
    else if(QFile::exists(m_CONFIG_FILE_DIRECTORY_NAME))
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
    // Create a welcome message box with appropriate primary and informative text
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

            // Break in the default case
        default:
        {
            break;
        }
    }
}

void MainWindow::createFatalErrorBox(const QString p_primaryText, const QString p_infoText)
{
    // Create the fatal error message box
    QMessageBox fatalErrorBox;
    fatalErrorBox.setText(p_primaryText);
    fatalErrorBox.setInformativeText(p_infoText);
    fatalErrorBox.setStandardButtons(QMessageBox::Ok);

    int fatalErrorBoxSelection = fatalErrorBox.exec();

    switch(fatalErrorBoxSelection)
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

void MainWindow::createCorruptConfigFileBox()
{
    // Create the corrupt config file QMessageBox with appropriate displayed text
    QMessageBox corruptBox;
    corruptBox.setText(m_CONFIG_CORRUPT_FILE_BOX_PRIMARY_TEXT);
    corruptBox.setInformativeText(m_CONFIG_CORRUPT_FILE_BOX_INFO_TEXT);

    // Give the user the options of "Ok'ing" the error or closing the application
    corruptBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Close);

    // Store the user's selection
    int corruptBoxSelection = corruptBox.exec();

    switch(corruptBoxSelection)
    {
    // If the user selected "Ok"
    case QMessageBox::Ok :
    {
        // Kick off the welcome sequence to have the user re-enter their financial information to get back to a functional state
        welcomeFirstTimeUser();
        break;
    }

        // If the user selected "Close"
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

QString MainWindow::fundingStatusBooleanToString(bool p_isBillFunded)
{
    // If the bill has been funded, return the funded string, otherwise return the not funded string
    return p_isBillFunded ? m_FUNDED_STRING : m_NOT_FUNDED_STRING;
}

bool MainWindow::fundingStatusStringToBoolean(QString p_fundingStatus)
{
    // If the bill has a funding status of "Funded", return true, otherwise return false
    return p_fundingStatus == m_FUNDED_STRING ? true : false;
}

QString MainWindow::removeSpaces(QString p_stringWithSpaces)
{
    // Convert the input string to a format in which characters can be replaced
    QString noSpaces = p_stringWithSpaces.simplified();

    // Return the string with spaces removed
    return noSpaces.replace(" ", "");
}

void MainWindow::openConfigForBillCreation()
{
    // Attempt to access the config file
    QSettings m_settings(m_CONFIG_FILE_DIRECTORY_NAME, QSettings::IniFormat);

    // If the attempt to open the config file results in an error
    if(m_settings.status() != QSettings::NoError)
    {
        // Alert the user with a message box
        createCorruptConfigFileBox();
    }

    // Otherwise if the config file was opened successfully
    else
    {
        // Save the entered Bill's name, amount due, and due date from the BillWidget
        QString enteredBillName = m_billWidget->getNameInput()->text();
        double enteredBillAmountDue = m_billWidget->getAmountDueInput()->text().toDouble();
        QDate enteredBillDueDate = m_billWidget->getDueDateInput()->date();

        // Write the Bill's name with spaces removed to the config file
        m_settings.beginGroup(removeSpaces(enteredBillName));

        // Write the amount due to the config file in decimal format
        m_settings.setValue(m_BILL_AMOUNT_DUE_KEY, QString::number(enteredBillAmountDue, 'f', 2));

        // Write the Bill's due date to the config file in M/d/yyyy format
        m_settings.setValue(m_BILL_DUE_DATE_KEY, enteredBillDueDate.toString(m_DATE_STRING_FORMAT));

        // Write the Bill's funding status to the config file, defaulted to not funded
        m_settings.setValue(m_BILL_FUNDING_STATUS_KEY, fundingStatusBooleanToString(false));
        m_settings.endGroup();
        m_settings.sync();

        // Create a new Bill object for the bill information inputted into the BillWidget
        Bill enteredBill;
        enteredBill.setName(enteredBillName);
        enteredBill.setAmountDue(enteredBillAmountDue);
        enteredBill.setDueDate(enteredBillDueDate);

        // Default the bill to not having been funded yet
        enteredBill.setFundedStatus(false);

        // Insert the Bill object into the map with a key of the name of the bill with spaces removed
        m_billMap[removeSpaces(enteredBillName)] = enteredBill;
    }
}

void MainWindow::createBoxWithNoResult(QString p_noResultPrimaryText, QString p_noResultInfoText)
{
    // Create the no result QMessageBox with text passed in as parameters
    QMessageBox boxWithNoResult;
    boxWithNoResult.setText(p_noResultPrimaryText);
    boxWithNoResult.setInformativeText(p_noResultInfoText);

    // Give the user the options of "Ok'ing" the error
    boxWithNoResult.setStandardButtons(QMessageBox::Ok);

    // Store the user's selection
    int boxWithNoResultSelection = boxWithNoResult.exec();

    switch(boxWithNoResultSelection)
    {
        // If the user selected Ok
        case QMessageBox::Ok :
        {
            // Close the message box so the user can continue what they're doing
            break;
        }

        default:
        {
            // Default to have the message box close so the user can continue what they're doing
            break;
        }
    }
}

void MainWindow::saveBillAndDisplayBillWidget()
{
    // If the bill name or amount due fields are empty
    if(m_billWidget->getNameInput()->text().isEmpty() || m_billWidget->getAmountDueInput()->text().isEmpty())
    {
        // Create the missing bill details message box
        createBoxWithNoResult(m_MISSING_BILL_DETAILS_BOX_PRIMARY_TEXT, m_MISSING_BILL_DETAILS_BOX_INFO_TEXT);
    }


    // Otherwise if the bill fields have been filled out appropriately
    else
    {
        // Attempt to open the config file, if successful create a new Bill object and store contents in the config file
        openConfigForBillCreation();

        // Clear the BillWidget if the user elects to add another bill
        clearBillWidget();
    }
}

void MainWindow::clearBillWidget()
{
    // Clear the BillWidget for entry of another bill
    m_billWidget->getNameInput()->clear();
    m_billWidget->getAmountDueInput()->clear();
    m_billWidget->getDueDateInput()->setDate(QDate::currentDate());
}

void MainWindow::displayBillTableWidget()
{
    // Hide the BillWidget as no more bills need to be entered since the Done button was pressed
    m_billWidget->hide();

    // Set the amount available as appropriate
    m_amountAvailableEdit->setText(QString::number(m_totalAmountAvailable, 'f', 2));

    // Create the bill table widget using the bill map
    createTableWidgetUsingMap();

    // Show the window
    this->show();
}

void MainWindow::saveBillAndDisplayBillTableWidget()
{
    // If the user pressed the Done button but did not enter a name and amount due for the bill, do not attempt to finish creating this bill
    if(m_billWidget->getNameInput()->text().isEmpty() && m_billWidget->getAmountDueInput()->text().isEmpty())
    {
        // Display the bill table widget
        displayBillTableWidget();
    }

    // If one of either the bill name or bill amount due fields are empty but the other has content in it
    else if(m_billWidget->getNameInput()->text().isEmpty() || m_billWidget->getAmountDueInput()->text().isEmpty())
    {
        // Create the missing bill details message box
        createBoxWithNoResult(m_MISSING_BILL_DETAILS_BOX_PRIMARY_TEXT, m_MISSING_BILL_DETAILS_BOX_INFO_TEXT);
    }

    // Otherwise all fields are filled out appropriately
    else
    {
        // Attempt to open the config file, if successful create a new Bill object and store contents in the config file
        openConfigForBillCreation();

        // After capturing the last entered Bill, display the bill table widget
        displayBillTableWidget();
    }
}

void MainWindow::showBillWidget()
{
    // Make sure to clear the BillWidget from the previous entry if the user chooses to add another bill from the bill table widget
    clearBillWidget();

    // Display the BillWidget so the user can add another bill
    m_billWidget->show();
}

void MainWindow::askForTotalAmountAvailable()
{
    // Variable which is set to true if user pressed ok, false if user pressed cancel
    bool isTotalAmountAvailableRecorded;

    // Set up the input dialog box with appropriate text and input restrictions and store the result
    double amountAvailable = QInputDialog::getDouble(this, m_TOTAL_AMOUNT_AVAILABLE_STRING, m_ASK_FOR_AMOUNT_AVAILABLE_TEXT, m_DEFAULT_AMOUNT_AVAILABLE, m_MIN_AMOUNT_AVAILABLE, m_MAX_AMOUNT_AVAILABLE, m_NUM_DECIMAL_PLACES,
                                                     &isTotalAmountAvailableRecorded, Qt::WindowFlags(), m_AMOUNT_AVAILABLE_STEP_SIZE);

    // If the user pressed ok
    if(isTotalAmountAvailableRecorded)
    {
        // Store the total amount available entered, if nothing was entered this defaults to $0.00
        m_totalAmountAvailable = amountAvailable;

        // Attempt to open the config file
        QSettings m_settings(m_CONFIG_FILE_DIRECTORY_NAME, QSettings::IniFormat);

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
            m_settings.setValue(m_TOTAL_FUNDS_AVAILABLE_KEY, QString::number(m_totalAmountAvailable, 'f', 2));
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

void MainWindow::updateConfigFromUI()
{
    // Attempt to access the config file
    QSettings m_settings(m_CONFIG_FILE_DIRECTORY_NAME, QSettings::IniFormat);

    // If the attempt to open the config file results in an error
    if(m_settings.status() != QSettings::NoError)
    {
        // Alert the user with a message box
        createCorruptConfigFileBox();
    }

    // Otherwise if the config file was opened successfully
    else
    {
        // Clear the bill map as we wish to use the content from the bill table widget for updates
        m_billMap.clear();

        // Update the amount available per the amount available line edit's contents
        m_totalAmountAvailable = m_amountAvailableEdit->text().toDouble();

        // Iterate over the rows of the bill table widget
        for(int row = 0; row < m_billTableWidget->rowCount(); row++)
        {
            // Store the name of the bill which is stored in the first column
            QString billName = m_billTableWidget->item(row, 0)->text();

            // Remove spaces from the bill name for easier handling in the config file
            QString billNameNoSpaces = removeSpaces(billName);

            // Create a temporary bill object to be inserted into the bill map
            Bill savedBill;

            // Iterate over the columns in the bill table widget
            for(int col = 0; col < m_billTableWidget->columnCount(); col++)
            {
                // Store the column header so we know which piece of data we're checking
                QString columnHeader = m_billTableWidget->horizontalHeaderItem(col)->text();

                // If the column header is the bill name
                if(columnHeader == m_BILL_NAME_COLUMN_HEADER_STRING)
                {
                    // Update the temporary bill object's name
                    savedBill.setName(billName);

                    // Since the bill name is checked first, we can insert a bill name, bill object key-value pair into the map
                    m_billMap[billNameNoSpaces] = savedBill;
                }

                // Otherwise if the column header is the amount due
                else if(columnHeader == m_BILL_AMOUNT_DUE_COLUMN_HEADER_STRING)
                {
                    // Update the bill's amount due in the map
                    m_billMap[billNameNoSpaces].setAmountDue(m_billTableWidget->item(row, col)->text().toDouble());
                }

                // Otherwise if the column header is the due date
                else if(columnHeader == m_BILL_DUE_DATE_COLUMN_HEADER_STRING)
                {
                    // Retrieve the due date edit from the bill table widget
                    QDateEdit *savedDate;
                    savedDate = (QDateEdit*)m_billTableWidget->cellWidget(row, col);

                    // Update the bill's due date in the map
                    m_billMap[billNameNoSpaces].setDueDate(savedDate->date());
                }

                // Otherwise the column header must be the funding status
                else
                {
                    // Retrieve the funded status combo box from the bill table widget
                    QComboBox *fundedStatusBox;
                    fundedStatusBox = (QComboBox*)m_billTableWidget->cellWidget(row, col);

                    // Store the current funding status
                    QString fundingStatus = fundedStatusBox->currentText();

                    // Update the bill's funding status in the map
                    m_billMap[billNameNoSpaces].setFundedStatus(fundingStatusStringToBoolean(fundingStatus));

                    // If a bill is marked as funded and is not already in the funded bill list
                    if(m_billMap[billNameNoSpaces].isFunded() && !m_fundedBillsList.contains(savedBill.getName()))
                    {
                        // Subtract the bill's amount due from the amount available as the funds set aside for this bill are no longer available
                        m_totalAmountAvailable -= m_billMap[billNameNoSpaces].getAmountDue();

                        // Add this bill to the funded bill list
                        m_fundedBillsList.append(savedBill.getName());
                    }

                    // Otherwise if a bill has been switched to no longer be funded (in the event of a defund) but is presently in the funded bill list
                    else if(!m_billMap[billNameNoSpaces].isFunded() && m_fundedBillsList.contains(savedBill.getName()))
                    {
                        // Add the bill's amount due back into the amount available as the bill no longer requires the funding set aside previously
                        m_totalAmountAvailable += m_billMap[billNameNoSpaces].getAmountDue();

                        // Remove the bill from the funded bill list
                        m_fundedBillsList.removeOne(savedBill.getName());
                    }
                }
            }
        }
    }

    // Update the amount available line edit with the updated value set to two decimal places
    m_amountAvailableEdit->setText(QString::number(m_totalAmountAvailable, 'f', 2));

    // Clear the settings object in preparation for updating the config file
    m_settings.clear();

    // Create the funds information group
    m_settings.beginGroup(m_FUNDS_INFORMATION_GROUP_LABEL);

    // Write the total funds available out to the config file
    m_settings.setValue(m_TOTAL_FUNDS_AVAILABLE_KEY, m_totalAmountAvailable);
    m_settings.endGroup();
    m_settings.sync();

    // Create an iterator to iterate over the bill map
    QMap<QString, Bill>::iterator billMapIterator;

    // Iterate over the bill map
    for(billMapIterator = m_billMap.begin(); billMapIterator != m_billMap.end(); ++billMapIterator)
    {
        // Retrieve the current bill being checked from the map
        Bill currentBill = *billMapIterator;

        // Set the group label as the bill name
        m_settings.beginGroup(removeSpaces(currentBill.getName()));

        // Write the bill amount due, due date, and status key-value pairs to the config file
        m_settings.setValue(m_BILL_AMOUNT_DUE_KEY, currentBill.getAmountDue());
        m_settings.setValue(m_BILL_DUE_DATE_KEY, currentBill.getDueDate().toString(m_DATE_STRING_FORMAT));
        m_settings.setValue(m_BILL_FUNDING_STATUS_KEY, fundingStatusBooleanToString(currentBill.isFunded()));
        m_settings.endGroup();
    }

    // Sync the settings object at the end
    m_settings.sync();
}

void MainWindow::switchFundingStatusIfSelected(int p_widgetRow, int p_isFunded)
{
    // If the current row being checked has been selected by the user
    if(m_billTableWidget->item(p_widgetRow, 0)->isSelected())
    {
        // Retrieve the funding status combo box found in the third column
        QComboBox *fundedStatusBox;
        fundedStatusBox = (QComboBox*)m_billTableWidget->cellWidget(p_widgetRow, 3);

        // Switch the funding status to either funded or not funded
        fundedStatusBox->setCurrentIndex(p_isFunded);
    }
}

void MainWindow::fundBillOnClick()
{
    // Iterate over the bill table widget rows
    for(int row = 0; row < m_billTableWidget->rowCount(); row++)
    {
        // If a row is selected, set the Bill's funding status to funded
        switchFundingStatusIfSelected(row, 1);
    }
}

void MainWindow::defundBillOnClick()
{
    // Iterate over the bill table widget rows
    for(int row = 0; row < m_billTableWidget->rowCount(); row++)
    {
        // If a row is selected, set the Bill's funding status to not funded
        switchFundingStatusIfSelected(row, 0);
    }
}

void MainWindow::deleteBillOnClick()
{
    // Iterate over the bill table widget rows
    for(int row = 0; row < m_billTableWidget->rowCount(); row++)
    {
        // If the current row being checked has been selected by the user
        if(m_billTableWidget->item(row, 0)->isSelected())
        {
            // Retrieve the funding status combo box found in the third column
            QComboBox *fundedStatusBox;
            fundedStatusBox = (QComboBox*)m_billTableWidget->cellWidget(row, 3);

            // If the funding status is marked as funded
            if(fundedStatusBox->currentText() == m_FUNDED_STRING)
            {
                // Add the bill's amount due back to the amount available by accessing the bill's amount due in the second column
                m_totalAmountAvailable+= m_billTableWidget->item(row, 1)->text().toDouble();

                // Update the amount available line edit
                m_amountAvailableEdit->setText(QString::number(m_totalAmountAvailable, 'f', 2));

                // Remove this bill from the funded bill list by accessing the bill's name in the first column
                m_fundedBillsList.removeOne(m_billTableWidget->item(row, 0)->text());
            }

            // Remove the selected row from the bill table widget
            m_billTableWidget->removeRow(row);

            // Decrement the row as there is now one less than before
            row--;
        }
    }
}

void MainWindow::createResetBillsConfirmationBox()
{
    // Create the reset bills QMessageBox with appropriate displayed text
    QMessageBox resetBillsConfirmationBox;
    resetBillsConfirmationBox.setText(m_RESET_BILLS_BOX_PRIMARY_TEXT);
    resetBillsConfirmationBox.setInformativeText(m_RESET_BILLS_BOX_INFO_TEXT);

    // Give the user the options of electing yes or no to reset their bills
    resetBillsConfirmationBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    // Store the user's selection
    int resetBillsConfirmationBoxSelection = resetBillsConfirmationBox.exec();

    switch(resetBillsConfirmationBoxSelection)
    {
        // If the user selects yes
        case QMessageBox::Yes :
        {
            // Remove the existing configuration file and launch the initialization sequence
            resetBillsAndLaunchInitialization();
            break;
        }

        // If the user selects no
        case QMessageBox::No :
        {
            // Break and return to the bill table widget
            break;
        }

        default:
        {
            // Default to breaking and returning to the bill table widget
            break;
        }
    }
}

void MainWindow::resetBillsAndLaunchInitialization()
{
    // If the configuration file was successfully removed
    if(m_configFileDirectory.remove(m_CONFIG_FILE_DIRECTORY_NAME))
    {
        // Hide the bill table widget
        this->hide();

        // Make sure to clear the bill map so the data to be shown in the bill table widget following initialization is reset
        m_billMap.clear();

        // Begin the initialization sequence
        welcomeFirstTimeUser();
    }

    // Otherwise if the configuration file could not be removed
    else
    {
        // Create an appropriate message box to alert the user
        createBoxWithNoResult(m_RESET_FAIL_BOX_PRIMARY_TEXT, m_RESET_FAIL_BOX_INFO_TEXT);
    }

}
