// @file: giftlist.cpp
// @author: Oliver Ocean

/*
Nice List (list of items)
Each object contains a name (string) and a list of items (instance of an ADT list)
Ch. 8, #2 (p 264)
*/

#include <iostream>
#include <vector>
#include <random>
#include "Array_List.h"

// function prototypes
bool driverChooser(std::string&);
int quantityChooser(std::string&, int&, int&);
void autoDriver();
void manualDriver();
std::string listNamer(const int&);
std::vector<std::string> itemNamer(const int&);
ArrayList<std::string>* listMaker(std::string&, int&, std::vector<std::string>&);
void listDisplayer(ArrayList<std::string>*);

int main() {

    std::cout << "\n---[ Input ]---\n";

    std::string driverChoice = "auto";
    if (driverChooser(driverChoice)) {
        if (driverChoice == "manual") {
            std::cout << "\n---[ Manual Driver ]---\n";
            manualDriver();
        } else {
            std::cout << "\n---[ Automatic Driver ]---\n";
            autoDriver();
        }
    }
    std::cout << "\n> Exiting.\n";
    return 0;
}

// asks user if they prefer a manual or automatic driver
bool driverChooser(std::string& driverChoice) {
    std::cout << "> Choose a driver method (or 'Q' to quit):\n" <<
              " 'A' for Automatic (default)\n" <<
              " 'M' for Manual\n" <<
              "? ";
    std::string rawInput;
    getline(std::cin, rawInput);
    if (rawInput == "Q" || rawInput == "q") {
        std::cout << "> You chose QUIT...\n";
        return false;
    } else if (rawInput == "M" || rawInput == "m") {
        driverChoice = "manual";
        return true;
    } else {
        driverChoice = "auto";
        return true;
    }
}

// asks user for input at each step (defaults exist so you can just hit enter throughout)
void manualDriver() {

    std::string chooserType;
    int defaultQuantity;
    int maxQuantity;

    // get list count
    chooserType = "lists";
    defaultQuantity = 3;
    maxQuantity = 10;
    int listCount = quantityChooser(chooserType, defaultQuantity, maxQuantity);

    // request list/item names, generate lists and store their pointers
    ArrayList<std::string>* theLists[listCount];
    for (int c = 0; c <= listCount - 1; ++c) {
        std::string inputListName = listNamer(c);

        // get item count (each list may have a different number of items)
        chooserType = "items";
        defaultQuantity = 3;
        maxQuantity = 10;
        int itemCount = quantityChooser(chooserType, defaultQuantity, maxQuantity);

        std::vector<std::string> inputItemNames = itemNamer(itemCount);
        auto listPtr = listMaker(inputListName, itemCount, inputItemNames);
        theLists[c] = listPtr;
    }

    // display previously generated lists
    std::cout << "---[ Output ]---\n";
    for (int d = 0; d < listCount; ++d) {
        listDisplayer(theLists[d]);
    }
}

// proceeds through all steps without user input
void autoDriver() {

    std::cout << "<< Creating a random number of lists with a random number of items per list...\n\n";

    // random number generator, uses time for seed
    std::default_random_engine generator{static_cast<unsigned int>(time(0))};

    std::uniform_int_distribution<int> listDistribution{3, 5};
    auto makeListCount = std::bind(listDistribution, generator);
    int listCount = makeListCount(); // no limit, 5000 works just fine

    std::uniform_int_distribution<int> itemDistribution{3, 10};
    auto makeItemCount = std::bind(itemDistribution, generator);
    // itemCount generated/assigned in loop below

    ArrayList<std::string>* theLists[listCount];
    for (int c = 0; c <= listCount - 1; ++c) {

        std::string listName = "List " + std::to_string(c + 1);
        std::vector<std::string> allItems;
        int itemCount = makeItemCount(); // randomly generated

        for (int n = 0; n < itemCount; ++n) {
            std::string anItem = "Item " + std::to_string(n + 1);
            allItems.emplace_back(anItem);
        }

        auto listPtr = listMaker(listName, itemCount, allItems);
        theLists[c] = listPtr;
    }

    // display previously generated lists
    std::cout << "---[ Output ]---\n";
    for (int d = 0; d < listCount; ++d) {
        listDisplayer(theLists[d]);
    }
}

// asks user how many lists OR items they would like to populate
int quantityChooser(std::string& chooserType, int& defaultQuantity, int& maxQuantity) {
    std::cout << "> Number of " << chooserType << "? (1 - " << maxQuantity << ")\n? ";
    std::string inputCount;
    getline(std::cin, inputCount);
    if (inputCount.empty() || std::stoi(inputCount) < 1 || std::stoi(inputCount) > maxQuantity) {
        std::cout << "<< Using default [ " << defaultQuantity << " ] " << chooserType << ".\n\n";
        return defaultQuantity;
    } else {
        std::cout << "<< You entered [ " << inputCount << " ] " << chooserType << ".\n\n";
        return stoi(inputCount);
    }
}

// asks user to input a name for a list
std::string listNamer(const int& listNumber) {

    std::string theTitle = "List"; // default

    std::cout << "> Enter the title of list #" << listNumber + 1 << "\n?";
    std::string inputTitle;
    getline(std::cin, inputTitle);
    if (!inputTitle.empty()) {
        return theTitle = inputTitle;
    }
    return theTitle; // return default if empty input
}

// asks user to input a name for each item in a list
std::vector<std::string> itemNamer(const int& itemCount) {

    std::cout << "> Enter name(s) for the " << itemCount << " item(s)\n";
    std::vector<std::string> allItems;
    std::string anItem;

    for (int c = 0; c < itemCount; ++c) {
        std::cout << " (" << c + 1 << ")?";
        getline(std::cin, anItem);
        if (anItem.empty()) {
            allItems.emplace_back("item");
        } else {
            allItems.emplace_back(anItem);
        }
    }
    std::cout << "\n";

    return allItems;
}

// creates a list from user inputs and returns a pointer to that list
ArrayList<std::string>* listMaker(std::string& aListName, int& aSize, std::vector<std::string>& theItems) {

    // dynamically allocate storage
    auto listPtr = new ArrayList<std::string>(aSize);

    // set title and populate items
    listPtr->setListTitle(aListName);
    for (const auto& m : theItems) {
        listPtr->append(m);
    }

    return listPtr;
}

// displays all items in a list via pointer to that list
void listDisplayer(ArrayList<std::string>* aList) {
    std::cout << "\n  -( " << aList->getListTitle() << " )-\n";
    for (int g = 1; g < aList->getListSize() + 1; ++g) {
        std::cout << "    (" << g << ")" << " " << aList->getAt(g) << "\n";
    }
}