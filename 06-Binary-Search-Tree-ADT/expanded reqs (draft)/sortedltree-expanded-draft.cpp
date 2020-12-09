/** @author: Oliver Ocean */

/*
 * Implement the class BinarySearchTree, as given in Listing 16-4 (p502)
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

#include "LinkedSortedList.h"

// function prototypes
void theDriver(bool);
void sortedListDisplayer(const LinkedSortedList<int>&);
void randomNumberMaker(std::vector<int>&, const int&, bool);
char seedTypeChooser();
std::string sequenceInputter();
void distributionRangeInputter(int&, int&);
char generatorTypeChooser();
std::string optionNamer(std::string, char);

int main()
{
    std::cout << "\n---[ Input ]---\n";

    // manual driver flag: set to false for options (seed types, range, and generator types)
    bool autoDrive = true;

    theDriver(autoDrive);
    std::cout << "\n<< Exiting.\n";

    return 0;
}

void theDriver(bool autoDrive)
{
    if (autoDrive) { std::cout << "< Automatic driver: no input required.\n"; }

    std::cout << "\n--[ STEP 1 ]--\n";
    std::cout << "-[ Create a List (Sorted List ADT) ]-\n";
    LinkedSortedList<int> sortedList;
    std::cout << "> Is the new list empty? [ " << std::boolalpha << sortedList.isEmpty() << " ]\n";
    std::cout << "<< Sorted List of [ " << sortedList.getLength() << " ] items created:\n";
    sortedListDisplayer(sortedList);

    std::cout << "\n--[ STEP 2 ]--\n";
    std::cout << "-[ Generate 21 random numbers (range 1 - 100, use STL random) ]-\n";
    int howManyNumbers = 21; // MAGIC NUMBER: from requirements
    std::vector<int> randomNumbers;
    randomNumberMaker(randomNumbers, howManyNumbers, autoDrive);
    std::cout << "<< --------------------- >>\n";
    std::cout << "<< Unsorted vector of [ " << randomNumbers.size() << " ] random numbers:\n";
    std::cout << " [ "; for (int n = 0; n < randomNumbers.size(); ++n) { std::cout << randomNumbers[n] << ", "; } std::cout << "]\n";

    std::cout << "\n--[ STEP 3 ]--\n";
    std::cout << "-[ Insert random numbers into Sorted List (ADT) ]-\n";
    for (int i = 0; i < randomNumbers.size(); ++i)
    {
        std::cout << "   " << i + 1 << ". inserting [ " << randomNumbers[i] << " ]\n";
        sortedList.insertSorted(randomNumbers[i]);
    }
    std::cout << "<< Sorted List of [ " << sortedList.getLength() << " ] items:\n";
    sortedListDisplayer(sortedList);

    std::cout << "\n--[ STEP 4 ]--\n";
    std::cout << "-[ Remove the first number inserted ]-\n";
    std::cout << "<< Removing the first number that was inserted: [ " << randomNumbers[0] << " ]\n";
    sortedList.removeSorted(randomNumbers[0]);

    std::cout << "\n--[ STEP 5 ]--\n";
    std::cout << "-[ Display the sorted list of 20 numbers ]-\n";
    std::cout << "<< Sorted List of [ " << sortedList.getLength() << " ] items:\n";
    sortedListDisplayer(sortedList);

    std::cout << "\n--[ STEP 6 ]--\n";
    std::cout << "-[ Test all methods implemented ]-\n";
    std::cout << "<< Duplicating the sorted list with copy constructor...\n";
    LinkedSortedList<int> sortedListCopy(sortedList);
    std::cout << "> Is the new list (copy) empty? [ " << std::boolalpha << sortedListCopy.isEmpty() << " ]\n";
    std::cout << "<< Sorted List (copy) of [ " << sortedListCopy.getLength() << " ] items:\n";
    sortedListDisplayer(sortedListCopy);

    std::cout << "\n> What is the 6th item? [ " << sortedListCopy.getEntry(6) << " ]\n";
    std::cout << "<< Remove the 6th item...\n";
    sortedListCopy.remove(6);
    std::cout << "<< Sorted List of [ " << sortedListCopy.getLength() << " ] items:\n";
    sortedListDisplayer(sortedListCopy);

    std::cout << "\n<< Insert the number 11...\n";
    sortedListCopy.insertSorted(11);
    std::cout << "> What position is number 11? [ " << sortedListCopy.getPosition(11) << " ]\n";
    std::cout << "<< Sorted List of [ " << sortedListCopy.getLength() << " ] items:\n";
    sortedListDisplayer(sortedListCopy);
    std::cout << "\n<< Remove the number 11...\n";
    sortedListCopy.removeSorted(11);
    std::cout << "<< Sorted List of [ " << sortedListCopy.getLength() << " ] items:\n";
    sortedListDisplayer(sortedListCopy);

    std::cout << "\n<< Verifying exceptions on a populated list...\n";
    try
    {
        std::cout << "> What position is number [ -1 ]?\n";
        sortedListCopy.getPosition(-1);
    }
    catch (CustomException& e)
    {
        std::cout << e.what() << "\n";
    }

    try
    {
        std::cout << "> What item is at position [ -1 ]?\n";
        sortedListCopy.getEntry(-1);
    }
    catch (CustomException& e)
    {
        std::cout << e.what() << "\n";
    }

    try
    {
        std::cout << "> Can the item at position [ -1 ] be removed?\n";
        sortedListCopy.remove(-1);
    }
    catch (CustomException& e)
    {
        std::cout << e.what() << "\n";
    }

    try
    {
        std::cout << "> What position is number [ 101 ]?\n";
        sortedListCopy.getPosition(101);
    }
    catch (CustomException& e)
    {
        std::cout << e.what() << "\n";
    }

    try
    {
        std::cout << "> What item is at position [ 22 ]?\n";
        sortedListCopy.getEntry(22);
    }
    catch (CustomException& e)
    {
        std::cout << e.what() << "\n";
    }

    try
    {
        std::cout << "> Can the item at position [ 22 ] be removed?\n";
        sortedListCopy.remove(22);
    }
    catch (CustomException& e)
    {
        std::cout << e.what() << "\n";
    }

    std::cout << "\n<< Clear the list...\n";
    sortedListCopy.clear();
    std::cout << "> Is the list empty? [ " << std::boolalpha << sortedListCopy.isEmpty() << " ]\n";
    std::cout << "<< Sorted List of [ " << sortedListCopy.getLength() << " ] items:\n";
    sortedListDisplayer(sortedListCopy);

    std::cout << "\n<< Verifying exceptions on an empty list...\n";
    try
    {
        std::cout << "> What position is number [ -1 ]?\n";
        sortedListCopy.getPosition(-1);
    }
    catch (CustomException& e)
    {
        std::cout << e.what() << "\n";
    }

    try
    {
        std::cout << "> What item is at position [ -1 ]?\n";
        sortedListCopy.getEntry(-1);
    }
    catch (CustomException& e)
    {
        std::cout << e.what() << "\n";
    }

    try
    {
        std::cout << "> Can the item at position [ -1 ] be removed?\n";
        sortedListCopy.remove(-1);
    }
    catch (CustomException& e)
    {
        std::cout << e.what() << "\n";
    }

    try
    {
        std::cout << "> What position is number [ 101 ]?\n";
        sortedListCopy.getPosition(101);
    }
    catch (CustomException& e)
    {
        std::cout << e.what() << "\n";
    }

    try
    {
        std::cout << "> What item is at position [ 22 ]?\n";
        sortedListCopy.getEntry(22);
    }
    catch (CustomException& e)
    {
        std::cout << e.what() << "\n";
    }

    try
    {
        std::cout << "> Can the item at position [ 22 ] be removed?\n";
        sortedListCopy.remove(22);
    }
    catch (CustomException& e)
    {
        std::cout << e.what() << "\n";
    }
}


void sortedListDisplayer(const LinkedSortedList<int>& aSortedList)
{
    std::cout << " [ ";
    for (int s = 1; s <= aSortedList.getLength(); ++s)
    {
        std::cout << aSortedList.getEntry(s) << ", ";
    }
    std::cout << "]\n";
}

void randomNumberMaker(std::vector<int>& randomNumbers, const int& howManyNumbers, bool autoDrive)
{
    std::cout << "<< Three elements will be used to produce random numbers:\n" <<
              "   • SEED:         duration-based or sequence-based\n" <<
              "   • DISTRIBUTION: probability of integer distribution\n" <<
              "   • GENERATOR:    a pseudo-random number engine\n";

    // <---[ SEEDS ]---> //
    char seedType = 'd'; // default is duration
    if (!autoDrive)
    {
         seedType = seedTypeChooser();
    }

    // start time measurement immediately (to produce larger value)
    typedef std::chrono::high_resolution_clock aHighResolutionClock;
    aHighResolutionClock::time_point aTimePoint = aHighResolutionClock::now();

    // generate sequence-based seed; collect user input if needed
    std::string sequenceString = "Hello Random World!";
    if (seedType == 's')
    {
        sequenceString = sequenceInputter();
    }
    std::seed_seq sequenceSeed(sequenceString.begin(), sequenceString.end());

    // finish time measurement; generate duration-based seed
    aHighResolutionClock::duration aDuration = aHighResolutionClock::now() - aTimePoint;
    auto durationSeed = static_cast<unsigned int>(aDuration.count());

    // <---[ DISTRIBUTION ]---> //
    // potentially add other distribution options in future
    if (!autoDrive)
    {
        std::cout << "<< Using a [ Uniform ] distribution.\n";
    }
    // collect user input for RANGE of numbers to use
    int distributionStart = 1;
    int distributionEnd = 100;
    if (!autoDrive)
    {
        distributionRangeInputter(distributionStart, distributionEnd);
    }
    std::uniform_int_distribution<int> uniformDistribution{distributionStart, distributionEnd};

    // <---[ GENERATORS ]---> //
    // regardless of choice, create all generator options for ease of implementation
    std::default_random_engine generatorA;
    std::minstd_rand0 generatorB;
    std::knuth_b generatorC;
    std::mt19937 generatorD;
    std::ranlux24_base generatorE;

    // regardless of choice, seed all generator options for ease of implementation
    if (seedType == 's')
    {
        generatorA.seed(sequenceSeed);
        generatorB.seed(sequenceSeed);
        generatorC.seed(sequenceSeed);
        generatorD.seed(sequenceSeed);
        generatorE.seed(sequenceSeed);
    }
    else
    {
        generatorA.seed(durationSeed);
        generatorB.seed(durationSeed);
        generatorC.seed(durationSeed);
        generatorD.seed(durationSeed);
        generatorE.seed(durationSeed);
    }

    if (!autoDrive)
    {
        std::cout << "<< --------------------- >>\n";
        std::cout << "> Generators created and initialized with a ";
        if (seedType == 's')
        {
            std::cout << "[ Sequence ]";
        }
        else
        {
            std::cout << "[ Duration ]";
        }
        std::cout << " seed.\n" <<
                  "  • Default Random seed   [ " << generatorA() << " ]\n" <<
                  "  • Minimal Standard seed [ " << generatorB() << " ]\n" <<
                  "  • Knuth-B seed          [ " << generatorC() << " ]\n" <<
                  "  • Mersenne Twister seed [ " << generatorD() << " ]\n" <<
                  "  • Ranlux 24 seed        [ " << generatorE() << " ]\n";
    }

    char generatorType = 'a'; // default is Default Random Engine
    if (!autoDrive)
    {
        generatorType = generatorTypeChooser();
    }

    // <---[ BIND GENERATORS TO DISTRIBUTION ]---> //
    auto uniformGeneratorA = std::bind(uniformDistribution, generatorA);
    auto uniformGeneratorB = std::bind(uniformDistribution, generatorB);
    auto uniformGeneratorC = std::bind(uniformDistribution, generatorC);
    auto uniformGeneratorD = std::bind(uniformDistribution, generatorD);
    auto uniformGeneratorE = std::bind(uniformDistribution, generatorE);

    // <---[ POPULATE AND RETURN VECTOR ]---> //
    int aRandomNumber;
    if (generatorType == 'b')
    {
        for (int r = 0; r < howManyNumbers; ++r)
        {
            aRandomNumber = uniformGeneratorB();
            randomNumbers.push_back(aRandomNumber);
        }
    }
    else if (generatorType == 'c')
    {
        for (int r = 0; r < howManyNumbers; ++r)
        {
            aRandomNumber = uniformGeneratorC();
            randomNumbers.push_back(aRandomNumber);
        }
    }
    else if (generatorType == 'd')
    {
        for (int r = 0; r < howManyNumbers; ++r)
        {
            aRandomNumber = uniformGeneratorD();
            randomNumbers.push_back(aRandomNumber);
        }
    }
    else if (generatorType == 'e')
    {
        for (int r = 0; r < howManyNumbers; ++r)
        {
            aRandomNumber = uniformGeneratorE();
            randomNumbers.push_back(aRandomNumber);
        }
    }
    else
    {
        for (int r = 0; r < howManyNumbers; ++r)
        {
            aRandomNumber = uniformGeneratorA();
            randomNumbers.push_back(aRandomNumber);
        }
    }

    // <---[ DISPLAY OPTIONS USED ]---> //
    std::cout << "<< --------------------- >>\n";
    std::cout << "<< Produced [ " << howManyNumbers << " ] random numbers with these options:\n" <<
                    "   • Seed type:         [ " << optionNamer("seed", seedType) << " ]\n" <<
                    "   • Distribution type: [ Uniform ] with range [ " << distributionStart <<
                                                                " - " << distributionEnd << " ]\n" <<
                    "   • Generator type:    [ " << optionNamer("generator", generatorType) << " ]\n" <<
                    "    (set manual driver flag for alternative options)\n";
}

// helper function for randomNumberMaker()
char generatorTypeChooser()
{
    char generatorTypeChoice;
    std::cout << "<< --------------------- >>\n";
    std::cout << "> Select a GENERATOR to use for the next step:\n" <<
              "  'a' for Default Random   (Linear Congruential Engine)\n" <<
              "  'b' for Minimal Standard (Linear Congruential Engine)\n" <<
              "  'c' for Knuth-B          (Linear Congruential with Shuffle-order Adapter)\n" <<
              "  'd' for Mersenne Twister (Mersenne Twister Engine)\n" <<
              "  'e' for Ranlux 24        (Subtract-with-carry Engine)\n" <<
              "? ";
    std::string rawInput;
    getline(std::cin, rawInput);
    if (rawInput == "b" || rawInput == "B")
    {
        std::cout << "<< Using the [ Minimal Standard ] engine.\n";
        return generatorTypeChoice = 'b';
    }
    else if (rawInput == "c" || rawInput == "C")
    {
        std::cout << "<< Using the [ Knuth-B ] engine.\n";
        return generatorTypeChoice = 'c';
    }
    else if (rawInput == "d" || rawInput == "D")
    {
        std::cout << "<< Using the [ Mersenne Twister ] engine.\n";
        return generatorTypeChoice = 'd';
    }
    else if (rawInput == "e" || rawInput == "E")
    {
        std::cout << "<< Using the [ Ranlux 24 ] engine.\n";
        return generatorTypeChoice = 'e';
    }
    else
    {
        std::cout << "<< Using the [ Default Random ] engine. (default)\n";
        return generatorTypeChoice = 'a';
    }
}

// helper function for randomNumberMaker()
void distributionRangeInputter(int& start, int& end)
{
    std::cout << "<< --------------------- >>\n";
    std::cout << "> Enter a Distribution RANGE\n";

    std::string rawStartInput;
    std::cout << "Start? ";
    getline(std::cin, rawStartInput);
    std::string rawEndInput;
    std::cout << "End? ";
    getline(std::cin, rawEndInput);

    if (rawStartInput.empty() || rawEndInput.empty())
    {
        start = 1;
        end = 100;
        std::cout << "< Empty input.\n<< Using the range [ 1 - 100 ] (default)\n";
    }
    else
    {
        start = stoi(rawStartInput);
        end = stoi(rawEndInput);
        if (start > end || start < 0 || end < 1)
        {
            start = 1;
            end = 100;
            std::cout << "< Invalid input.\n<< Using the range [ 1 - 100 ] (default)\n";
        }
        else
        {
            std::cout << "<< Using the range [ " << start << " - " << end << " ]\n";
        }
    }
}

// helper function for randomNumberMaker()
char seedTypeChooser()
{
    char seedTypeChoice;
    std::cout << "<< --------------------- >>\n";
    std::cout << "> Select a SEED type (note: a specific duration or sequence always produces the same seed).\n" <<
                 "  'd' for Duration (accumulates a series of time increments)\n" <<
                 "  's' for Sequence (evaluates a series of values within a sequence)\n" <<
                 "? ";
    std::string rawInput;
    getline(std::cin, rawInput);
    if (rawInput == "s" || rawInput == "S")
    {
        std::cout << "<< Using a seed based upon [ Sequence ].\n";
        return seedTypeChoice = 's';
    }
    else
    {
        std::cout << "<< Using a seed based upon [ Duration ]. (default)\n";
        return seedTypeChoice = 'd';
    }
}

// helper function for randomNumberMaker()
std::string sequenceInputter()
{
    std::string sequenceInput;
    std::cout << "<< --------------------- >>\n";
    std::cout << "> Input a SEQUENCE (anything you like, phrases, words, letters, numbers:\n" <<
              "? ";
    std::string rawInput;
    getline(std::cin, rawInput);
    if (rawInput.empty())
    {
        std::cout << "<< Using the sequence [ 'Hello Random World!' ] (default)\n";
        return sequenceInput = "Hello Random World!";
    }
    else
    {
        std::cout << "<< You entered the sequence [ '" << rawInput << "' ]\n";
        return sequenceInput = rawInput;
    }
}

// helper function for randomNumberMaker()
std::string optionNamer(std::string element, char option)
{
    if (element == "seed")
    {
        if (option == 's')
        {
            return "Sequence";
        }
        else if (option == 'd')
        {
            return "Duration";
        }
    }
    else if (element == "generator")
    {
        if (option == 'a')
        {
            return "Default Random";
        }
        else if (option == 'b')
        {
            return "Minimal Standard";
        }
        else if (option == 'c')
        {
            return "Knuth-B";
        }
        else if (option == 'd')
        {
            return "Mersenne Twister";
        }
        else if (option == 'e')
        {
            return "Ranlux 24";
        }
    }
    return "Unknown";
}
