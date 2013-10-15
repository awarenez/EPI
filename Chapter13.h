//
//  Chapter13.h
//  EPI
//
//  Created by Chih-Yang Chang on 10/4/13.
//  Copyright (c) 2013 Chih-Yang Chang. All rights reserved.
//

#ifndef __EPI__Chapter13__
#define __EPI__Chapter13__

#include <iostream>
#include <fstream>

#include <vector>
#include <set>
#include <unordered_set>

using namespace std;

// 13.5
// n ~ m
template<typename T>
vector<T> intersections(const vector<T> &A, const vector<T> &B) {
    int i = 0, j = 0;
    vector<T> intersect;
    while (i < A.size() && j < B.size()) {
        if (A[i] == B[j] && (i == 0 || A[i] != A[i - 1])) {
            intersect.emplace_back(A[i]);
            i++; j++;
        } else if (A[i] < B[j]) {
            i++;
        } else {
            j++;
        }
    }
    return intersect;
}

// n << m
template<typename T>
vector<T> intersection2(const vector<T> &A, const vector<T> &B) {
    vector<T> intersect;
    for (int i = 0; i < A.size(); i++) {
        // binary search on B
        if ((i == 0 || A[i] != A[i - 1]) && binary_search(B.begin(), B.end(), A[i])) {
            intersect.emplace_back(A[i]);
        }
    }
    return intersect;
}

// 13.2 Variable length sort, indirect sort
template<typename T>
void indirect_sort(const string &file_name) {
    
    ifstream ifs(file_name.c_str());
    
    vector<T> A;
    
    T x;
    while (ifs >> x) {
        A.emplace_back(x);
    }
    
    // Initialize P
    vector<T*> P;
    for (T &a : A) {
        P.emplace_back(&a);
    }
    
    // Indirect sort file
    sort(P.begin(), P.end(), [](const T* a, const T* b) -> bool {return *a < *b;});
    
    // output file
    ofstream ofs(file_name.c_str());
    for (const T *p : P) {
        ofs << *p << endl;
    }
}

// 13.12 find intersection intervals
template<typename TimeType>
struct Interval {
    TimeType left;
    TimeType right;
};

template<typename TimeType>
class LeftComp {
    const bool operator() (const Interval<TimeType> *a,
                           const Interval<TimeType> *b) const {
        return a->left != b->left ? a->left < b->left : a->right < b->right;
    }
};
        
template<typename TimeType>
class RightComp {
    const bool operator() (const Interval<TimeType> *a,
                           const Interval<TimeType> *b) const {
        return a->right != b->right ? a->right > b->right : a->left > b->left;
    }
};

template<typename TimeType>
vector<Interval<TimeType>> find_minimum_visit(const vector<Interval<TimeType>> &I) {
    set<const Interval<TimeType> *, LeftComp<TimeType>> L;
    set<const Interval<TimeType> *, RightComp<TimeType>> R;
    
    for (const auto &i : I) {
        L.emplace_back(&i), R.emplace_back(&i);
    }
    
    vector<Interval<TimeType>> S;
    while (!L.empty() && !R.empty()) {
        TimeType b = *R.begin()->right;
        S.emplace_back(b);
        
        auto it = L.cbegin();
        while (it != L.end() && (*it)->left <= b) {
            R.erase(it);
            L.erase(it++);
        }
    }
    
    return S;
}
        
// Method 2
template<typename TimeType>
struct EndPoint {
    const bool operator<(const EndPoint<TimeType> &that) const {
        const TimeType a = is_left ? ptr->left : ptr->right,
        b = that.is_left ? that.ptr->left : that.ptr->right;
        return a < b;
    }
    
    const Interval<TimeType>* ptr;
    bool is_left;
};
        
template<typename TimeType>
vector<TimeType> find_minimum_visit_helper(const vector<EndPoint<TimeType>> &endpoints) {
    vector<TimeType> S;
    unordered_set<const Interval<TimeType>*> covered;
    vector<const Interval<TimeType>*> covering;
    for (const auto &e : endpoints) {
        if (e.is_left) {
            covering.emplace(e.ptr);
        } else if (covered.find(e.ptr) == covered.end()) {
            // e's interval has not been covered
            S.emplace_back(e.ptr->right);
            covered.insert(covering.cbegin(), covering.cend());
            covering.clear();
        }
    }
    return S;
}
        
template<typename TimeType>
vector<TimeType> find_minimum_visit(const vector<Interval<TimeType>> &I) {
    vector<EndPoint<TimeType>> endpoints;
    
    for (int i = 0; i < I.size(); i++) {
        endpoints.emplace_back(EndPoint<TimeType>{&I[i], true});
        endpoints.emplace_back(EndPoint<TimeType>{&I[i], false});
    }
    sort(endpoints.begin(), endpoints.end());
    return find_minimum_visit_helper(endpoints);
}

#endif /* defined(__EPI__Chapter13__) */
