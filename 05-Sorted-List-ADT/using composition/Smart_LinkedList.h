/** @author: Oliver Ocean */

#ifndef SMART_LINKEDLIST_
#define SMART_LINKEDLIST_

#include <memory>

#include "LinkedList_Interface.h"
#include "Smart_Node.h"
#include "CustomException.h"

template<typename T>
class SmartLinkedList
{
private:
    std::shared_ptr<SmartNode<T>> head;
    int itemCount;

    auto getNodeAt(const int& position) const;
    auto getNodeBefore(const T& item) const;
    auto getNodeOf(const T& item) const;

public:
    SmartLinkedList();
    SmartLinkedList(const SmartLinkedList<T>& aList); // copy constructor
    ~SmartLinkedList();

    bool isListEmpty() const;
    int getListSize() const;
    void clearList();
    int getPositionOf(const T& item) const;
    T getItemAt(const int& position) const;
    void removeItemAt(const int& position);
    void remove(const T& item);
    void insertAt(const T& item, const int& position);
    void replaceAt(const T& item, const int& position);
};

// default constructor
template<typename T>
SmartLinkedList<T>::SmartLinkedList(): head(nullptr), itemCount(0) {}

// copy constructor
template<typename T>
SmartLinkedList<T>::SmartLinkedList(const SmartLinkedList<T>& aList) : itemCount(aList.itemCount)
{
    auto theList = head;
    for (int position = 1; position <= aList.getListSize(); ++position)
    {
        theList->insertAt(aList.getItemAt(position), position);
    }
}

// destructor
template<typename T>
SmartLinkedList<T>::~SmartLinkedList() { clearList(); }

// private method
template<typename T>
auto SmartLinkedList<T>::getNodeAt(const int& position) const
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
auto SmartLinkedList<T>::getNodeBefore(const T& item) const
{
    auto current = head;
    std::shared_ptr<SmartNode<T>> previous;

    while (current != nullptr && item > current->getData())
    {
        previous = current;
        current = current->getNext();
    }
    return previous;
}

// private method
template<typename T>
auto SmartLinkedList<T>::getNodeOf(const T& item) const
{
    auto current = head;

    while (current != nullptr && item > current->getData())
    {
        current = current->getNext();
    }
    return current;
}

template<typename T>
bool SmartLinkedList<T>::isListEmpty() const { return itemCount == 0; }

template<typename T>
int SmartLinkedList<T>::getListSize() const { return itemCount; }

template<typename T>
void SmartLinkedList<T>::clearList()
{
    head.reset();
    itemCount = 0;
}

template<typename T>
int SmartLinkedList<T>::getPositionOf(const T& item) const
{
    if (isListEmpty())
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
T SmartLinkedList<T>::getItemAt(const int& position) const
{
    if (isListEmpty())
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
void SmartLinkedList<T>::removeItemAt(const int& position)
{
    if (isListEmpty())
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
void SmartLinkedList<T>::remove(const T& item)
{
    int position = getPositionOf(item);
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
void SmartLinkedList<T>::insertAt(const T& item, const int& position)
{
    if (position < 1 || position > itemCount + 1) // + 1 to allow adding to end of list
    {
        std::string message = "invalid position parameter.";
        throw(CustomException(message));
    }
    else
    {
        auto newNode = std::make_shared<SmartNode<T>>(item);

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
void SmartLinkedList<T>::replaceAt(const T& item, const int& position)
{
    auto current = getNodeAt(position);
    current->setData(item);
}

#endif