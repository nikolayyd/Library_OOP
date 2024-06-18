#ifndef PERIODICAL_EDITION_H
#define PERIODICAL_EDITION_H

#include "PrintEdition.h"

enum Period
{
    DEFAULT = -1,
    WEEKLY,
    MONTHLY,
    ANNUALLY
};

class PeriodicalEdition : virtual public PrintEdition
{
private:

    const char* periodToString(const Period& period) const;
    const Period periodToEnum(const char* period) const;
private:
    Period period;
    unsigned count;

protected:
    void copy(const PeriodicalEdition& other);
    void setPeriod(const char* period);

    void periodicalRead(std::ifstream& in);
    void periodicalWrite(std::ofstream& out);

    void printPeriodical();    

    void setCount(unsigned count);
public:
    virtual const char* getTypeOfEdition() const override;

    unsigned getCount() const;
    const Period getPeriod() const;

public:
    PeriodicalEdition();
    PeriodicalEdition(const char* title,
                const char* shortDescription, 
                int libraryNumber,
                int yearCreated,
                const char* period, 
                unsigned count);
    PeriodicalEdition(const PeriodicalEdition& other);
    PeriodicalEdition& operator=(const PeriodicalEdition& other);
    bool operator==(const PeriodicalEdition& obj);
    virtual ~PeriodicalEdition() = default; 

    virtual PrintEdition* clone() const override;

    virtual PrintEdition* read(std::ifstream& in) override;
    virtual void write(std::ofstream& out) override;
};


#endif //PERIODICAL_EDITION_H