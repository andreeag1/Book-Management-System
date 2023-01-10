#include <iostream>
#include <string>
#include <fstream>

class Book 
{
    private: 
        std::string title;
        std::string author;
        int collectionID;

    public:
        Book(std::string x, std::string y, int ID) 
        {
            title = x;
            author = y;
            collectionID = ID;
        }

        std::string getTitle() {
            return title;
        }

        std::string getAuthor() {
            return author;
        }

        int getID() {
            return collectionID;
        }
};