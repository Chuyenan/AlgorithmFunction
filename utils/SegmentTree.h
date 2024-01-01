//
// Created by 14911 on 2023/9/12.
//

#ifndef C__TEST_SEGMENTTREE_H
#define C__TEST_SEGMENTTREE_H

#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
public:
    SegmentTree() = default;
    ~SegmentTree() = default;
    explicit SegmentTree(vector<int> rawTree): rawSize_(rawTree.size()), rawTree_(std::move(rawTree)) {
        auto sz = static_cast<int>(ceil(pow(2.0, ceil(log(rawSize_) / log(2)) + 1) - 1));
        segmentTree_.resize(sz);
        status_.resize(sz);
    }

    /**
     * 构建线段树
     * @param start 当前下标所覆盖的原始数组的起始索引
     * @param end 当前下标所覆盖的原始数组的终止索引
     * @param pos 当前下标
     * @return 原始数组的和
     */
    int build(int start, int end, int pos) {
        if (start > end) return -1;
        if (start == end) {
            return segmentTree_[pos] = rawTree_[start];
        }
        auto left = build(start, (start + end) >> 1, (pos << 1) + 1);
        auto right = build(((start + end) >> 1) + 1, end, (pos << 1) + 2);
        return segmentTree_[pos] = left + right;
    }

    /**
     *
     * @param left 查询左边界
     * @param right 查询右边界
     * @param start 当前下标覆盖的左边界
     * @param end 当前下标覆盖的右边界
     * @param pos 当前下标值
     * @return 返回区间和
     */
    int sumInterval(int left, int right, int start, int end, int pos) {
        if (left <= start && right >= end) {
            return segmentTree_[pos];
        }
        int mid = ((start + end) >> 1), ret = 0;
        if (status_[pos] != 0) {
            segmentTree_[pos * 2 + 1] += status_[pos], segmentTree_[pos * 2 + 2] += status_[pos];
            status_[pos * 2 + 1] += status_[pos], status_[pos * 2 + 2] += status_[pos];
            status_[pos] = 0;
        }
        if (left <= mid) ret += sumInterval(left, mid, start, mid, (pos << 1) + 1);
        if (mid + 1 <= right) ret += sumInterval(mid + 1, right, mid + 1, end, (pos << 1) + 2);
        return ret;
    }

    /**
     *
     * @param left 更新的左边界
     * @param right 更新的右边界
     * @param upd 更新的变值
     * @param start 当前索引的左边界
     * @param end 当前索引的右边界
     * @param pos 当前索引值
     */
    void modify(int left, int right, int upd, int start, int end, int pos) {
        if (left <= start && right >= end) {
            status_[pos] += upd, segmentTree_[pos] += upd * (end - start + 1);
            return;
        }
        int mid = (end + start) >> 1;
        if (status_[pos] != 0 && start != end) {
            segmentTree_[pos * 2 + 1] += status_[pos] * (mid - start), segmentTree_[pos * 2 + 2] += status_[pos] * (end - mid);
            status_[pos * 2 + 1] += status_[pos], status_[pos * 2 + 2] += status_[pos];
            status_[pos] = 0;
        }
        if (left <= mid) modify(left, mid, upd, start, mid, pos * 2 + 1);
        if (right > mid) modify(mid + 1, right, upd, mid + 1, end, pos * 2 + 2);
    }

    void getMax() {};

    void getMin() {};

    void print() {
        for (auto item : segmentTree_) {
            cout << item << " ";
        }
        cout << endl;
    }
private:
    size_t rawSize_{};
    vector<int> segmentTree_;
    vector<int> rawTree_;
    vector<int> status_;
    vector<int> mn, mx;
};

#endif //C__TEST_SEGMENTTREE_H
