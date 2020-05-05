// @file: List_Interface.h
// @author: Oliver Ocean

#ifndef LIST_INTERFACE_
#define LIST_INTERFACE_

template<typename T>
class ListInterface {

public:

    virtual bool isListEmpty() const = 0;
    virtual int getListSize() const = 0;
    virtual void clearList() = 0;

    virtual T getAt(const int& position) const = 0;
    virtual bool append(const T& item) = 0;
    virtual bool insertAt(const T& item, const int& position) = 0;
    virtual bool replaceAt(const T& item, const int& position) = 0;
    virtual bool removeAt(const int& position) = 0;

    virtual ~ListInterface() {};
};

#endif