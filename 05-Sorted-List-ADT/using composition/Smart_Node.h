/** @author: Oliver Ocean */

#ifndef SMART_NODE_
#define SMART_NODE_

#include <memory>

template<typename T>
class SmartNode
{
private:
    T data;
    std::shared_ptr<SmartNode<T>> next;

public:
    SmartNode();
    explicit SmartNode(const T& newData);
    SmartNode(const T& newData, std::shared_ptr<SmartNode<T>> newNext);

    T getData() const;
    std::shared_ptr<SmartNode<T>> getNext() const;
    void setData(const T& newData);
    void setNext(std::shared_ptr<SmartNode<T>> newNext);
};

template<typename T>
SmartNode<T>::SmartNode() = default;

template<typename T>
SmartNode<T>::SmartNode(const T& newData): data(newData) {}

template<typename T>
SmartNode<T>::SmartNode(const T& newData, std::shared_ptr<SmartNode<T>> newNext) : data(newData), next(newNext) {}

template<typename T>
T SmartNode<T>::getData() const { return data; }

template<typename T>
void SmartNode<T>::setData(const T& newData) { data = newData; }

template<typename T>
std::shared_ptr<SmartNode<T>> SmartNode<T>::getNext() const { return next; }

template<typename T>
void SmartNode<T>::setNext(std::shared_ptr<SmartNode<T>> newNext) { next = newNext; }

#endif
