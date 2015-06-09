#include "HeapType.h"
#include <iostream>

// check node at "index" to see if it's greater than it's parent
// if greater -> swap
template<class T>
void HeapType<T>::bubbleUp(int index) {
    if(index > 0) {
        int parentIndex = (index - 1)/2;
        if(innerHeap[parentIndex] < innerHeap[index]) {
            T tmp = innerHeap[parentIndex];
            innerHeap[parentIndex] = innerHeap[index];
            innerHeap[index] = tmp;
        }
        bubbleUp(parentIndex);
    }
}

// check node at "index" to see if it's less than it's children
// if less -> swap with max child
template<class T>
void HeapType<T>::bubbleDown(int index) {
    
    // if have children
    if(index < innerHeap.size() ) {
        
        int leftChildIndex = 2*index + 1;
        int rightChildIndex = 2*index + 2;
        int maxChildIndex;
        // if have 2 children
        if( rightChildIndex < innerHeap.size() ) {
            maxChildIndex = innerHeap[leftChildIndex] > innerHeap[rightChildIndex] ? leftChildIndex : rightChildIndex;
        }
        // else if one child
        else if( leftChildIndex < innerHeap.size() ) {
            maxChildIndex = leftChildIndex;
        }
        
        // if less than maximum child, swap and recurse
        if( innerHeap[index] < innerHeap[maxChildIndex] ) {
            T tmp = innerHeap[maxChildIndex];
            innerHeap[maxChildIndex] = innerHeap[index];
            innerHeap[index] = tmp;
            bubbleDown(maxChildIndex);
        }
    }
}

template<class T>
void HeapType<T>::insert(T val) {
    innerHeap.push_back(val);
    bubbleUp(static_cast<int>(innerHeap.size() - 1));
}

// This is a max heap, deleteMax deletes top of heap, then performs some bubblin'
template<class T>
void HeapType<T>::deleteMax() {
    if( ! innerHeap.empty() ) {
        innerHeap[0] = innerHeap.back();
        innerHeap.pop_back();
        bubbleDown(0);
    }
}

// remove a node at some index, then bubble around until the heap is in order again
template<class T>
void HeapType<T>::remove(int index) {
    
    T tmp = innerHeap.back();
    innerHeap.pop_back();
    if( index < innerHeap.size() ) {
        innerHeap[index] = tmp;
        bubbleUp(index);
        bubbleDown(index);
    }
}