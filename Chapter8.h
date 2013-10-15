//
//  Chapter8.h
//  EPI
//
//  Created by Chih-Yang Chang on 10/10/13.
//  Copyright (c) 2013 Chih-Yang Chang. All rights reserved.
//

#ifndef __EPI__Chapter8__
#define __EPI__Chapter8__

#include <iostream>

#include <stack>
#include <queue>
#include <array>

using namespace std;

// 8.1
template<typename T>
class Stack {
    stack<T> s_;
    stack<pair<T, int>> aux;
    
public:
    const bool empty(void) const {
        return s_.empty();
    }
    
    
    const T &max(void) const {
        if (empty() == false) {
            return aux.top().first;
        }
        return length_error("empty stack");
    }
    
    T pop(void) {
        if (empty() == false) {
            T ret = s_.top();
            s_.pop();
        
            if (ret == aux.top().first) {
                aux.top().second--;
                if (aux.top().second == 0)
                    aux.pop();
            }
            return ret;
        }
        throw length_error("empty stack");
    }
    
    void push(T val) {
        s_.emplace(val);
        if (aux.empty() == false) {
            if (aux.top() == val) {
                aux.top.second++;
            } else if (val > aux.top().first) {
                aux.emplace(val, 1);
            }
        } else {
            aux.emplace(val, 1);
        }
    }
};

// 8.3
// in-order traversal w/o recursion
template<typename T>
struct TreeNode {
    T data;
    shared_ptr<TreeNode<T>> left;
    shared_ptr<TreeNode<T>> right;
};

template<typename T>
void traversal(const shared_ptr<TreeNode<T>> &n) {
    stack<shared_ptr<TreeNode<T>>> s;
    shared_ptr<TreeNode<T>> curr = n;
    
    while (!s.empty() || curr) {
        if (curr) {
            s.emplace(curr);
            curr = curr->left;
        } else {
            curr = s.top();
            s.pop();
            cout << curr->data << endl;
            curr = curr->right;
        }
    }
}

// 8.5 Hanoi Tower
void transfer(const int &n, array<stack<int>, 3> &pegs,
              const int &from, const int &to, const int &use) {
    if (n > 0) {
        // recusively transfer n-1 rings from p1 to p3
        transfer(n - 1, pegs, from, use, to);
        // transfer n-th ring from p1 to p2
        pegs[to].push(pegs[from].top());
        pegs[from].pop();
        // recursively transfer n-1 rights from p3 to p2 using p1
        transfer(n - 1, pegs, use, to, from);
    }
}

void move_tower_hanoi(const int &n) {
    array<stack<int>, 3> pegs;
    // initialize pegs
    for (int i = n; i >= 1; i++) {
        pegs[0].push(i);
    }
    transfer(n, pegs, 0, 1, 2);
}
    
// 8.9 level order traversal
template<typename T>
void level_order_traversal(const shared_ptr<TreeNode<T>> &root) {
    if (!root) return;
    queue<shared_ptr<TreeNode<T>>> q;
    q.emplace(root);
    
    int count = q.size();
    while (!q.empty()) {
        cout << q.front()->data << " ";
        if (q.front()->left) q.emplace(q.front()->left);
        if (q.front()->right) q.emplace(q.front()->right);
        q.pop();
        if (--count == 0) {
            cout << endl;
            count = q.size();
        }
    }
}

#endif /* defined(__EPI__Chapter8__) */
