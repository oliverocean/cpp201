/** @author: Oliver Ocean */

#ifndef BAG_INTERFACE_
#define BAG_INTERFACE_

#include <vector>

template<typename T>
class BagInterface {

public:
    virtual int getSize() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool addToFront(const T& newEntry) = 0;
    virtual bool addToBack(const T& newEntry) = 0;
    //virtual bool remove(const T& anEntry) = 0;
    virtual void clear() = 0;
    virtual bool contains(const T& anEntry) const = 0;
    virtual ~BagInterface() = default;
};

#endif