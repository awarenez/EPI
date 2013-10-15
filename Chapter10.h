//
//  Chapter10.h
//  EPI
//
//  Created by Chih-Yang Chang on 10/3/13.
//  Copyright (c) 2013 Chih-Yang Chang. All rights reserved.
//

#ifndef __EPI__Chapter10__
#define __EPI__Chapter10__

#include <iostream>

#include <vector>
#include <queue>
#include <utility>

using namespace std;

template<typename T>
class Compare {
    const bool operator() (const pair<T, int> &lhs, const pair<T, int> &rhs) const {
        return lhs.first > rhs.first;
    }
};

template<typename T>
vector<T> merge(vector<vector<T>> &S) {
    vector<T> ret; // return vector
    priority_queue<pair<T, int>, vector<pair<T, int>, Compare<T>>> min_heap; // min-heap
    vector<int> S_idx(S.size(), 0); // store the usage of each vector using index
    
    // construct the min-heap
    for (int i = 0; i < S.size(); i++) {
        min_heap.emplace(S[i][0], i);
        S_idx[i] = 1;
    }
    
    // keep looping the element in the list to the heap
    while (!min_heap.empty()) {
        pair<T, int> p = min_heap.top();
        ret.emplace_back(p.first);
        // get the smallest one
        if (S_idx[p.second] < S[p.second].size()) {
            min_heap.emplace(S[p.second][S_idx[p.second]++], p.second);
        }
        min_heap.pop();
    }
    return ret;
}

// 10.6
template<typename T>
void approximate_sort(istringstream &sin, const int &k) {
    // create a priority queue from the first k elements
    priority_queue<T, vector<T>, greater<T>> min_heap;
    
    T x;
    for (int i = 0; i < k; sin >> x, i++) {
        min_heap.push(x);
    }
    
    // while add element, add to the heap and pop the root
    while (sin >> x) {
        min_heap.push();
        cout << min_heap.top() << endl;
        min_heap.pop();
    }
    
    // print the rest elements in the priority queue
    while (!min_heap.empty()) {
        cout << min_heap.top() << endl;
        min_heap.pop();
    }
}


// 10.8 running median
template<typename T>
void running_median(istringstream &sin) {
    // build two heaps, min_heap and max_heap
    priority_queue<T, vector<T>, greater<T>> L;
    priority_queue<T, vector<T>, less<T>> H;
    
    T x;
    while (sin >> x) {
        if (L.empty() == false && x > L.top()) {
            L.emplace(x);
        } else {
            H.emplace(x);
        }
        
        if (H.size() > L.size() + 1) {
            L.emplace(H.top());
            H.pop();
        } else if (L.size() > H.size() + 1) {
            H.emplace(L.top());
            L.pop();
        }
        
        if (H.size() == L.size()) {
            cout << 0.5 * (H.top() + L.top()) << endl;
        } else {
            cout << (H.size() > L.size() ? H.top() : L.top()) << endl;
        }
    }
}

#endif /* defined(__EPI__Chapter10__) */
