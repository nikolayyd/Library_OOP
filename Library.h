#ifndef LIBRARY_H
#define LIBRARY_H

#include "PrintEdition.h"
#include "Book.h"
#include "PeriodicalEdition.h"
#include "Comic.h"
#include "User.h"

#include <typeinfo>

class Library
{

private:
    void erase();
    void usersResize();
    void editionsResize();

    bool isValidPrintEdition(int libraryNumber);
    bool isUniqueLibraryNumber(int libraryNumber);

    unsigned findUserIndex(const char* name) const;
    unsigned findEditionIndex(int libraryNumber) const;
    bool editionAlreadyAdded(const PrintEdition* edition) const;

private:
    User* users;
    unsigned sizeOfUsers;
    unsigned capacityOfUsers;

    PrintEdition** editions;
    unsigned sizeOfEditions;
    unsigned capacityOfEditions;

    unsigned* countsOfEdition;
    
public:
    const PrintEdition* getObject(int libraryNum) const;
    const User* getUsers() const;
    void borrowEdition(const char* userName, int libraryNumber);
    void returnBorrowedEdition(const char* userName, int libraryNumber);

    void addEdition(PrintEdition* edition);
    void removeEdition(int libraryNumber);

    void addUser(const User& user);
    void removeUser(const char* name);
    
    void readEditionsData(std::ifstream& in);
    void writeEditionsData(std::ofstream& out);

    void readUsersData(std::ifstream& in);
    void writeUsersData(std::ofstream& out);

    void printUsersWithBorrowedEdition(int libraryNumber) const;
    void sortUsersReadBooks();
    void printSortedPrintEditions();



    Library();
    Library(const Library& other) = delete;
    Library& operator=(const Library& other) = delete;
    ~Library();
};


#endif //LIBRARY_H