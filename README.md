# Student Management System  

A command line student management system written in c

## Features  
- Add students (ID, name, semester, course)  
- Display all students  
- Search student by ID  
- Delete student by ID  
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