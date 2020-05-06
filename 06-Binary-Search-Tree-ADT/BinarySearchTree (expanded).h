/** @author: Oliver Ocean */
// NOTE: for a BST: adding, removing, and retrieving are by value
// NOT position (as in Binary Node Tree) because the structure is ordered

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
   auto placeNode(std::shared_ptr<BinaryNode<T>> subTreePtr, std::shared_ptr<BinaryNode<T>> newNode);
   auto removeValue(std::shared_ptr<BinaryNode<T>> subTreePtr, const T& target, bool& success);
   auto removeNode(std::shared_ptr<BinaryNode<T>> nodePtr);
   auto removeLeftmostNode(std::shared_ptr<BinaryNode<T>> subTreePtr, T& inorderSuccessor);
   auto findNode(std::shared_ptr<BinaryNode<T>> treePtr, const T& target) const;
   
public:
   void setRootData(const T& newData);
   bool add(const T& newEntry);
   bool remove(const T& anEntry);
   T getEntry(const T& anEntry) const;
   bool contains(const T& anEntry) const;
};

// <---[ protected methods ]---> //

// Recursively finds where the given node should be placed and inserts it in a leaf at that point.
template<typename T>
auto BinarySearchTree<T>::placeNode(std::shared_ptr<BinaryNode<T>> subTreePtr, std::shared_ptr<BinaryNode<T>> newNode)
{
    // search for the value first
    // that is the spot (leaf) to put the new item.
}

// Removes the given target value from the tree while maintaining a binary search tree.
template<typename T>
auto BinarySearchTree<T>::removeValue(std::shared_ptr<BinaryNode<T>> subTreePtr, const T& target, bool& success)
{
    // todo
}

// Removes a given node from a tree while maintaining a binary search tree.
template<typename T>
auto BinarySearchTree<T>::removeNode(std::shared_ptr<BinaryNode<T>> nodePtr)
{
    // todo
}

// Removes the leftmost node in the left subtree of the node pointed to by nodePtr.
// Sets inorderSuccessor to the value in this node. Returns a pointer to the revised subtree.
template<typename T>
auto BinarySearchTree<T>::removeLeftmostNode(std::shared_ptr<BinaryNode<T>> subTreePtr, T& inorderSuccessor)
{
    // todo
}

// Returns a pointer to the node containing the given value, or nullptr if not found.
template<typename T>
auto BinarySearchTree<T>::findNode(std::shared_ptr<BinaryNode<T>> treePtr, const T& target) const
{
    if (this->isTreeEmpty())
    {
        return treePtr;
    }
    else if (target == treePtr)
    {
        return treePtr;
    }
    else if (target < treePtr)
    {
        findNode(treePtr->getLeft(), target);
    }
    else
    {
        findNode(treePtr->getRight(), target);
    }
}

// <---[ public methods ]---> //
template<typename T>
void BinarySearchTree<T>::setRootData(const T& newData)
{
    // todo
}

template<typename T>
bool BinarySearchTree<T>::add(const T& newEntry)
{
    return true; // todo
}

template<typename T>
bool BinarySearchTree<T>::remove(const T& anEntry)
{
    return true; // todo
}

template<typename T>
T BinarySearchTree<T>::getEntry(const T& anEntry) const
{
    return anEntry; // todo
}

template<typename T>
bool BinarySearchTree<T>::contains(const T& anEntry) const
{
    return true; // todo
}

#endif
