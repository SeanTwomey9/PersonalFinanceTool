/*##################################################################################
#   File name:          MainWindow.h
#   Created on:         08/30/2024
#   Author:             stwomey
#   Description:        Header file for the MainWindow
#   Change History:     See https://github.com/SeanTwomey9/PersonalFinanceTool
#   Relative Location:  PersonalFinanceTool/src/
##################################################################################*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Local file includes
#include "Bill.h"
#include "BillWidget.h"

// Qt includes
#include <QMainWindow>
#include <QSettings>
#include <QTableWidget>

/**
 * @brief The MainWindow class represents the primary window which will display the user's personal financial information.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /**
     * @brief Constructs the MainWindow by initializing various UI components and kicking off the initial processing of the user's financial information.
     */
    MainWindow();

    /**
     * @brief Destructs the MainWindow by appropriately deleting objects which were dynamically allocated.
     */
    ~MainWindow();

signals:

    /**
     * @brief Emitted when the application needs to be terminated.
     */
    void conditionToTerminateMet();

public slots:

    /**
     * @brief Terminates the application.
     */
    void terminateApplication();

    /**
     * @brief Attempts to open the config file, if successful a new Bill object is created for the current information inputted into the BillWidget.
     * Information is also written as a new bill entry in the config file.
     */
    void openConfigForBillCreation();

    /**
     * @brief Calls the openConfigForBillCreation() helper method, before the BillWidget is reset for entry of another bill.
     */
    void saveBillAndDisplayBillWidget();

    /**
     * @brief Calls the openConfigForBillCreation() helper method, before the BillWidget is hidden.
     * The bill map is then iterated over, and its contents are used to display financial information to the user.
     */
    void saveBillAndDisplayBillTableWidget();

    /**
     * @brief Called when the Save button is pressed. Opens the config file and initially updates the bill map to match the contents of the bill table widget.
     * Then updates the config file with the contents of the updated bill map.
     */
    void updateConfigFromUI();

    /**
     * @brief Clears the BillWidget and then displays it so a user can enter another bill.
     */
    void showBillWidget();

    /**
     * @brief Called when the Fund Bill button is pressed. Iterates over the rows and columns of the bill table widget checking for which rows are selected.
     * If a row is selected, the bill corresponding to that row will have its funding status set to Funded.
     */
    void fundBillOnClick();

    /**
     * @brief Called when the Defund Bill button is pressed. Iterates over the rows and columns of the bill table widget checking for which rows are selected.
     * If a row is selected, the bill corresponding to that row will have its funding status set to Not Funded.
     */
    void defundBillOnClick();

    /**
     * @brief Called when the Delete Bill button is pressed. Iterates over the rows and columns of the bill table widget checking for which rows are selected.
     * If a row is selected, the bill corresponding to that row will have its funding status checked for a value of Funded.
     * If the bill is funded, the amount of money allocated to that bill is returned to the total amount available, the bill is removed from the funded bills list, and lastly the row is removed from the bill table widget.
     */
    void deleteBillOnClick();

