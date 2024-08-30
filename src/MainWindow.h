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

private:

    void welcomeFirstTimeUser();

    const QString m_APP_NAME = "Personal Finance Tool";
    const QString m_CONFIG_FILE_NAME = m_APP_NAME + ".ini";
    const QString m_CONFIG_FILE_DIRECTORY = "../config/" + m_CONFIG_FILE_NAME;
    const QString m_WELCOME_BOX_PRIMARY_TEXT = "Welcome to the Personal Finance Tool!";
    const QString m_WELCOME_BOX_INFO_TEXT = "On the subsequent screens, you will be asked to provide some financial information.";
};
#endif // MAINWINDOW_H
