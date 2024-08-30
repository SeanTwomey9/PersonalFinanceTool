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

#include <QMainWindow>

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

private:

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

    const QString m_APP_NAME = "Personal Finance Tool"; //!< The name of the application.
    const QString m_CONFIG_FILE_NAME = m_APP_NAME + ".ini"; //!< The name of the config file.
    const QString m_CONFIG_FILE_DIRECTORY = "../config/" + m_CONFIG_FILE_NAME; //!< The path where the config file should be read/generated if absent.
    const QString m_WELCOME_BOX_PRIMARY_TEXT = "Welcome to the Personal Finance Tool!"; //!< The welcome message box title.
    const QString m_WELCOME_BOX_INFO_TEXT = "On the subsequent screens, you will be asked to provide some financial information."; //!< The welcome message box informative text.
    const QString m_ASK_FOR_AMOUNT_AVAILABLE_TITLE = "Total Amount Available"; //!< The total amount available input box title.
    const QString m_ASK_FOR_AMOUNT_AVAILABLE_TEXT = "Please enter the total amount of money available in USD."; //!< The total amount available informative text.
    const double m_DEFAULT_AMOUNT_AVAILABLE = 0.0; //!< The default amount of money available assigned if the user does not provide the actual amount.
    const double m_MIN_AMOUNT_AVAILABLE = 0.0; //!< The minimum amount the user can specify for the total amount of money they have available.
    const double m_MAX_AMOUNT_AVAILABLE = static_cast<double>(INT64_MAX); //!< The maximum amount the user can specify for the total amount of money they have available.
    const int m_NUM_DECIMAL_PLACES = 2; //!< The number of decimal places allowed in the total amount available input box.
    double m_AMOUNT_AVAILABLE_STEP_SIZE = 1.0; //!< The step size for the up and down arrows in the total amount available input box.
    double m_amountAvailable = 0.0; //!< The total amount of money the user has available, defaulted to zero dollars.
};
#endif // MAINWINDOW_H
