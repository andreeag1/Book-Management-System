#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include "Book.cpp"
#include "Collection.cpp"
#include <limits>

void MainMenu ();
Book CreateBook();
Book CreateWantToReadBook();
Collection CreateCollection();
void WriteCollectionToFile(Collection collection);
void ReadCollectionFile();
void WriteBookToFile(Book book);
void ReadBookFile();
int NumberOfCollections();
int ReadID();
int nthOccurrence(const std::string& str, const std::string& findMe, int nth);
void readSpecificID(int choice);
void WriteProgressToFile(Book book);
void ReadProgressToFile();
int NumberOfCurrentReads();
void editProgress();
void WriteWantToReadBookToFile(Book book);
void ReadWantToReadBookFile();
std::string Validation(int num, std::string choice);

int main() {

    std::cout << "\tWelcome to BookManager!" << std::endl;
    std::cout << "Press enter to continue to the HOME PAGE..." << std::endl;
    std::cin.get();
    MainMenu();
}   

std::string Validation(int num, std::string choice) {
    bool validate=0;
    int selectedChoice = std::stoi(choice);
    std::string newChoice;
    if (selectedChoice != num && selectedChoice < num) {
        newChoice = choice;
        validate = 1;
    }
    while (newChoice != choice) {
        std::cout << "This is an invalid option. Please choose a number within the possible range of options (0-" << num-1 << ")" << std::endl;
        std::getline(std::cin, choice);
        newChoice = choice;
    }
    return newChoice;
}

void MainMenu () {
    std::string choice;
    std::cout << "Welcome to your HOME PAGE" << std::endl;
    std::cout << "[0] Enter a new book" << std::endl;
    std::cout << "[1] View your current reads" << std::endl;
    std::cout << "[2] View the books you want to read" << std::endl;
    std::cout << "[3] View your book collections" << std::endl;
    std::getline(std::cin, choice);
    choice = Validation(4, choice);
    if (choice == "0") {
        std::string choice1="";
        std::cout << "[0] Finished reading" << std::endl;
        std::cout << "[1] Still reading" << std::endl;
        std::getline(std::cin, choice1);
        choice1 = Validation(2, choice1);
        if (choice1 == "0") {
            Book new_book = CreateBook();
            WriteBookToFile(new_book);
        } else if (choice1 == "1") {
            Book new_book = CreateBook();
            WriteProgressToFile(new_book);
        }   
    } else if (choice == "1") {
        ReadProgressToFile();
        std::cout << "[0] Edit Progress" << std::endl;
        std::cout << "[1] Back to home page" << std::endl;
        std::string choice;
        std::getline(std::cin, choice);
        choice = Validation(2, choice);
        if (choice == "0") {
            editProgress();
        } else if (choice == "1") {
            MainMenu();
        }
    } else if (choice == "2") {
        ReadWantToReadBookFile();
    } else if (choice == "3") {
        ReadCollectionFile();
    }
}

int NumberOfCollections() {
    int numberOfLines = 0;
    std::string line;
    std::ifstream MyFile("collections.txt");
    while (std::getline(MyFile, line))
    {
        numberOfLines++;
    }
    return numberOfLines;

}

Book CreateBook() {
    std::string title;
    std::string author;
    std::string choice;
    int collectionID;

    std::cout << "Enter the title of the book: " << std::endl;
    std::getline(std::cin, title);
    std::cout << "Enter the author of the book: " << std::endl;
    std::getline(std::cin, author);
    std::cout << "Would you like to add your book to a collection? [Y] or [N]" << std::endl;
    std::getline(std::cin, choice);
    if (choice == "Y" || choice == "y") {
        std::string collections;
        std::string choice1;
        std::ifstream MyFile ("collections.txt");
        for (int x=0; x<NumberOfCollections(); x++) {
            while(std::getline(MyFile, collections)){
                std::cout << "[" << x << "] " << collections << std::endl;
                break;
            }  
            
        }
        std::cout << "[" << NumberOfCollections() << "] Add a new collection" << std::endl;
        std::getline (std::cin, choice1);
        std::string str = std::to_string(NumberOfCollections());
        int newCollectionID = std::stoi(choice1);
        if (newCollectionID < NumberOfCollections()) {
            collectionID = newCollectionID;
        } else if (choice1 == str) {
            Collection new_collection = CreateCollection();
            WriteCollectionToFile(new_collection);
            collectionID = NumberOfCollections();
        }
    } else if (choice == "N" || choice == "n") {
        collectionID = -1;
    } 

    Book book(title, author, collectionID);

    return book;
}

