//
//  HashTable.h
//  Project
//
//  Created by Carl Dehlin on 09/06/15.
//  Copyright (c) 2015 Carl Dehlin. All rights reserved.
//

#ifndef __Project__HashTable__
#define __Project__HashTable__

#include <vector>
#include <iostream>

// Node struct
template<class K, class V>
struct HTNode {
    HTNode() = default;
    HTNode(K k, V v) : key(k), val(v) {}
    K key;
    V val;
    HTNode* next;
};

template<class K, class V> class HTListIterator;
// Single linked list class
template<class K, class V>
class HTList {
public:
    typedef HTNode<K,V> NodeType;
//private:
    int m_size;
    NodeType* front;
    NodeType* back;
public:
    HTList() : m_size(0), front(nullptr), back(nullptr) {}
    virtual ~HTList();
    void push_back(NodeType* node);
    V* get(K key);
    void erase(K key);
    int size() { return m_size; }
    
    // iterator
    typedef HTListIterator<K, V> iterator;
    iterator begin() { return iterator(front); }
    iterator end() { return iterator(nullptr); }
    
};

template<class K, class V>
class HTListIterator {
public:
    typedef HTNode<K,V> NodeType;
    HTListIterator(NodeType* node) : node(node) {}
    bool nonend() { return node != nullptr; }
    void operator++() { node = node->next; }
    bool operator==(HTListIterator& it) { return node == &(*it); }
    bool operator!=(HTListIterator& it) { return !(operator==(it)); }
    NodeType& operator*() { return *node; }
    NodeType* operator->() { return &(operator*()); }
private:
    NodeType* node;
};

// Hash table class, basically just an array of linked lists and a hash function pointer
template<class K, class V>
class HashTable {
public:
    typedef HTNode<K, V> NodeType;
    typedef HTList<K, V> ListType;
    typedef typename std::vector<HTList<K,V> >::iterator iterator;
    HashTable() = default;
    HashTable(int size, int (*hashfunc)(K key));
    ~HashTable() = default;
    void insert(K key, V val);
    void erase(K key);
    V* get(K key);
    int size() const { return static_cast<int>(table.size()); }
    
    // operators
    ListType& operator[](unsigned index) { return table[index]; }
    
    // iterator
    iterator begin() { return table.begin(); }
    iterator end() { return table.end(); }
private:
    //int hashfunc(K key);
    int (*hashfunc)(K key);
    std::vector<HTList<K, V> > table;
};

#endif /* defined(__Project__HashTable__) */
