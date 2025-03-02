#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include "system.h"

using namespace std;

//Import data from CSV file into library
void importLibrary(Library& library){
    string line, word;

    ifstream inFile;
    inFile.open("libraryCatalog.csv");

    // Check whether file opening was successful
    if(!inFile.is_open()) {
        cout << "Error in opening csv file." << endl;
        return;
    }

    getline(inFile, line); // Skip the header line

    while(getline(inFile, line)){
        vector<string> temp;
        stringstream ss(line);

        while(getline(ss, word, ',')){      
            temp.push_back(word);
        }

        if (temp.size() == 5) {
            string title = temp[0];
            string author = temp[1];
            string ISBN = temp[2];
            bool availability = (temp[3] == "True");
            string dueDate = temp[4];

            library.addBook(Book(title, author, ISBN, availability, dueDate));
        } else {
            cout << "Invalid format in CSV file." << endl;
        }
    }

    inFile.close();
}

//Check if user exists in the system and validate password
bool checkUser(const string& username, AccountList& accounts){
    string password;
    
    cout << "Password: ";
    cin >> password;

    if(accounts.validateAccount(username, password)){
        cout << "Login successful!" << endl;
        return true;
    } else {
        cout << "Invalid username or password. Please try again." << endl;
        return false;
    }
}

//Start menu after user has logged in
void startMenu(const string& username, AccountList& accounts, Library& library){
    int selection = 0;
    
    while(selection != 5){
        cout << "---------------------------------------------------------------------------------" << endl;
        cout << "Nice to see you, " << username << "! What would you like to do today?" << endl;
        cout << "1. Check out a book." << endl;
        cout << "2. Search for a book." << endl;
        cout << "3. View checked out books and due dates." << endl;
        cout << "4. Return a book." << endl;
        cout << "5. Log out." << endl;
        cout << "---------------------------------------------------------------------------------" << endl;
    
        try {
            cin >> selection;

            // Check if the input is invalid
            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the input
                throw invalid_argument("Invalid input.");
            }

            cin.ignore(); // Clear the input buffer

            //Check out a book
            if(selection == 1){
                string input;
                int num = 0;

                while(num != 1){
                    cout << "Please enter the book title or book ISBN: ";
                    getline(cin, input);
        
                    if(library.searchBookExistence(input)){
                        library.searchBook(input);
                        num = 1;
                    } else {
                        cout << "Book not found. Please try again." << endl;
                    }
                }

                Book* book = library.getBook(input);
                if(book == nullptr || !book->getAvailability()){
                    cout << "Book not available for checkout." << endl;
                    continue;
                } else {
                    while(num != 2){
                        cout << "Would you like to check this book out? Press 1 to check out and 2 to cancel." << endl;
                        cin >> num;

                        // Check if the input is invalid
                        if(cin.fail()){
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the input
                            throw invalid_argument("Invalid input.");
                        }

                        cin.ignore(); // Clear the input buffer
            
                        if(num == 1){
                            // Get the current time and add two weeks to it
                            const auto now = std::chrono::system_clock::now();
                            auto twoWeeks = std::chrono::hours(24 * 14);
                            auto lastTwoWeeks = now + twoWeeks;

                            // Convert the time to a time_t object
                            std::time_t tt = std::chrono::system_clock::to_time_t(lastTwoWeeks);

                            library.checkoutBook(input, ctime(&tt));
                            accounts.searchAccount(username)->addCheckedOutBook(*book);
                            cout << "Book checked out successfully!" << endl;
                            
                            num = 2;
                        } else if (num == 2) {
                            cout << "Cancelling..." << endl;
                        } else {
                            cout << "Please enter a valid input." << endl;
                        }
                    }
                }
            //Search for a book
            } else if (selection == 2) {
                string input;

                cout << "Please enter the book title or book ISBN: ";
                getline(cin, input);

                library.searchBook(input);
            //View checked out books and due dates
            } else if (selection == 3) {
                accounts.searchAccount(username)->printCheckedOutBooks();
            //Return a book
            } else if (selection == 4) {
                string input;
                int num = 0;

                while(num != 1){
                    cout << "Please enter the book title or book ISBN: ";
                    getline(cin, input);
        
                    if(library.searchBookExistence(input)){
                        library.searchBook(input);
                        num = 1;
                    } else {
                        cout << "Book not found. Please try again." << endl;
                    }
                }

                Book* book = library.getBook(input);
                if(book == nullptr || book->getAvailability()){
                    cout << "Book is already returned." << endl;
                    continue;
                } else {
                    while(num != 2){
                        cout << "Would you like to return this book? Press 1 to return and 2 to cancel." << endl;
                        cin >> num;

                        // Check if the input is invalid
                        if(cin.fail()){
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the input
                            throw invalid_argument("Invalid input.");
                        }

                        cin.ignore(); // Clear the input buffer

                        if(num == 1){   
                            //Make sure user has checked out the book
                            if(!accounts.searchAccount(username)->checkBook(book->getTitle())){
                                cout << "You have not checked out this book." << endl;
                                continue;
                            }

                            library.returnBook(input);
                            accounts.searchAccount(username)->removeCheckedOutBook(book->getTitle());
                            cout << "Book returned successfully!" << endl;
                            
                            num = 2;
                        } else if (num == 2) {
                            cout << "Cancelling..." << endl;
                        } else {
                            cout << "Please enter a valid input." << endl;
                        }
                    }
                }
            //Log out
            } else if (selection == 5){
                cout << "Logging out..." << endl;
                createInterface(accounts, library);
            } else {
                cout << "Please enter a valid input." << endl;
            }
        } catch (const invalid_argument& e) {
            cout << e.what() << endl;
        } catch (const runtime_error& e) {
            cout << e.what() << endl;
        }
    }
}

//Interface for user logging in or registering
bool createInterface(AccountList& accounts, Library& library){
    string username;
    int userAttempt = 0;

    cout << "---------------------------------------------------------------------------------" << endl;
    cout << "Welcome to the library! Please login with your username and password to continue." << endl;
    cout << "If you are here for the first time, please register by pressing 1." << endl;
    cout << "To exit the library system, please type 'exit'." << endl;
    cout << "---------------------------------------------------------------------------------" << endl;

    while(userAttempt < 5){
        cout << "Username: ";
        getline(cin, username);

        if(username == "1"){ //register user
            string newUsername, newPassword;

            cout << "Please create an account by first typing in a username: ";
            cin >> newUsername;
            cout << "Please type a password: ";
            cin >> newPassword;
    
            accounts.addAccount(Account(newUsername, newPassword));
    
            cout << "Please login." << endl;
            userAttempt = 0;
            
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        } else if (username == "exit") {
            return false;
        } else {  
            if(checkUser(username, accounts)){
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

                startMenu(username, accounts, library);
                return true;
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            }
        }

        userAttempt++;
    }
    
    cout << "Too many attempts! Please contact the administrator to reset your password." << endl;

    return false;
}