Book CreateWantToReadBook() {
    std::string title;
    std::string author;
    int collectionID = -1;

    std::cout << "Enter the title of the book: " << std::endl;
    std::getline(std::cin, title);
    std::cout << "Enter the author of the book: " << std::endl;
    std::getline(std::cin, author);

    Book book(title, author, collectionID);

    return book;
}

Collection CreateCollection() {
    std::string collectionName;
    int collectionID;

    std::cout << "Enter the name of your new collection: " << std::endl;
    std::getline (std::cin, collectionName);

    Collection collection(collectionName, collectionID);
    collectionID++;
    
    return collection;
}

int NumberOfCurrentReads() {
    int numberOfLines = 0;
    std::string line;
    std::ifstream MyCurrentReadFile("progress.txt");
    while (std::getline(MyCurrentReadFile, line))
    {
        numberOfLines++;
    }
    return numberOfLines;

}

void WriteWantToReadBookToFile(Book book) {
    std::ofstream WantToReadFile;
    WantToReadFile.open("TBR.txt", std::ios::app);
    WantToReadFile << book.getTitle() << ", " << book.getAuthor() << std::endl;
    WantToReadFile.close();
    ReadWantToReadBookFile();
}

void ReadWantToReadBookFile() {
    std::string books;
    std::string choice;
    std::ifstream WantToReadFile ("TBR.txt");
    std::cout<< "YOUR WANT TO READ BOOKS" << std::endl;
    while (std::getline(WantToReadFile, books)) {
        std::cout << books << std::endl;
    }
    std::cout << "[0] Enter a new book" << std::endl;
    std::cout << "[1] Back to home page" << std::endl;
    std::getline(std::cin, choice);
    choice = Validation(2, choice);
    if (choice == "0") {
        Book new_book = CreateWantToReadBook();
        WriteWantToReadBookToFile(new_book);
    } else if (choice == "1") {
        MainMenu();
    }
}

void ReadCollectionFile() {
    std::cout << "YOUR COLLECTIONS" << std::endl;
    std::cout << "Please select which collection you would like to view: " << std::endl;
    std::string collections;
    int x = 0; 
    std::string choice1;
    std::ifstream MyFile ("collections.txt");
    for (x=0; x<NumberOfCollections(); x++) {
        while(std::getline(MyFile, collections)){
            std::cout << "[" << x << "] " << collections << std::endl;
            break;
        }   
    }
    std::cout << "[" << NumberOfCollections() <<"] " << "Read Books" << std::endl;
    std::cout << "[" << NumberOfCollections()+1 <<"] " << "Add a new collection" << std::endl;
    std::cout << "[" << NumberOfCollections()+2 << "] " << "Back to home page" << std::endl;
    std::getline (std::cin, choice1);
    choice1 = Validation(NumberOfCollections()+3, choice1);
    int choice = std::stoi(choice1);
        if (choice == NumberOfCollections()) {
            ReadBookFile();
        } else if (choice<NumberOfCollections()) {
            readSpecificID(choice);
        } else if (choice == NumberOfCollections()+1) {
            Collection new_collection = CreateCollection();
            WriteCollectionToFile(new_collection);
        } else if (choice == NumberOfCollections()+2) {
            MainMenu();
        }
}

void WriteCollectionToFile(Collection collection) {
    std::ofstream MyFile;
    MyFile.open("collections.txt", std::ios::app);
    MyFile << collection.getCollection() << std::endl;
    MyFile.close();
    ReadCollectionFile();
}


int nthOccurrence(std::string& str, std::string& findMe, int nth)
{
    size_t  pos = 0;
    int     cnt = 0;

    while( cnt != nth )
    {
        pos+=1;
        pos = str.find(findMe, pos);
        if ( pos == std::string::npos )
            return -1;
        cnt++;
    }
    return pos;
}

