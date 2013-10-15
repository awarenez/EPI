//
//  Chapter17.h
//  EPI
//
//  Created by Chih-Yang Chang on 10/5/13.
//  Copyright (c) 2013 Chih-Yang Chang. All rights reserved.
//

#ifndef __EPI__Chapter17__
#define __EPI__Chapter17__

#include <iostream>
#include <vector>

using namespace std;

// 17.2 Knapsack problem
struct Item {
    int value;
    int weight;
};

template<typename ValueType>
ValueType Knapsack(const int &w, const vector<pair<int, ValueType>> &items) {
    vector<ValueType> v;
    for (int i = 0; i < items.size(); i++) { // clocks
        for (int j = w; j >= items[i].first; j--) { // weight
            v[j] = max(v[j], v[j - items[i].first] + items[i].second);
        }
    }
    return v[w];
}

#endif /* defined(__EPI__Chapter17__) */
