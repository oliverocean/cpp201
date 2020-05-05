/* *
 * @author: Oliver Ocean
 *
 * Requirements:
 * Implement the algorithm maxArray(), discussed in Section 2.4.3, as a C++ function.
 * What other recursive definitions of maxArray can you describe?
 *
 * - Name the program maxarray.cpp
 * - maxArray() must be a recursive template function
 * - Add a main function to test the maxArray() function so that you have a complete program
 * - Test the maxArray() function on two arrays of different types
 *
 * */

#include <iostream>
#include <algorithm>

template <typename T>
T maxArray(T [], int, int, int);

int main() {

    int sampleArrayOne[]{24, 74, 783, 93, 203, 4, 640, 446, 11, 36};
    std::string sampleArrayTwo[]{"bb", "xx", "tt", "hh", "vv", "ee", "kk", "mm", "uu", "ii"};

    int first{0};
    int last{9};
    int size{10};

    std::cout << maxArray(sampleArrayOne, first, last, size) << "\n";
    std::cout << maxArray(sampleArrayTwo, first, last, size) << "\n";

    return 0;
}

template <typename T>
T maxArray(T anArray[], int first, int last, int size) {

    T theMax{0};

    if (size == 1) {
        theMax = anArray[first];
    }
    else {
        int mid = first + (last - first) / 2;
        theMax = std::max(
                maxArray(anArray, 0, mid, mid+1), // left array
                maxArray(anArray, mid+1, last, last-mid) // right array
                );
    }
    return theMax;
}