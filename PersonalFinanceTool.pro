###################################################################################
#   File name:          PersonalFinanceTool.pro
#   Created on:         08/30/2024
#   Author:             stwomey
#
#   Description:        Project file for the PersonalFinanceTool
#
#   Change History:     See https://github.com/SeanTwomey9/PersonalFinanceTool
#   Relative Location:  PersonalFinanceTool/
#
###################################################################################

QT += core
QT += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# The name of the binary
TARGET = PersonalFinanceTool

# The directory where the binary is generated
DESTDIR = ./bin

OBJECTS_DIR = ./obj
MOC_DIR = ./moc
UI_DIR = ./ui

SOURCES += \
    src/Bill.cpp \
    src/BillWidget.cpp \
    src/main.cpp \
    src/MainWindow.cpp

HEADERS += \
    src/Bill.h \
    src/BillWidget.h \
    src/MainWindow.h

OTHER_FILES += \
    config/*.ini

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
