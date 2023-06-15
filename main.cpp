#include "Library.h"

int main()
{
    try
    {
        Book book1("Book1", "a new book", 10, 1999, "B. G.", "M1", 
                    Characteristic::CRIMINAL_PROSE, Type::DRAMA, AimedAudience::ADULTS);
        Book book2("Book2", "a new book 2", 13, 1998, "B. G.", "M1",
                    Characteristic::FANTASTICS, Type::POETRY, AimedAudience::TEENAGERS);

        PeriodicalEdition pe1("Periodical Edition 1", "a new periodical", 11, 2003, "Annually", 1);
        PeriodicalEdition pe2("Periodical Edition 1", "a new periodical 2", 14, 2003, "Weekly", 2);
        
        Comic comic1("Comic 1", "a new comic", 12, 1999, "B. G.", "M1",
                    Characteristic::THRILLER, Type::DRAMA, AimedAudience::CHILDREN,
                    "Monthly", 3);

        Library library;


        library.addEdition(comic1.clone());
        library.addEdition(pe1.clone());
        library.addEdition(pe2.clone());
        library.addEdition(book1.clone());
        library.addEdition(book2.clone());

        // std::ifstream in("editions.txt");
        // library.readEditionsData(in);
        // in.close();


        User user1("Niki");
        User user2("Peter");
        User user3("Alexander");
        library.addUser(user1);
        library.addUser(user2);
        library.addUser(user3);

        library.borrowEdition("Niki", 11);
        library.borrowEdition("Peter", 12);
        library.returnBorrowedEdition("Niki", 11);
        library.returnBorrowedEdition("Peter", 12);
        library.borrowEdition("Niki", 14);
        library.borrowEdition("Peter", 13);
        library.returnBorrowedEdition("Peter", 13);
        library.borrowEdition("Alexander", 13);
        library.borrowEdition("Alexander", 10);
        library.returnBorrowedEdition("Niki", 14);
        library.returnBorrowedEdition("Alexander", 13);

        // library.removeEdition(11);


        // std::ifstream usersIn("users.txt");
        // library.readUsersData(usersIn);
        // usersIn.close();

        std::ofstream usersOut("users.txt");
        library.writeUsersData(usersOut);
        usersOut.close();

        std::ofstream out("editions.txt");
        library.writeEditionsData(out);
        out.close();

        // library.printInfoForEditions();
        
        // library.sortUsersReadBooks();

        // library.printUsersWithBorrowedEdition(13);
        // library.printUsersWithBorrowedEdition(10);

        library.printSortedPrintEditions();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }


    return 0;
}
