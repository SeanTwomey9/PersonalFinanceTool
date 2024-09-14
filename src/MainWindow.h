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

#include "Bill.h"
#include "BillWidget.h"

#include <QMainWindow>
#include <QSettings>
#include <QTableWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
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
    void saveBillAndDisplayDashboard();

    void updateConfigFromUI();

private:

    /**
     * @brief Creates a message box in the event that the config file was unable to be generated in the desired directory before terminating the application.
     */
    void createConfigFileGenerateFailureBox();

    /**
     * @brief Creates a message box in the event that the attempting to open the config file resulted in an error.
     *  If the user chooses to press the "Ok" button, the welcome sequence will initiate where the user will provide their financial information again.
     *  If the user chooses to press the "Close" button, the application will terminate.
     */
    void createCorruptConfigFileBox();

    /**
     * @brief Creates a message box in the event that an invalid key was found in the config file.
     * Warns the user to correct the config file, before terminating the application.
     */
    void createInvalidKeyBox();

    void attemptConfigFileGeneration();
    /**
     * @brief Generates a message box to welcome a first time user.
     * Has clickable buttons allowing the user to advance to the total funds available prompt, and to exit the application.
     */
    void welcomeFirstTimeUser();

    /**
     * @brief Asks the user for the total amountof money they have available for spending.
     * Saves the input to a member variable for usage.
     */
    void askForTotalAmountAvailable();

    /**
     * @brief Sets some preliminary attributes of the bill table widget before iterating over the bill map.
     * Uses the bill map's contents to create the bill table widget before displaying the financial information to the user.
     */
    void createTableWidgetUsingMap();

    /**
     * @brief In the event that a config file already existed in the desired directory, read the config file and store its contents in the bill map.
     * Then, iterate over the bill map and use its contents to display the user's financial information.
     */
    void readConfigAndCreateUI();

    /**
     * @brief Checks a payment status and returns "Paid" or "Not Paid" if the status is true or false respectively.
     * @param p_isBillPaid - Payment status as a boolean, true or false.
     * @return The payment status as a string.
     */
    QString paymentStatusBooleanToString(bool p_isBillPaid);

    /**
     * @brief Checks a payment status and returns true or false if the status is "Paid" or "Not Paid" respectively.
     * @param p_paymentStatus - Payment status as a string, "Paid" or "Not Paid".
     * @return The payment status as a boolean.
     */
    bool paymentStatusStringToBoolean(QString p_paymentStatus);

    QDate convertDateStringToDate(QString p_dateString);

    const QString m_APP_NAME = "PersonalFinanceTool"; //!< The name of the application.
    const QString m_CONFIG_FILE_NAME = m_APP_NAME + ".ini"; //!< The name of the config file.
    const QString m_CONFIG_PARENT_FOLDER = "config/"; //!< The parent folder of the config file.
    const QString m_CONFIG_FILE_DIRECTORY = m_CONFIG_PARENT_FOLDER + m_CONFIG_FILE_NAME; //!< The path where the config file should be read/generated if absent.
    const QString m_CONFIG_FILE_GENERATE_FAIL_BOX_TITLE = "Failure To Generate Configuration File"; //!< The title of the config file generation failure message box.
    const QString m_CONFIG_FILE_GENERATE_FAIL_BOX_INFO_TEXT = "The configuration file could not be generated in " + m_CONFIG_PARENT_FOLDER; //!< The informative text of the config file generation failure message box.
    const QString m_CONFIG_CORRUPT_FILE_BOX_TITLE = "Configuration File Is Corrupt"; //!< The title of the config file corrupt message box.
    const QString m_CONFIG_CORRUPT_FILE_BOX_INFO_TEXT = "The configuration file could not be opened, a new one will be created following the welcoming sequence."; //!< The informative text of the corrupt config file message box.
    const QString m_WELCOME_BOX_PRIMARY_TEXT = "Welcome to the Personal Finance Tool!"; //!< The welcome message box title.
    const QString m_WELCOME_BOX_INFO_TEXT = "On the subsequent screens, you will be asked to provide some financial information."; //!< The welcome message box informative text.
    const QString m_TOTAL_AMOUNT_AVAILABLE = "Total Amount Available"; //!< The total amount available represented as a string.
    const QString m_ASK_FOR_AMOUNT_AVAILABLE_TEXT = "Please enter the total amount of money available in USD."; //!< The total amount available informative text.
    const QString m_INVALID_KEY_BOX_TEXT = "Invalid Configuration File Key/Value Pair";
    const QString m_INVALID_KEY_BOX_INFO_TEXT = "A key/value pair from " + m_CONFIG_FILE_NAME + " is invalid. Please correct the file to have a single value per key and relaunch the application.";
    const double m_DEFAULT_AMOUNT_AVAILABLE = 0.0; //!< The default amount of money available assigned if the user does not provide the actual amount.
    const double m_MIN_AMOUNT_AVAILABLE = 0.0; //!< The minimum amount the user can specify for the total amount of money they have available.
    const double m_MAX_AMOUNT_AVAILABLE = static_cast<double>(INT64_MAX); //!< The maximum amount the user can specify for the total amount of money they have available.
    const int m_NUM_DECIMAL_PLACES = 2; //!< The number of decimal places allowed in the total amount available input box.
    double m_AMOUNT_AVAILABLE_STEP_SIZE = 1.0; //!< The step size for the up and down arrows in the total amount available input box.
    double m_amountAvailable = 0.0; //!< The total amount of money the user has available, defaulted to zero dollars.

    QSettings m_settings; //!< The QSettings object which reads and writes to the configuration file.
    const QString m_FUNDS_INFORMATION_GROUP_LABEL = "FundsInformation"; //!< The group label for the funds information section of the configuration file.
    const QString m_TOTAL_FUNDS_AVAILABLE_KEY = "TotalFundsAvailable"; //!< The total funds available key which maps to the total funds available value.
    const QString m_BILL_AMOUNT_DUE_KEY = "AmountDue"; //!< The amount due key which maps to various amounts due of bills.
    const QString m_BILL_DUE_DATE_KEY = "DueDate"; //!< The due date key which maps to various due dates of bills.
    const QString m_BILL_PAYMENT_STATUS_KEY = "PaymentStatus"; //!< The payment status key which maps to whether or not a bill has been paid.
    const QString m_BILL_NAME_COLUMN_HEADER_STRING = "Bill Name";
    const QString m_BILL_AMOUNT_DUE_COLUMN_HEADER_STRING = "Amount Due";
    const QString m_BILL_DUE_DATE_COLUMN_HEADER_STRING = "Due Date";
    const QString m_BILL_PAYMENT_STATUS_COLUMN_HEADER_STRING = "Payment Status";
    const QString m_PAID_STRING = "Paid"; //!< Payment status of paid represented as a string.
    const QString m_NOT_PAID_STRING = "Not Paid"; //!< Payment status of not paid represented as a string.
    const QString m_SAVE_STRING = "Save"; //!< Save represented as a string.
    const QString m_DATE_STRING_FORMAT = "M/d/yyyy"; //!< The format to use when converting dates to strings.

    BillWidget *m_billWidget; //!< Pointer to a BillWidget which allows the user to enter the bills they wish to keep track of.
    QMap<QString, Bill> m_billMap; //!< Map which stores (key, value) pairs of (the names of bills, corresponding bill objects).
    QTableWidget *m_billTableWidget; //!< Table widget displaying inputted bill information.

    QLabel *m_amountAvailableLabel; //!< The label for the total amount available.
    QLineEdit *m_amountAvailableEdit; //!< The input field for the total amount available, initially set to the user's amount available but can be edited.

    QPushButton *m_saveButton;
};
#endif // MAINWINDOW_H
