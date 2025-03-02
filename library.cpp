#include <iostream>
#include <string>
#include "library.h"

using namespace std;

//Destructor
Library::~Library() {
    for(int i = 0; i < numBooks; i++) {
        delete library[i];
    }

    library.clear();
    numBooks = 0;

    cout << "Library has been destroyed." << endl;
}

//Add book
void Library::addBook(const Book& book) {
    Book* newBook = new Book(book.title, book.author, book.ISBN, book.availability, book.dueDate);
    library.push_back(newBook);

    cout << book.title << " added successfully!" << endl;

    numBooks++;
}

//Removes book using title & ISBN
void Library::removeBook(string text) {
    for(int i = 0; i < numBooks; i++) {
        if(library[i]->title == text || library[i]->ISBN == text) {
            cout << library[i]->title << " removed successfully!" << endl;
            
            delete library[i];
            library.erase(library.begin() + i);

            numBooks--;

            return;
        }
    }

    cout << "Book not found." << endl;
}

//Get book address
Book* Library::getBook(string text) const {
    for (const auto& book : library) {
        if (book->title == text || book->ISBN == text) {
            return book;
        }
    }

    return nullptr;
}

//Prints information of book
void Library::printBookInformation(Book* book) const {
    cout << "Title: " << book->title << endl;
    cout << "Author: " << book->author << endl;
    cout << "ISBN: " << book->ISBN << endl;
    if(book->availability == true){
        cout << "Availability: " << "Available" << endl;
    } else {
        cout << "Availability: " << "Not Available" << endl;
        cout << "Date of Return: " << book->dueDate << endl;
    }
}

//Search for books with title, author, and ISBN
void Library::searchBook(string text) const {
    for (const auto& book : library) {
        if (book->title == text || book->ISBN == text) {
            printBookInformation(book);
            return;
        }
    }

    cout << "Book not found" << endl;
}

//Search book existence
bool Library::searchBookExistence(string text) const {
    for (const auto& book : library) {
        if (book->title == text || book->ISBN == text) {
            return true;
        }
    }

    return false;
}

//Checkout book
void Library::checkoutBook(string text, string date) {
    for (const auto& book : library) {
        if (book->title == text || book->ISBN == text) {
            book->dueDate = date;
            book->availability = false;
            return;
        }
    }
    cout << "Book not found" << endl;
}

//Return book
void Library::returnBook(string text) const {
    for (const auto& book : library) {
        if (book->title == text || book->ISBN == text) {
            book->dueDate = "";
            book->availability = true;
            return;
        }
    }
    cout << "Book not found" << endl;
}