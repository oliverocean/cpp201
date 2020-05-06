// @file: Array_Stack.h
// @author: Oliver Ocean

#ifndef ARRAY_STACK_
#define ARRAY_STACK_

#include <array>
#include "Stack_Interface.h"

const int MAX_SIZE_ARRAYSTACK = 20;

template<typename T>
class ArrayStack : public StackInterface<T> {

private:
    T items[MAX_SIZE_ARRAYSTACK];
    int top; // stacks are LIFO, so this is the index of last item in the array

public:
    ArrayStack();
    explicit ArrayStack(const T& item);
    ArrayStack(const ArrayStack<T>& aStack);
    ~ArrayStack();

    T peek() const;
    bool push(const T& item);
    bool pop();
    bool isEmpty() const;
};

template<typename T>
ArrayStack<T>::ArrayStack() : top{-1} {
    // default constructor
    // using -1 as there is nothing in the stack currently
}

template<typename T>
ArrayStack<T>::ArrayStack(const T& item) : top{-1} {
    items.push(item);
    ++top; // first item on the stack is at array index 0
}

template<typename T>
ArrayStack<T>::ArrayStack(const ArrayStack<T>& aStack) : top{-1} {
    // TO DO: copy constructor
}

template<typename T>
ArrayStack<T>::~ArrayStack() {
    while (!isEmpty()) {
        pop();
    }
}

template<typename T>
T ArrayStack<T>::peek() const {
    if (!isEmpty()) {
        return items[top];
    }
    return 0; // optimally throw an error
}

template<typename T>
bool ArrayStack<T>::push(const T& item) {
    if (top < MAX_SIZE_ARRAYSTACK - 1) {
        ++top;
        items[top] = item;
        return true;
    }
    return false; // if there wasn't room to add the item
}

template<typename T>
bool ArrayStack<T>::pop() {
    if (!isEmpty()) {
        --top;
        return true;
    }
    return false; // if/when stack is empty
}

template<typename T>
bool ArrayStack<T>::isEmpty() const {
    return top < 0;
}

#endif