/** @author: Oliver Ocean */

#ifndef NODE_
#define NODE_

template<typename T>
class Node
{
private:
    T data;
    Node<T>* next;

public:
    Node();
    explicit Node(const T& newData);
    Node(const T& newData, Node<T>* newNext);

    T getData() const;
    Node<T>* getNext() const;
    void setData(const T& newData);
    void setNext(Node<T>* newNext);
};

template<typename T>
Node<T>::Node() : next(nullptr) {}

template<typename T>
Node<T>::Node(const T& newData): data(newData), next(nullptr) {}

template<typename T>
Node<T>::Node(const T& newData, Node<T>* newNext): data(newData), next(newNext) {}

template<typename T>
T Node<T>::getData() const { return data; }

template<typename T>
void Node<T>::setData(const T& newData) { data = newData; }

template<typename T>
Node<T>* Node<T>::getNext() const { return next; }

template<typename T>
void Node<T>::setNext(Node<T>* newNext) { next = newNext; }

#endif
