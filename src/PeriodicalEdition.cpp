#include "../headers/PeriodicalEdition.h"

void PeriodicalEdition::copy(const PeriodicalEdition& other) {
    PrintEdition::operator=(other);
    this->period = other.period;
    setCount(other.count);
}

const char* PeriodicalEdition::periodToString(const Period& period) const {
    switch (period)
    {
    case Period::WEEKLY:
        return "Weekly";
    case Period::MONTHLY:
        return "Monthly";
    case Period::ANNUALLY:
        return "Annually";
    default:
        throw std::out_of_range("There is not such an period set!");
    }
}

const Period PeriodicalEdition::periodToEnum(const char* period) const {
    if (!strcmp(period, "Weekly")) {
        return Period::WEEKLY;
    } else if(!strcmp(period, "Monthly")) {
        return Period::MONTHLY;
    } else if (!strcmp(period, "Annually")) {
        return Period::ANNUALLY;
    } else {
        throw std::invalid_argument("This period is not valid!");
    }
}

void PeriodicalEdition::setPeriod(const char* period) {
    this->period = periodToEnum(period);
}

void PeriodicalEdition::setCount(unsigned count) {
    this->count = count;
}

const char* PeriodicalEdition::getTypeOfEdition() const {
    return "PeriodicalEdition";
}


void PeriodicalEdition::periodicalRead(std::ifstream& in) {
    if (in.is_open()) {
        char s;
        char bufferPeriod[128];
        unsigned lenghtOfPeriodArr = 0;
        unsigned count;

        in >> std::noskipws;

        in >> s;

        in >> s;
        while (s != ',') {
            bufferPeriod[lenghtOfPeriodArr++] = s;
            in >> s;
        }
        
        char* periodArr = new (std::nothrow) char[lenghtOfPeriodArr + 1];
        strcpy(periodArr, bufferPeriod);
        periodArr[lenghtOfPeriodArr] = '\0';
        setPeriod(periodArr);

        in >> count;
        setCount(count);
    } else {
        throw std::runtime_error("Ërror while opening file!");
    }
}

void PeriodicalEdition::periodicalWrite(std::ofstream& out) {
    if (out.good()) {
        out << ',' << periodToString(period) << ','
            << count;
    } else {
        throw std::runtime_error("Error while writing in file!");
    }
}  

unsigned PeriodicalEdition::getCount() const {
    return count;
}

const Period PeriodicalEdition::getPeriod() const {
    return period;
}


PeriodicalEdition::PeriodicalEdition() : PrintEdition(), 
                                        period(Period::DEFAULT),
                                        count(0) {}

PeriodicalEdition::PeriodicalEdition(const char* title,
                                const char* shortDescription, 
                                int libraryNumber,
                                int yearCreated,
                                const char* period, 
                                unsigned count) : PrintEdition(title, 
                                                            shortDescription, 
                                                            libraryNumber, 
                                                            yearCreated)
{
    setPeriod(period);
    setCount(count);
}

PeriodicalEdition::PeriodicalEdition(const PeriodicalEdition& other)
{
    copy(other);
}

PeriodicalEdition& PeriodicalEdition::operator=(const PeriodicalEdition& other) {
    if (this != &other) {
        copy(other);
    }

    return *this;
}

bool PeriodicalEdition::operator==(const PeriodicalEdition& obj) {
    return (PrintEdition::operator==(obj) &&
            period == obj.period &&
            count == obj.count);
}


PrintEdition* PeriodicalEdition::clone() const {
    return new (std::nothrow) PeriodicalEdition(*this);
}

PrintEdition* PeriodicalEdition::read(std::ifstream& in) {
    printEditionRead(in);
    periodicalRead(in);
    PeriodicalEdition pe(*this);

    if (in.is_open()) {
        char s;
        in >> std::skipws;
        // removes '}'
        in >> s;
    } else {
        throw std::runtime_error("The file is not opened!");
    }

    return pe.clone();
}

void PeriodicalEdition::write(std::ofstream& out) {
    if (out.good()) {
        out << "PeriodicalEdition: ";
        PrintEdition::write(out);
        periodicalWrite(out);
        out << '}' << '\n';
    } else {
        throw std::runtime_error("Error with the file!");
    }
}