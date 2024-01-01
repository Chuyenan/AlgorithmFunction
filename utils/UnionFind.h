//
// Created by 14911 on 2023/4/11.
//

#ifndef C__TEST_UNIONFIND_H
#define C__TEST_UNIONFIND_H

#include "bits/stdc++.h"

using namespace std;

class UnionFind {
    int count;
    vector<int> parent;
public:
    UnionFind(): count(0), parent({}) {}
    explicit UnionFind(const int n): count(n) {
        parent.reserve(n);
        for (int i = 0; i < n; ++i) {
            parent.emplace_back(i);
        }
    }

    int get_count() const {
        return count;
    }

    int find(const int child) {
        if(parent[child] != child) {
            parent[child] = find(parent[child]);
        }
        return parent[child];
    }

    void merge(const int childA, const int childB) {
        int rootA = find(childA);
        int rootB = find(childB);
        if(rootA == rootB) return;
        parent[rootB] = rootA;
        count--;
    }

    bool is_connected(const int a, const int b) {
        return find(a) == find(b);
    }
};


#endif //C__TEST_UNIONFIND_H
