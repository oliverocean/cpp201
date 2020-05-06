/** @author: Oliver Ocean */

#ifndef BINARY_NODE_
#define BINARY_NODE_

#include <memory>

template<typename T>
class BinaryNode
{
private:
    T data;
    std::shared_ptr<BinaryNode<T>> left;
    std::shared_ptr<BinaryNode<T>> right;

public:
    // <---[ constructors ]---> //
    BinaryNode();
    explicit BinaryNode(const T& newData);
    BinaryNode(const T& newData,
            std::shared_ptr<BinaryNode<T>> nextLeft,
            std::shared_ptr<BinaryNode<T>> nextRight);

    // <---[ getters ]---> //
    T getData() const;
    std::shared_ptr<BinaryNode<T>> getLeft() const;
    std::shared_ptr<BinaryNode<T>> getRight() const;

    // <---[ setters ]---> //
    void setData(const T& newData);
    void setLeft(std::shared_ptr<BinaryNode<T>> nextLeft);
    void setRight(std::shared_ptr<BinaryNode<T>> nextRight);

    // <---[ helpers ]---> //
    bool isLeaf() const;
};

// <---[ constructors ]---> //
template<typename T>
BinaryNode<T>::BinaryNode() : data(nullptr), left(nullptr), right(nullptr) {}

template<typename T>
BinaryNode<T>::BinaryNode(const T& newData) : data(newData), left(nullptr), right (nullptr) {}

template<typename T>
BinaryNode<T>::BinaryNode(const T& newData,
        std::shared_ptr<BinaryNode<T>> nextLeft,
        std::shared_ptr<BinaryNode<T>> nextRight) : data(newData), left(nextLeft), right(nextRight) {}

// <---[ getters ]---> //
template<typename T>
T BinaryNode<T>::getData() const { return data; }

template<typename T>
std::shared_ptr<BinaryNode<T>> BinaryNode<T>::getLeft() const { return left; }

template<typename T>
std::shared_ptr<BinaryNode<T>> BinaryNode<T>::getRight() const { return right; }

// <---[ setters ]---> //
template<typename T>
void BinaryNode<T>::setData(const T& newData) { data = newData; }

template<typename T>
void BinaryNode<T>::setLeft(std::shared_ptr<BinaryNode<T>> nextLeft) { left = nextLeft; }

template<typename T>
void BinaryNode<T>::setRight(std::shared_ptr<BinaryNode<T>> nextRight) { right= nextRight; }

// <---[ helpers ]---> //
template<typename T>
bool BinaryNode<T>::isLeaf() const { return left == nullptr && right == nullptr; }

#endif
