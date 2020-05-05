/** @author: Oliver Ocean */
/** @brief: Link-based implementation of the ADT binary search tree. */

#ifndef BINARY_SEARCH_TREE_
#define BINARY_SEARCH_TREE_

#include <memory>
#include <vector>
#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "BinaryNodeTree.h"
#include "NotFoundException.h"
#include "PrecondViolatedExcep.h"

template<typename T>
class BinarySearchTree : public BinaryNodeTree<T>
{
protected:
    std::shared_ptr<BinaryNode<T>> placeNode(std::shared_ptr<BinaryNode<T>> subTreePtr, std::shared_ptr<BinaryNode<T>> newNode);
    std::shared_ptr<BinaryNode<T>> removeValue(std::shared_ptr<BinaryNode<T>> subTreePtr, const T& target, bool& success);
    std::shared_ptr<BinaryNode<T>> removeNode(std::shared_ptr<BinaryNode<T>> nodePtr);
    std::shared_ptr<BinaryNode<T>> removeLeftmostNode(std::shared_ptr<BinaryNode<T>> subTreePtr, T& inorderSuccessor);
    std::shared_ptr<BinaryNode<T>> findNode(std::shared_ptr<BinaryNode<T>> treePtr, const T& target) const;
   
public:
    void setRootData(const T& newData);
    bool add(const T& newEntry);
    bool remove(const T& anEntry);
    T getEntry(const T& anEntry) const;
    bool contains(const T& anEntry) const;
};

// <---[ protected methods (recursive / helper) ]---> //

template<typename T>
std::shared_ptr<BinaryNode<T>> BinarySearchTree<T>::placeNode(std::shared_ptr<BinaryNode<T>> subTreePtr, std::shared_ptr<BinaryNode<T>> newNode)
{
    if (subTreePtr == nullptr)
    {
        return newNode;
    }
    else if (subTreePtr->getItem() > newNode->getItem())
    {
        std::shared_ptr<BinaryNode<T>> tempLeftPtr = placeNode(subTreePtr->getLeftChildPtr(), newNode);
        subTreePtr->setLeftChildPtr(tempLeftPtr);
    }
    else
    {
        std::shared_ptr<BinaryNode<T>> tempRightPtr = placeNode(subTreePtr->getRightChildPtr(), newNode);
        subTreePtr->setRightChildPtr(tempRightPtr);
    }
    return subTreePtr;
}

template<typename T>
std::shared_ptr<BinaryNode<T>> BinarySearchTree<T>::findNode(std::shared_ptr<BinaryNode<T>> treePtr, const T& target) const
{
    if (treePtr == nullptr)
    {
        return nullptr;
    }
    else if (treePtr->getItem() == target)
    {
        return treePtr;
    }
    else if (treePtr->getItem() > target)
    {
        return findNode(treePtr->getLeftChildPtr(), target);
    }
    else
    {
        return findNode(treePtr->getRightChildPtr(), target);
    }
}


template<typename T>
std::shared_ptr<BinaryNode<T>> BinarySearchTree<T>::removeValue(std::shared_ptr<BinaryNode<T>> subTreePtr, const T& target, bool& success)
{
    if (subTreePtr == nullptr)
    {
        success = false;
    }
    else if (subTreePtr->getItem() == target)
    {
        subTreePtr = removeNode(subTreePtr);
        // for leaf, nullptr returned
        // for single child, singleChildToPromote returned
        // for two children, nullptr returned
        success = true;
    }
    else if (subTreePtr->getItem() > target)
    {
        std::shared_ptr<BinaryNode<T>> tempLeftNode = removeValue(subTreePtr->getLeftChildPtr(), target, success);
        subTreePtr->setLeftChildPtr(tempLeftNode);
    }
    else
    {
        std::shared_ptr<BinaryNode<T>> tempRightNode = removeValue(subTreePtr->getRightChildPtr(), target, success);
        subTreePtr->setRightChildPtr(tempRightNode);
    }
    return subTreePtr;
}

template<typename T>
std::shared_ptr<BinaryNode<T>> BinarySearchTree<T>::removeNode(std::shared_ptr<BinaryNode<T>> nodeToRemove)
{
    // leaf
    if (nodeToRemove->isLeaf())
    {
        nodeToRemove = nullptr;
        return nodeToRemove;
    }
    // one child
    else if (nodeToRemove->getLeftChildPtr() == nullptr)
    {
        return nodeToRemove->getRightChildPtr();
    }
    else if (nodeToRemove->getRightChildPtr() == nullptr)
    {
        return nodeToRemove->getLeftChildPtr();
    }
    // two children
    else
    {
        T inorderSuccessorValue; // pass by reference to removeLeftmostNode
        auto tempNodePtr = removeLeftmostNode(nodeToRemove->getRightChildPtr(), inorderSuccessorValue);

        nodeToRemove->setRightChildPtr(tempNodePtr); // this is either nullptr or the rhs subtree from the removed leaf
        nodeToRemove->setItem(inorderSuccessorValue); // this copies the correct value into nodeToRemove
        return nodeToRemove; // this is now the correct value
    }
}

template<typename T>
std::shared_ptr<BinaryNode<T>> BinarySearchTree<T>::removeLeftmostNode(std::shared_ptr<BinaryNode<T>> subTreePtr, T& inorderSuccessorValue)
{
    // is this a base case?
    // removes the inorder node using removeNode - should not reach the "two-child" case.
    if (subTreePtr->getLeftChildPtr() == nullptr)
    {
        inorderSuccessorValue = subTreePtr->getItem(); // saves the value; will be copied after completing this function
        return removeNode(subTreePtr); // returns the subTreePtr = nullptr OR subTreePtr = singleChildToPromote if rhs child
    }
    else
    {
        // call this function recursively until reaching the leaf on the left - this is the inorder successor
        std::shared_ptr<BinaryNode<T>> tempPtr = removeLeftmostNode(subTreePtr->getLeftChildPtr(), inorderSuccessorValue);

        // i don't understand this part.
        // this is reached when the stack unwinds?
        subTreePtr->setLeftChildPtr(tempPtr);
        return subTreePtr;
    }
}



// <---[ public methods ]---> //
template<typename T>
bool BinarySearchTree<T>::remove(const T& anEntry)
{
    bool success = false;
    this->rootPtr = removeValue(this->rootPtr, anEntry, success);
    return success;
}


template<typename T>
bool BinarySearchTree<T>::add(const T& newEntry)
{
    auto newNode = std::make_shared<BinaryNode<T>>(newEntry);
    this->rootPtr = placeNode(this->rootPtr, newNode);
    return true;
}

template<typename T>
T BinarySearchTree<T>::getEntry(const T& anEntry) const
{
    auto binaryNodePtr = findNode(this->rootPtr, anEntry);

    if (binaryNodePtr != nullptr)
    {
        return binaryNodePtr->getItem();
    }
    else
    {
        throw NotFoundException("Entry not found in tree!");
    }
}

template<typename T>
bool BinarySearchTree<T>::contains(const T& anEntry) const
{
    auto binaryNodePtr = findNode(this->rootPtr, anEntry);
    if (!binaryNodePtr) { return false; }
    return true;
}

template<typename T>
void BinarySearchTree<T>::setRootData(const T& newData)
{
    throw PrecondViolatedExcep("Not allowed to set Root Data in BST.");
}

#endif
