//
//  Chapter14.h
//  EPI
//
//  Created by Chih-Yang Chang on 10/4/13.
//  Copyright (c) 2013 Chih-Yang Chang. All rights reserved.
//

#ifndef __EPI__Chapter14__
#define __EPI__Chapter14__

#include <iostream>
#include <memory>

using namespace std;

template<typename T>
struct BinarySearchTree {
    T data;
    shared_ptr<BinarySearchTree<T>> left, right;
};

// 14.1
template<typename T>
bool is_BST_helper(const shared_ptr<BinarySearchTree<T>> &r, const T &lower, const T &upper) {
    if (!r) return false;
    else if (r->data < lower || r->data > upper) return false;
    
    return is_BST_helper(r->left, lower, r->data) && is_BST_helper(r->right, r->data, upper);
}

template<typename T>
bool is_BST(const shared_ptr<BinarySearchTree<T>> &r) {
    return is_BST_helper(r, numeric_limits<T>::min(), numeric_limits<T>::max());
}

// 14.4
template<typename T>
shared_ptr<BinarySearchTree<T>> find_first_larger_k_with_k_exist(const shared_ptr<BinarySearchTree<T>> r, const T &k) {
    shared_ptr<BinarySearchTree<T>> first = nullptr;
    bool found_k = false;
    
    while (r) {
        if (r->data == k) {
            found_k = true;
            r = r->right;
        } else if (r->data > k) {
            first = r;
            r = r->left;
        } else {
            r = r->right;
        }
    }
    
    return found_k ? first : nullptr;
}

#endif /* defined(__EPI__Chapter14__) */
