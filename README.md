# Contact Manager Software Testing Project

## Overview

This project focuses on testing and validating a **C++ Console-Based Contact Manager System**.  
The Contact Manager allows users to manage contact information through core operations such as adding, viewing, searching, updating, and deleting contacts.

The main goal of this project was to verify that the system meets its functional and non-functional requirements through different software testing techniques, including static testing, unit testing, integration testing, dynamic testing, and system testing.

## Project Scope

The testing process covered the main features of the Contact Manager System, including:

- System initialization
- Main menu navigation
- Add contact
- View all contacts
- Search contact
- Update contact
- Delete contact
- Input validation
- JSON file data persistence

## Testing Types Used

### Static Testing
Reviewed the system design, UML diagrams, and implementation without executing the program.  
This helped identify design and code inconsistencies before runtime testing.

### Unit Testing
Tested individual functions separately, such as:

- Adding a valid contact
- Rejecting empty name or phone number
- Validating phone format
- Searching contacts
- Updating contacts
- Deleting contacts
- Detecting duplicate contacts

### Integration Testing
Verified that different modules worked correctly together, such as:

- Console to service layer
- Service layer to JSON file storage
- Loading and saving contacts
- Updating and deleting stored data

### Dynamic Testing
Executed the system manually through the console menu to check actual behavior during runtime.

### System Testing
Tested the full workflow of the application from start to finish, including adding, viewing, searching, updating, and deleting contacts.

## Test Cases Summary

Some of the main test cases included:

| Test ID | Test Case | Status |
|--------|-----------|--------|
| UT-01 | Add valid contact | Passed |
| UT-02 | Add contact with empty name | Passed |
| UT-03 | Add contact with empty phone | Passed |
| UT-04 | Generate unique ID | Passed |
| UT-05 | Validate phone format | Passed |
| UT-06 | Add duplicate contact | Failed |
| IT-01 | Add contact integration | Passed |
| IT-02 | View contacts integration | Passed |
| IT-03 | Search integration | Passed |
| ST-01 | Full workflow test | Passed |
| ST-03 | Data persistence test | Passed |
| DT-08 | Manual JSON modification then update | Failed |

## Defects Found

During testing, several defects were identified and documented, including:

- Duplicate contacts were accepted by the system.
- Manual changes in the JSON file could cause data inconsistency.
- No rollback mechanism existed if saving failed after adding a contact.
- Some validation checks needed improvement.
- Some design diagrams did not fully match the implementation.

A total of **9 defects** were reported. The most important issues were related to duplicate contact handling and JSON file data manipulation.

## Tools and Technologies

- C++
- JSON file storage
- Google Test
- Visual Studio
- Manual Testing
- Static Review
- Dynamic Testing

## Key Features Tested

- Contact creation
- Contact search
- Contact update
- Contact deletion
- Data saving and loading
- Menu navigation
- Input validation
- Error handling
- Data persistence

## Results

Most test cases passed successfully, showing that the Contact Manager System works correctly for its main features.  
However, some issues were found, especially in duplicate contact validation and handling manually edited JSON data.

These issues were documented in the defect log and recommended for future improvement.

## Conclusion

The testing process helped improve confidence in the Contact Manager System by verifying its functionality, reliability, and maintainability.  
The project demonstrated the importance of applying different testing levels, including unit testing, integration testing, system testing, and static review, to detect defects early and improve software quality.

## Team Members

- Mazen Yasser
- Jasmine Ali
- Sandy Atef
- Mariam Mohamed Reyad
- Marwan Ehab

## Course

Software Testing, Validation and Verification  
CSE265  
Faculty of Engineering - MSA University
