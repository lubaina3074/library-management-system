#include "librarian.hpp"
using namespace std;
#include <iostream>
#include <string.h>
#include <stdio.h>

void displayMenu()
{
    cout << "Welcome to the Library Management System!" << endl;
    cout << "What action do you want to perform?" << endl;
    cout << "--------------------------" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. View Books" << endl;
    cout << "3. Delete Book" << endl;
    cout << "4. Search Books" << endl;
    cout << "5. Update Books" << endl;
    cout << "6. Display borrowed books" << endl;
    cout << "7. Display overdue books" << endl;
    cout << "8. Exit" << endl;
    cout << "Enter your choice (1-8): ";
}

int main()
{

    int choice;
    BooksList booklist;
    booklist.loadFile("books.txt");
    string reply;
    bool changesMade = false;

    do
    {
        displayMenu();
        cin >> choice;
        cin.ignore();
        cout << endl;

        switch (choice)
        {
        case 1:
            booklist.addBookFromUserInput(); // Call the function to add a book
            changesMade = true;
            break;
        case 2:
            booklist.displayAllNodes(); // Call the function to view books
            break;
        case 3:
            booklist.deleteBook(); // Call the function to delete a book
            changesMade = true;
            break;
        case 4:
            booklist.searchBook(); // Call the function to search books
            break;
        case 5:
            booklist.updateBook(); // Call the function to search books
            changesMade = true;
            break;
        case 6:
            booklist.showBorrowed(); //Call the function to display the borrowed books
            break;
        case 7:
            booklist.display0verdueBook(); //Call the funcion to display the overdue books
            break;
        case 8:

            if (changesMade) //only if the books list has been updated
            {
                cout << "Do you want to save the updated books to the file? (y/n): ";
                getline(cin, reply);
                if (reply == "y" || reply == "Y")
                {
                    booklist.SaveToFile();
                    cout << "Exiting program. Goodbye!" << endl;
                    break;
                }
                else
                {
                    cout << "Exiting program. Goodbye!" << endl;
                    break;
                }
            }
            cout << "Exiting program. Goodbye!" << endl;
            break;

        default:
            cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
            break;
        }

        cout << endl; 

    } while (choice != 8);

    return 0;
}