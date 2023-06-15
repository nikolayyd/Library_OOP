#ifndef USER_H
#define USER_H

#include <cstring>
#include <new>
#include <exception>
#include <stdexcept>
#include <fstream>
#include <iostream>

class User {
public:
private:
    void removeBorrowedEdition(unsigned position, int libraryNumber);
    void addReadEdition(int libraryNumber);
    void addBorrowedEdition(int libraryNumber);
    void resize(unsigned size, unsigned capacity, int* arr);
    void copy(const User& other);
    void erase();

private:
    char* name;

    // Array of library numbers of read editions.
    int* readEditions;
    // Size and capacity of read editions' library numbers.
    unsigned sizeOfReadEditions;
    unsigned capacityOfReadEditions;
    
    // Array of library numbers of current borrowed editions.
    int* borrowedEditions;
    // Size and capacity of current borrowed editions' library numbers.
    unsigned sizeOfBorrowedEditions;
    unsigned capacityOfBorrowedEditions;

    void setName(const char* name);

public:
    void printBorrowed(int libraryNumber) const;
    void printInfo() const;
    bool isUserAssignedEdition(int libraryNumber) const;
    bool isUserReadEdition(int libraryNumber) const;

    const char* getName() const;
    const int* getBorrowedEditions() const;
    const int* getReadEditions() const;
    const unsigned getSizeOfReadEditions() const;
    const unsigned getSizeOfBorrowedEditions() const;

    User();
    User(const char* name);
    User(const User& other);
    User& operator=(const User& other);
    
    bool operator==(const User& other) const;
	bool operator!=(const User& other) const;
	bool operator>(const User& other) const;
	bool operator<(const User& other) const;
	bool operator>=(const User& other) const;
	bool operator<=(const User& other) const;
    const char* operator[](int libraryNumber) const; 

	User& operator+=(int libraryNumber);
	User& operator-=(int libraryNumber);

	friend User operator+(const User& lhs, int rhs);
	friend User operator-(const User& lhs, int rhs);

    void write(std::ofstream& out);
    const User read(std::ifstream& in);
    
    ~User();
};

#endif //USER_H