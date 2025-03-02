#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include "library.h"

using namespace std;

class Account {
    private:
        string username;
        string password;
        vector<Book*> checkedOutBooks;
        int numCheckedOutBooks;

        friend class AccountList;

    public:
        //Getter
        inline string getUsername() const { return username; }
        inline string getPassword() const { return password; }
        inline int getNumCheckedOutBooks() const { return numCheckedOutBooks; }

        //Setter
        inline void setUsername(string username) { this->username = username; }
        inline void setPassword(string password) { this->password = password; }

        Account (string username, string password) {
            this->username = username;
            this->password = password;
            numCheckedOutBooks = 0;
        }

        //Member functions
        void addCheckedOutBook(const Book& book);
        void removeCheckedOutBook(string text);
        void printCheckedOutBooks() const;
        bool checkBook(string text) const;
};

class AccountList {
    private: 
        vector<Account*> accounts;
        int numOfAccounts;

    public:
        //Constructor
        AccountList() : numOfAccounts(0) {}

        //Destructor
        ~AccountList();

        //Member functions
        void addAccount(const Account& account);
        void removeAccount(string text);
        bool validateAccount(string username, string password) const;
        Account* searchAccount(string text) const;
};

#endif