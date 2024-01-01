//
// Created by 14911 on 2023/10/9.
//

#ifndef HELPER_UNIONFIND_H
#define HELPER_UNIONFIND_H
#include <bits/stdc++.h>
using namespace std;

class UnionFind {
public:
    int count_ = 0;
    vector<int> parent_;
    explicit UnionFind(int count): count_(count) {
        parent_.resize(count);
        iota(parent_.begin(), parent_.end(), 0);
    }

    int find(int x) {
        if (x != parent_[x]) {
            parent_[x] = find(parent_[x]);
        }
        return parent_[x];
    }

    int merge(int x, int y) {
        auto rootx = find(x);
        auto rooty = find(y);
        if (rootx != rooty) {
            parent_[rooty] = rootx;
            count_--;
        }
    }

    bool isConnected(int x, int y) {
        return find(x) == find(y);
    }

    int getCount() const {
        return count_;
    }
};

#endif //HELPER_UNIONFIND_H
