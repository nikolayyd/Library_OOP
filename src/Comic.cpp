#include "../headers/Comic.h"

void Comic::copy(const Comic& other) {
    Book::operator=(other);
    PeriodicalEdition::operator=(other);
}

const char* Comic::getTypeOfEdition() const {
    return "Comic";
}


Comic::Comic() : Book(), PeriodicalEdition() {}
Comic::Comic(const char* title,
                const char* shortDescription, 
                int libraryNumber,
                int yearCreated,
                const char* author,
                const char* publishingHouse,
                const Characteristic& characteristic,
                const Type& type,
                const AimedAudience& aimedAudience,
                const char* period, 
                unsigned count) : PrintEdition(title, 
                                            shortDescription, 
                                            libraryNumber, 
                                            yearCreated) 
{
    Book::setAuthor(author);
    Book::setPublishingHouse(publishingHouse);
    Book::setGenre(characteristic, type, aimedAudience);
    PeriodicalEdition::setPeriod(period);
    PeriodicalEdition::setCount(count);
}

Comic::Comic(const Comic& other) {
    copy(other);
}

Comic& Comic::operator=(const Comic& other) {
    if (this != &other) {
        copy(other);
    }

    return *this;
}

bool Comic::operator==(const Comic& obj) {
    return (PeriodicalEdition::operator==(obj) 
            && Comic::operator==(obj));
}


PrintEdition* Comic::clone() const {
    return new (std::nothrow) Comic (*this);
}

PrintEdition* Comic::read(std::ifstream& in) {
    printEditionRead(in);
    bookRead(in);
    periodicalRead(in);

    Comic comic(*this);

    if (in.is_open()) {
        char s;
        in >> std::skipws;
        in >> s;
    }

    return comic.clone();
}

void Comic::write(std::ofstream& out) {
    if (out.good()) {
        out << "Comic: ";
        PrintEdition::write(out);
        Book::bookWrite(out);
        PeriodicalEdition::periodicalWrite(out);
        out << '}' << '\n';
    } else {
        throw std::runtime_error("Problem with the file!");
    }
}