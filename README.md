Library Management System
Overview
The Library Management System (LMS) is a console-based application designed to manage library books and user interactions efficiently. It allows users to perform various operations such as adding, viewing, updating, deleting, and searching for books, as well as managing borrowed books and fines for overdue items. This system is implemented in C++ using a doubly linked list for managing book records and file handling for data persistence.

Features
Add Book: Add new books to the library with details such as Title, Author, ISBN, Publication Year, and Borrowed Status.

View Books: Display a list of all books in the library.

Delete Book: Remove books from the library by specifying the Book ID.

Search Books: Search for books based on Title, Author, ISBN, or Book ID.

Update Books: Modify the details of existing books.

Display Borrowed Books: View a list of books currently borrowed by users.

Display Overdue Books: List books that are overdue along with the applicable fines.

Save and Load Data: Save book records to a file and load them upon startup.
Implementation Details

Data Structure
The system uses a Doubly Linked List to manage book records. Each node in the list contains:

Book Details: Book ID, Title, Author, ISBN, Publication Year, Borrowed Status, Borrowed Date.

Pointers: next and prev pointers to navigate forward and backward through the list

This structure allows efficient insertion and deletion of book records, as well as bidirectional traversal for flexible operations.

File Management
Book records are saved and loaded from a file using a simple CSV format. Each book record is stored as a line in the file with the following fields separated by commas:

BookID (integer)
Title (string)
Author (string)
ISBN (string)
Publication Year (integer)
Borrowed Status (string)
Borrowed Date (string, optional)
The file management functionalities include:

Saving Data: Save the current state of the library to a file to persist changes.
Loading Data: Load book records from a file when the application starts, ensuring that previously saved data is available.
How to Use
Compile and Run: Compile the source code using a C++ compiler. Run the executable to start the application.

Menu Options: Use the menu to navigate between different functionalities:

Add Book: Enter details to add a new book to the library.
View Books: Display all books in the library.
Delete Book: Remove a book by specifying its Book ID.
Search Books: Search for books by Title, Author, ISBN, or Book ID.
Update Books: Modify details of an existing book.
Display Borrowed Books: See which books are currently borrowed.
Display Overdue Books: View overdue books and their fines.
Exit: Save changes to the file and exit the application.
Data Persistence: Upon exiting, the system will prompt whether to save changes to the file. Ensure that data is saved before closing to preserve the current state.

Requirements
C++ Compiler: Requires a C++ compiler to build the application.
Standard Library: Utilizes standard C++ libraries for file handling and data management.
Contributing
Feel free to contribute by submitting issues or pull requests. Contributions to enhance functionality or improve code quality are welcome!

