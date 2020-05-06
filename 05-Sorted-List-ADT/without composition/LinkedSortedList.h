/** @author: Oliver Ocean */

#ifndef LINKEDSORTEDLIST_
#define LINKEDSORTEDLIST_

#include <memory>

#include "SortedListInterface.h"
#include "Node.h"
#include "CustomException.h"

template<typename T>
class LinkedSortedList
{
private:
    std::shared_ptr<Node<T>> head;
    int itemCount;

    auto getNodeAt(const int& position) const;
    auto getNodeBefore(const T& item) const;
    auto getNodeOf(const T& item) const;
    void insert(const T& item, const int& position);

public:
    LinkedSortedList();
    LinkedSortedList(const LinkedSortedList<T>& aList); // copy constructor
    ~LinkedSortedList();

    bool isEmpty() const;
    int getLength() const;
    void clear();
    int getPosition(const T& item) const;
    T getEntry(const int& position) const;
    void remove(const int& position);
    void removeSorted(const T& item);
    void insertSorted(const T& item);
};

// default constructor
template<typename T>
LinkedSortedList<T>::LinkedSortedList() : head(nullptr), itemCount(0) {}

// copy constructor
template<typename T>
LinkedSortedList<T>::LinkedSortedList(const LinkedSortedList<T>& aList) : itemCount(aList.itemCount)
{
    auto originListCurrent = aList.head;

    if (originListCurrent == nullptr)
    {
        head = nullptr; // if originList is empty, make newList empty also
    }
    else
    {
        head = std::make_shared<Node<T>>(originListCurrent->getData()); // setup first/head node
        auto newListTail = head; // traverser

        originListCurrent = originListCurrent->getNext(); // traverse, prepare to copy data to a new node (or exit)

        while (originListCurrent != nullptr)
        {
            // initialize new node with matching data and add new node to newList
            auto newNode = std::make_shared<Node<T>>(originListCurrent->getData());
            newListTail->setNext(newNode); // adds new node to newList

            // traverse both lists
            newListTail = newListTail->getNext();
            originListCurrent = originListCurrent->getNext(); // always one node ahead of newListTail to copy data into newNode(s)
        }
    }
}

// destructor
template<typename T>
LinkedSortedList<T>::~LinkedSortedList() { clear(); }

// private method
template<typename T>
auto LinkedSortedList<T>::getNodeAt(const int& position) const
{
    auto current = head;
    for (int p = 1; p < position; ++p)
    {
        current = current->getNext();
    }
    return current;
}

// private method
template<typename T>
auto LinkedSortedList<T>::getNodeBefore(const T& item) const
{
    auto current = head;
    std::shared_ptr<Node<T>> previous;

    while (current != nullptr && item > current->getData())
    {
        previous = current;
        current = current->getNext();
    }
    return previous;
}

// private method
template<typename T>
auto LinkedSortedList<T>::getNodeOf(const T& item) const
{
    auto current = head;

    while (current != nullptr && item > current->getData())
    {
        current = current->getNext();
    }
    return current;
}

// private method
template<typename T>
void LinkedSortedList<T>::insert(const T& item, const int& position)
{
    if (position < 1 || position > itemCount + 1) // + 1 to allow adding to end of list
    {
        std::string message = "invalid position parameter.";
        throw(CustomException(message));
    }
    else
    {
        auto newNode = std::make_shared<Node<T>>(item);

        if (position == 1)
        {
            newNode->setNext(head);
            head = newNode;

        }
        else
        {
            auto previous = getNodeAt(position - 1);
            newNode->setNext(previous->getNext());
            previous->setNext(newNode);
        }
        ++itemCount;
    }
}

template<typename T>
bool LinkedSortedList<T>::isEmpty() const { return itemCount == 0; }

template<typename T>
int LinkedSortedList<T>::getLength() const { return itemCount; }

template<typename T>
void LinkedSortedList<T>::clear()
{
    head.reset();
    itemCount = 0;
}

template<typename T>
int LinkedSortedList<T>::getPosition(const T& item) const
{
    if (isEmpty())
    {
        std::string message = "list is empty.";
        throw(CustomException(message));
    }

    int position = 1;
    auto current = head;
    while (current != nullptr && position <= itemCount)
    {
        if (item == current->getData())
        {
            return position;
        }
        else
        {
            ++ position;
            current = current->getNext();
        }
    }
    std::string message = "item not found.";
    throw(CustomException(message));
}

template<typename T>
T LinkedSortedList<T>::getEntry(const int& position) const
{
    if (isEmpty())
    {
        std::string message = "list is empty.";
        throw(CustomException(message));
    }
    else if (position < 1 || position > itemCount)
    {
        std::string message = "invalid position parameter.";
        throw(CustomException(message));
    }
    else
    {
        auto nodePtr = getNodeAt(position);
        return nodePtr->getData();
    }
}

template<typename T>
void LinkedSortedList<T>::remove(const int& position)
{
    if (isEmpty())
    {
        std::string message = "list is empty.";
        throw(CustomException(message));
    }
    else if (position < 1 || position > itemCount)
    {
        std::string message = "invalid position parameter.";
        throw(CustomException(message));
    }
    else
    {
        if (position == 1)
        {
            head = head->getNext();
        }
        else
        {
            auto previous = getNodeAt(position - 1);
            auto current = previous->getNext();
            previous->setNext(current->getNext());
        }
        --itemCount;
    }
}

template<typename T>
void LinkedSortedList<T>::removeSorted(const T& item)
{
    int position = getPosition(item);
    if (position == 1)
    {
        head = head->getNext();
    }
    else
    {
        auto previous = getNodeAt(position - 1);
        auto current = previous->getNext();
        previous->setNext(current->getNext());
    }
    --itemCount;
}

template<typename T>
void LinkedSortedList<T>::insertSorted(const T& item)
{
    int position = 1;

    if (this->isEmpty())
    {
        this->insert(item, position);
    }
    else
    {
        while (position <= getLength() && item > this->getEntry(position))
        {
            ++position;
        }
        this->insert(item, position);
    }
}

#endif