void readSpecificID(int choice) {
    int ID;
    std::string readBooks;
    std::string currentReads;
    std::ifstream MyReadBooksFile ("read.txt");
    size_t thirdComma;
    std::string comma = ",";
    std::string stringID;
    std::vector<int> arr;
    while (std::getline(MyReadBooksFile, readBooks))
    {   
        thirdComma = nthOccurrence(readBooks, comma , 3);
        int convertdata = static_cast<int>(thirdComma);
        stringID = readBooks.substr(convertdata+2, readBooks.back());
        ID = std::stoi(stringID);
        arr.push_back(ID);
    }
    std::ifstream MyCurrentReadFile ("progress.txt");
    while (std::getline(MyCurrentReadFile, currentReads))
    {   
        thirdComma = nthOccurrence(currentReads, comma , 3);
        int convertdata = static_cast<int>(thirdComma);
        stringID = currentReads.substr(convertdata+2, currentReads.back());
        ID = std::stoi(stringID);
        arr.push_back(ID);
    }
    int arrSize = sizeof(arr)/sizeof(arr[0]);
    std::string chosenBooks;
    std::string currentChosenReads;
    for (int x=0; x<arrSize; x++) {
        if (x == choice) {
            std::ifstream MyReadBooksFile ("read.txt");
            std::string str = std::to_string(choice);
            while (std::getline(MyReadBooksFile, chosenBooks))
            {
                thirdComma = nthOccurrence(chosenBooks, comma , 3);
                int convertdata = static_cast<int>(thirdComma);
                std::string chosenBookID = chosenBooks.substr(convertdata+2, chosenBooks.back());
                if (chosenBookID.find(str) != -1) {
                    thirdComma = nthOccurrence(chosenBooks, comma , 3);
                    int convertdata = static_cast<int>(thirdComma);
                    std::cout << chosenBooks.substr(0, convertdata) << std::endl;
                }
            }
            std::ifstream MyCurrentReadFile ("progress.txt");
            while (std::getline(MyCurrentReadFile, currentChosenReads))
            {
                thirdComma = nthOccurrence(currentChosenReads, comma , 3);
                int convertdata = static_cast<int>(thirdComma);
                std::string chosenBookID = currentChosenReads.substr(convertdata+2, currentChosenReads.back());
                if (chosenBookID.find(str) != -1) {
                    thirdComma = nthOccurrence(currentChosenReads, comma , 3);
                    int convertdata = static_cast<int>(thirdComma);
                    std::cout << currentChosenReads.substr(0, convertdata) << std::endl;
                }
            }
            
            break;
        }
    }
    std::cout << "[0] Back to home page" << std::endl;
    std::string choice1;
    std::getline(std::cin, choice1);
    choice1 = Validation(1, choice1);
    if (choice1 == "0") {
        MainMenu();
    }
}


void WriteBookToFile(Book book) {
    std::string rating;
    std::ofstream MyReadBooksFile;
    MyReadBooksFile.open("read.txt", std::ios::app);
    std::cout<< "Give your book a rating (out of 5 stars): " << std::endl;
    std::getline(std::cin, rating);
    MyReadBooksFile << book.getTitle() << ", " << book.getAuthor() << ", " << rating << " stars, " << book.getID() << std::endl;
    MyReadBooksFile.close();
    ReadBookFile();
}

int ReadID() {
    int ID;
    std::string readBooks;
    std::ifstream MyReadBooksFile ("read.txt");
    size_t thirdComma;
    std::string comma;
    comma = ",";
    std::string stringID;
    while (std::getline(MyReadBooksFile, readBooks))
    {   
        thirdComma = nthOccurrence(readBooks, comma , 3);
        int convertdata = static_cast<int>(thirdComma);
        stringID = readBooks.substr(convertdata+2, readBooks.back());
    }
    ID = std::stoi(stringID);
    return ID;
}

