// @file: Linked_Stack.h
// @author: Oliver Ocean

#ifndef LINKED_STACK_
#define LINKED_STACK_

#include "Stack_Interface.h"
#include "Node.h"

template<typename T>
class LinkedStack : public StackInterface<T> {

private:
    Node<T>* top;

public:
    LinkedStack();
    explicit LinkedStack(const T& item);
    LinkedStack(const LinkedStack<T>& aStack);
    ~LinkedStack();

    T peek() const;
    bool push(const T& item);
    bool pop();
    bool isEmpty() const;
};

// constructors
template<typename T>
LinkedStack<T>::LinkedStack() : top(nullptr) {
    // default constructor
}

template<typename T>
LinkedStack<T>::LinkedStack(const T& item) : top(nullptr) {
    push(item);
}

template<typename T>
LinkedStack<T>::LinkedStack(const LinkedStack<T>& aStack) : top(nullptr) {

    auto origin = aStack.top;

    if (origin == nullptr) { // origin is empty; don't bother allocating storage
        top = nullptr;
    } else {
        top = new Node<T>(); // origin has at least one node; make a new stack
        top->setData(origin->getData()); // initialize the first node

        auto newStack = top; // pointer to traverse the new stack

        while (origin->getNext() != nullptr) {
            origin = origin->getNext();

            T newData = origin->getData();
            auto newNode = new Node<T>(newData);

            newStack->setNext(newNode);
            newStack = newStack->getNext();
        }
    }
}

template<typename T>
LinkedStack<T>::~LinkedStack() {
    while (!isEmpty()) {
        pop();
    }
}

template<typename T>
T LinkedStack<T>::peek() const {
    if (!isEmpty()) {
        return top->getData();
    }
    return 0; // optimally throw an error
}

template<typename T>
bool LinkedStack<T>::push(const T& item) {
    auto newNode = new Node<T>(item, top);
    top = newNode;
    return true;
}

template<typename T>
bool LinkedStack<T>::pop() {
    if (!isEmpty()) {
        auto popItem = top;
        top = top->getNext();
        popItem->setNext(nullptr);
        delete popItem;
        return true;
    }
    return false; // if/when stack is empty
}

template<typename T>
bool LinkedStack<T>::isEmpty() const {
    return top == nullptr;
}

#endif