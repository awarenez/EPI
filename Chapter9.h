//
//  Chapter9.h
//  EPI
//
//  Created by Chih-Yang Chang on 10/12/13.
//  Copyright (c) 2013 Chih-Yang Chang. All rights reserved.
//

#ifndef __EPI__Chapter9__
#define __EPI__Chapter9__

#include <iostream>

#include <memory>
#include <vector>
#include <unordered_set>

using namespace std;

template<typename T>
struct TreeNode {
    T data;
    shared_ptr<TreeNode<T>> parent;
    shared_ptr<TreeNode<T>> left;
    shared_ptr<TreeNode<T>> right;
};

// Morris traversal: in-order traversal using O(1) space
template<typename T>
void inorder_traversal(shared_ptr<TreeNode<T>> n) {
    while (n) {
        if (n->left) {
            // find the predecessor of n
            shared_ptr<TreeNode<T>> pre = n->left;
            while (pre->right && pre->right != n) {
                pre = pre->right;
            }
            
            // Build the successor link
            if (pre->right) { // pre->right == n
                // reverse the successor link if predecessor's successor is n
                pre->right = nullptr;
                cout << n->data << endl;
                n = n->right;
            } else {
                pre->right = n;
                n = n->right;
            }
        } else {
            cout << n->data << endl;
            n = n->right;
        }
    }
}

// 9.5 inorder traversal using O(1) with parent link
template<typename T>
void traversal(const shared_ptr<TreeNode<T>> &r) {
    shared_ptr<TreeNode<T>> pre = nullptr, curr = r, next;
    
    if (!r) return;
    
    while (curr) {
        if (!pre || pre->left == curr || pre->right == curr) {
            if (curr->left) {
                next = curr->left;
            } else {
                cout << curr->data << endl;
            }
        } else if (curr->left == prev) {
            cout << curr->data << endl;
            next = curr->right ? curr->right : curr->parent;
        } else {
            next = curr->parent;
        }
        prev = curr;
        curr = next;
    }
}

// 9.8 reconstruct a binary tree from inorder and pre-order/post-order traversal
template<typename T>
shared_ptr<TreeNode<T>> reconstruct_pre_in_orders(const vector<T> &preorder,
                                                  const vector<T> &inorder) {
    return reconstruct_pre_in_orders(preorder, 0, preorder.size(),
                                     inorder, 0, inorder.size());
}

template<typename T>
shared_ptr<TreeNode<T>> reconstruct_pre_in_orders_helper(const vector<T> &preorder,
                const int &pre_s, const int &pre_e, const vector<T> &inorder, const int &in_s, const int &in_e) {
    
    // Valid
    if (pre_s > pre_e && in_e > in_s) {
        // find the element in inorder sequence
        auto it = find(inorder.cbegin() + in_s, inorder.cbegin() + in_e, preorder[pre_s]);
        auto left_tree_size = distance(inorder.cbegin(), it) - in_s;
        
        return shared_ptr<TreeNode<T>> (new TreeNode<T> {preorder[pre_s],
            // reconstruct left tree
            reconstruct_pre_in_orders(preorder, pre_s + 1, pre_s + 1 + left_tree_size,
                                      inorder, in_s, distance(inorder.cbegin(), it)),
            // reconstruct right tree
            reconstruct_pre_in_orders(preorder, pre_s + 1 + left_tree_size,
                                      inorder, distance(inorder.cbegin(), it) + 1, in_e)});
    }
    return nullptr;
}

template<typename T>
shared_ptr<TreeNode<T>> reconstruct_post_in_orders_helper(const vector<T> &postorder,
                                                          const int &post_s, const int &post_e,
                                                          const vector<T> &inorder,
                                                          const int &in_s, const int &in_e) {
    if (post_e > post_s && in_e > in_s) {
        // find the element in inorder
        auto it = find(inorder.cbegin() + in_s, inorder.cend() + in_e, postorder[post_e - 1]);
        auto left_tree_size = distance(inorder.cbegin(), it) - in_s;
    
        return shared_ptr<TreeNode<T>> (new TreeNode<T> {postorder[post_e - 1],
            reconstruct_post_in_orders_helper(postorder, post_s, post_s + left_tree_size,
                                              inorder, in_s, distance(inorder.cbegin(), it)),
            reconstruct_post_in_orders_helper(postorder, post_s + left_tree_size, post_e - 1,
                                              inorder, in_s + distance(inorder.cbegin, it) + 1, in_e)
        });
    }
    return nullptr;
}

template<typename T>
shared_ptr<TreeNode<T>> reconstruct_post_in_orders(const vector<T> &postorder, const vector<T> inorder) {
    return reconstruct_post_in_orders_helper(postorder, 0, postorder.size(),
                                             inorder, 0, inorder.size());
}

// 9.13
template<typename T>
shared_ptr<TreeNode<T>> LCA(const shared_ptr<TreeNode<T>> root, shared_ptr<TreeNode<T>> A, shared_ptr<TreeNode<T>> B) {

    int depth_A = get_depth(A);
    int depth_B = get_depth(B);
    
    int depth_diff = abs(depth_A - depth_B);
    
    if (depth_A > depth_B) {
        swap(A, B);
    }
    
    while (depth_diff--) {
        A = A->parent;
    }
    
    while (A != B) {
        A = A->parent;
        B = B->parent;
    }
    
    return A;
}

template<typename T>
int get_depth(shared_ptr<TreeNode<T>> n) {
    int d = 0;
    while (n) {
        d++;
        n = n->parent;
    }
    return d;
}

// 9.14
template<typename T>
shared_ptr<TreeNode<T>> LCA(shared_ptr<TreeNode<T>> A, shared_ptr<TreeNode<T>> B) {
    unordered_set<shared_ptr<TreeNode<T>>> hash;
    while (A || B) {
        if (A) {
            if (hash.emplace(A).second == false) {
                return A;
            }
            A = A->parent;
        }
        
        if (B) {
            if (hash.emplace(B).second == false) {
                return B;
            }
            B = B->parent;
        }
    }
    throw invalid_argument("A and B are not in the same tree");
}

#endif /* defined(__EPI__Chapter9__) */
