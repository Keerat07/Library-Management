#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
using namespace std;

class Book {
public:
    int id;
    string title, author;
    bool isIssued;
    Book* next;

    Book(int id, string title, string author) {
        this->id = id;
        this->title = title;
        this->author = author;
        this->isIssued = false;
        this->next = nullptr;
    }

    void display() {
        cout << "ID: " << id << " | Title: " << title << " | Author: " << author
             << " | Issued: " << (isIssued ? "Yes" : "No") << endl;
    }
};

#endif

#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include <string>
using namespace std;

class Member {
public:
    int memberId;
    string name;
    Member* next;

    Member(int memberId, string name) {
        this->memberId = memberId;
        this->name = name;
        this->next = nullptr;
    }

    void display() {
        cout << "Member ID: " << memberId << " | Name: " << name << endl;
    }
};

#endif


#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <string>
using namespace std;

class Transaction {
public:
    int bookId, memberId;
    string date;
    Transaction* next;

    Transaction(int bookId, int memberId, string date) {
        this->bookId = bookId;
        this->memberId = memberId;
        this->date = date;
        this->next = nullptr;
    }

    void display() {
        cout << "Book ID: " << bookId << " | Member ID: " << memberId << " | Date: " << date << endl;
    }
};

#endif


#include "Book.h"
#include "Member.h"
#include "Transaction.h"
#include <iostream>

using namespace std;

class Library {
public:
    Book* bookHead;
    Member* memberHead;
    Transaction* transactionHead;

    Library() {
        bookHead = nullptr;
        memberHead = nullptr;
        transactionHead = nullptr;
    }

    void addBook(int id, string title, string author) {
        Book* newBook = new Book(id, title, author);
        newBook->next = bookHead;
        bookHead = newBook;
        cout << "Book added successfully!\n";
    }

    void addMember(int id, string name) {
        Member* newMember = new Member(id, name);
        newMember->next = memberHead;
        memberHead = newMember;
        cout << "Member registered successfully!\n";
    }

    void issueBook(int bookId, int memberId, string date) {
        Book* book = bookHead;
        while (book) {
            if (book->id == bookId && !book->isIssued) {
                book->isIssued = true;
                Transaction* newTransaction = new Transaction(bookId, memberId, date);
                newTransaction->next = transactionHead;
                transactionHead = newTransaction;
                cout << "Book issued successfully!\n";
                return;
            }
            book = book->next;
        }
        cout << "Book not available or already issued.\n";
    }

    void returnBook(int bookId) {
        Book* book = bookHead;
        while (book) {
            if (book->id == bookId && book->isIssued) {
                book->isIssued = false;
                cout << "Book returned successfully!\n";
                return;
            }
            book = book->next;
        }
        cout << "Book not found or not issued.\n";
    }

    void displayBooks() {
        Book* temp = bookHead;
        while (temp) {
            temp->display();
            temp = temp->next;
        }
    }
};

int main() {
    Library library;
    int choice, id;
    string title, author, name, date;

    while (true) {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n2. Add Member\n3. Issue Book\n4. Return Book\n5. Display Books\n6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Book ID, Title, Author: ";
                cin >> id;
                cin.ignore();
                getline(cin, title);
                getline(cin, author);
                library.addBook(id, title, author);
                break;
            case 2:
                cout << "Enter Member ID, Name: ";
                cin >> id;
                cin.ignore();
                getline(cin, name);
                library.addMember(id, name);
                break;
            case 3:
                cout << "Enter Book ID, Member ID, Issue Date: ";
                cin >> id;
                cin.ignore();
                getline(cin, name);
                library.issueBook(id, stoi(name), name);
                break;
            case 4:
                cout << "Enter Book ID to return: ";
                cin >> id;
                library.returnBook(id);
                break;
            case 5:
                library.displayBooks();
                break;
            case 6:
                exit(0);
            default:
                cout << "Invalid choice. Try again!\n";
        }
    }
    return 0;
}
