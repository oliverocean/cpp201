// @file: Stack_Interface.h
// @author: Oliver Ocean

#ifndef STACK_INTERFACE_
#define STACK_INTERFACE_

template<typename T>
class StackInterface {

public:
    virtual T peek() const = 0;
    virtual bool push(const T& item) = 0;
    virtual bool pop() = 0;
    virtual bool isEmpty() const = 0;

    virtual ~StackInterface() {}
};

#endif