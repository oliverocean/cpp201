/** @author: Oliver Ocean */

#ifndef NODE_
#define NODE_

#include <memory>

template<typename T>
class Node
{
private:
    T data;
    std::shared_ptr<Node<T>> next;

public:
    Node();
    explicit Node(const T& newData);
    Node(const T& newData, std::shared_ptr<Node<T>> newNext);

    T getData() const;
    std::shared_ptr<Node<T>> getNext() const;
    void setData(const T& newData);
    void setNext(std::shared_ptr<Node<T>> newNext);
};

template<typename T>
Node<T>::Node() = default;

template<typename T>
Node<T>::Node(const T& newData): data(newData) {}

template<typename T>
Node<T>::Node(const T& newData, std::shared_ptr<Node<T>> newNext) : data(newData), next(newNext) {}

template<typename T>
T Node<T>::getData() const { return data; }

template<typename T>
void Node<T>::setData(const T& newData) { data = newData; }

template<typename T>
std::shared_ptr<Node<T>> Node<T>::getNext() const { return next; }

template<typename T>
void Node<T>::setNext(std::shared_ptr<Node<T>> newNext) { next = newNext; }

#endif
