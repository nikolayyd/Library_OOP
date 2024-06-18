#include "../headers/PrintEdition.h"

void PrintEdition::copy(const PrintEdition& other) {
    setTitle(other.title);
    setShortDescription(other.shortDescription);
    setLibraryNumber(other.libraryNumber);
    setYearCreated(other.yearCreated);
}

void PrintEdition::erase() {
        delete[] title;
        delete[] shortDescription;
}

void PrintEdition::setTitle(const char* title) {
    this->title = new (std::nothrow) char[strlen(title) + 1];
    strcpy(this->title, title);
    this->title[strlen(title)] = '\0';
}

void PrintEdition::setShortDescription(const char* shortDescription) {
    this->shortDescription = new (std::nothrow) char[strlen(shortDescription) + 1];
    strcpy(this->shortDescription, shortDescription);
    this->shortDescription[strlen(shortDescription)] = '\0';
}

void PrintEdition::setLibraryNumber(int libraryNumber) {\
    if (libraryNumber > 0) {
        this->libraryNumber = libraryNumber;
    } else {
        throw std::invalid_argument("Invalid library number!");
    }
}

void PrintEdition::setYearCreated(int yearCreated) {
    if (yearCreated > 0 && yearCreated <= 2023) {
        this->yearCreated = yearCreated;
    } else {
        throw std::invalid_argument("Invalid year of creation!");
    }
}
void PrintEdition::printEditionRead(std::ifstream& in) {
 if (in.is_open()) {
        char s;
        char bufferTitle[128];
        unsigned lengthOfTitleArr = 0;
        char bufferShortDescription[256];
        unsigned lengthOfDescriptionArr = 0;
        int libraryNum;
        int yearCreated;

        // removes {
        in >> s;
        in >> std::noskipws;

        in >> s;
        while (s != ',') {
            bufferTitle[lengthOfTitleArr++] = s;
            in >> s;
        }

        title = new char[lengthOfTitleArr + 1];
        strcpy(title, bufferTitle);
        title[lengthOfTitleArr] = '\0';

        in >> s;
        while (s != ',') {
            bufferShortDescription[lengthOfDescriptionArr++] = s;
            in >> s;
        }

        shortDescription = new (std::nothrow) char[lengthOfDescriptionArr + 1];
        strcpy(shortDescription, bufferShortDescription);
        shortDescription[lengthOfDescriptionArr] = '\0';

        in >> libraryNum;
        setLibraryNumber(libraryNum);
        
        in >> s;

        in >> yearCreated;
        setYearCreated(yearCreated);

    } else {
        throw std::runtime_error("The file is not opened!");
    }
}


const char* PrintEdition::getTitle() const {
    return title;
}

const char* PrintEdition::getShortDescription() const {
    return shortDescription;
}

int PrintEdition::getLibraryNumber() const {
    return libraryNumber;
}

int PrintEdition::getYearCreated() const {
    return yearCreated;
}

void PrintEdition::printInfo() const {
    std::cout << "Title: " << title << '\n'
            << "Type: " << getTypeOfEdition() << '\n'
            << "Short description: " << shortDescription << '\n'
            << "Library number: " << libraryNumber << '\n';
}


PrintEdition::PrintEdition() : title(nullptr), 
                                shortDescription(nullptr),
                                libraryNumber(0),
                                yearCreated(0) {}

PrintEdition::PrintEdition(const char* title,
                            const char* shortDescription, 
                            int libraryNumber,
                            int yearCreated) 
{
    setTitle(title);
    setShortDescription(shortDescription);
    setLibraryNumber(libraryNumber);
    setYearCreated(yearCreated);
}

PrintEdition::PrintEdition(const PrintEdition& other) {
    copy(other);
}

PrintEdition& PrintEdition::operator=(const PrintEdition& other) {
    if(this != &other) {
        erase();
        copy(other);
    }

    return *this;
}

bool PrintEdition::operator==(const PrintEdition& obj) {
    return (!strcmp(title, obj.title) && 
            !strcmp(shortDescription, obj.shortDescription) &&
            libraryNumber == obj.libraryNumber &&
            yearCreated == obj.yearCreated);
}


PrintEdition::~PrintEdition() {
    erase();
}

PrintEdition* PrintEdition::read(std::ifstream& in) {
    printEditionRead(in);
    return this;
}

void PrintEdition::write(std::ofstream& out) {
    if (out.good()) {
        out << '{';
        out << title << ','
            << shortDescription << ','
            << libraryNumber << ','
            << yearCreated;
    } else {
        throw std::runtime_error("Error while writing from file!"); 
    }
}