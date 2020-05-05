// @file: Array_List.h
// @author: Oliver Ocean

#ifndef ARRAY_LIST_
#define ARRAY_LIST_

#include <array>
#include <string>

#include "List_Interface.h"

template<typename T>
class ArrayList : public ListInterface<T> {

private:
    static const int ABSOLUTE_MAX_ITEMS = 10;
    int maxItems = ABSOLUTE_MAX_ITEMS;
    int itemCount;
    T* items;
    std::string listTitle;

public:
    ArrayList();
    explicit ArrayList(const int& size);
    ArrayList(const std::string& title, const int& size);
    ArrayList(const ArrayList<T>& list); // copy constructor
    ~ArrayList();

    bool isListEmpty() const override;
    int getListSize() const override;
    std::string getListTitle() const; // no override
    void setListTitle(const std::string& title); // no override
    void clearList() override;

    T getAt(const int& position) const override;
    bool append(const T& item) override;
    bool insertAt(const T& item, const int& position) override;
    bool replaceAt(const T& item, const int& position) override;
    bool removeAt(const int& position) override;
};

template<typename T>
ArrayList<T>::ArrayList() : itemCount(0) {
    listTitle = "List";
    items = new T[maxItems]; // dynamically allocated array
};

template<typename T>
ArrayList<T>::ArrayList(const int& size) : itemCount(0) {
    listTitle = "List";
    if (size > maxItems) {
        items = new T[maxItems];
    } else {
        items = new T[size];
    }
};

template<typename T>
ArrayList<T>::ArrayList(const std::string& title, const int& size) : itemCount(0) {
    listTitle = title;
    if (size > maxItems) {
        items = new T[maxItems];
    } else {
        items = new T[size];
    }
};

// copy constructor
template<typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& list): itemCount(0) {
    listTitle = list.getListTitle();
    itemCount = list.getListSize();
    items = new T[itemCount];
    for (auto& i : list) {
        items[i] = list.getAt(i - 1); // test for off-by-one error
        ++itemCount;
    }
}

// destructor
template<typename T>
ArrayList<T>::~ArrayList() { delete[] items; }

// public class methods
template<typename T>
bool ArrayList<T>::isListEmpty() const { return itemCount < 0; }

template<typename T>
int ArrayList<T>::getListSize() const { return itemCount; }

template<typename T>
std::string ArrayList<T>::getListTitle() const { return listTitle; }

template<typename T>
void ArrayList<T>::setListTitle(const std::string& title) { listTitle = title; }

template<typename T>
void ArrayList<T>::clearList() { itemCount = 0; }

template<typename T>
T ArrayList<T>::getAt(const int& position) const {
    if (position < 1 || position > maxItems) {
        return items[0]; // optimally throw an error
    } else {
        return items[position - 1];
    }
}

template<typename T>
bool ArrayList<T>::append(const T& item) {
    if (itemCount == maxItems) {
        return false; // optimally throw an error
    } else {
        items[itemCount] = item;
        ++itemCount;
        return true;
    }
}

template<typename T>
bool ArrayList<T>::insertAt(const T& item, const int& position) {
    if (itemCount == maxItems || position < 1 || position > maxItems) {
        return false; // optimally throw an error
    } else if (position == itemCount + 1) { // simple append to end of list
        append(item);
        return true;
    } else { // move items one position to right, then insert new item
        for (int j = itemCount; j <= position; --j) {
            items[j] = items[j - 1];
        }
        items[position - 1] = item;
        ++itemCount;
        return true;
    }
}

template<typename T>
bool ArrayList<T>::replaceAt(const T& item, const int& position) {
    if (position < 1 || position > maxItems) {
        return false; // optimally throw an error
    } else {
        items[position - 1] = item;
        return true;
    }
}

template<typename T>
bool ArrayList<T>::removeAt(const int& position) {
    if (position < 1 || position > maxItems) {
        return false; // optimally throw an error
    } else if (position == itemCount) { // simple removal from end of list
        --itemCount;
        return true;
    } else { // move items one position to right, then insert new item
        for (int k = position - 1; k < itemCount; ++k) {
            items[k] = items[k + 1];
        }
        --itemCount;
        return true;
    }
}

#endif