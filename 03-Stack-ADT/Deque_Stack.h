// @file: Deque_Stack.h
// @author: Oliver Ocean

#ifndef DEQUE_STACK_
#define DEQUE_STACK_

#include <deque>
#include "Stack_Interface.h"

template<typename T>
class DequeStack : public StackInterface<T> {

private:
    std::deque<T> stack;

public:
    DequeStack();
    explicit DequeStack(const T& item);
    DequeStack(const DequeStack<T>& aStack);
    ~DequeStack();

    T peek() const;
    bool push(const T& item);
    bool pop();
    bool isEmpty() const;
};

template<typename T>
DequeStack<T>::DequeStack() = default;

template<typename T>
DequeStack<T>::DequeStack(const T& item) {
    stack.push_front(item);
}

template<typename T>
DequeStack<T>::DequeStack(const DequeStack<T>& aStack) {
    for (const auto& item : aStack) {
        stack.push_front(aStack.item);
    }
}

template<typename T>
DequeStack<T>::~DequeStack() {
    while (!isEmpty()) {
        pop();
    }
}

template<typename T>
T DequeStack<T>::peek() const {
    return stack.front();
}

template<typename T>
bool DequeStack<T>::push(const T& item) {
    stack.push_front(item);
    return true;
}

template<typename T>
bool DequeStack<T>::pop() {
    if (!isEmpty()) {
        stack.pop_front();
        return true;
    }
    return false; // if/when stack is empty
}

template<typename T>
bool DequeStack<T>::isEmpty() const {
    return stack.empty();
}

#endif