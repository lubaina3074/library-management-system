#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <chrono>
#include <ctime>

using namespace std;

class Books // Books class to store all the book objects
{
public:
    int bookID;
    string title;
    string author;
    string isbn;
    int publicationYear;
    string borrowed;
    string borrowedDate;

    Books(int id, const string &t, const string &a, const string &i, int year, const string &b, const string &bd) : bookID(id), title(t), author(a), isbn(i), publicationYear(year), borrowed(b), borrowedDate(bd) {}
};

class Node // Node class to store the Book nodes
{
public:
    Books data;
    Node *prev;
    Node *next;

    Node(const Books &data)
        : data(data), prev(nullptr), next(nullptr) {}
};

class BooksList // Books list for the doubly linked list
{
public:
    Node *head;
    Node *tail;
    int size;

    BooksList() : head(nullptr), tail(nullptr), size(0) {}

    ~BooksList()
    {
        Node *current = head;
        while (current)
        {
            Node *toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }

    void AddBook(const Books &book) // adding book function
    {
        Node *newNode = new Node(book);
        if (head == nullptr && tail == nullptr)
        {
            head = tail = newNode;
            size++;
        }

        // insert before head
        else if (book.bookID < head->data.bookID)
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;

            size++;
            return;
        }

        // insert after tail
        else if (book.bookID > tail->data.bookID)
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;

            size++;
            return;
        }

