/*##################################################################################
#   File name:          main.cpp
#   Created on:         08/30/2024
#   Author:             stwomey
#   Description:        Main file for the PersonalFinanceTool
#   Change History:     See https://github.com/SeanTwomey9/PersonalFinanceTool
#   Relative Location:  PersonalFinanceTool/src/
##################################################################################*/

#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // Create the application object
    QApplication application(argc, argv);

    // Create the main window object
    MainWindow window;

    // Start the main application thread
    return application.exec();
}
