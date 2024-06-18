#ifndef BOOK_H
#define BOOK_H

#include "PrintEdition.h"

enum Characteristic {
    DEFAULT_CHARACTERISTIC = 0,
    THRILLER = 1,
    FANTASTICS = 2,
    CRIMINAL_PROSE = 3
};

enum Type {
    DEFAULT_TYPE = 0,
    POETRY = 1,
    PROSE = 2,
    DRAMA = 3
};

enum AimedAudience {
    DEFAULT_AIM_AUDITORIUM = 0,
    CHILDREN = 1,
    TEENAGERS = 2,
    ADULTS = 3
};

class Book : virtual public PrintEdition {
private:
    void erase();
private:
    char* author;
    char* publishingHouse;
    unsigned int genre;

protected:
    void copy(const Book& other);

    void setAuthor(const char* author);
    void setPublishingHouse(const char* publishingHouse);
    void setGenre(const Characteristic& characteristic,
                    const Type& type,
                    const AimedAudience& aimedAudience);

    void setGenreAsNumber(unsigned int genre);
    void setCharacteristic(const Characteristic& characteristic);
    void setType(const Type& type);
    void setAimedAudience(const AimedAudience& aimedAudience);

    void bookRead(std::ifstream& in);
    void bookWrite(std::ofstream& out);

public:
    const char* getAuthor() const;
    const char* getPublishingHouse() const;
    unsigned getGenre() const;
    const Characteristic getCharacteristic() const;
    const Type getType() const;
    const AimedAudience setAimedAuditorium() const;

public:
    virtual const char* getTypeOfEdition() const override;

    Book();
    Book(const char* title,
                const char* shortDescription, 
                int libraryNumber,
                int yearCreated,
                const char* author,
                const char* publishingHouse,
                const Characteristic& characteristic,
                const Type& type,
                const AimedAudience& aimedAudience);
    Book(const Book& other);
    Book& operator=(const Book& other);
    bool operator==(const Book& obj);
    virtual ~Book();

    virtual PrintEdition* clone() const override;

    virtual PrintEdition* read(std::ifstream& in) override;
    virtual void write(std::ofstream& out) override;
};


#endif //BOOK_H