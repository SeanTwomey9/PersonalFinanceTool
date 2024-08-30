/*##################################################################################
#   File name:          MainWindow.h
#   Created on:         08/30/2024
#   Author:             stwomey
#
#   Description:        Header file for the MainWindow
#
#   Change History:     See https://github.com/SeanTwomey9/PersonalFinanceTool
#   Relative Location:  PersonalFinanceTool/src/
#
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

    const QString m_APP_NAME = "Personal Finance Tool";
    const QString m_CONFIG_FILE_NAME = m_APP_NAME + ".ini";
    const QString m_CONFIG_FILE_DIRECTORY = "../config/" + m_CONFIG_FILE_NAME;
    const QString m_WELCOME_BOX_PRIMARY_TEXT = "Welcome to the Personal Finance Tool!";
    const QString m_WELCOME_BOX_INFO_TEXT = "On the subsequent screens, you will be asked to provide some financial information.";
    const QString m_ASK_FOR_AMOUNT_AVAILABLE_TITLE = "Total Amount Available";
    const QString m_ASK_FOR_AMOUNT_AVAILABLE_TEXT = "Please enter the total amount of money available in USD.";
    const double m_DEFAULT_AMOUNT_AVAILABLE = 0.0;
    const double m_MIN_AMOUNT_AVAILABLE = 0.0;
    const double m_MAX_AMOUNT_AVAILABLE = static_cast<double>(INT64_MAX);
    const int m_NUM_DECIMAL_PLACES = 2;
    double m_AMOUNT_AVAILABLE_STEP_SIZE = 1.0;
    double m_amountAvailable = 0.0;
};
#endif // MAINWINDOW_H
