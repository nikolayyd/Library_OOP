#include "../headers/Library.h"

void Library::erase() {
    delete[] users;
    delete[] countsOfEdition;

    for (unsigned i = 0; i < sizeOfEditions; i++)
    {
        delete editions[i];
    }

    delete[] editions;
}

void Library::usersResize() {
    capacityOfUsers = 2 * capacityOfUsers;
    User* copyUsers = new (std::nothrow) User[capacityOfUsers];

    for (unsigned i = 0; i < sizeOfUsers; i++)
    {
        copyUsers[i] = users[i];
    }

    delete[] users;

    users = copyUsers;
}

void Library::editionsResize() {
    capacityOfEditions = capacityOfEditions * 2;
    PrintEdition** editionsCopy = new (std::nothrow) PrintEdition*[capacityOfEditions];
    unsigned* countsOfEditionCopy = new (std::nothrow) unsigned[capacityOfEditions];

    for (unsigned i = 0; i < sizeOfEditions; i++)
    {
        editionsCopy[i] = editions[i];
        countsOfEdition[i] = countsOfEditionCopy[i];
    }

    delete[] editions;
    delete[] countsOfEdition;
    
    editions = editionsCopy;
    countsOfEdition = countsOfEditionCopy;
    
}
bool Library::isValidPrintEdition(int libraryNumber) {
    for (unsigned i = 0; i < sizeOfEditions; i++)
    {
        if(editions[i]->getLibraryNumber() == libraryNumber) {
            return true;
        }
    }

    return false;
}

bool Library::isUniqueLibraryNumber(int libraryNumber) {
    for (unsigned i = 0; i < sizeOfEditions; i++)
    {
        if(editions[i]->getLibraryNumber() == libraryNumber) {
            return false;
        }
    }

    return true;
    
}

unsigned Library::findUserIndex(const char* name) const {
    for (unsigned i = 0; i < sizeOfUsers; i++)
    {
        if (!strcmp(users[i].getName(), name)) {
            return i;
        }
    }

    throw std::invalid_argument("The user does not exist!\n");
    
}

unsigned Library::findEditionIndex(int libraryNumber) const {
    for (unsigned i = 0; i < sizeOfEditions; i++) {
        if (libraryNumber == editions[i]->getLibraryNumber()) {
            return i;
        }
    } 

    throw std::invalid_argument("Edition with this library number does not exist!");
}

bool Library::editionAlreadyAdded(const PrintEdition* edition) const {
    for (unsigned i = 0; i < sizeOfEditions; i++)
    {
        if (editions[i] == edition) {
            return true;
        }
    }

    return false;
    
}

const PrintEdition* Library::getObject(int libraryNumber) const {
    for (int i = 0; i < sizeOfEditions; i++)
    {
        if (editions[i]->getLibraryNumber() == libraryNumber) {
            return editions[i];
        }   
    }

    return nullptr;
    // throw std::invalid_argument("There is no edition with this library number");
}

const User* Library::getUsers() const {
    return users;
}

void Library::borrowEdition(const char* userName, int libraryNumber) {
    if (!isValidPrintEdition(libraryNumber)) {
        throw std::invalid_argument("There is no edition with this library number.");
    }

    unsigned userPosition = findUserIndex(userName);

    if(!users[userPosition].isUserAssignedEdition(libraryNumber) && 
        countsOfEdition[findEditionIndex(libraryNumber)] > 0)
    {
        users[userPosition] += libraryNumber;
        countsOfEdition[findEditionIndex(libraryNumber)]--;
    } else {
        throw std::out_of_range("This edition hasn't enought counts or the user has already borrowed it!");
    }
}

void Library::returnBorrowedEdition(const char* userName, int libraryNumber) {
    if (!isValidPrintEdition(libraryNumber)) {
        throw std::out_of_range("There is no edition with this library number.");
    }
    
    unsigned userPosition = findUserIndex(userName); 

    if (users[userPosition].isUserAssignedEdition(libraryNumber)) {
        users[userPosition] -= libraryNumber;
    } else {
        throw std::runtime_error("This book haven't been borrowed!");
    }

    countsOfEdition[findEditionIndex(libraryNumber)]++;
}

void Library::removeEdition(int libraryNumber) {
    for (unsigned i = 0; i < sizeOfUsers; i++)
    {
        if (users[i].isUserReadEdition(libraryNumber) == true 
            || users[i].isUserAssignedEdition(libraryNumber) == true) 
        {
           throw std::runtime_error("Edition is borrowed or read by user and cannot be deleted!");
        }
    }
    
    for (unsigned i = 0; i < sizeOfEditions; i++)
    {
        if (libraryNumber == editions[i]->getLibraryNumber()) {
            delete editions[i];
            editions[i] = editions[sizeOfEditions-1];
            sizeOfEditions--;
        }  
    }
}

void Library::addEdition(PrintEdition* edition) {

    if (editionAlreadyAdded(edition)) {
        countsOfEdition[findEditionIndex(edition->getLibraryNumber())]++;
        return;
    }

    if (isUniqueLibraryNumber(edition->getLibraryNumber())) {
        if (sizeOfEditions == capacityOfEditions) {
            editionsResize();
        }
        
        countsOfEdition[sizeOfEditions] = 1;
        editions[sizeOfEditions++] = edition;

    } else {
        throw std::invalid_argument("There is already such a library number!");
    }

}

