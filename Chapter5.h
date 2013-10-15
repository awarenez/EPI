//
//  Chapter5.h
//  EPI
//
//  Created by Chih-Yang Chang on 10/5/13.
//  Copyright (c) 2013 Chih-Yang Chang. All rights reserved.
//

#ifndef __EPI__Chapter5__
#define __EPI__Chapter5__

#include <iostream>
#include <vector>

using namespace std;

// C0
// 5.1
short parity(unsigned long x) { // 64-bit non-negative val
    short result = 0;
    while (x) {
        result ^= 1;
        x &= (x - 1);
    }
    return result;
}


// C1
// 5.2
long swap(long x, int i, int j) {
    // swap only when the bit at i and j are different
    if ( ((x >> i) & 1) != ((x >> j) & 1)) {
        x ^= ((1L << i) | (1L << j));
    }
    return x;
}

// 5.5
template<typename T>
void generate_powerset_helper(const vector<T> &S, int idx, vector<T> &res) {
    if (res.empty() == false) {
        // print subset
        
    }
    for (int i = idx; i < S.size(); i++) {
        res.emplace(S[i]);
        powerset(S, i + 1, res);
        res.pop_back();
    }
}

template<typename T>
void generate_powerset(const vector<T> &S) {
    vector<T> res;
    generate_powerset_helper(S, 0, res);
}

// 5.6
string intToString(int x) {
    bool is_negative = false;
    
    if (x < 0) {
        is_negative = true;
        x = -x;
    }
    
    string s;
    
    while (x) {
        s.push_back('0' + x % 10);
        x /= 10;
    }
    
    if (s.empty()) return s;
    
    if (is_negative) {
        s.push_back('-');
    }
    
    reverse(s.begin(), s.end());
    return s;
}

int stringToInt(string s) {
    bool is_negative = s[0] == '-';
    
    int x = 0;
    for (int j = is_negative; j < s.length(); j++) {
        if (isdigit(s[j]))
            x = x * 10 + (s[j] - '0');
        else
            throw invalid_argument("illegal input");
    }
    
    return is_negative ? -x : x;
}

#endif /* defined(__EPI__Chapter5__) */
