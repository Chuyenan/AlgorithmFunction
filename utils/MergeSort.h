//
// Created by 14911 on 2023/4/11.
//

#ifndef C__TEST_MERGESORT_H
#define C__TEST_MERGESORT_H

#include "bits/stdc++.h"

using namespace std;

class MergeSort {
    vector<int> tem;
    void merge(vector<int>& nums, int start, int end, int mid) {
        for(int i = start; i < end; i++) {
            tem[i] = nums[i];
        }
        int left = start, right = mid;
        int pos = start;
        while(pos < end) {
            if(left == mid) {
                nums[pos++] = tem[right++];
            }else if(right == end) {
                nums[pos++] = tem[left++];
            }else{
                if(tem[left] <= tem[right]) {
                    nums[pos++] = tem[left++];
                }else
                    nums[pos++] = tem[right++];
            }
        }
    }

    void helper(vector<int>& nums, int start, int end, int mid) {
        if(start == mid) return;
        helper(nums, start, mid, ((mid - start) >> 1) + start);
        helper(nums, mid, end, ((end - mid) >> 1) + mid);
        merge(nums, start, end, mid);
    }
public:
    vector<int> mergeSort(vector<int>& nums) {
        int n = nums.size();
        tem.resize(n);
        helper(nums, 0, n, n >> 1);
        return nums;
    }
};


#endif //C__TEST_MERGESORT_H
