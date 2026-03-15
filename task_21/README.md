## 21
Design a struct which will have members that describe an employee's:

last name,
first name,
employee ID number,
last 4 digits of their SSN, and
title.

Design a second struct which will store two employees as members. The employees will be structures of the type of your first struct. Inside of main(), prompt the user to enter each employee's credentials and store them. Finally, print the employee's credentials to the terminal.

output

```terminal_session
Enter the employee's first name: yeisrael dawit
Enter the employee's last name: Enter the employee's ID number: 2
Enter the last four digits of the employee's SSN: 98
Enter the employee's job title (do not include the word 'Engineer'): dev

Enter the employee's first name: ana
Enter the employee's last name: something 
Enter the employee's ID number: 34
Enter the last four digits of the employee's SSN: 54
Enter the employee's job title (do not include the word 'Engineer'): dev


Employee information for yeisrael dawit:
ID: 12
SSN: 98
Title: dev Engineer

Employee information for ana something:
ID: 34
SSN: 54
Title: dev Engineer

```