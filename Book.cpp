#include "Book.h"

void Book::erase() {
        delete[] author;
        delete[] publishingHouse;
}

void Book::copy(const Book& other) {
    PrintEdition::operator=(other);
    setAuthor(other.author);
    setPublishingHouse(other.publishingHouse);
    setGenreAsNumber(other.genre);
}

void Book::setAuthor(const char* author) {
    this->author = new (std::nothrow) char[strlen(author) + 1];
    strcpy(this->author, author);
    this->author[strlen(author)] = '\0';
}

void Book::setPublishingHouse(const char* publishingHouse) {
    this->publishingHouse = new (std::nothrow) char[strlen(publishingHouse) + 1];
    strcpy(this->publishingHouse, publishingHouse);
    this->publishingHouse[strlen(publishingHouse)] = '\0';
}

void Book::setCharacteristic(const Characteristic& characteristic) {
    genre |= (characteristic) << 9;
}

void Book::setType(const Type& type) {
    genre |= (type) << 5; 
}

void Book::setAimedAudience(const AimedAudience& aimedAudience) {
     genre |= (aimedAudience) << 1;
}

void Book::setGenre(const Characteristic& characteristic,
                    const Type& type,
                    const AimedAudience& aimedAudience) 
{
    genre = 0;
    setCharacteristic(characteristic);
    setType(type);
    setAimedAudience(aimedAudience);
    
       
    int count = 0;
    unsigned int tempGenre = genre;
    while (tempGenre) {
        count += tempGenre & 1;
        tempGenre >>= 1;
    }

    genre |= (count % 2 == 0 ? 0 : 1) << 15;
}

void Book::setGenreAsNumber(unsigned int genre) {
    this->genre = genre;
}

const char* Book::getTypeOfEdition() const {
    return "Book";
}


void Book::bookRead(std::ifstream& in) {
    if (in.is_open()) {
        char s;
        char bufferAuthor[128];
        unsigned lengthOfAuthorArr = 0;
        char bufferPublishingHouse[128];
        unsigned lenghtOfPublishingHouseArr = 0;
        unsigned genre;

        in >> std::noskipws;

        in >> s;

        in >> s;
        while (s != ',') {
            bufferAuthor[lengthOfAuthorArr++] = s;
            in >> s;
        }

        author = new (std::nothrow) char [lengthOfAuthorArr + 1];
        strcpy(author, bufferAuthor);
        author[lengthOfAuthorArr] = '\0';

        in >> s;
        while (s != ',') {
            bufferPublishingHouse[lenghtOfPublishingHouseArr++] = s;
            in >> s;
        }
        
        publishingHouse = new (std::nothrow) char[lenghtOfPublishingHouseArr + 1];
        strcpy(publishingHouse, bufferPublishingHouse);
        publishingHouse[lenghtOfPublishingHouseArr] = '\0';
        
        in >> genre;
        setGenreAsNumber(genre);
    } else {
        throw std::runtime_error("Error while opening file!");
    }
}

void Book::bookWrite(std::ofstream& out) {
    if (out.good()) {
        out << ',' << author
            << ',' << publishingHouse
            << ',' << genre;
    }
}

const char* Book::getAuthor() const {
    return author;
}

const char* Book::getPublishingHouse() const {
    return publishingHouse;
}

unsigned Book::getGenre() const {
    return genre;
}

const Characteristic Book::getCharacteristic() const {
    return static_cast<Characteristic>((genre >> 9));
}

const Type Book::getType() const {
    return static_cast<Type>((genre >> 5));
}

const AimedAudience Book::setAimedAuditorium() const {
    return static_cast<AimedAudience>((genre >> 1));
}


Book::Book() : PrintEdition(), 
                author(nullptr), 
                publishingHouse(nullptr),
                genre(0) {}

Book::Book(const char* title,
    const char* shortDescription, 
    int libraryNumber,
    int yearCreated,
    const char* author,
    const char* publishingHouse,
    const Characteristic& characteristic,
    const Type& type,
    const AimedAudience& aimedAudience) : PrintEdition(title,
                                    shortDescription,
                                    libraryNumber,
                                    yearCreated)
{
    setAuthor(author);
    setPublishingHouse(publishingHouse);
    setGenre(characteristic,type, aimedAudience);
}

Book::Book(const Book& other) {
    copy(other);
}

Book& Book::operator=(const Book& other) {
    if (this != &other) {
        erase();
        copy(other);
    }

    return *this;
}

bool Book::operator==(const Book& obj) {
    return (PrintEdition::operator==(obj) &&
            !strcmp(author, obj.author) &&
            !strcmp(publishingHouse, obj.publishingHouse) &&
            genre == obj.genre);
}


Book::~Book() {
    erase();
}

PrintEdition* Book::clone() const {
    return new (std::nothrow) Book(*this);
}

PrintEdition* Book::read(std::ifstream& in) {
    printEditionRead(in);
    bookRead(in);
    Book book(*this);

    if (in.is_open()) {
        char s;
        in >> std::skipws;
        // removes '}'
        in >> s;
    }

    return book.clone();
}

void Book::write(std::ofstream& out) {
    if (out.good()) {
        out << "Book: ";
        PrintEdition::write(out);
        bookWrite(out);
        out << '}' << '\n';
    }

}