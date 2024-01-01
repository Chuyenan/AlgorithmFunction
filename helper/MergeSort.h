//
// Created by 14911 on 2023/10/9.
//

#ifndef C_TEST_MERGESORT_H
#define C_TEST_MERGESORT_H
#include <bits/stdc++.h>
using namespace std;

class MergeSort {
public:
    static void mSort(vector<int>& vec) {
        auto n = vec.size();
        msHelper(vec, 0, n);
    }
    static void msHelper(vector<int>& vec, int start, int end) {
        if (start >= end - 1) return;
        auto mid = start + ((end - start) >> 1);
        msHelper(vec, start, mid);
        msHelper(vec, mid, end);
        merge(vec, start, end);
    }
    static void merge(vector<int>& vec, int start, int end) {
        auto tmp = vec;
        int mid = start + ((end - start) >> 1);
        int left = start, right = mid;
        int pos = start;
        while (left < mid || right < end) {
            if (left == mid) vec[pos++] = tmp[right++];
            else if (right == end) vec[pos++] = tmp[left++];
            else {
                if (tmp[left] < tmp[right]) {
                    vec[pos++] = tmp[left++];
                } else {
                    vec[pos++] = tmp[right++];
                }
            }
        }
    }
    static void print(const vector<int>& vec) {
        for (auto i: vec) {
            cout << i << " ";
        }
        cout << endl;
    }
};

#endif //C_TEST_MERGESORT_H
