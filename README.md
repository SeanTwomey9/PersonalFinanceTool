# PersonalFinanceTool

## Introduction

The PersonalFinanceTool (PFT) is an application which allows a user to keep track of the total amount of money they have available as well as bills which they wish to track. Bills will be tracked in the form of name, amount due, due date, and funded status. The user can allocate funds from their total amount available to their tracked bills.

## Prerequisities

Before attempting to utilize the PFT, a user should ensure they have the following installed on their machine:

- gcc/g++
- Qt installation granting access to Qmake executable
- Add the path to the Qmake executable to PATH environment variable

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
      - Class containing the primary user interface (UI) of the application. The financial dashboard is displayed here and the majority of the processing of user data occurs here.
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
6. The user should see they now have a *bin* folder within the *PersonalFinanceTool* folder. Run the executable file inside that folder.

If all was successful, the user should receive a pop-up welcoming them to the PFT.

## Usage

The following sections will detail various functionalities of the PFT.

### Entering Total Amount Available

Upon the initial run of the PFT, the user will receive a welcome pop-up, followed by a prompt to enter the total amount of money they have available in United States Dollars (USD).

![Entering Total Amount Available](/images/total_amount_available_request.png)

### Bill Entry

Following the total amount available request, the user will be prompted to enter the bills they wish to keep track of via the bill widget. They'll be asked for the name of the bill, the amount due in USD, and the due date. When entering the due date, they can either manually type it in in *mm/dd/yyyy* format, or utilize the calendar view to select the date instead.

![Bill Entry](/images/bill_entry.png)

If the user does not enter a name for the bill and/or the amount due, they will receive an error message indicating there's missing bill information.

![Missing Bill Information](/images/missing_bill_information.png)

While entering bills, the user can click the *Close* button to terminate the application, the *Enter Another Bill* button to save the currently entered bill and relaunch the Bill Entry widget, and the *Done* button to save the currently entered bill and display the financial dashboard.

### Configuration File

As the user enters their bill information, the data entered will be written to a *.ini* configuration file. The file will be generated in a top level folder (*PersonalFinanceTool/config/*).

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

This file will be read on subsequent runs of the application to populate the bill table widget where the user can manage their bills (discussed in next section). The user can edit this information in the configuration file if they so choose, and the updated information will be used for the next run of the PFT.

### Managing Bills

After the user is finished entering their bills, the bill table widget will be displayed. This will display their entered bills, sorted in alphabetical order by name.

![Managing Bills](/images/bill_table_widget.png)

The bill table widget can be used like a standard table, each cell can be edited via either entering text or interacting with a dropdown depending on the specific cell. The user can also select multiple rows in the widget and make use of the convenience buttons in the top right corner. When the user is finished making changes to their bill information, they can click the *Save* button which will update the total amount available (if they chose to fund or defund any bills) and write the updated information out to the configuration file.