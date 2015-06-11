#ifndef __Project__HeapType__
#define __Project__HeapType__

#include <stdio.h>
#include <vector>

#endif /* defined(__Project__HeapType__) */

using namespace std;

template<class T>
struct MaxComp {
    bool operator()(const T& t1, const T& t2) const {
        return !(t1 < t2);
    }
};

template<class T, class Comp = MaxComp<T> >
class HeapType {
public:
    HeapType() = default;
    HeapType(Comp comp) : comp(comp) {}
    void insert(T val);
    T top();
    void pop();
    void remove(int index);
    void bubbleUp(int index);
    void bubbleDown(int index);
    int find(const T& elem);
    int size() const {return static_cast<int>(innerHeap.size()); }
    bool empty() { return innerHeap.empty(); }
    
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
    Comp comp;
};