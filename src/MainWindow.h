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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
