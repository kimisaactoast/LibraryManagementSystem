#include <iostream>
#include <string>
#include "accounts.h"
#include "library.h"

using namespace std;

//Add checked out book
void Account::addCheckedOutBook(const Book& book) {            
    Book* newBook = new Book(book.title, book.author, book.ISBN, book.availability, book.dueDate);
    checkedOutBooks.push_back(newBook);

    numCheckedOutBooks++;
}

//Remove checked out book
void Account::removeCheckedOutBook(string text) {
    for(int i = 0; i < numCheckedOutBooks; i++) {
        if(checkedOutBooks[i]->title == text) {
            delete checkedOutBooks[i];
            checkedOutBooks.erase(checkedOutBooks.begin() + i);

            numCheckedOutBooks--;

            return;
        }
    }
}

//Print checked out books
void Account::printCheckedOutBooks() const {
    for (const auto& book : checkedOutBooks) {
        cout << "Title: " << book->title << ", Due Date: " << book->dueDate << endl;
    }

    if(numCheckedOutBooks == 0) {
        cout << "No books checked out." << endl;
    }
}

//Check if book is in checked out books
bool Account::checkBook(string text) const {
    for (const auto& book : checkedOutBooks) {
        if (book->title == text || book->ISBN == text) {
            return true;
        }
    }

    return false;
}

//Destructor for AccountList
AccountList::~AccountList() {
    for(int i = 0; i < numOfAccounts; i++) {
        delete accounts[i];
    }

    accounts.clear();
    numOfAccounts = 0;

    cout << "Account list has been destroyed." << endl;
}

//Add account to system
void AccountList::addAccount(const Account& account) {
    Account* newAccount = new Account(account.username, account.password);
    accounts.push_back(newAccount);

    cout << account.username << " registered successfully! ";

    numOfAccounts++;
}

//Remove account from system
void AccountList::removeAccount(string text) {
    for(int i = 0; i < numOfAccounts; i++) {
        if(accounts[i]->username == text) {
            cout << accounts[i]->username << " removed successfully!" << endl;
            
            delete accounts[i];
            accounts.erase(accounts.begin() + i);

            numOfAccounts--;

            return;
        }
    }

    cout << "Account not found." << endl;
}

//Validate account
bool AccountList::validateAccount(string username, string password) const {
    for (const auto& account : accounts) {
        if (account->username == username && account->password == password) {
            return true;
        }
    }

    return false;
}

//Search account
Account* AccountList::searchAccount(string text) const {
    for (const auto& account : accounts) {
        if (account->username == text) {
            return account;
        }
    }

    return nullptr;
}