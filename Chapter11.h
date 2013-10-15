//
//  Chapter11.h
//  EPI
//
//  Created by Chih-Yang Chang on 10/3/13.
//  Copyright (c) 2013 Chih-Yang Chang. All rights reserved.
//

#ifndef __EPI__Chapter11__
#define __EPI__Chapter11__

#include <iostream>
#include <vector>
#include <random>

using namespace std;

// 11.1
template<typename T>
int search_first(const vector<T> &arr, const T &key) {
    int L = 0, R = arr.size() - 1, res = -1;
    while (L <= R) {
        int M = L + ((R - L) >> 1);
        if (key < arr[M]) {
            R = M - 1;
        } else if (key > arr[M]) {
            L = M + 1;
        } else { // find key
            res = M; R = M - 1;
        }
    }
    return res;
}

// 11.2
template<typename T>
int search_first_larger_than_k(const vector<T> &A, const T &k) {
    int l = 0, r = A.size() - 1, res = -1;
    while (l <= r) {
        int m = l + ((r - l) >> 1);
        if (k < A[m]) {
            res = m; r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return res;
}

// 11.3
template<typename T>
int search_Ai_i(const vector<T> &A) {
    int l = 0, r = A.size() - 1;
    
    while (l <= r) {
        int m = l + (r - l) >> 1;
        int val = A[m] - m;
        if (val == 0) {
            return m;
        } else if (val > 0) {
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    
    return -1;
}

// 11.13
// Find k-th element in an unsorted array: quick-select
template<typename T>
int partition(vector<T> &A, const int &l, const int &r, const int &pivot) {
    T pivot_value = A[pivot];
    
    int larger_index = l;
    
    swap(A[pivot], A[r]);
    for (int i = l; i < r; i++) {
        if (A[i] > pivot_value) {
            swap(A[i], A[larger_index++]);
        }
    }
    
    swap(A[r], A[larger_index]);
    return larger_index;
}

template<typename T>
T find_kth_largest(vector<T> array, const int &k) {
    int l = 0, r = array.size() - 1;
    
    while (l <= r) {
        // generate random int in [l, r]
        default_random_engine gen((random_device())());
        uniform_int_distribution<int> dis(l, r);
        int p = partition(array, l, r, dis(gen));
        if (p == k - 1) return array[p];
        else if (p < k - 1) {
            l = p + 1;
        } else {
            r = p - 1;;
        }
    }
}

#endif /* defined(__EPI__Chapter11__) */
