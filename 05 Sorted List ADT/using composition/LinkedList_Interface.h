/** @author: Oliver Ocean */

#ifndef LINKEDLIST_INTERFACE_
#define LINKEDLIST_INTERFACE_

template<typename T>
class LinkedListInterface
{
public:
    virtual bool isListEmpty() const = 0;
    virtual int getListSize() const = 0;
    virtual void clearList() = 0;
    virtual int getPositionOf(const T& item) const = 0;
    virtual T getItemAt(const int& position) const = 0;
    virtual void removeItemAt(const int& position) = 0;
    virtual void remove(const T& item) = 0;
    virtual void insertAt(const T& item, const int& position) = 0;
    virtual void replaceAt(const T& item, const int& position) = 0;

    virtual ~LinkedListInterface() {};
};

#endif