        else
        {

            Node *current = head;

            // general case: insert between the nodes
            while (current != nullptr && current->data.bookID < book.bookID)
            {
                current = current->next;
            }

            newNode->prev = current->prev;
            newNode->next = current;
            current->prev->next = newNode;
            current->prev = newNode;

            size++;
        }
    }

    void addBookFromUserInput() // user inputs the book's information
    {
        int bookID, publicationYear;
        string title, author, isbn, borrowed, borrowedDate;

        cout << "Enter Book ID: ";
        cin >> bookID;
        cin.ignore();

        cout << "Enter Title: ";
        getline(cin, title);

        cout << "Enter Author: ";
        getline(cin, author);

        cout << "Enter ISBN: ";
        getline(cin, isbn);

        cout << "Enter Publication Year: ";
        cin >> publicationYear;
        cin.ignore();

        cout << "Enter status (borrowed or available): ";
        getline(cin, borrowed);

        toLowerCase(borrowed);

        if (borrowed == "borrowed")
        {
            cout << "Enter the date the book was borrowed (dd/mm/yyyy): ";
            getline(cin, borrowedDate);
        }
        else
        {
            borrowedDate = "N/A"; // default for not borrowed books
        }

        Books newBook(bookID, title, author, isbn, publicationYear, borrowed, borrowedDate);
        AddBook(newBook);

        cout << "Book added successfully!" << endl;
    }

    void deleteAllNodes() // delete all books
    {
        Node *current = head;
        while (current != nullptr)
        {
            Node *toDelete = current;
            current = current->next;
            delete toDelete;
        }

        head = nullptr;
        tail = nullptr;
        size = 0;

        cout << "All nodes have been deleted." << endl;
    }

    void displayAllNodes() const // display all books
    {
        if (head == nullptr)
        {
            cout << "No books in the list." << endl;
            return;
        }

        Node *current = head;
        while (current)
        {
            const Books &book = current->data;
            cout << book.bookID << ","
                 << book.title << ","
                 << book.author << ","
                 << book.isbn << ","
                 << book.publicationYear << ","
                 << book.borrowed << ","
                 << book.borrowedDate << "\n";

            current = current->next;
        }

        cout << endl;

        cout << "There are " << size << " books currently in the list" << endl;
    }

    void SaveToFile() const // saves all the book nodes to the "books.txt" file
    {
        ofstream outFile("books.txt", ios::trunc);
        if (outFile.is_open())
        {
            Node *current = head;
            while (current)
            {
                const Books &book = current->data;
                outFile << book.bookID << ","
                        << book.title << ","
                        << book.author << ","
                        << book.isbn << ","
                        << book.publicationYear << ","
                        << book.borrowed << ","
                        << book.borrowedDate << "\n";

                current = current->next;
            }
            outFile.close();
        }
        else
        {
            cerr << "Failed to open the file." << endl;
        }
    }

    int loadFile(const string &filename) // at the start of the program, loads all of the books in the file to the linked list
    {
        ifstream file(filename);

        if (!file.is_open())
        {
            cerr << "Failed to open the file." << endl;
            return 1;
        }

        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            int bookID, publicationYear;
            string title, author, isbn, borrowed, borrowedDate;

            ss >> bookID;
            ss.ignore();

            getline(ss, title, ',');

            getline(ss, author, ',');

            getline(ss, isbn, ',');

            ss >> publicationYear;
            ss.ignore();

            getline(ss, borrowed, ',');

            getline(ss, borrowedDate);

            Books newBook(bookID, title, author, isbn, publicationYear, borrowed, borrowedDate);
            AddBook(newBook);
        }

        file.close();
        return 0;
    }

    int searchBook() //search for a prticular using a particular field
    {
        int choice;
        int bookid = 0;

        cout << "How would you like to search for the book?" << endl;
        cout << "--------------------------" << endl;
        cout << "1. Search by Title" << endl;
        cout << "2. Search by Author" << endl;
        cout << "3. Search by ISBN" << endl;
        cout << "4. Search by Book ID" << endl;
        cout << "--------------------------" << endl;
        cout << endl;
        cout << "Enter your choice here (1-4): ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            bookid = searchByTitle();
            break;

        case 2:
            bookid = SearchByAuthor();
            break;

        case 3:
            bookid = SearchByISBN();
            break;

        case 4:
            bookid = searchByID();
            break;

        default:
            cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
            break;
        }

        return bookid;
    }

    int searchByID() const
    {

        int bookid;
        cout << "Please enter the book ID of the book you want to search for: ";

        cin >> bookid;
        cin.ignore();

        Node *first = head;
        Node *last = tail;
        bool found = false;

        while (first != nullptr || last != nullptr)
        {
            if (first != nullptr && first->data.bookID == bookid)
            {
                cout << endl;
                cout << first->data.bookID << endl;
                cout << first->data.title << endl;
                cout << first->data.author << endl;
                cout << first->data.isbn << endl;
                cout << first->data.publicationYear << endl;
                cout << first->data.borrowed << endl;
                cout << first->data.borrowedDate << endl;
                cout << endl;
                found = true;

                return first->data.bookID;

                break;
            }

            if (last != nullptr && last->data.bookID == bookid) //searches both ways for faster retrieval
            {
                cout << endl;
                cout << last->data.bookID << endl;
                cout << last->data.title << endl;
                cout << last->data.author << endl;
                cout << last->data.isbn << endl;
                cout << last->data.publicationYear << endl;
                cout << last->data.borrowed << endl;
                cout << last->data.borrowedDate << endl;
                cout << endl;

                found = true;
                return last->data.bookID;
                break;
            }

            if (first != nullptr)
            {

                first = first->next;
            }

            if (last != nullptr)
            {

                last = last->prev;
            }
        }

        if (!found)
        {
            cout << "This book is not in the list!" << endl;
            return 0;
        }
        return 0;
    }

    void toLowerCase(string &str) //converts string into lower case
    {
        transform(str.begin(), str.end(), str.begin(), ::tolower);
    };

    int searchByTitle()
    {

        bool found = false;
        string title;

        cout << "Please enter the title of the book you are searching for: ";
        getline(cin, title);
        toLowerCase(title);

        Node *first = head;

        if (head == nullptr)
        {
            cout << "No books in the list!" << endl;
        }

        while (first != nullptr)
        {
            string booktitle;

            booktitle = first->data.title;
            toLowerCase(booktitle);

            if (booktitle == title)
            {

                cout << endl;
                cout << first->data.bookID << endl;
                cout << first->data.title << endl;
                cout << first->data.author << endl;
                cout << first->data.isbn << endl;
                cout << first->data.publicationYear << endl;
                cout << first->data.borrowed << endl;
                cout << first->data.borrowedDate << endl;
                cout << endl;

                return first->data.bookID;
                found = true;
            }

            if (first != nullptr)
            {
                first = first->next;
            }
        }

        cout << "Book not found!" << endl;
        found = false;
        return 0;
    }

    int SearchByISBN()
    {

        bool found = false;
        string ISBN;
        cout << "Enter the ISBN: ";
        getline(cin, ISBN);

        Node *first = head;

        if (head == nullptr)
        {
            cout << "No books in the list!" << endl;
        }

        while (first != nullptr)
        {
            if (first->data.isbn == ISBN)
            {
                cout << endl;
                cout << first->data.bookID << endl;
                cout << first->data.title << endl;
                cout << first->data.author << endl;
                cout << first->data.isbn << endl;
                cout << first->data.publicationYear << endl;
                cout << first->data.borrowed << endl;
                cout << first->data.borrowedDate << endl;
                cout << endl;
                return first->data.bookID;

                found = true;
            }

            if (first != nullptr)
            {
                first = first->next;
            }
        }

        cout << "Book not found! " << endl;
        found = false;
        return 0;
    }

    int SearchByAuthor()
    {

        bool found = false;
        string author;
        string authorlist;
        cout << "Enter the author's name: ";
        getline(cin, author);
        toLowerCase(author);

        Node *first = head;
        int count = 0;
        int no_of_books[size];

        if (head == nullptr)
        {
            cout << "No books in the list!" << endl;
        }

        while (first != nullptr)
        {
            authorlist = first->data.author;
            toLowerCase(authorlist);

            if (authorlist == author)
            {
                no_of_books[count] = first->data.bookID;
                count++;

                cout << endl;
                cout << first->data.bookID << endl;
                cout << first->data.title << endl;
                cout << first->data.author << endl;
                cout << first->data.isbn << endl;
                cout << first->data.publicationYear << endl;
                cout << first->data.borrowed << endl;
                cout << first->data.borrowedDate << endl;
                cout << endl;
            }

            first = first->next;
        }

        if (count > 1)
        {
            int choice;
            cout << "Which book are you searching for from the list (enter Book ID): ";
            cin >> choice;
            cin.ignore();

            for (int i = 0; i < count; i++)
            {
                if (choice == no_of_books[i])
                {
                    return no_of_books[i];
                    found = true;
                }
            }
        }
        if (count == 0)
        {
            cout << "Book not found!" << endl;
            found = false;
            return 0;
        }
        return 0;
    }

    int deleteBook() //delete a certain book
    {
        int bookid;
        cout << "Enter the book ID of the book you want to delete: ";
        cin >> bookid;
        bool found = false;

        Node *first = head;

        while (first != nullptr)
        {
            if (first->data.bookID == bookid)
            {

                if (first == head) // the bookID is the first node
                {
                    head = first->next;
                    if (head != nullptr) // more than one node
                    {
                        head->prev = nullptr;
                    }
                    else // only one node
                    {
                        tail = nullptr;
                    }
                }
                else if (first == tail)
                {
                    tail = first->prev;
                    if (tail != nullptr) // list had more than one node
                    {
                        tail->next = nullptr;
                    }
                }

                else
                {

                    first->prev->next = first->next;
                    first->next->prev = first->prev;
                }

                cout << endl;
                cout << first->data.bookID << endl;
                cout << first->data.title << endl;
                cout << first->data.author << endl;
                cout << first->data.isbn << endl;
                cout << first->data.publicationYear << endl;
                cout << first->data.borrowed << endl;
                cout << first->data.borrowedDate << endl;
                cout << endl;

                string decision;

                cout << "Are you sure you want to delete this book (yes/no): ";
                cin.ignore();
                getline(cin, decision);
                toLowerCase(decision);

                if (decision == "yes")
                {
                    delete first; // Delete the node
                    cout << "Book with ID " << bookid << " has been deleted." << endl;
                    return 1; // Deletion successful
                }
                else if (decision == "no")
                {
                    cout << "Book is not deleted " << endl;
                    return 0;
                }
                else
                {
                    cout << "Please enter a valid choice" << endl;
                    return 0;
                }
            }

            first = first->next;
        }
        cout << "Book with ID " << bookid << " not found." << endl;
        return 0; // Return failure if not found
    }

    int UpdateBookStatus(int &bookid)
    {

        if (head == nullptr)
        {
            cout << "No books in the list!" << endl;
        }

        if (bookid > tail->data.bookID)
        {
            cout << "Book ID is not in the list! " << endl;
            return 0;
        }

        Node *current = head;

        while (current != nullptr)
        {

            if (current->data.bookID == bookid)
            {
                if (current->data.borrowed == "borrowed")
                {
                    current->data.borrowed = "available";
                    current->data.borrowedDate = "N/A";
                }
                else
                {
                    string borroweddate;
                    current->data.borrowed = "borrowed";
                    cout << "What date was it borrowed: ";
                    getline(cin, borroweddate);
                    current->data.borrowedDate = borroweddate;
                }
                cout << "Status has been updated! " << endl;
                return 1;
                break;
            }

            current = current->next;
        }
        cout << "Book ID not found!" << endl;
        return 0;
    }

    int updateTitle(int &bookid)
    {
        string newtitle;
        cout << "Enter the new title for the book: ";
        cin.ignore();
        getline(cin, newtitle);

        Node *current = head;

        if (head == nullptr)
        {
            cout << "No books in the list" << endl;
            return 0;
        }

        while (current->data.bookID != bookid)
        {
            current = current->next;
        }

        if (current == nullptr)
        {
            cout << "Book ID not found" << endl;
            return 0;
        }

        if (current->data.bookID == bookid)
        {
            current->data.title = newtitle;
            cout << endl;
            cout << "Book title has been updated" << endl;
            return 1;
        }

        return 0;
    }

    int updateAuthor(int &bookid)
    {
        string newAuthor;
        cout << "Enter the new Author for the book: ";
        cin.ignore();
        getline(cin, newAuthor);

        Node *current = head;

        if (head == nullptr)
        {
            cout << "No books in the list" << endl;
            return 0;
        }

        while (current->data.bookID != bookid)
        {
            current = current->next;
        }

        if (current == nullptr)
        {
            cout << "Book ID not found" << endl;
            return 0;
        }

        if (current->data.bookID == bookid)
        {
            current->data.author = newAuthor;
            cout << endl;
            cout << "Book author has been updated" << endl;
            return 1;
        }
        return 0;
    }

    int updateISBN(int &bookid)
    {
        string newISBN;
        cout << "Enter the new ISBN for the book: ";
        cin.ignore();
        getline(cin, newISBN);

        Node *current = head;

        if (head == nullptr)
        {
            cout << "No books in the list" << endl;
            return 0;
        }

        while (current->data.bookID != bookid)
        {
            current = current->next;
        }

        if (current == nullptr)
        {
            cout << "Book ID not found" << endl;
            return 0;
        }

        if (current->data.bookID == bookid)
        {
            current->data.isbn = newISBN;
            cout << endl;
            cout << "Book ISBN has been updated" << endl;
            return 1;
        }
        return 0;
    }

    int updatePubYear(int &bookid)
    {
        int newYear;
        cout << "Enter the new publication year for the book: ";
        cin.ignore();
        cin >> newYear;

        Node *current = head;

        if (head == nullptr)
        {
            cout << "No books in the list" << endl;
            return 0;
        }

        while (current->data.bookID != bookid)
        {
            current = current->next;
        }

        if (current == nullptr)
        {
            cout << "Book ID not found" << endl;
            return 0;
        }

        if (current->data.bookID == bookid)
        {
            current->data.publicationYear = newYear;
            cout << endl;
            cout << "Book publication year has been updated" << endl;
            return 1;
        }
        return 0;
    }

    int updateBook() //update a book's fields, continues until a user decides to exit
    {

        int bookid = searchBook();

        if (bookid == 0)
        {
            cout << endl;
            searchBook();
            cout << endl;
            return 0;
        }

        else
        {
            string reply;

            cout << "Are you sure this is the book you want to update? (y/n): ";

            getline(cin, reply);

            toLowerCase(reply);

            if (reply == "y")
            {
                int choice1;

                do
                {

                    cout << endl;
                    cout << "What book information do you want to update: " << endl;
                    cout << "--------------------------" << endl;
                    cout << "1. Title" << endl;
                    cout << "2. Author" << endl;
                    cout << "3. ISBN" << endl;
                    cout << "4. Publication Year" << endl;
                    cout << "5. Book Status" << endl;
                    cout << "6. Exit" << endl;
                    cout << "--------------------------" << endl;
                    cout << endl;
                    cout << "Enter your choice here (1-6): ";
                    cin >> choice1;
                    cin.ignore();
                    cout << endl;

                    switch (choice1)
                    {
                    case 1:
                        updateTitle(bookid);
                        break;

                    case 2:
                        updateAuthor(bookid);
                        break;
                    case 3:
                        updateISBN(bookid);
                        break;
                    case 4:
                        updatePubYear(bookid);
                        break;
                    case 5:
                        UpdateBookStatus(bookid);
                        break;
                    case 6:
                        cout << "Going back to the main menu" << endl;
                        break;
                    default:
                        cout << "Please enter a number between 1 and 6" << endl;
                        break;
                    }
                } while (choice1 != 6);
                return 0;
            }
            else if (reply == "n")
            {
                updateBook();
            }
            else
            {
                cout << "Please answer yes or no (y/n)" << endl;
            }
        }
        return 0;
    }

    int showBorrowed() //show the borrowed books
    {

        Node *current = head;

        if (head == nullptr)
        {
            cout << "No books in the list!" << endl;
            return 0;
        }

        while (current != nullptr)
        {
            string borrowedList = current->data.borrowed;
            toLowerCase(borrowedList);

            if (current->data.borrowed == "borrowed")
            {
                cout << endl;
                cout << current->data.bookID << endl;
                cout << current->data.title << endl;
                cout << current->data.author << endl;
                cout << current->data.isbn << endl;
                cout << current->data.publicationYear << endl;
                cout << current->data.borrowed << endl;
                cout << current->data.borrowedDate << endl;
                cout << endl;
            }

            current = current->next;
        }

        return 0;
    }

    tm parseDate(string &datestr) //parse the borrowed date field
    {
        tm date = {};
        stringstream ss(datestr);
        ss >> get_time(&date, "%d/%m/%Y");
        return date;
    }

    int display0verdueBook() //display overdue books
    {
        Node *current = head;

        while (current != nullptr)
        {

            string datestr = current->data.borrowedDate;
            double fine = 0;

            if (datestr != "N/A")
            {

                tm borroweddate = parseDate(datestr);
                time_t borrowedtime = mktime(&borroweddate);

                time_t currenttime = time(nullptr);
                double difference = difftime(currenttime, borrowedtime) / (60 * 60 * 24);

                if (difference > 7)
                {
                    int overdueDays = difference - 7;
                    fine = overdueDays * 0.50;
                    cout << endl;
                    cout << current->data.bookID << endl;
                    cout << current->data.title << endl;
                    cout << current->data.author << endl;
                    cout << current->data.isbn << endl;
                    cout << current->data.publicationYear << endl;
                    cout << current->data.borrowed << endl;
                    cout << current->data.borrowedDate << endl;
                    cout << "$" << fine << endl;
                    cout << endl;
                }
            }

            current = current->next;
        }

        return 0;
    }
};
