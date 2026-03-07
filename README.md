# Student Management System  

A command line student management system written in c

## Features  
- Add students (ID, name, semester, course)  
- Display all students  
- Search student by ID  
- Delete student by ID  
- Update student information by ID  
- Check for duplicate id (basically input validation)  
- Makefile for compilation automation  

## How to build  
```bash
make
```

## How to run  
```bash
./student_manager
```

## How to clean  
```bash
make clean
```

## Structure  
- 'main.c' - initializes the system by calling by interface function which provides a way for the user to interact with the system
- 'interface.h' - function declaration
- 'interface.c' - contains menu logic, handles user input and commandline display formart
- 'student.h' - defines Student and functio declarations
- 'student.c' - contains the core logic of adding, searching, deleting and updating students
- 'file_ops.h' - file function declarations
- 'file_ops.c' - contains functions for saving and loading data from a file
- 'Makefile' - Build automation

## Future plans  
- Remove the array data structure and use a linked list 
- A GUI that will enable regular individuals use it

## Purpose  
This project is for learning purposes, for anyone trying to break into open source to understand how they work  
So its kind of a getway project feel free to contribute any and all ideas  