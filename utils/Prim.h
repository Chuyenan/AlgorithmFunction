//
// Created by 14911 on 2023/4/16.
//

#ifndef C__TEST_PRIM_H
#define C__TEST_PRIM_H

#include <bits/stdc++.h>

using namespace std;

struct PointToPoint{
    int x, y, val;
    PointToPoint(int x, int y, int val): x(x), y(y), val(val) {}
    bool operator < (const PointToPoint& rhs) const {
        return val > rhs.val;
    }
};


class Prim {
    vector<bool> inMST;
    int weightsum = 0;
    priority_queue<PointToPoint> pq;
    void cut(vector<vector<PointToPoint>>& graph, int x) {
        for(auto& ptp: graph[x]) {
            int y = ptp.y;
            if(inMST[y]) continue;
            pq.push(ptp);
        }
    }
public:
    // 邻接表
    explicit Prim(vector<vector<PointToPoint>>& graph) {
        int n = graph.size();
        inMST.resize(n);

        inMST[0] = true;
        cut(graph, 0);

        while(!pq.empty()) {
            auto cur = pq.top();
            pq.pop();
            int y = cur.y, val = cur.val;
            if (inMST[y]) continue;
            inMST[y] = true;
            weightsum += val;
            cut(graph, y);
        }
    }

    int getWeightSum() const{
        if(haveMST())
            return weightsum;
        else
            return -1;
    }

    bool haveMST() const {
        return all_of(inMST.begin(), inMST.end(), [](auto x){ return x == true; });
    }

};


#endif //C__TEST_PRIM_H
