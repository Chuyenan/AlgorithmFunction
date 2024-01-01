//
// Created by 14911 on 2023/4/16.
//

#ifndef C__TEST_KRUSKAL_H
#define C__TEST_KRUSKAL_H

#include <bits/stdc++.h>
#include "UnionFind.h"

using namespace std;

struct PointToPoint{
    int x, y, val;
    PointToPoint(int x, int y, int val): x(x), y(y), val(val) {}
};

class Kruskal {
    vector<PointToPoint> edge;
public:
    // 邻接矩阵
    int getMinTreeVal(vector<vector<int>>& graph) {
        int n = static_cast<int>(graph.size());
        UnionFind uf(n);
        int res = 0;
        for (int i = 0; i < n - 1; ++i) {
            for (int j = i + 1; j < n; ++j) {
                edge.emplace_back(i, j, abs(graph[i][0] - graph[j][0]) + abs(graph[i][1] - graph[j][1]));
            }
        }
        sort(edge.begin(), edge.end(), [](PointToPoint& a, PointToPoint& b) { return a.val < b.val; });
        for(auto& ptp : edge) {
            int x = ptp.x, y = ptp.y, val = ptp.val;
            if(uf.is_connected(x, y)) continue;
            res += val;
            uf.merge(x, y);
        }
        return uf.get_count() == 1 ? res : -1;
    }

};


#endif //C__TEST_KRUSKAL_H
