/** @author: Oliver Ocean */

/** @brief:
 * > Chapter 4, Problem #8, Page 157: Specify and implement an
 * ADT character string (class), using a linked chain of characters.
 *
 * Include typical operations such as length, appending one string to another,
 * finding the index of leftmost occurrence of a character in a string,
 * and testing whether one string is a substring of another.
 *
 * */

#include "NodeBag.h"

#include <iostream>
#include <string>

// function prototypes
void menuTester(NodeBag<char>&);
int displayMenu();

int main() {

    NodeBag<char> charChain;
    menuTester(charChain);

    return 0;
}

void menuTester(NodeBag<char>& charChain) {

    int menuChoice;
    std::string userInput;

    do {

        switch (menuChoice = displayMenu()) {

            case 1: // "Enter a new string and store"
                if (!charChain.isEmpty()) {
                    std::cout << ">> A string already exists: " << charChain.getDataAsString() << "\n";
                    std::cout << ">> Deleting it...\n";
                    charChain.clear();
                }

                std::cout << ">> Enter a new string:\n";
                std::cin.ignore();
                std::getline(std::cin, userInput);
                std::cout << ">> You entered: " << userInput << "\n";
                charChain.addToFront(userInput);
                std::cout << ">> New string stored: " << charChain.getDataAsString();
                break;

            case 2: // "Append a new string to stored string"
                if (charChain.isEmpty()) {
                    std::cout << ">> No string currently stored.";
                } else {
                    std::cout << ">> The previously stored string: " << charChain.getDataAsString() << "\n";
                    std::cout << ">> Enter a string to append:\n";
                    std::cin.ignore();
                    std::getline(std::cin, userInput);
                    std::cout << ">> You entered: " << userInput << "\n";
                    NodeBag<char> newNodeBagToAppend;
                    newNodeBagToAppend.addToFront(userInput);
                    if (charChain.append(newNodeBagToAppend)) {
                        std::cout << ">> New appended string: " << charChain.getDataAsString();
                    }
                }
                break;

            case 3: // "Display the stored string"
                if (charChain.isEmpty()) {
                    std::cout << "\n>> No string currently stored.\n";
                    std::cout << ">> In this case, length is 0.";
                } else {
                    std::cout << ">> The previously stored string: " << charChain.getDataAsString();
                    std::cout << "\n>> The length of this string: " << charChain.getSize();
                }
                break;

            case 4: // "Find a character within the stored string"
                if (charChain.isEmpty()) {
                    std::cout << ">> No string currently stored.";
                } else {
                    std::cout << ">> A string has previously been stored: " << charChain.getDataAsString() << "\n";
                    std::cout << ">> Enter a single character to locate:\n"
                              << ">> (additional characters will be ignored)\n";
                    std::cin.ignore();
                    std::getline(std::cin, userInput);
                    std::cout << "\n>> You entered: " << userInput[0] << "\n";
                    if (charChain.getIndex(userInput[0]) != -1) {
                        std::cout << ">> Found a match!\n"
                                  << ">> Position: " << (charChain.getIndex(userInput[0]) + 1) << "\n"
                                  << ">> Index: " << charChain.getIndex(userInput[0]);
                    } else {
                        std::cout << " >> Not found.";
                    }
                }
                break;

            case 5: // "Find a new string within the stored string"
                if (charChain.isEmpty()) {
                    std::cout << ">> No string currently stored.";
                } else {
                    std::cout << ">> A string has previously been stored: " << charChain.getDataAsString();
                    std::cout << "\n>> Enter the string to locate:\n";
                    std::cin.ignore();
                    std::getline(std::cin, userInput);
                    std::cout << "\n>> You entered: " << userInput << "\n";
                    NodeBag<char> newNodeBag;
                    newNodeBag.addToFront(userInput);
                    std::cout << "Saved a new (additional) string that contains: " << newNodeBag.getDataAsString();
                    std::cout << "\n-- Does the old string contain the new string? --\n";
                    if (charChain.contains(newNodeBag)) {
                        std::cout << "yes.";
                    } else {
                        std::cout << "no.";
                    }
                }
                break;

            default: {
                break;
            }
        } // end switch
    } while (menuChoice != 6);
    std::cout << "<< Exiting program >>";
}

int displayMenu() {
    int userMenuInput;
    std::cout << "\n\n --- Program Menu ---------------\n"
            << " (1) Enter a new string and store\n"
            << " (2) Append a new string to stored string\n"
            << " (3) Display the stored string and the length\n"
            << " (4) Find a character within the stored string\n"
            << " (5) Find a new string within the stored string\n"
            << " (6) Quit the program\n"
            << " --------------------------------\n"
            << ">> \n";

    while (!(std::cin >> userMenuInput) || userMenuInput < 0 || userMenuInput > 6)
    {
        std::cout << ">> Invalid choice, try again.\n>> \n";
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
    }
    return userMenuInput;
}