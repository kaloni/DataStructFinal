//
//  Graph.cpp
//  Project
//
//  Created by Carl Dehlin on 10/06/15.
//  Copyright (c) 2015 Carl Dehlin. All rights reserved.
//

#include "Graph.h"
#include <set>
#include <limits>
#include "HeapType.cpp"

struct GraphComp {
    typedef vector<int> distance;
    GraphComp(int from, distance& d) : from(from), d(d) {}
    bool operator()(const int i, const int j) {
        return d[i] < d[j];
    }
private:
    distance& d;
    int from;
};

void Graph::insert(int from, int to, int weight) {
    if( ! (from < adj_list.size() && to < adj_list.size() ) ) {
        adj_list.resize(max(from,to));
    }

    adj_list[from].insert(make_pair(to, weight));
    adj_list[to].insert(make_pair(from, weight));
}

bool intComp(int i, int j) {
    return i == j;
}

vector<int> Graph::dijkstra(int from) {

    vector<int> prev(size(), -1);
    vector<int> distance(size(), numeric_limits<int>::max());
    distance[from] = 0;
    HeapType<int, GraphComp> unvisited(GraphComp(from, distance));

    distance[from] = 0;

    for(int i = 0; i < size(); ++i) {
        unvisited.insert(i);
    }

    while( ! unvisited.empty() ) {

        int cur_min = unvisited.top();

        for(map<int,int>::iterator it = adj_list[cur_min].begin(); it != adj_list[cur_min].end(); ++it) {
            if( distance[cur_min] + it->second < distance[it->first] ) {
                distance[it->first] = distance[cur_min] + it->second;
                prev[it->first] = cur_min;
                int heap_index = unvisited.find(it->first, &intComp);
                // if( heap_index >= 0 )
                unvisited.bubbleUp(heap_index);
            }
        }

        unvisited.pop();
    }

    return prev;
}

int Graph::distance(int from, int to){
    for(map<int, int>::iterator it = adj_list[from].begin(); it != adj_list[from].end(); ++it) {
        if( it->first == to )
            return it->second;
    }
    return -1;
}

forward_list<int> Graph::getPath(const vector<int>& prev, int to) {
    forward_list<int> path;
    int current = to;
    while( current != -1 ) {
        path.push_front(current);
        current = prev[current];
    }
    return path;
}

ostream& operator<<(ostream& os, const Graph& g) {
    for(int i = 0; i < g.size(); ++i) {
        os << "[" << i << "] : ";
        for(map<int,int>::const_iterator it = g.adj_list[i].cbegin(); it != g.adj_list[i].cend();) {
            os << it->first;
            if( ++it != g.adj_list[i].cend() )
                os << ", ";
        }
        os << endl;
    }
    return os;
}

