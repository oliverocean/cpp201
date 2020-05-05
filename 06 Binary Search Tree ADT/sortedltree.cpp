/** @author: Oliver Ocean */

/*
 * @brief: Implement the class BinarySearchTree, as given in Listing 16-4 (p502)
 *
 * Ch. 16, Programming Problems 2, p513
 *
 * 1. insert 21 random numbers (1-100) on the binary search tree using the STL random library
 * 2. remove the first number inserted and display the tree
 *
 * > To display just use in order traversal
 * > No user input for driver program.
 * > Inherit from binarytree ( binarytree.zip ) as a starting point.
 * > Use the BST ADT  BinarySearchTree.h
 *
 * */

#include <iostream>
#include <random>
#include <vector>

#include "BinarySearchTree.h"

// function prototypes
void theDriver();
void displayer(int&);
void randomNumberMaker(std::vector<int>&, const int&);

int main()
{
    std::cout << "\n---[ Input ]---\n";
    theDriver();
    std::cout << "\n<< Exiting.\n";

    return 0;
}

void theDriver()
{
    std::cout << "\n--[ STEP 1 ]--\n";
    std::cout << "-[ Create a Tree (Binary Search Tree ADT) ]-\n";
    auto aBinarySearchTree = std::make_unique<BinarySearchTree<int>>();
    std::cout << "\n<< BST Contains:\n [ ";
    aBinarySearchTree->inorderTraverse(displayer);
    std::cout << " ]\n";
    std::cout << "<< Empty? [ " << std::boolalpha << aBinarySearchTree->isEmpty() << " ]\n";
    std::cout << "<< Height [ " << aBinarySearchTree->getHeight() << " ]\n";
    std::cout << "<< Size   [ " << aBinarySearchTree->getNumberOfNodes() << " ]\n";

    std::cout << "\n--[ STEP 2 ]--\n";
    std::cout << "-[ Generate 21 random numbers ]-\n";
    int howManyNumbers = 21; // MAGIC NUMBER: from requirements
    std::vector<int> randomNumbers;
    randomNumberMaker(randomNumbers, howManyNumbers);
    std::cout << "<< --------------------- >>\n";
    std::cout << "<< Unsorted vector of [ " << randomNumbers.size() << " ] random numbers:\n";
    std::cout << " [ "; for (int n = 0; n < randomNumbers.size(); ++n) { std::cout << randomNumbers[n] << ", "; } std::cout << "]\n";

    std::cout << "\n--[ STEP 3 ]--\n";
    std::cout << "-[ Insert 21 random numbers ]-\n";
    for (int i = 0; i < randomNumbers.size(); ++i)
    {
        std::cout << "   " << i + 1 << ". inserting [ " << randomNumbers[i] << " ]\n";
        aBinarySearchTree->add(randomNumbers[i]);
    }
    std::cout << "\n<< BST Contains:\n [ ";
    aBinarySearchTree->inorderTraverse(displayer);
    std::cout << " ]\n";
    std::cout << "<< Empty? [ " << std::boolalpha << aBinarySearchTree->isEmpty() << " ]\n";
    std::cout << "<< Height [ " << aBinarySearchTree->getHeight() << " ]\n";
    std::cout << "<< Size   [ " << aBinarySearchTree->getNumberOfNodes() << " ]\n";

    std::cout << "\n--[ STEP 4 ]--\n";
    std::cout << "-[ Remove the first number inserted ]-\n";
    std::cout << "<< Removing the first number that was inserted: [ " << randomNumbers[0] << " ]\n";
    std::cout << "<< Success? [ " << aBinarySearchTree->remove(randomNumbers[0]) << " ]\n";

    std::cout << "\n--[ STEP 5 ]--\n";
    std::cout << "-[ Display the modified Binary Search Tree ]-\n";
    std::cout << "<< BST Contains:\n [ ";
    aBinarySearchTree->inorderTraverse(displayer);
    std::cout << " ]\n";
    std::cout << "<< Empty? [ " << std::boolalpha << aBinarySearchTree->isEmpty() << " ]\n";
    std::cout << "<< Height [ " << aBinarySearchTree->getHeight() << " ]\n";
    std::cout << "<< Size   [ " << aBinarySearchTree->getNumberOfNodes() << " ]\n";
}

void displayer(int& anItem) { std::cout << anItem << ", "; }

void randomNumberMaker(std::vector<int>& randomNumbers, const int& howManyNumbers)
{
    // start time measurement immediately (to produce larger value)
    typedef std::chrono::high_resolution_clock aHighResolutionClock;
    aHighResolutionClock::time_point aTimePoint = aHighResolutionClock::now();

    // per requirements, distribution from 1 - 100
    std::uniform_int_distribution<int> aDistribution{1, 100};

    // finish time measurement; generate duration-based seed
    aHighResolutionClock::duration aDuration = aHighResolutionClock::now() - aTimePoint;
    auto aSeed = static_cast<unsigned int>(aDuration.count());

    std::default_random_engine anEngine;
    anEngine.seed(aSeed);

    auto aGenerator = std::bind(aDistribution, anEngine);

    // populate and return vector
    int aRandomNumber;
    for (int r = 0; r < howManyNumbers; ++r)
    {
        aRandomNumber = aGenerator();
        randomNumbers.push_back(aRandomNumber);
    }
}
