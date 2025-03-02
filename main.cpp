#include <iostream>
#include "library.h"
#include "system.h"
#include "accounts.h"

using namespace std;

int main() {
    AccountList accounts;
    Library myLibrary;
    importLibrary(myLibrary);

    if(createInterface(accounts, myLibrary)){
        cout << "Thank you for joining us today! Come back again." << endl;
    } else {
        cout << "Exiting software..." << endl;
    }

    return 0;
}