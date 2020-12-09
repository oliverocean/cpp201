//* author: Oliver Ocean */

#ifndef BINARYNODE_TREE_
#define BINARYNODE_TREE_

#include <memory>

#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "CustomException.h"

template<typename T>
class BinaryNodeTree : public BinaryTreeInterface<T>
{
protected:
    std::shared_ptr<BinaryNode<T>> root;

    // <---[ recursive helper functions ]---> //
    auto copyTree(std::shared_ptr<BinaryNode<T>> aRoot) const;
    void destroyTree(std::shared_ptr<BinaryNode<T>> aRoot);
    int getTreeHeight(std::shared_ptr<BinaryNode<T>> aRoot) const;
    int getTreeSize(std::shared_ptr<BinaryNode<T>> aRoot) const;

    auto findNode(std::shared_ptr<BinaryNode<T>> aRoot, const T& aDatum, bool& found) const;
    auto addNode(std::shared_ptr<BinaryNode<T>> aRoot, std::shared_ptr<BinaryNode<T>> newNode);
    auto removeNode(std::shared_ptr<BinaryNode<T>> aRoot, const T& oldNode, bool& success);
    auto replaceNodeWithChild(std::shared_ptr<BinaryNode<T>> aNode);

    void preorder(void visit(T&), std::shared_ptr<BinaryNode<T>> aRoot) const;
    void inorder(void visit(T&), std::shared_ptr<BinaryNode<T>> aRoot) const;
    void postorder(void visit(T&), std::shared_ptr<BinaryNode<T>> aRoot) const;
   
public:
    BinaryNodeTree();
    explicit BinaryNodeTree(const T& anItem);
    BinaryNodeTree(const T& anItem,
                std::shared_ptr<BinaryNodeTree<T>> nextLeft,
                std::shared_ptr<BinaryNodeTree<T>> nextRight);
    BinaryNodeTree(const BinaryNodeTree<T>& aTree); // copy constructor
    ~BinaryNodeTree();

    bool isTreeEmpty() const;
    int getHeightOfTree() const;
    int getSizeOfTree() const;
    void clearTree();

    T getItemAtRoot() const;
    T getItem(const T& anItem) const;
    bool containsItem(const T& anItem) const;

    void addItemAtRoot(const T& anItem);
    bool addItem(const T& anItem);
    bool removeItem(const T& anItem);

    void preorderTraversal(void visit(T&)) const;
    void inorderTraversal(void visit(T&)) const;
    void postorderTraversal(void visit(T&)) const;
};

// <---[ protected methods (recursive / helper) ]---> //
template<typename T>
auto BinaryNodeTree<T>::copyTree(std::shared_ptr<BinaryNode<T>> aRoot) const
{
    std::shared_ptr<BinaryNode<T>> newTree;
    if (aRoot != nullptr)
    {
        newTree = std::make_shared<BinaryNode<T>>(aRoot->getData(), nullptr, nullptr);

        newTree->setLeft(copyTree(aRoot->getLeft()));
        newTree->setRight(copyTree(aRoot->getRight()));
    }
    return newTree;
}

template<typename T>
void BinaryNodeTree<T>::destroyTree(std::shared_ptr<BinaryNode<T>> aRoot)
{
    if (aRoot != nullptr)
    {
        destroyTree(aRoot->getLeft());
        destroyTree(aRoot->getRight());
        aRoot.reset();
    }
}

template<typename T>
int BinaryNodeTree<T>::getTreeHeight(std::shared_ptr<BinaryNode<T>> aRoot) const
{
    if (aRoot == nullptr)
    {
        return 0;
    }
    else
    {
        return 1 + std::max(getTreeHeight(aRoot->getLeft()), getTreeHeight(aRoot->getRight()));
    }
}

template<typename T>
int BinaryNodeTree<T>::getTreeSize(std::shared_ptr<BinaryNode<T>> aRoot) const
{
    if (aRoot == nullptr)
    {
        return 0;
    }
    else
    {
        return 1 + getTreeSize(aRoot->getLeft()) + getTreeSize(aRoot->getRight());
    }
}

template<typename T>
auto BinaryNodeTree<T>::findNode(std::shared_ptr<BinaryNode<T>> aRoot, const T& aDatum, bool& found) const
{
    if (aRoot == nullptr) { return aRoot; }

    if (aRoot->getData() == aDatum)
    {
        found = true;
        return aRoot;
    }
    else
    {
        auto aNode = findNode(aRoot->getLeft(), aDatum, found);
        if (!found)
        {
            aNode = findNode(aRoot->getRight(), aDatum, found);
        }
        return aNode;
    }
}

template<typename T>
auto BinaryNodeTree<T>::addNode(std::shared_ptr<BinaryNode<T>> aRoot, std::shared_ptr<BinaryNode<T>> newNode)
{
    if (aRoot == nullptr)
    {
        return aRoot;
    }
    else
    {
        auto leftTree = aRoot->getLeft();
        auto rightTree = aRoot->getRight();
        
        if (getTreeSize(leftTree) > getTreeSize(rightTree))
        {
            rightTree = addNode(rightTree, newNode);
            aRoot->setRight(rightTree);
        }
        else
        {
            leftTree = addNode(leftTree, newNode);
            aRoot->setLeft(leftTree);
        }
        return aRoot;
    }
}

template<typename T>
auto BinaryNodeTree<T>::removeNode(std::shared_ptr<BinaryNode<T>> aRoot, const T& oldNode, bool& success)
{
    if (aRoot == nullptr) { return aRoot; }

    if (aRoot->getData() == oldNode)
    {
        aRoot = replaceWithChild(aRoot);
        success = true;
        return aRoot;
    }
    else
    {
        auto aNode = removeNode(aRoot->getLeft(), oldNode, success);
        aRoot->setLeft(aNode);

        if (!success)
        {
            aNode = removeNode(aRoot->getRight(), oldNode, success);
            aRoot->setRight(aNode);
        }
        return aRoot;
    }
}

