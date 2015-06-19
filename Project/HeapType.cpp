#include "HeapType.h"
#include <iostream>
#include <stack>

// check node at "index" to see if it's greater than it's parent
// if greater -> swap
template<class T, class Comp>
void HeapType<T, Comp>::bubbleUp(int index) {

    if(index > 0) {
        int parentIndex = (index - 1)/2;
        //if(innerHeap[parentIndex] < innerHeap[index]) {
        if( comp(innerHeap[index], innerHeap[parentIndex]) ) {
            T tmp = innerHeap[parentIndex];
            innerHeap[parentIndex] = innerHeap[index];
            innerHeap[index] = tmp;
        }
        bubbleUp(parentIndex);
    }
}

// check node at "index" to see if it's less than it's children
// if less -> swap with max child
template<class T, class Comp>
void HeapType<T, Comp>::bubbleDown(int index) {

    // if have children
    if(index < innerHeap.size() ) {

        int leftChildIndex = 2*index + 1;
        int rightChildIndex = 2*index + 2;
        int maxChildIndex = index;
        // if have 2 children
        if( rightChildIndex < innerHeap.size() ) {
            //maxChildIndex = innerHeap[leftChildIndex] > innerHeap[rightChildIndex] ? leftChildIndex : rightChildIndex;
            maxChildIndex = comp(innerHeap[leftChildIndex], innerHeap[rightChildIndex]) ? leftChildIndex : rightChildIndex;
        }
        // else if one child
        else if( leftChildIndex < innerHeap.size() ) {
            maxChildIndex = leftChildIndex;
        }

        // if less than maximum child, swap and recurse
        //if( innerHeap[index] < innerHeap[maxChildIndex] ) {
        if( index != maxChildIndex && comp(innerHeap[maxChildIndex], innerHeap[index]) ) {
            T tmp = innerHeap[maxChildIndex];
            innerHeap[maxChildIndex] = innerHeap[index];
            innerHeap[index] = tmp;
            bubbleDown(maxChildIndex);
        }
    }
}

template<class T, class Comp>
int HeapType<T,Comp>::find(const T& elem, bool (*findComp)(T t1, T t2)) {

    if( ! innerHeap.empty() ) {
        stack<int> index_stack;
        index_stack.push(0);
        int cur_index = 0;
        while( ! index_stack.empty() ) {

            cur_index = index_stack.top();
            index_stack.pop();
            //if( ( ! comp(elem, innerHeap[cur_index]) ) && (! comp(innerHeap[cur_index], elem) ) ) {
            if( findComp(elem, innerHeap[cur_index]) )
                return cur_index;

            int left_index = 2*cur_index + 1;
            int right_index = left_index + 1;
            if( left_index < innerHeap.size() ) {
                if( comp(innerHeap[left_index], elem) )
                    index_stack.push(left_index);
            }
            if( right_index < innerHeap.size() ) {
                if( comp(innerHeap[right_index], elem) )
                    index_stack.push(right_index);
            }
        }
    }
    return -1;
}

template<class T, class Comp>
void HeapType<T, Comp>::insert(T val) {
    innerHeap.push_back(val);
    bubbleUp(static_cast<int>(innerHeap.size() - 1));
}

// gets top of heap
template<class T, class Comp>
T HeapType<T, Comp>::top() {
    return innerHeap[0];
}

// deletes top of heap, then performs some bubblin'
template<class T, class Comp>
void HeapType<T, Comp>::pop() {
    if( ! innerHeap.empty() ) {
        innerHeap[0] = innerHeap.back();
        innerHeap.pop_back();
        bubbleDown(0);
    }
}

// remove a node at some index, then bubble around until the heap is in order again
template<class T, class Comp>
void HeapType<T, Comp>::remove(int index) {

    T tmp = innerHeap.back();
    innerHeap.pop_back();
    if( index < innerHeap.size() ) {
        innerHeap[index] = tmp;
        bubbleUp(index);
        bubbleDown(index);
    }
}