void Library::addUser(const User& user) {
    if (sizeOfUsers == capacityOfUsers) {
        usersResize();
    }

    for (unsigned i = 0; i < sizeOfUsers; i++)
    {
        if (!strcmp(user.getName(), users[i].getName())) {
            throw std::invalid_argument("This user already exists!");
        }
    }
    
    
    users[sizeOfUsers++] = user;
}
void Library::removeUser(const char* name) {
    for (unsigned i = 0; i < sizeOfUsers; i++)
    {
        if (!strcmp(users[i].getName(), name)) {
            if (i != (sizeOfUsers - 1)) {
                User temp = users[i];
                users[i] = users[sizeOfUsers];
                users[sizeOfUsers - 1] = temp;
            }
        }

        sizeOfUsers--;
        break;
    }
    
}

void Library::readEditionsData(std::ifstream& in) {
    if (in.is_open()) {
        char s;
        char bufferTypeOfReading[32];
        unsigned length;
        
        while (in) {
            in >> s;

            // Check do we have end of file.
            if (in.eof()) {
                break;
            }

            length = 0;
            while (s != ':') {
                bufferTypeOfReading[length++] = s;
                in >> s;
            }

            bufferTypeOfReading[length] = '\0';

            if (sizeOfEditions == capacityOfEditions) {
                editionsResize();
            }


            if (!strcmp(bufferTypeOfReading, "PeriodicalEdition")) {
                PeriodicalEdition pe;
                addEdition(pe.read(in));
            } else if(!strcmp(bufferTypeOfReading, "Book")) {
                Book book;
                addEdition(book.read(in));
            } else if(!strcmp(bufferTypeOfReading, "Comic")) {
                Comic comic;
                addEdition(comic.read(in));
            } else {
                throw std::out_of_range("Error while reading the file!");
            }

            bufferTypeOfReading[0] = '\0';
        }
    } else {
        throw std::runtime_error("Error while opening file!");
    } 
}




void Library::writeEditionsData(std::ofstream& out) {
    if (out.good()) {
        for (unsigned i = 0; i < sizeOfEditions; i++) {
            editions[i]->write(out);
        }
    } else {
        throw std::runtime_error("Error with file while writing!");
    }
    
}

void Library::readUsersData(std::ifstream& in) {
    
    if (in.is_open()) {    
        char s;
        int usersCount;
        

        in >> usersCount;

        while (usersCount > 0) {
            User currentUser;
            if (sizeOfUsers == capacityOfUsers) {
                usersResize();
            }

            addUser(currentUser.read(in));
            in >> s;

            usersCount--;
        }
    } 
    else {
        throw std::runtime_error("The file is not opened correctly!");
    }
}

void Library::writeUsersData(std::ofstream& out) {
    if(out.good()) {
        out << sizeOfUsers << '\n';
        for (unsigned i = 0; i < sizeOfUsers; i++)
        {

            users[i].write(out);
        }
    } else {
        throw std::runtime_error("Error with file while writing!");
    }
}

void Library::printUsersWithBorrowedEdition(int libraryNumber) const {
    for (unsigned i = 0; i < sizeOfUsers; i++)
    {
        users[i].printBorrowed(libraryNumber);
    }
    
}

void Library::sortUsersReadBooks() {
    User* copyUsers = new (std::nothrow) User[sizeOfUsers];
    User temp;
    for (unsigned i = 0; i < sizeOfUsers; i++) {
        copyUsers[i] = users[i];
    }

    for (unsigned i = 0; i < sizeOfUsers; i++) {
        
        for (unsigned j = 0; j < sizeOfUsers - i - 1; j++) {
            
            if (copyUsers[j].getSizeOfReadEditions() 
                < copyUsers[j + 1].getSizeOfReadEditions()) 
            {    
                temp = copyUsers[j];
                copyUsers[j] = copyUsers[j + 1];
                copyUsers[j + 1] = temp;
            }
        }
    }

    for (unsigned i = 0; i < sizeOfUsers; i++) {
        copyUsers[i].printInfo();
    }

    delete[] copyUsers;
}

void Library::printSortedPrintEditions() {
    PrintEdition** editionsCopy = new (std::nothrow) PrintEdition*[capacityOfEditions];
    PrintEdition* temp;

    for (unsigned i = 0; i < sizeOfEditions; i++)
    {
        editionsCopy[i] = editions[i];
    }

    for (unsigned i = 0; i < sizeOfEditions; i++) {
        for (unsigned j = 0; j < sizeOfEditions - i - 1; j++) {
            if (editionsCopy[j]->getYearCreated() <
                editionsCopy[j + 1]->getYearCreated()) 
            {
                temp = editionsCopy[j];
                editionsCopy[j] = editionsCopy[j + 1];
                editionsCopy[j + 1] = temp;
            } else if (editionsCopy[j]->getYearCreated() ==
                editionsCopy[j + 1]->getYearCreated()) 
            {

                // if strcmp ... 
                if (strcmp(editionsCopy[j]->getTitle(), 
                    editionsCopy[j + 1]->getTitle()) > 0) 
                {
                    temp = editionsCopy[j];
                    editionsCopy[j] = editionsCopy[j + 1];
                    editionsCopy[j + 1] = temp;
                }
            }
        }
        
    }
    
    for (unsigned i = 0; i < sizeOfEditions; i++)
    {
        editionsCopy[i]->printInfo();
    }
    

    for (unsigned i = 0; i < sizeOfEditions; i++)
    {
        delete editionsCopy[i];
    }

    delete[] editionsCopy;    
}


Library::Library() {
    sizeOfUsers = 0;
    capacityOfUsers = 16;
    users = new (std::nothrow) User [capacityOfUsers];
    
    sizeOfEditions = 0;
    capacityOfEditions = 16;
    editions = new (std::nothrow) PrintEdition* [capacityOfEditions];
    countsOfEdition = new (std::nothrow) unsigned [capacityOfEditions];
}

Library::~Library() {
    erase();
}