#ifndef PRINT_EDITION_H
#define PRINT_EDITION_H
#include <cstring>
#include <fstream>
#include <exception>
#include <new>
#include <iostream>
#include <stdexcept>

class PrintEdition
{
protected:
    char* title;
    char* shortDescription;
    int libraryNumber;
    int yearCreated;

    void erase();
 
    void copy(const PrintEdition& other);
    void setShortDescription(const char* shortDescription);
    void setTitle(const char* title);
    void setLibraryNumber(int libraryNumber);
    void setYearCreated(int yearCreated);
    void printEditionRead(std::ifstream& in);
public:
    const char* getTitle() const;
    const char* getShortDescription() const;
    int getLibraryNumber() const;
    int getYearCreated() const;
    void printInfo() const;

public:
    virtual const char* getTypeOfEdition() const = 0;
    PrintEdition();
    PrintEdition(const char* title,
                const char* shortDescription, 
                int libraryNumber,
                int yearCreated);
    PrintEdition(const PrintEdition& other);
    PrintEdition& operator=(const PrintEdition& other);
    bool operator==(const PrintEdition& obj);
    virtual ~PrintEdition();

    virtual PrintEdition* read(std::ifstream& in);
    virtual void write(std::ofstream& out);

    virtual PrintEdition* clone() const = 0;

};

#endif //PRINT_EDITION_H