template<typename T>
auto BinaryNodeTree<T>::replaceNodeWithChild(std::shared_ptr<BinaryNode<T>> aNode)
{
    auto leftSubTree = aNode->getLeft();
    auto rightSubTree = aNode->getRight();

    //int leftTreeHeight = getTreeHeight(leftTree);
    //int rightTreeHeight = getTreeHeight(rightTree);

    if (getTreeHeight(leftSubTree) > getTreeHeight(rightSubTree))
    {
        aNode->setData(leftSubTree->getData());

        leftSubTree = replaceNodeWithChild(leftSubTree);
        aNode->setLeft(leftSubTree);

        return aNode;
    }
    else
    {
        if (rightSubTree != nullptr)
        {
            aNode->setData(rightSubTree->getData());

            rightSubTree = replaceNodeWithChild(rightSubTree);
            aNode->setRight(rightSubTree);

            return aNode;
        }
        else
        {
            return nullptr; // leaf node reached, end recursion
        }
    }
}

template<typename T>
void BinaryNodeTree<T>::preorder(void visit(T&), std::shared_ptr<BinaryNode<T>> aRoot) const
{
    if (aRoot != nullptr)
    {
        T aNode = aRoot->getData();
        visit(aNode);

        preorder(visit, aRoot->getLeft());
        preorder(visit, aRoot->getRight());
    }
}

template<typename T>
void BinaryNodeTree<T>::inorder(void visit(T&), std::shared_ptr<BinaryNode<T>> aRoot) const
{
    if (aRoot != nullptr)
    {
        inorder(visit, aRoot->getLeft());

        T aNode = aRoot->getData();
        visit(aNode);

        inorder(visit, aRoot->getRight());
    }
}

template<typename T>
void BinaryNodeTree<T>::postorder(void visit(T&), std::shared_ptr<BinaryNode<T>> aRoot) const
{
    if (aRoot != nullptr)
    {
        postorder(visit, aRoot->getLeft());
        postorder(visit, aRoot->getRight());

        T aNode = aRoot->getData();
        visit(aNode);
    }
}

// <---[ constructors ]---> //
template<typename T>
BinaryNodeTree<T>::BinaryNodeTree() = default;

template<typename T>
BinaryNodeTree<T>::BinaryNodeTree(const T& anItem) : root(std::make_shared<BinaryNode<T>>(anItem, nullptr, nullptr)) {}

template<typename T>
BinaryNodeTree<T>::BinaryNodeTree(const T& anItem,
                                const std::shared_ptr<BinaryNodeTree<T>> nextLeft,
                                const std::shared_ptr<BinaryNodeTree<T>> nextRight) :
                                        root(std::make_shared<BinaryNode<T>>(anItem,
                                                copyTree(nextLeft->root),
                                                copyTree(nextRight->root))) {}

template<typename T>
BinaryNodeTree<T>::BinaryNodeTree(const BinaryNodeTree<T>& aTree) { root = copyTree(aTree.root); }

template<typename T>
BinaryNodeTree<T>::~BinaryNodeTree() { destroyTree(root); }

// <---[ public methods ]---> //
template<typename T>
bool BinaryNodeTree<T>::isTreeEmpty() const { return root == nullptr; }

template<typename T>
int BinaryNodeTree<T>::getHeightOfTree() const { return getTreeHeight(root); }

template<typename T>
int BinaryNodeTree<T>::getSizeOfTree() const { return getTreeSize(root); }

template<typename T>
void BinaryNodeTree<T>::clearTree() { destroyTree(root); }

template<typename T>
T BinaryNodeTree<T>::getItemAtRoot() const
{
    if (isTreeEmpty())
    {
        throw CustomException("tree is empty.");
    }
    else
    {
        return root->getData();
    }
}

template<typename T>
T BinaryNodeTree<T>::getItem(const T& anItem) const
{
    bool found = false;
    auto theNode = findNode(root, anItem, found);

    if (!found)
    {
        throw CustomException("item not found.");
    }
    else
    {
        return theNode->getData();
    }
}

template<typename T>
bool BinaryNodeTree<T>::containsItem(const T& anItem) const
{
    bool found = false;
    findNode(root, anItem, found);
    return found;
}

template<typename T>
void BinaryNodeTree<T>::addItemAtRoot(const T& anItem)
{
    if (isTreeEmpty())
    {
        root = std::make_shared<BinaryNode<T>>(anItem, nullptr, nullptr);
    }
    else
    {
        root->setData(anItem);
    }
}

template<typename T>
bool BinaryNodeTree<T>::addItem(const T& anItem)
{
    auto newNode = std::make_shared<BinaryNode<T>>(anItem);
    root = addNode(root, newNode);
    return true;
}

template<typename T>
bool BinaryNodeTree<T>::removeItem(const T& anItem)
{
    bool success = false;
    root = removeNode(root, anItem, success);
    return success;
}

template<typename T>
void BinaryNodeTree<T>::preorderTraversal(void visit(T&)) const { preorder(visit, root); }

template<typename T>
void BinaryNodeTree<T>::inorderTraversal(void visit(T&)) const { inorder(visit, root); }

template<typename T>
void BinaryNodeTree<T>::postorderTraversal(void visit(T&)) const { postorder(visit, root); }

//template<typename T>
//BinaryNodeTree<T>& BinaryNodeTree<T>::operator=(const BinaryNodeTree<T>& rhs)
//{
//    if (!isTreeEmpty())
//        clearTree();
//    this = copyTreeHelper(&rhs);
//    return *this;
//}

#endif
