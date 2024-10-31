# PersonalFinanceTool

## Introduction

The PersonalFinanceTool (PFT) is an application which allows a user to keep track of the total amount of money they have available as well as bills which they wish to track. Bills will be tracked in the form of name, amount due, and due date. The user can allocate funds from their total amount available to their tracked bills.

## Prerequisities

Before attempting to utilize the PFT, a user should ensure they have the following installed on their machine:

- `gcc/g++`
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
 