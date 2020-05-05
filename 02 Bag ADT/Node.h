/** @author: Oliver Ocean */

#ifndef NODE_
#define NODE_

template<typename T>
class Node {

private:
    T data;
    Node<T>* next;

public:
    Node();
    explicit Node(const T& newData);
    Node(const T& newData, Node<T>* newNext);

    // item: get and set
    T getData() const;
    void setData(const T& newData);

    // next: get and set
    Node<T>* getNext() const;
    void setNext(Node<T>* newNext);
};

// constructors
template<typename T>
Node<T>::Node() : next(nullptr) {}

template<typename T>
Node<T>::Node(const T& newData): data(newData), next(nullptr) {}

template<typename T>
Node<T>::Node(const T& newData, Node<T>* newNext): data(newData), next(newNext) {}

// item: get and set
template<typename T>
T Node<T>::getData() const {
    return data;
}

template<typename T>
void Node<T>::setData(const T& newData) {
    data = newData;
}

// next: get and set
template<typename T>
Node<T>* Node<T>::getNext() const {
    return next;
}

template<typename T>
void Node<T>::setNext(Node<T>* newNext) {
    next = newNext;
}

#endif
