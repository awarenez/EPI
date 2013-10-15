//
//  Chapter15.h
//  EPI
//
//  Created by Chih-Yang Chang on 10/5/13.
//  Copyright (c) 2013 Chih-Yang Chang. All rights reserved.
//

#ifndef __EPI__Chapter15__
#define __EPI__Chapter15__

#include <iostream>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

// 15.11
int Levenshtein_distance(string A, string B) {
    // try to reduce the space usage
    if (A.size() < B.size()) {
        swap(A, B);
    }
    
    vector<int> D(B.size() + 1);
    // Initialization
    iota(D.begin(), D.end(), 0);
    
    for (int i = 1; i <= A.size(); ++i) {
        int pre_i_1_j_1 = D[0]; // stores the value of D[i-1][j-1]
        D[0] = i;
        for (int j = 1; j <= B.size(); ++j) {
            int pre_i_1_j = D[j];
            D[j] = A[i-1] == B[j-1] ?
            pre_i_1_j_1 : 1 + min(pre_i_1_j_1, min(D[j-1], D[j]));
            pre_i_1_j_1 = pre_i_1_j;
        }
    }
    return D.back();
}

#endif /* defined(__EPI__Chapter15__) */
