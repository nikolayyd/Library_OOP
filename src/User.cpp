#include "../headers/User.h"

void User::removeBorrowedEdition(unsigned position, int libraryNumber) {
    borrowedEditions[position] = borrowedEditions[sizeOfBorrowedEditions - 1];
    borrowedEditions[sizeOfBorrowedEditions - 1] = -1;
    sizeOfBorrowedEditions--;
}

bool User::isUserAssignedEdition(int libraryNumber) const {
    for (unsigned i = 0; i < sizeOfBorrowedEditions; i++)
    {
        if (libraryNumber == borrowedEditions[i]) {
            return true;
        }
    }
    
    return false;
}

bool User::isUserReadEdition(int libraryNumber) const {
    for (unsigned i = 0; i < sizeOfReadEditions; i++)
    {
        if (libraryNumber == readEditions[i]) {
            return true;
        }
    }
    
    return false;
}

void User::printBorrowed(int libraryNumber) const {
    
    for (unsigned i = 0; i < sizeOfBorrowedEditions; i++) {
        if (libraryNumber == borrowedEditions[i]) {
            std::cout << "Name: " << name << '\n';
        }   
    }
    
}

void User::printInfo() const {
        std::cout << "Name: " << name
                << "\nRead editions: " 
                << sizeOfReadEditions << '\n';
}


void User::addReadEdition(int libraryNumber) {
    if(sizeOfReadEditions == capacityOfReadEditions) {
        resize(sizeOfReadEditions, capacityOfReadEditions, readEditions);
    }

    if(isUserReadEdition(libraryNumber)) {
        throw std::runtime_error("This book is read by the user!");
    }
    
    for (unsigned i = 0; i < sizeOfBorrowedEditions; i++)
    {
        if (libraryNumber == borrowedEditions[i]) {      
            removeBorrowedEdition(i, libraryNumber);    
            break;
        }

    }

    readEditions[sizeOfReadEditions++] = libraryNumber;

}

void User::addBorrowedEdition(int libraryNumber) {
    if (isUserAssignedEdition(libraryNumber)) {
        throw std::runtime_error("This edition is already borrowed by the user!");
    }

    if (sizeOfBorrowedEditions < 5) {
        borrowedEditions[sizeOfBorrowedEditions++] = libraryNumber;
    } else {
       throw std::out_of_range("More than five editions cannot be borrowed!");
    }
}

void User::resize(unsigned size, unsigned capacity, int* arr) {
    capacity += 16;
    int* copy = new (std::nothrow) int[capacity];    

    for (unsigned i = 0; i < size; i++) {
        copy[i] = arr[i]; 
    }

    delete[] arr;
    arr = copy;
}

void User::copy(const User& other) {
    
    sizeOfReadEditions = other.sizeOfReadEditions;
    capacityOfReadEditions = other.capacityOfReadEditions;
    readEditions = new (std::nothrow) int[capacityOfReadEditions];
    
    for (unsigned i = 0; i < sizeOfReadEditions; i++) {
        readEditions[i] = other.readEditions[i];
    }

    sizeOfBorrowedEditions = other.sizeOfBorrowedEditions;
    capacityOfBorrowedEditions = other.capacityOfBorrowedEditions;
    borrowedEditions = new (std::nothrow) int[capacityOfBorrowedEditions];

    for (unsigned i = 0; i < sizeOfBorrowedEditions; i++) {
        borrowedEditions[i] = other.borrowedEditions[i];
    }
    

    setName(other.name);
}

void User::erase() {
    delete[] name;
    delete[] readEditions;
    delete[] borrowedEditions;
}


void User::setName(const char* name) {
    this->name = new (std::nothrow) char[strlen(name) + 1];
    strcpy(this->name, name);
    this->name[strlen(name)] = '\0';
}

const char* User::getName() const {
    return name;
}

const int* User::getBorrowedEditions() const {
    return borrowedEditions;
}

const int* User::getReadEditions() const {
    return readEditions;
}

const unsigned User::getSizeOfReadEditions() const {
    return sizeOfReadEditions;
}

const unsigned User::getSizeOfBorrowedEditions() const {
    return sizeOfBorrowedEditions;
}

User::User() : name(nullptr), 
            readEditions(nullptr), 
            sizeOfReadEditions(0),
            capacityOfReadEditions(0),
            borrowedEditions(nullptr),
            sizeOfBorrowedEditions(0),
            capacityOfBorrowedEditions(0) {}


