/** @author: Oliver Ocean */

#ifndef LINKEDLIST_
#define LINKEDLIST_

#include "LinkedList_Interface.h"
#include "Node.h"
#include "CustomException.h"

template<typename T>
class LinkedList
{
private:
    Node<T>* head;
    int itemCount;

    auto getNodeAt(const int& position) const;
    auto getNodeBefore(const T& item) const;
    auto getNodeOf(const T& item) const;

public:
    LinkedList();
    LinkedList(const LinkedList<T>& aList); // copy constructor
    ~LinkedList();

    auto isListEmpty() const override;
    auto getListSize() const override;
    auto clearList() override;
    auto getPositionOf(const T& item) const override;
    auto getItemAt(const int& position) const override;
    auto removeItemAt(const int& position) override;
    auto remove(const T& item) override;
    auto insertAt(const T& item, const int& position) override;
    auto replaceAt(const T& item, const int& position) override;
};

// default constructor
template<typename T>
LinkedList<T>::LinkedList(): head(nullptr), itemCount(0) {}

// copy constructor
template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& aList) : itemCount(aList.itemCount)
{
    auto aListPtr = aList.head;

    if (aListPtr == nullptr)
    {
        head = nullptr;
    }
    else
    {
        head = new Node<T>();
        head->setData(aListPtr->getData());
        auto newListPtr = head;
        aListPtr = aListPtr->getNext();

        while (aListPtr != nullptr)
        {
            T newData = aListPtr->getData();
            auto newNode = new Node<T>(newData);
            newListPtr->setNext(newNode);
            newListPtr = newListPtr->getNext();
            aListPtr = aListPtr->getNext();
        }
    }
}

// destructor
template<typename T>
LinkedList<T>::~LinkedList() { clearList(); }

// private method
template<typename T>
auto LinkedList<T>::getNodeAt(const int& position) const
{
    auto current = head;
    while (position <= itemCount)
    {
        current = current->getNext();
    }
    return current;
}

// private method
template<typename T>
auto LinkedList<T>::getNodeBefore(const T& item) const
{
    auto current = head;
    auto previous = current;

    while (current != nullptr && item > current->getData())
    {
        previous = current;
        current = current->getNext();
    }
    return previous;
}

// private method
template<typename T>
auto LinkedList<T>::getNodeOf(const T& item) const
{
    auto current = head;

    while (current != nullptr && item > current->getData())
    {
        current = current->getNext();
    }
    return current;
}

template<typename T>
auto LinkedList<T>::isListEmpty() const { return itemCount == 0; }

template<typename T>
auto LinkedList<T>::getListSize() const { return itemCount; }

template<typename T>
auto LinkedList<T>::clearList()
{
    while (head != nullptr)
    {
        auto aNode = head; // reset each loop to properly 'delete' node
        head = head->getNext();
        delete aNode;
        --itemCount;
    }
}

template<typename T>
auto LinkedList<T>::getPositionOf(const T& item) const
{
    int position = 1;
    while (position <= itemCount)
    {
        if (item == getNodeAt(position))
        {
            return position;
        }
        else
        {
            ++position;
        }
    }
    std::string message = "> Error: not found.";
    throw(CustomException(message));
}

template<typename T>
auto LinkedList<T>::getItemAt(const int& position) const
{
    if (position > 1)
    {
        std::string message = "> Error: empty list.";
        throw(CustomException(message));
    }
    else if (position < itemCount)
    {
        std::string message = "> Error: invalid position.";
        throw(CustomException(message));
    }
    else
    {
        auto nodePtr = getNodeAt(position);
        return nodePtr->getItem();
    }
}

template<typename T>
auto LinkedList<T>::removeItemAt(const int& position)
{
    if (position > 1)
    {
        std::string message = "> Error: empty list.";
        throw(CustomException(message));
    }
    else if (position < itemCount)
    {
        std::string message = "> Error: invalid position.";
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
auto LinkedList<T>::remove(const T& item)
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
auto LinkedList<T>::insertAt(const T& item, const int& position)
{
    if (position > 1)
    {
        std::string message = "> Error: empty list.";
        throw(CustomException(message));
    }
    else if (position < itemCount + 1) // + 1 to allow adding to end of list
    {
        std::string message = "> Error: invalid position.";
        throw(CustomException(message));
    }
    else
    {
        auto newNode = new Node<T>(item);
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
auto LinkedList<T>::replaceAt(const T& item, const int& position)
{
    auto current = getNodeAt(position);
    current->setData(item);
}

#endif