//
//  Graph.h
//  Project
//
//  Created by Carl Dehlin on 10/06/15.
//  Copyright (c) 2015 Carl Dehlin. All rights reserved.
//

#ifndef __Project__Graph__
#define __Project__Graph__

#include <vector>
#include <map>
#include <forward_list>

using namespace std;

class Graph {
public:
    Graph() = default;
    Graph(int size) : adj_list(size) {}
    vector<int> dijkstra(int from);
    forward_list<int> getPath(const vector<int>& prev, int to);
    void insert(int from, int to, int weight);
    int size() const { return static_cast<int>(adj_list.size()); }
    
    // operators
    friend ostream& operator<<(ostream&, const Graph&);
    
    // iterator
    typedef vector<map<int,int> > AdjList;
    AdjList::iterator begin() { return adj_list.begin(); }
    AdjList::iterator end() { return adj_list.end(); }
    AdjList::const_iterator cbegin() const { return adj_list.cbegin(); }
    AdjList::const_iterator cend() const { return adj_list.cend(); }
private:
    AdjList adj_list;
};

#endif /* defined(__Project__Graph__) */
