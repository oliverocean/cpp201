/** @author: Oliver Ocean */

#ifndef SORTEDLIST_HAS_A_SMARTLINKEDLIST_
#define SORTEDLIST_HAS_A_SMARTLINKEDLIST_

#include <memory>

#include "SortedList_Interface.h"
#include "Smart_LinkedList.h"
#include "CustomException.h"

template<typename T>
class SortedListHasA : public SortedListInterface<T>
{
private:
    std::unique_ptr<SmartLinkedList<T>> theList;

public:
    SortedListHasA();
    SortedListHasA(const SortedListHasA<T>& aList); // copy constructor

    bool isListEmpty() const override;
    int getListSize() const override;
    void clearList() override;
    int getPositionOf(const T& item) const override;
    T getItemAt(const int& position) const override;
    void removeItemAt(const int& position) override;
    void remove(const T& item) override;
    void insert(const T& item) override;

    ~SortedListHasA();
};

// default constructor
template<typename T>
SortedListHasA<T>::SortedListHasA() : theList(std::make_unique<SmartLinkedList<T>>()) {}

// copy constructor
template<typename T>
SortedListHasA<T>::SortedListHasA(const SortedListHasA<T>& aList) : theList(std::make_unique<SmartLinkedList<T>>())
{
    for (int position = 1; position <= aList.getListSize(); ++position)
    {
        theList->insertAt(aList.getItemAt(position), position);
    }
}

// destructor
template<typename T>
SortedListHasA<T>::~SortedListHasA() = default;

template<typename T>
bool SortedListHasA<T>::isListEmpty() const { return theList->isListEmpty(); }

template<typename T>
int SortedListHasA<T>::getListSize() const { return theList->getListSize(); }

template<typename T>
void SortedListHasA<T>::clearList() { theList->clearList(); }

template<typename T>
int SortedListHasA<T>::getPositionOf(const T& item) const { return theList->getPositionOf(item); }

template<typename T>
T SortedListHasA<T>::getItemAt(const int& position) const { return theList->getItemAt(position); }

template<typename T>
void SortedListHasA<T>::removeItemAt(const int& position) { theList->removeItemAt(position); }

template<typename T>
void SortedListHasA<T>::remove(const T& item) { theList->remove(item); }

template<typename T>
void SortedListHasA<T>::insert(const T& item)
{
    int position = 1;

    if (theList->isListEmpty())
    {
        theList->insertAt(item, position);
    }
    else
    {
        while (position <= getListSize() && item > theList->getItemAt(position))
        {
            ++position;
        }
        theList->insertAt(item, position);
    }
}

#endif