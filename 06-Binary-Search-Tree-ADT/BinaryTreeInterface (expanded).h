/** @author: Oliver Ocean */

#ifndef BINARYTREE_INTERFACE_
#define BINARYTREE_INTERFACE_

template<typename T>
class BinaryTreeInterface
{
public:
    virtual bool isTreeEmpty() const = 0;
    virtual int getHeightOfTree() const = 0;
    virtual int getSizeOfTree() const = 0;
    virtual void clearTree() = 0;

    virtual T getItemAtRoot() const = 0;
    virtual T getItem(const T& anItem) const = 0;
    virtual bool containsItem(const T& anItem) const = 0;

    virtual void addItemAtRoot(const T& anItem) = 0;
    virtual bool addItem(const T& anItem) = 0;
    virtual bool removeItem(const T& anItem) = 0;

    virtual void preorderTraversal(void visit(T&)) const = 0;
    virtual void inorderTraversal(void visit(T&)) const = 0;
    virtual void postorderTraversal(void visit(T&)) const = 0;

    virtual ~BinaryTreeInterface() {};
};

#endif