void ReadBookFile() {
    std::string readBooks;
    std::ifstream MyReadBooksFile ("read.txt");
    size_t thirdComma;
    std::string comma;
    comma = ",";
    std::cout << "YOUR READ BOOKS" << std::endl;
    while (std::getline(MyReadBooksFile, readBooks))
    {
        thirdComma = nthOccurrence(readBooks, comma , 3);
        int convertdata = static_cast<int>(thirdComma);
        std::cout << readBooks.substr(0, convertdata) << std::endl;
    }
    std::cout << "[0] Back to home page" << std::endl;
    std::string choice;
    choice = Validation(1, choice);
    std::getline(std::cin, choice);
    if (choice == "0") {
        MainMenu();
    }
}

void WriteProgressToFile(Book book) {
    std::string progress;
    std::cout << "Enter your progress in percentage: " << std::endl;
    std::getline (std::cin, progress);
    std::ofstream MyCurrentReadFile;
    MyCurrentReadFile.open("progress.txt", std::ios::app); 
    MyCurrentReadFile << book.getTitle() << ", " << book.getAuthor() << ", " << progress << "%, " << book.getID() << std::endl;
    MyCurrentReadFile.close();
    ReadProgressToFile();
}

void ReadProgressToFile() {
    std::string currentBooks;
    std::ifstream MyCurrentReadFile ("progress.txt");
    size_t thirdComma;
    std::string comma;
    comma = ",";
    std::cout << "YOUR CURRENT READS" << std::endl;
    while (std::getline(MyCurrentReadFile, currentBooks))
    {
        thirdComma = nthOccurrence(currentBooks, comma , 3);
        int convertdata = static_cast<int>(thirdComma);
        std::cout << currentBooks.substr(0, convertdata) << std::endl;
    }
}

void editProgress() {
    std::cout << "Please select which book you would like to edit its progress: " << std::endl;
    std::string progress;
    std::string newProgress;
    std::string bookInfo;
    std::string newBookInfo;
    int x = 0;
    int y = 0;
    std::string choice;
    std::ifstream MyCurrentReadFile ("progress.txt");
    size_t thirdComma;
    size_t secondComma;
    std::string comma;
    std::string line;
    comma = ",";
    while (std::getline(MyCurrentReadFile, progress)){
        thirdComma = nthOccurrence(progress, comma , 3);
        int convertdata = static_cast<int>(thirdComma);
        secondComma = nthOccurrence(progress, comma, 2);
        int convertdata1 = static_cast<int>(secondComma);
        bookInfo = progress.substr(0, convertdata);
        newBookInfo = progress.substr(0, convertdata1);
        std::cout << "[" << x << "] " << bookInfo << std::endl;
        x++;
            
            std::ofstream OutputFile;
            std::cout << "Update progress? [Y] or [N]" << std::endl;
            std::getline (std::cin, choice);
            if (choice == "Y" || choice=="y") {
                OutputFile.open("temp.txt", std::ios::app);
                std::cout << "Enter your updated progress in percentage or enter 'D' for done!" << std::endl;
                std::getline (std::cin, newProgress);
                if (newProgress == "D" || newProgress == "d") {
                    std::string rating;
                    std::ofstream MyReadBooksFile;
                    MyReadBooksFile.open("read.txt", std::ios::app);
                    std::cout<< "Give your book a rating (out of 5 stars): " << std::endl;
                    std::getline(std::cin, rating);
                    MyReadBooksFile << newBookInfo << ", " << rating << " stars, " << progress.substr(convertdata+2, progress.back()) << std::endl;
                    MyReadBooksFile.close();
                } else {
                    OutputFile << newBookInfo << ", " << newProgress << "%, " << progress.substr(convertdata+2, progress.back()) << "\n";
                }
            } else if (choice == "N" || choice=="n") {
                OutputFile.open("temp.txt", std::ios::app);
                OutputFile << progress << "\n";
            } 
        OutputFile.close();

    }
    
    MyCurrentReadFile.close();
    std::remove("progress.txt");
    std::rename("temp.txt", "progress.txt");
    std::ifstream OutputFile ("progress.txt");
    while (std::getline (OutputFile, line)) {
        thirdComma = nthOccurrence(line, comma, 3);
        int convertdata2 = static_cast<int>(thirdComma);
        std::cout << "[" << y << "] " << line.substr(0, convertdata2) << std::endl;
        y++;
    }

}