private:

    /**
     * @brief Creates a message box in the event that attempting to open the config file resulted in an error.
     *  If the user chooses to press the "Ok" button, the welcome sequence will initiate where the user will provide their financial information again.
     *  If the user chooses to press the "Close" button, the application will terminate.
     */
    void createCorruptConfigFileBox();

    /**
     * @brief Creates a message box for a fatal error requiring termination of the application.
     * @param p_primaryText - The primary text to be used for the fatal error message box.
     * @param p_infoText - The informative text to be used for the fatal error message box.
     */
    void createFatalErrorBox(const QString p_primaryText, const QString p_infoText);

    /**
     * @brief Creates a message box in the event that a user attempts to save a bill they entered which is missing a name or an amount due.
     */
    void createMissingBillDetailsBox();

    /**
     * @brief Checks if the pre-determined directory for the config file can be generated, if it cannot an error message is displayed to the user. Then checks if the config file exists in that directory, if so the file is parsed.
     * If the file does not exist in the directory, the welcome sequence initiates in which the user is asked for their financial information.
     */
    void attemptConfigFileGeneration();

    /**
     * @brief Generates a message box to welcome a first time user.
     * Has clickable buttons allowing the user to advance to the total funds available prompt, and to exit the application.
     */
    void welcomeFirstTimeUser();

    /**
     * @brief Asks the user for the total amount of money they have available for spending.
     * Saves the input to a member variable to be displayed in the bill table widget.
     */
    void askForTotalAmountAvailable();

    /**
     * @brief Sets some preliminary attributes of the bill table widget before iterating over the bill map.
     * Uses the bill map's contents to create the bill table widget before displaying the financial information to the user.
     */
    void createTableWidgetUsingMap();

    /**
     * @brief In the event that a config file already exists in the desired directory, read the config file and store its contents in the bill map.
     * Then, iterate over the bill map and use its contents to display the user's financial information.
     */
    void readConfigAndCreateUI();

    /**
     * @brief Checks a funding status and returns "Funded" or "Not Funded" if the status is true or false respectively.
     * @param p_isBillFunded - Funding status as a boolean, true or false.
     * @return The funding status as a string.
     */
    QString fundingStatusBooleanToString(bool p_isBillFunded);

    /**
     * @brief Checks a funding status and returns true or false if the status is "Funded" or "Not Funded" respectively.
     * @param p_fundingStatus - Funding status as a string, "Funded" or "Not Funded".
     * @return The funding status as a boolean.
     */
    bool fundingStatusStringToBoolean(QString p_fundingStatus);

    /**
     * @brief Converts a date represented as a string into a date object in the appropriate "M/d/yyyy" format.
     * @param p_dateString - A date represented as a string.
     * @return The input string as a date object in "M/d/yyyy" format.
     */
    QDate convertDateStringToDate(QString p_dateString);

    /**
     * @brief Removes spaces from an input string containing spaces.
     * @param p_stringWithSpaces - String with spaces.
     * @return The original string but with spaces removed.
     */
    QString removeSpaces(QString p_stringWithSpaces);

    /**
     * @brief Clears the name, amount due, and due date fields in preparation for allowing a user to enter another bill.
     */
    void clearBillWidget();

    /**
     * @brief Organizes various buttons used for interacting with the bill table widget into a layout.
     */
    void createButtonGridLayout();

    /**
     * @brief Parses group labels, keys, and values in the config file in order to update the bill map and funded bills list before bill table widget is shown.
     * @param p_groupLabel - Group label being checked in config file, will be either FundsInformation group or a bill name.
     * @param p_key - Key being checked in config file, whill be either the amount due, due date, or funding status.
     * @param p_value - Value being checked in config file, will be the information the user entered for the specific bill.
     */
    void parseConfigContents(QString p_groupLabel, QString p_key, QString p_value);

    /**
     * @brief Hides the BillWidget before displaying the bill table widget using the updated contents of the bill map.
     */
    void displayBillTableWidget();

    /**
     * @brief If a row in the bill table widget is selected, set the associated Bill's funding status to either funded or not funded.
     * @param p_widgetRow - The row of the bill table widget being checked for selection.
     * @param p_isFunded - The Bill's funded status, 1 for funded and 0 for not funded.
     */
    void switchFundingStatusIfSelected(int p_widgetRow, int p_isFunded);

    // Window variables
    const QString m_APP_NAME = "PersonalFinanceTool"; //!< The name of the application displayed as the window title.
    QGridLayout *m_buttonGridLayout = nullptr; //!< Grid layout used to organize buttons on the MainWindow.

    // Config file generation strings
    const QString m_CONFIG_FILE_NAME = m_APP_NAME + ".ini"; //!< The name of the config file.
    const QString m_CONFIG_PARENT_FOLDER = "config/"; //!< The parent folder of the config file.
    const QString m_CONFIG_FILE_DIRECTORY = m_CONFIG_PARENT_FOLDER + m_CONFIG_FILE_NAME; //!< The path where the config file should be read/generated if absent.

    // Message box strings
    const QString m_INVALID_KEY_BOX_PRIMARY_TEXT = "Invalid Configuration File Key/Value Pair"; //!< The invalid key message box title.
    const QString m_INVALID_KEY_BOX_INFO_TEXT = "A key/value pair from " + m_CONFIG_FILE_NAME + " is invalid. Please correct the file to have a single value per key and relaunch the application."; //!< The invalid key message box informative text.
    const QString m_MISSING_BILL_DETAILS_BOX_PRIMARY_TEXT = "Missing Bill Information"; //!< The missing bill details box title.
    const QString m_MISSING_BILL_DETAILS_BOX_INFO_TEXT = "Please enter a name, amount due, and due date for each bill"; //!< The informative text of the missing bill details message box.
    const QString m_CONFIG_FILE_GENERATE_FAIL_BOX_PRIMARY_TEXT = "Failure To Generate Configuration File"; //!< The title of the config file generation failure message box.
    const QString m_CONFIG_FILE_GENERATE_FAIL_BOX_INFO_TEXT = "The configuration file could not be generated in " + m_CONFIG_PARENT_FOLDER; //!< The informative text of the config file generation failure message box.
    const QString m_CONFIG_CORRUPT_FILE_BOX_PRIMARY_TEXT = "Configuration File Is Corrupt"; //!< The title of the config file corrupt message box.
    const QString m_CONFIG_CORRUPT_FILE_BOX_INFO_TEXT = "The configuration file could not be opened, a new one will be created following the welcoming sequence."; //!< The informative text of the corrupt config file message box.
    const QString m_WELCOME_BOX_PRIMARY_TEXT = "Welcome to the Personal Finance Tool!"; //!< The welcome message box title.
    const QString m_WELCOME_BOX_INFO_TEXT = "In the subsequent prompts, you will be asked to provide some financial information."; //!< The welcome message box informative text.

    // Total amount available variables
    const QString m_TOTAL_AMOUNT_AVAILABLE_STRING = "Total Amount Available: $"; //!< The total amount available represented as a string.
    const QString m_ASK_FOR_AMOUNT_AVAILABLE_TEXT = "Please enter the total amount of money available in USD."; //!< The total amount available informative text.
    const double m_DEFAULT_AMOUNT_AVAILABLE = 0.00; //!< The default amount of money available assigned if the user does not provide the actual amount.
    const double m_MIN_AMOUNT_AVAILABLE = 0.00; //!< The minimum amount the user can specify for the total amount of money they have available.
    const double m_MAX_AMOUNT_AVAILABLE = static_cast<double>(INT64_MAX); //!< The maximum amount the user can specify for the total amount of money they have available.
    const int m_NUM_DECIMAL_PLACES = 2; //!< The number of decimal places allowed in the total amount available input box.
    double m_AMOUNT_AVAILABLE_STEP_SIZE = 1.00; //!< The step size for the up and down arrows in the total amount available input box.
    double m_totalAmountAvailable = 0.00; //!< The total amount of money the user has available, defaulted to zero dollars.

    // Config file content strings
    QSettings m_settings; //!< The QSettings object which reads and writes to the configuration file.
    const QString m_FUNDS_INFORMATION_GROUP_LABEL = "FundsInformation"; //!< The group label for the funds information section of the configuration file.
    const QString m_TOTAL_FUNDS_AVAILABLE_KEY = "TotalFundsAvailable"; //!< The total funds available key which maps to the total funds available value.
    const QString m_BILL_AMOUNT_DUE_KEY = "AmountDue"; //!< The amount due key which maps to various amounts due of bills.
    const QString m_BILL_DUE_DATE_KEY = "DueDate"; //!< The due date key which maps to various due dates of bills.
    const QString m_BILL_FUNDING_STATUS_KEY = "FundingStatus"; //!< The funding status key which maps to whether or not a bill has been funded.

    // Bill table widget strings
    const QString m_BILL_NAME_COLUMN_HEADER_STRING = "Bill Name"; //!< The bill name column title.
    const QString m_BILL_AMOUNT_DUE_COLUMN_HEADER_STRING = "Amount Due"; //!< The bill amount due column title.
    const QString m_BILL_DUE_DATE_COLUMN_HEADER_STRING = "Due Date"; //!< The bill due date column title.
    const QString m_BILL_FUNDING_STATUS_COLUMN_HEADER_STRING = "Funding Status"; //!< The bill funding status column title.

    // Button text strings
    const QString m_SAVE_BUTTON_TEXT = "Save"; //!< Save button text.
    const QString m_DELETE_BUTTON_TEXT = "Delete"; //!< Delete button text.
    const QString m_ADD_BILL_BUTTON_TEXT = "Add Another Bill"; //!< Add another bill button text.
    const QString m_FUND_BILL_BUTTON_TEXT = "Fund Bill"; //!< Fund bill button text.
    const QString m_DEFUND_BILL_BUTTON_TEXT = "Defund Bill"; //!< Defund bill button text.

    // Widgets used throughout the MainWindow
    BillWidget *m_billWidget = nullptr; //!< Pointer to a BillWidget which allows the user to enter the bills they wish to keep track of.
    QTableWidget *m_billTableWidget = nullptr; //!< Table widget displaying inputted bill information.

    // Amount avaiable UI objects
    QLabel *m_amountAvailableLabel = nullptr; //!< The label for the total amount available.
    QLineEdit *m_amountAvailableEdit = nullptr; //!< The input field for the total amount available, initially set to the user's amount available but can be edited.

    // Buttons used for manipulating the bill table widget
    QPushButton *m_saveButton = nullptr; //!< Button used to save the current state of the tool to the configuration file for subsequent launches of the application.
    QPushButton *m_deleteBillButton = nullptr; //!< Button used to delete a bill from the bill table widget.
    QPushButton *m_addBillButton = nullptr; //!< Button used to add another bill to the bill table widget.
    QPushButton *m_fundBillButton = nullptr; //!< Button used to fund a bill in the bill table widget.
    QPushButton *m_defundBillButton = nullptr; //!< Button used to defund a bill in the bill table widget.

    // Data structures used for storing bill information
    QMap<QString, Bill> m_billMap; //!< Map which stores (key, value) pairs of (the names of bills, corresponding bill objects).
    QList<QString> m_fundedBillsList; //!< List which holds the currently funded bills.

    // Miscellaneous variables
    const QString m_FUNDED_STRING = "Funded"; //!< Funded status of funded represented as a string.
    const QString m_NOT_FUNDED_STRING = "Not Funded"; //!< Funded status of not funded represented as a string.
    const QString m_DATE_STRING_FORMAT = "M/d/yyyy"; //!< The format to use when converting dates to strings.
};
#endif // MAINWINDOW_H
