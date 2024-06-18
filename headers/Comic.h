#ifndef COMIC_H
#define COMIC_H

#include "Book.h"
#include "PeriodicalEdition.h"

class Comic : public Book, public PeriodicalEdition
{
private:
    void copy(const Comic& other);
public:
    virtual const char* getTypeOfEdition() const override;
    Comic();
    Comic(const char* title,
                const char* shortDescription, 
                int libraryNumber,
                int yearCreated,
                const char* author,
                const char* publishingHouse,
                const Characteristic& characteristic,
                const Type& type,
                const AimedAudience& aimedAudience,
                const char* period, 
                unsigned count);
    Comic(const Comic& other);
    Comic& operator=(const Comic& other);
    bool operator==(const Comic& obj);

    ~Comic() = default;

    virtual PrintEdition* clone() const override;

    virtual PrintEdition* read(std::ifstream& in) override;
    virtual void write(std::ofstream& out) override;
};


#endif //COMIC_H