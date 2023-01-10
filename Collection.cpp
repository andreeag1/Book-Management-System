#include <iostream>
#include <string>

class Collection
{
    private:
        std::string collectionName;
        int collectionID;
    
    public:
        Collection(std::string x, int ID) {
            collectionName = x;
            collectionID = ID;
        }

        std::string getCollection() {
            return collectionName;
        }

        int getID() {
            return collectionID;
        }
};