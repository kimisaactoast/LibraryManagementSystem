#ifndef SYSTEM_H
#define SYSTEM_H

#include "library.h"
#include "accounts.h"

using namespace std;

//Function prototypes
bool createInterface(AccountList& accounts, Library& library);
void importLibrary(Library& library);
bool checkUser(const string& username, AccountList& accounts);
void startMenu(const string& username, AccountList& accounts, Library& library);

#endif