#ifndef __Project__HeapType__
#define __Project__HeapType__

#include <stdio.h>
#include <vector>

#endif /* defined(__Project__HeapType__) */

using namespace std;

template<class T>
class HeapType {
public:
    void insert(T val);
    void deleteMax();
    void remove(int index);
    void bubbleUp(int index);
    void bubbleDown(int index);
    int size() const {return static_cast<int>(innerHeap.size()); }
    
    // operators
    T& operator[](int index) {
        return innerHeap[index];
    }
    
    // iterator
    typedef typename vector<T>::iterator iterator;
    iterator begin() { return innerHeap.begin(); }
    iterator end() { return innerHeap.end(); }
private:
    vector<T> innerHeap;
};