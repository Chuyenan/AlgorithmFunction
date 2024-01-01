//
// Created by 14911 on 2023/4/11.
//

#ifndef C__TEST_QUICKSORT_H
#define C__TEST_QUICKSORT_H

#include <bits/stdc++.h>

using namespace std;

class QuickSort {
    int partition(vector<int>& nums, int start, int end) {
        int left = start - 1;
        for(int i = start; i <= end; i++) {
            if(nums[i] < nums[end]) {
                swap(nums[++left], nums[i]);
            }
        }
        swap(nums[++left], nums[end]);
        return left;
    }
    int random_partition(vector<int>& nums, int start, int end) {
        int pos = rand() % (end - start + 1) + start;
        swap(nums[pos], nums[end]);
        return partition(nums, start, end);
    }
    void q_sort(vector<int>& nums, int start, int end) {
        if(start >= end) return;
        int pos = random_partition(nums, start, end);
        q_sort(nums, start, pos - 1);
        q_sort(nums, pos + 1, end);
    }
public:

    vector<int> quick(vector<int>& nums) {
        int n = nums.size();
        q_sort(nums, 0, n - 1);
        return nums;
    }
};


#endif //C__TEST_QUICKSORT_H
