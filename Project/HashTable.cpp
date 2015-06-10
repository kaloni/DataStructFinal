//
//  HashTable.cpp
//  Project
//
//  Created by Carl Dehlin on 09/06/15.
//  Copyright (c) 2015 Carl Dehlin. All rights reserved.
//

#include "HashTable.h"
#include <iostream>

using namespace std;

template<class K, class V>
HTList<K,V>::~HTList() {
    NodeType* cur_ptr = front;
    while( cur_ptr ) {
        NodeType* next_ptr = cur_ptr->next;
        delete cur_ptr;
        cur_ptr = next_ptr;
    }
}

// attach node at end of list
template<class K, class V>
void HTList<K,V>::push_back(NodeType* node) {
    if( m_size > 0 ) {
        back->next = node;
        back = node;
    }
    else {
        front = back = node;
    }
    m_size++;
}

// erase a node with a certain key, nothing happens if not found
template<class K, class V>
void HTList<K,V>::erase(K key) {
    NodeType* cur_ptr = front;
    if( front ) {
        if( cur_ptr->key == key ) {
            front = cur_ptr->next;
            delete cur_ptr;
            m_size--;
        }
    }
    else while( cur_ptr ) {
        if( cur_ptr->next ) {
            if( cur_ptr->next->key == key ) {
                
                cur_ptr->next = (cur_ptr->next->next);
                
                if( back == cur_ptr->next )
                    back = cur_ptr;
                
                delete cur_ptr->next;
                m_size--;
                break;
            }
            cur_ptr = cur_ptr->next;
        }
    }
}

// return pointer to node with key, null if not found
template<class K, class V>
HTNode<K,V>* HTList<K,V>::get(K key) {
    NodeType* cur_ptr = front;
    while( cur_ptr ) {
        if( cur_ptr->key == key )
            return cur_ptr;
        cur_ptr = cur_ptr->next;
    }
    return nullptr;
}

template<class K, class V>
HashTable<K,V>::HashTable(int size, int (*hashfunc)(K key)) : hashfunc(hashfunc), table(std::vector<HTList<K,V> >(size)) {}

// hash key, push_back in linked list at hashed key index in vector
template<class K, class V>
void HashTable<K,V>::insert(K key, V val) {
    int index = hashfunc(key);
    table[index].push_back(new NodeType(key,val));
}

// Deletes the first node found with certain key
template<class K, class V>
void HashTable<K,V>::erase(K key) {
    int index = hashfunc(key);
    table[index].erase(key);
}

// return node pointer to first node found with certain key
template<class K, class V>
HTNode<K,V>* HashTable<K,V>::get(K key) {
    int index = hashfunc(key);
    return table[index].get(key);
}