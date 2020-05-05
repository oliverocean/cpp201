/** @author: Oliver Ocean */

#ifndef SORTEDLIST_IS_A_SMARTLINKEDLIST_
#define SORTEDLIST_IS_A_SMARTLINKEDLIST_

#include "Smart_LinkedList.h"
#include "CustomException.h"

template<typename T>
class SortedListIsA : public SmartLinkedList<T>
{
public:
    SortedListIsA();
    SortedListIsA(const SortedListIsA<T>& aList); // copy constructor

    //// Using public inheritance thus, all of these functions
    //// are available to client via parent (SmartLinkedList)
    // auto isListEmpty() const override;
    // auto getListSize() const override;
    // auto clearList() override;
    // auto getPositionOf(const T& item) const override;
    // auto getItemAt(const int& position) const override;
    // auto removeItemAt(const int& position) override;
    // auto remove(const T& item) override;

    // this function is not available in parent, thus properly defined below
    auto insert(const T& item) override;

    // These functions are inherited from parent but are
    // specifically disabled because they can modify/break sort order.
    // The IDE (appropriately) is giving a warning that these functions
    // hide the corresponding non-virtual functions in the parent
    auto insertAt(const T& item, const int& position) override;
    auto replaceAt(const T& item, const int& position) override;

    ~SortedListIsA();
};

// default constructor
template<typename T>
SortedListIsA<T>::SortedListIsA() = default;

// copy constructor
template<typename T>
SortedListIsA<T>::SortedListIsA(const SortedListIsA<T>& aList) : SmartLinkedList<T>(aList) {}

// destructor
template<typename T>
SortedListIsA<T>::~SortedListIsA() = default;


template<typename T>
auto SortedListIsA<T>::insert(const T& item)
{
    int position = 1;
    int listSize = this->getListSize();

    while (position <= listSize && item > this->getItemAt(position))
    {
        ++position;
    }
    this->insertAt(item, position);
}

// from SmartLinkedList: disabled (can modify/break sort order)
template<typename T>
auto SortedListIsA<T>::insertAt(const T& item, const int& position)
{
    std::string message = "> Error: arbitrary insert not allowed because it may break sort order.\n"
                          "> (Try 'insert(item)' or use an unsorted list).";
    throw(CustomException(message));
}

// from SmartLinkedList: disabled (can modify/break sort order)
template<typename T>
auto SortedListIsA<T>::replaceAt(const T& item, const int& position)
{
    std::string message = "> Error: arbitrary replacement not allowed because it may break sort order.\n"
                          "> (Try 'delete(old_item)' with 'insert(new_item)' or use an unsorted list).";
    throw(CustomException(message));
}

#endif