//
//  Chapter12.h
//  EPI
//
//  Created by Chih-Yang Chang on 10/3/13.
//  Copyright (c) 2013 Chih-Yang Chang. All rights reserved.
//

#ifndef __EPI__Chapter12__
#define __EPI__Chapter12__

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

// 12.9
bool composeLfromM(const string &L, const string &M) {
    // construct the table for L
    unordered_map<char, int> hash;
    for_each(L.begin(), L.end(), [&hash](const char &c) { ++hash[c];});
    // loop over M and see if L can be composed of M
    for (const char &c : M) {
        auto it = hash.find(c);
        if (it != hash.cend()) {
            if (--it->second == 0) {
                hash.erase(it);
                if (hash.empty() == true) return true;
            }
        }
    }
    return hash.empty();
}

// 12.1
// examine each word
int string_hash(const string &str, const int &modulus) {
    const int MULT = 997;
    int val = 0;
    for (const char &c : str) {
        val = (val * MULT + c) % modulus;
    }
    return val;
}


// 12.7, Anagrams
void find_anagrams(const vector<string> &dict) {
    unordered_map<string, vector<string>> hash;
    
    for (const string &word : dict) {
        string key(word);
        sort(key.begin(), key.end());
        hash[key].emplace_back(word);
    }
    
    for (const pair<string, vector<string>> &p : hash) {
        if (p.second.size() >= 2) {
            copy(p.second.begin(), p.second.end(),
                  ostream_iterator<string>(cout, " "));
            cout << endl;
        }
    }
}

#endif /* defined(__EPI__Chapter12__) */
