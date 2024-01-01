//
// Created by 14911 on 2023/10/9.
//

#ifndef HELPER_HEAPSORT_H
#define HELPER_HEAPSORT_H
#include <bits/stdc++.h>
using namespace std;

class HeapSort {
public:
    static void hSort(vector<int>& vec) {
        auto n = vec.size();
        generate(vec);
        output();
    }
    static void print(const vector<int>& vec) {
        for (auto i: vec) {
            cout << i << " ";
        }
        cout << endl;
    }
    static void generate(vector<int>& vec) {
        auto n = vec.size();
        heap.reserve(n);
        auto modify = [&]() {
            auto sz = heap.size();
            if (sz == 1 || sz == 0) return;
            auto child = sz - 1, parent = (child - 1) >> 1;
            while (child > 0) {
                if (heap[child] < heap[parent]) {
                    swap(heap[child], heap[parent]);
                }
                child = parent, parent = (child - 1) /2;
            }
        };
        for (auto i = 0; i < n; ++i) {
            heap.emplace_back(vec[i]);
            modify();
        }
    }
    static void output() {
        auto n = heap.size();

        auto modify = [&]() {
            auto sz = heap.size();
            if (sz == 0 || sz == 1) return;
            auto parent = 0, child = (parent << 1) + 1;
            while (child < sz) {
                if (child + 1 < sz && heap[child] > heap[child + 1]) {
                    child += 1;
                }
                if (heap[child] < heap[parent]) {
                    swap(heap[parent], heap[child]);
                }
                parent = child, child = (parent << 1) + 1;
            }
        };

        for (int i = 0; i < n; ++i) {
            swap(heap.front(), heap.back());
            cout << heap.back() << " ";
            heap.pop_back();
            modify();
        }
        cout << endl;
    }
    static vector<int> heap;
};
vector<int> HeapSort::heap = {};
#endif //HELPER_HEAPSORT_H
