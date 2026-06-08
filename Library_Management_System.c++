#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Book
{
public:
    int id;
    string title;
    string author;
    bool isIssued;

    Book()
    {
        id = 0;
        title = "";
        author = "";
        isIssued = false;
    }

    Book(int i, string t, string a, bool s)
    {
        id = i;
        title = t;
        author = a;
        isIssued = s;
    }
};

class Library
{
private:
    vector<Book> books;

public:
    void loadBooks()
    {
        books.clear();

        ifstream file("books.txt");

        int id;
        string title;
        string author;
        bool status;

        while (file >> id)
        {
            file.ignore();

            getline(file, title);
            getline(file, author);
            file >> status;
            file.ignore();

            books.push_back(Book(id, title, author, status));
        }

        file.close();
    }

    void saveBooks()
    {
        ofstream file("books.txt");

        for (auto &b : books)
        {
            file << b.id << endl;
            file << b.title << endl;
            file << b.author << endl;
            file << b.isIssued << endl;
        }

        file.close();
    }

    int findBook(int id)
    {
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].id == id)
                return i;
        }
        return -1;
    }

    void addBook()
    {
        int id;
        string title, author;

        cout << "\nEnter Book ID: ";
        cin >> id;

        cin.ignore();

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        books.push_back(Book(id, title, author, false));

        saveBooks();

        cout << "\nBook Added Successfully!\n";
    }

    void viewBooks()
    {
        cout << "\n===== BOOK LIST =====\n";

        for (auto &b : books)
        {
            cout << "\nID     : " << b.id;
            cout << "\nTitle  : " << b.title;
            cout << "\nAuthor : " << b.author;
            cout << "\nStatus : " << (b.isIssued ? "Issued" : "Available");
            cout << "\n----------------------";
        }
    }

    void searchBook()
    {
        int id;

        cout << "\nEnter Book ID: ";
        cin >> id;

        int index = findBook(id);

        if (index == -1)
        {
            cout << "Book Not Found!\n";
            return;
        }

        Book b = books[index];

        cout << "\nBook Found:";
        cout << "\nTitle  : " << b.title;
        cout << "\nAuthor : " << b.author;
        cout << "\nStatus : " << (b.isIssued ? "Issued" : "Available");
    }

    void issueBook()
    {
        int id;

        cout << "\nEnter Book ID to Issue: ";
        cin >> id;

        int index = findBook(id);

        if (index == -1)
        {
            cout << "Book Not Found!\n";
            return;
        }

        if (books[index].isIssued)
        {
            cout << "Book Already Issued!\n";
            return;
        }

        books[index].isIssued = true;

        saveBooks();

        cout << "Book Issued Successfully!\n";
    }

    void returnBook()
    {
        int id;

        cout << "\nEnter Book ID to Return: ";
        cin >> id;

        int index = findBook(id);

        if (index == -1)
        {
            cout << "Book Not Found!\n";
            return;
        }

        if (!books[index].isIssued)
        {
            cout << "Book is not issued!\n";
            return;
        }

        books[index].isIssued = false;

        saveBooks();

        cout << "Book Returned Successfully!\n";
    }
};

int main()
{
    Library lib;

    lib.loadBooks();

    int choice;

    do
    {
        cout << "\n================================";
        cout << "\n LIBRARY MANAGEMENT SYSTEM";
        cout << "\n================================";
        cout << "\n1. Add Book";
        cout << "\n2. View Books";
        cout << "\n3. Search Book";
        cout << "\n4. Issue Book";
        cout << "\n5. Return Book";
        cout << "\n6. Exit";
        cout << "\n================================";
        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            lib.addBook();
            break;

        case 2:
            lib.viewBooks();
            break;

        case 3:
            lib.searchBook();
            break;

        case 4:
            lib.issueBook();
            break;

        case 5:
            lib.returnBook();
            break;

        case 6:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}