User::User(const char* name) {
    sizeOfReadEditions = 0;
    capacityOfReadEditions = 16;
    readEditions = new (std::nothrow) int[capacityOfReadEditions];

    sizeOfBorrowedEditions = 0;
    capacityOfBorrowedEditions = 5;
    borrowedEditions = new (std::nothrow) int[capacityOfBorrowedEditions];

    setName(name);
}

User::User(const User& other) {
    copy(other);
}

User& User::operator=(const User& other) {
    if (this != &other) {
        erase();
        copy(other);
    }

    return *this;
}

bool User::operator==(const User& other) const {
    return (!strcmp(name, other.name)) ? true : false;
}

bool User::operator!=(const User& other) const {
    return !(this == &other);
}

bool User::operator>(const User& other) const {
    return (sizeOfReadEditions > other.sizeOfReadEditions) ?
        true : false;
}



bool User::operator<(const User& other) const {
    return (sizeOfReadEditions < other.sizeOfReadEditions) ?
        true : false;
}

bool User::operator>=(const User& other) const {
        return (sizeOfReadEditions >= other.sizeOfReadEditions) ?
        true : false;
}

bool User::operator<=(const User& other) const {
    return (sizeOfReadEditions <= other.sizeOfReadEditions) ?
        true : false;
}

const char* User::operator[](int libraryNumber) const {
    bool isCurrentRead = false;
    bool isCurrentBorrowed = false;
    
    for (unsigned i = 0; i < sizeOfReadEditions; i++) {
        if (libraryNumber == readEditions[i]) {
            isCurrentRead = true;
        }
    }
    
    for (unsigned i = 0; i < sizeOfBorrowedEditions; i++) {
        if (libraryNumber == borrowedEditions[i]) {
            isCurrentBorrowed = true;
        }
    }

    if (isCurrentRead) {
        return "The edition is currently read!";
    } else if(isCurrentBorrowed) {
        return "The edition is currently borrowed!";
    } else {
        return "The edition is never borrowed!";
    }
} 

User& User::operator+=(int libraryNumber) {
    addBorrowedEdition(libraryNumber);
    return *this;
}

User& User::operator-=(int libraryNumber) {
    addReadEdition(libraryNumber);
    return *this;
}

User operator+(const User& lhs, int rhs) {
    User user = lhs;
    user += rhs;
    return user;
}   

User operator-(const User& lhs, int rhs) {
    User user = lhs;
    user -= rhs;
    return user;
}

void User::write(std::ofstream& out) {
    if (out.good())
    {
        out << name << ':';

        if (sizeOfBorrowedEditions > 0) {
            out << ' ';
        }

        for (unsigned i = 0; i < sizeOfBorrowedEditions; i++)
        {
            if (i + 1 == sizeOfBorrowedEditions) {
                out << borrowedEditions[i];
                break;
            } else {
                out << borrowedEditions[i] << ',';
            }
        }

        out << '|';

        if (sizeOfReadEditions > 0) {
            out << ' ';
        }

        for (unsigned i = 0; i < sizeOfReadEditions; i++)
        {
            if (i + 1 == sizeOfReadEditions) {
                out << readEditions[i];
                break;
            } else {
                out << readEditions[i] << ',';
            }
        }

        out << '.' << '\n';
    } else {
        throw std::runtime_error("Error while writing file!");
    }
    
}

const User User::read(std::ifstream& in) {
    
    if (in.is_open()) {
        char buffer[128];
        unsigned length = 0;
        char s;
        int libNum;

        in >> s;
        for (unsigned i = 0; s != ':'; i++)
        {
            buffer[i] = s;
            in >> s;
            length++;
        }

        buffer[length] = '\0';

        char* name = new (std::nothrow) char[length + 1];
        strcpy(name, buffer);
        User user(name);

        in >> std::noskipws;

        while (!in.eof())
        {
            in >> s;
            if (s == '|') {
                break;
            }

            in >> libNum;
            user += libNum;
        }
        
        while (!in.eof())
        {
            in >> s;
            if (s == '.') {
                break;
            }
            in >> libNum;
            user -= libNum;
        }

        return user;
        
    } else {
        throw std::runtime_error("File is not correctly opened!");
    }
}

User::~User() {
    erase();
}