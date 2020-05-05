/** @author: Oliver Ocean */

#ifndef NODE_BAG_
#define NODE_BAG_

#include "BagInterface.h"
#include "Node.h"

// FOR DEBUG ONLY
#include <iostream>

template<typename T>
class NodeBag {

private:
    Node<T>* head;
    int nodeCount;

    auto findNode(const T& aDatum) const;

public:
    // constructors
    NodeBag();
    NodeBag(const NodeBag<T>& oldNodeBag);

    // implementations of BagInterface.h
    auto getSize() const;
    auto isEmpty() const;
    auto addToFront(const std::string& aString);
    auto append(const NodeBag<T>& newNodeBag);
    //bool remove(const T& anEntry);
    auto clear();
    bool contains(const NodeBag<T>& aNodeBag) const;
    ~NodeBag();

    // new functions
    auto getIndex(const T& aDatum) const;
    auto getDataAsString();

};

// private
template<typename T>
auto NodeBag<T>::findNode(const T& aDatum) const {

    auto currentNode = head;
    int index = 0;

    while (currentNode != nullptr) {
        if (aDatum == currentNode->getData()) {
            return index;
        } else {
            currentNode = currentNode->getNext();
        }
        ++index;
    }
    index = -1;
    return index;
}

// constructors
template<typename T>
NodeBag<T>::NodeBag(): head(nullptr), nodeCount(0) {}

template<typename T>
NodeBag<T>::NodeBag(const NodeBag<T>& oldNodeBag) {

    nodeCount = 0;
    auto oldNodeBagPtr = oldNodeBag.head;

    if (oldNodeBagPtr == nullptr) {
        head = nullptr;
    } else {
        head = new Node<T>();
        head->setData(oldNodeBagPtr->getData());

        auto newNodeBagPtr = head;
        oldNodeBagPtr = oldNodeBagPtr->getNext();

        while (oldNodeBagPtr != nullptr) {
            T newData = oldNodeBagPtr->getData();
            auto newNode = new Node<T>(newData);
            newNodeBagPtr->setNext(newNode);
            ++nodeCount;

            newNodeBagPtr = newNodeBagPtr->getNext();
            oldNodeBagPtr = oldNodeBagPtr->getNext();
        }
        // newNodeBagPtr->setNext(nullptr); // extraneous because Node.h sets this
    }
}

// destructor
template<typename T>
NodeBag<T>::~NodeBag() {
    clear();
}

// public
template<typename T>
auto NodeBag<T>::getSize() const {
    return nodeCount;
}

template<typename T>
auto NodeBag<T>::isEmpty() const {
    return nodeCount == 0;
}

template<typename T>
auto NodeBag<T>::addToFront(const std::string& aString) {

    for (int c = (static_cast<int>(aString.length() - 1)); c >= 0; --c) {
        auto traverser = new Node<T>();
        traverser->setData(aString[c]);
        traverser->setNext(head);
        head = traverser;
        ++nodeCount;
    }
    return true;
}


template<typename T>
auto NodeBag<T>::append(const NodeBag<T>& newNodeBag) { // oldNodeBag.append(newNodeBag)

    // if new string is empty, do nothing.
    if (newNodeBag.head == nullptr) {
        std::cout << ">> Error: cannot add an empty string.\n";
        return false;
    }

    auto oldNodeBagPtr = head;
    auto newNodeBagPtr = newNodeBag.head;

    // move the pointer to the last node of the existing string
    while (oldNodeBagPtr->getNext() != nullptr) {
        oldNodeBagPtr = oldNodeBagPtr->getNext();
    }

    // move through new string, create nodes and copy data from new string, append new nodes to old string
    while (newNodeBagPtr != nullptr) {
        auto nodeToAppend = new Node<T>(newNodeBagPtr->getData());
        oldNodeBagPtr->setNext(nodeToAppend);
        ++nodeCount;
        newNodeBagPtr = newNodeBagPtr->getNext();
        oldNodeBagPtr = oldNodeBagPtr->getNext();
    }
    return true;
}


template<typename T>
auto NodeBag<T>::clear() {

    while (head != nullptr) {
        auto traverser = head; // reset each loop because of delete
        head = head->getNext();
        delete traverser;
        --nodeCount;
    }
}

template<typename T>
auto NodeBag<T>::getDataAsString() {

    std::string dataAsString;
    auto traverser = head;

    while(traverser != nullptr) {
        dataAsString += traverser->getData();
        traverser = traverser->getNext();
    }
    return dataAsString;
}

template<typename T>
auto NodeBag<T>::getIndex(const T& aDatum) const {
    return findNode(aDatum);
}

template<typename T>
bool NodeBag<T>::contains(const NodeBag<T>& aNodeBag) const {

    auto oldBagPtr = head;
    auto newBagPtr = aNodeBag.head;

    // helper lambda function, used to compare nodes
    auto nodeCompare = [](const Node<T>* lhs, const Node<T>* rhs) { // automatically makes copies of pointers
        while (lhs != nullptr && rhs != nullptr) { // evaluate both strings entirely; uneven strings caught below
            if (rhs->getData() == lhs->getData()) { // found a match? advance both pointers
                lhs = lhs->getNext();
                rhs = rhs->getNext();
            } else {
                return false; // found a mismatch? exit the lambda
            }
        }
        return (rhs == nullptr); // if true, match was successful
    };

    while (oldBagPtr != nullptr) {
        if (nodeCompare(oldBagPtr, newBagPtr)) {
            return true;
        }
        oldBagPtr = oldBagPtr->getNext();
    }
    return false;
}


#endif



