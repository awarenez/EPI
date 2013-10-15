//
//  Chapter7.h
//  EPI
//
//  Created by Chih-Yang Chang on 10/6/13.
//  Copyright (c) 2013 Chih-Yang Chang. All rights reserved.
//

#ifndef __EPI__Chapter7__
#define __EPI__Chapter7__

#include <iostream>
#include <memory>

using namespace std;

// 7.1
template <typename T>
struct node_t {
    T data;
    shared_ptr<node_t<T>> next;
};

template<typename T>
void append_node(shared_ptr<node_t<T>> &head, shared_ptr<node_t<T>> tail, shared_ptr<node_t<T>> n) {
    head ? tail->next = n : head = n;
    tail = n;
}

template<typename T>
void append_node_and_advance(shared_ptr<node_t<T>> &head, shared_ptr<node_t<T>> &tail, shared_ptr<node_t<T>> &n) {
    append_node(head, tail, n);
    n = n->next;
}

template<typename T>
shared_ptr<node_t<T>> merge_sorted_linked_lists(shared_ptr<node_t<T>> &F, shared_ptr<node_t<T>> &L) {
    shared_ptr<node_t<T>> sorted_head = nullptr, tail = nullptr;
    while (F && L) {
        apppend_node_and_advance(sorted_head, tail, F->data < L->data ? F : L);
    }
    
    if (F) append_node(sorted_head, tail, F);
    if (L) append_node(sorted_head, tail, L);
    
    return sorted_head;
}

// 7.2
template<typename T>
shared_ptr<node_t<T>> has_cycle(const shared_ptr<node_t<T>> &head) {
    shared_ptr<node_t<T>> slow = head, fast = head;
    
    while (slow && fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        
        // list is cyclic
        if (slow == fast) {
            int cycle_len = 0;
            do {
                ++cycle_len;
                fast = fast->next;
            } while (slow != fast);
            
            slow = head, fast = head;
            
            while (cycle_len--) {
                fast = fast->next;
            }
            
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            
            return slow;
        }
    }
    
    return nullptr;
}

// 7.4 my solution
template<typename T>
shared_ptr<node_t<T>> has_overlap(const shared_ptr<node_t<T>> &L1, const shared_ptr<node_t<T>> &L2) {
    int L1_len = 0, L2_len = 0;
    shared_ptr<node_t<T>> &L1_head = L1, &L2_head = L2;
    
    while (L1_head) {
        L1_len++;
        L1_head = L1_head->next;
    }
    
    while (L2_head) {
        L2_len++;
        L2_head = L2_head->next;
    }
    
    int L_diff = L2_len > L1_len ? L2_len - L1_len - 1 : L1_len - L2_len - 1;
    
    shared_ptr<node_t<T>> L_overlap = nullptr;
    if (L1_len < L2_len) {
        L_overlap = L1;
    } else {
        L_overlap = L2;
    }
    
    while (L_diff--) {
        L_overlap = L_overlap->next;
    }
    return L_overlap;
}

template<typename T>
int count_len(shared_ptr<node_t<T>> L) {
    int len = 0;
    while (L) {
        ++len;
        L = L->next;
    }
    return len;
}

template<typename T>
void advance_list_by_k(shared_ptr<node_t<T>> &L, int k) {
    while (k--) {
        L = L->next;
    }
}

template<typename T>
shared_ptr<node_t<T>> overlap_no_cycle(shared_ptr<node_t<T>> L1, shared_ptr<node_t<T>> L2) {
    int L1_len = count_len(L1), L2_len = count_len(L2);
    
    advance_list_by_k(L1_len > L2_len ? L1 : L2, abs(L1_len - L2_len));
    
    while (L1 && L2 && L1 != L2) {
        L1 = L1->next;
        L2 = L2->next;
    }
    
    return L1;
}

#endif /* defined(__EPI__Chapter7__) */
