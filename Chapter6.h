//
//  Chapter6.h
//  EPI
//
//  Created by Chih-Yang Chang on 10/6/13.
//  Copyright (c) 2013 Chih-Yang Chang. All rights reserved.
//

#ifndef __EPI__Chapter6__
#define __EPI__Chapter6__

#include <iostream>

#include <vector>
#include <algorithm>
#include <string>
#include <array>
using namespace std;


// 6.1
template<typename T>
void rearrange(vector<T> &A, const int &pivot_index) {
    T pivot = A[pivot_index];
    int smaller = 0, equal = 0, larger = A.size() - 1;
    // one pass
    while (equal <= larger) {
        if (A[equal] < pivot) {
            swap(A[smaller++], A[equal++]);
        } else if (A[equal] == pivot) {
            equal++;
        } else {
            swap(A[equal], A[larger--]);
        }
    }
}

// 6.14

// 6.22
const array<string, 10> M = {"0", "1", "ABC", "DEF", "GHI", "JKL", "MNO", "PQRS", "TUV", "WXYZ"};
void phone_mnemonic_helper(const string &num, const int &d, string &ans) {
    if (d == num.size())
        cout << ans << endl;
    else {
        for (const char &c : M[num[d] - '0']) {
            ans[d] = c;
            phone_mnemonic_helper(num, d + 1, ans);
        }
    }
}

void phone_monemonic(const string &num) {
    string ans(num.size(), 0);
    phone_mnemonic_helper(num, 0, ans);
}

#endif /* defined(__EPI__Chapter6__) */
