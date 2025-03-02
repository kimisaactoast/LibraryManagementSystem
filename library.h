#ifndef LIBRARY_H
#define LIBRARY_H

using namespace std;

class Book {
    private:
        string title;
        string author;
        string ISBN;
        bool availability;
        string dueDate;

        friend class Account;
        friend class Library;

    public:
        //Constructors
        Book () {
            title = "";
            author = "";
            ISBN = "";
            availability = 0;
            dueDate = "";
        }

        Book (string title, string author, string ISBN, bool availability, string dueDate) {
            this->title = title;
            this->author = author;
            this->ISBN = ISBN;
            this->availability = availability;
            this->dueDate = dueDate;
        }

        //Getters
        inline string getTitle() const { return title; }
        inline string getAuthor() const { return author; }
        inline string getISBN() const { return ISBN; }
        inline bool getAvailability() const { return availability; }
        inline string getDueDate() const { return dueDate; }

        //Setters
        inline void setTitle(string title) { this->title = title; }
        inline void setAuthor(string author) { this->author = author; }
        inline void setISBN(string ISBN) { this->ISBN = ISBN; }
        inline void setAvailability(bool availability) { this-> availability = availability; }
        inline void setDueDate(string dueDate) { this-> dueDate = dueDate; }
};

class Library {
    private:
        vector<Book*> library;
        int numBooks = 0;

    public:
        //Constructor
        Library() : numBooks(0) {}

        //Destructor
        ~Library();

        //Getter for numBooks
        inline int getNumBooks() const { return numBooks; }

        //Member functions
        void addBook(const Book& book);
        void removeBook(string text);
        Book* getBook(string text) const;
        void printBookInformation(Book* book) const;
        void searchBook(string text) const;
        bool searchBookExistence(string text) const;
        void checkoutBook(string text, string date);
        void returnBook(string text) const;
};

#endif