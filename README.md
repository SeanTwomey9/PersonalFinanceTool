# PersonalFinanceTool

## Introduction

The PersonalFinanceTool (PFT) is an application which allows a user to keep track of the total amount of money they have available as well as bills which they wish to track. Bills will be tracked in the form of name, amount due, due date, and funded status. The user can fund their tracked bills using the total amount of money available.

## Prerequisites

### Dependencies

Before attempting to utilize the PFT, a user should ensure they have the following installed on their machine:

- Qt source components
- Qt Creator IDE
- C++ compiler
  - Mac/Linux: gcc/g++
  - Windows: gcc/g++, MinGW, or MSVC 
- Build tools
  - CMake (alternative to QMake), Ninja

The user must install Qt-related components via the installer or from source components. It's recommended to create an open-source Qt [account](https://login.qt.io/register) and then install Qt via either the online or offline [installer](https://www.qt.io/download-qt-installer-oss). Below is an example of a Qt installation on Mac which installs all necessary components onto the development machine:

![Qt Installation](/images/qt_installation.png)

Other development tools such as C++ compilers and build tools can be installed manually via package managers/from source but can also be installed via the Qt installer depending on the platform.

### Environment Variables

One method of building Qt projects is with QMake. To ensure the development environment is able to use QMake, the path to the QMake executable must be specified in the user's *PATH* environment variable. On Mac/Linux this can be done by adding a line such as the following to the *.bashrc* file:

`export PATH="/Users/seantwomey/Qt/6.7.1/macos/bin:$PATH"`

On Windows it can be done by adding the path as an entry in the *Path* list via the *Environment Variables* in the settings.

## Installation

To install the source code necessary to build the PFT, the user should clone the repository from this [link](https://github.com/SeanTwomey9/PersonalFinanceTool.git) into a desired directory on the filesystem. Once the code has been cloned, the user should see the following top-level directories and files:

- *Documentation*
  - Contains the Software Design Document (SDD) and SoftwareRequirementsSpecification (SRS) in their own respective folders. 
  - Each folder has a LaTeX source file as well as a PDF for the document. Users can view the PDF for a better understanding of the requirements and design choices which were implemented for the application.
- *src*
  - Contains the source code for the PFT. This folder has the following header and source file pairs:
    - *Bill*
      - Class representing a bill object. Allows creation of bills with their respective names, amount due, due dates, and funding status.
    - *BillWidget*
      - Class representing the widget the user will use to enter the bills they wish to keep track of. This is a widget they will utilize upon first launch, as well as if they choose to add additional bills on subsequent runs of the application.
    - *MainWindow*
      - Class containing the primary user interface (UI) of the application. The bill table widget  is displayed here and the majority of the processing of user data occurs here.
    - *main*
      - Main file to execute the program.
- *.gitignore*
  - Used for indicating which folders and files should not be tracked by git.
  - *PersonalFinanceTool.pro*
    - Qt project file which contains configuration flags, the included source and header files, and more.
  - *README.md*
    - This file which serves as supplemental material to help a user better understand how to obtain, install, and utilize the PFT.

## Execution

Assuming the prerequisites from above have been met and the source code has been cloned, the user should perform the following steps to run the PFT:

1. Change directory into the *PersonalFinanceTool* folder.
2. `qmake`
3. `make clean`
4. `make`
5. `sudo make install`
6. The user should see they now have a *bin* folder within the *PersonalFinanceTool* folder. The *PersonalFinanceTool* executable file can now be run. Note, if on Linux or Windows this file should simply reside in the *bin* folder. If on Mac, it may be several directories deeper, likely in *bin/PersonalFinanceTool.app/Contents/MacOS/* .

If all was successful, the user should receive a pop-up welcoming them to the PFT.

## Usage

The following sections will detail various functionalities of the PFT.

### Entering Total Amount Available

Upon the initial run of the PFT, the user will receive a welcome pop-up, followed by a prompt to enter the total amount of money they have available in United States Dollars (USD).

![Entering Total Amount Available](/images/total_amount_available_request.png)

### Bill Entry

Following the total amount available request, the user will be prompted to enter the bills they wish to keep track of via the bill widget. They'll be asked for the name of the bill, the amount due in USD, and the due date. When entering the due date, they can either manually type it in in *mm/dd/yyyy* format, or utilize the calendar view to select the date instead.

![Bill Entry](/images/bill_entry.png)

While entering bills, the user can click the *Close* button to terminate the application, the *Enter Another Bill* button to save the currently entered bill and reopen the bill widget for entry of another bill, and the *Done* button to save the currently entered bill and display the bill table widget.

### Configuration File

As the user enters their bill information, the data entered will be written to a *.ini* configuration file. The file will be generated in a top level folder (*PersonalFinanceTool/config/*). Below is an example of what this configuration file will resemble:

```ini
[Car]
AmountDue=300.50
DueDate=11/15/2024
FundingStatus=Not Funded

[FundsInformation]
TotalFundsAvailable=100.00

[Loans]
AmountDue=200.00
DueDate=11/28/2024
FundingStatus=Not Funded

[Rent]
AmountDue=1200.00
DueDate=11/1/2024
FundingStatus=Not Funded
```

This file will be read on subsequent runs of the application to populate the bill table widget where the user can manage their bills (discussed in next section). The user can edit this information in the configuration file if they so choose, and the updated information will be used for the next run of the PFT. The file ultimately allows the user to not have to re-enter their financial information on each run of the application as it allows them to "save the state" of their financial information.

### Managing Bills

After the user is finished entering their bills, the bill table widget will be displayed. This will display their entered bills, sorted in alphabetical order by name.

![Managing Bills](/images/bill_table_widget.png)

The bill table widget can be used like a standard table, each cell can be edited via either entering text or interacting with a dropdown depending on the specific cell. The user can also select multiple rows in the widget and make use of the convenience buttons in the top right corner. When the user is finished making changes to their bill information, they can click the *Save* button which will update the total amount available (if they chose to fund or defund any bills) and write the updated information out to the configuration file.

If the user wishes to reset their inputted bills, they can click the *Reset Bills* button. If they confirm this action, their existing data will be wiped and they'll be prompted to enter their next round of bills. Otherwise if they cancel the action, they'll retain their data and be returned to the bill widget.

## Common Errors

1. If the user does not enter a name for the bill and/or the amount due, they will receive an error message indicating there's missing bill information.

![Missing Bill Information](/images/missing_bill_information.png)

This can be resolved by ensuring that each bill is added with an appropriate name, amount due, and due date.

2. ```make: *** No rule to make target `PersonalFinanceTool'.  Stop.```

  This can occur if the Software Development Kit (SDK) or a different element of the development environment has changed since the previous build of the application. This can be resolved by removing the *.qmake.stash* file from the application folder.
