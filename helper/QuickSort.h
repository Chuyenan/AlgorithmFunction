//
// Created by 14911 on 2023/10/9.
//

#ifndef C_TEST_QUICKSORT_H
#define C_TEST_QUICKSORT_H

#include "bits/stdc++.h"
using namespace std;

class QuickSort {
public:
    static void qSort(vector<int>& vec) {
        auto n = vec.size();
        qsHelper(vec, 0, n - 1);
    }
    static void qsHelper(vector<int>& vec, int start, int end) {
        if (start >= end) return;
        auto pos = handle(vec, start, end);
        qsHelper(vec, start, pos - 1);
        qsHelper(vec, pos + 1, end);
    }
    static int handle(vector<int>& vec, int start, int end) {
        int ret = start - 1;
        for (int i = start; i <= end; ++i) {
            if (vec[i] < vec[end]) {
                swap(vec[++ret], vec[i]);
            }
        }
        swap(vec[++ret], vec[end]);
        return ret;
    }
    static void print(const vector<int>& vec) { 
        for (auto i: vec) {
            cout << i << " ";
        }
        cout << endl;
    }
};

#endif //C_TEST_QUICKSORT_H
