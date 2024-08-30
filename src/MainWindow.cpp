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

MainWindow::MainWindow()
{
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

void MainWindow::welcomeFirstTimeUser()
{
    QMessageBox welcomeBox;
    welcomeBox.setText(m_WELCOME_BOX_PRIMARY_TEXT);
    welcomeBox.setInformativeText(m_WELCOME_BOX_INFO_TEXT);
    welcomeBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Close);

    int welcomeBoxSelection = welcomeBox.exec();

    switch(welcomeBoxSelection)
    {
        case QMessageBox::Ok:
        {
            // Ask for total funds available
            break;
        }

        case QMessageBox::Close:
        {
            // Close app
            break;
        }

        default:
        {
            break;
        }
    }
}
