//
// Created by 14911 on 2023/4/16.
//

#ifndef C_TEST_LRUCACHE_H
#define C_TEST_LRUCACHE_H

#include "bits/stdc++.h"

using namespace std;


class LRUCache {
    list<int> times;
    unordered_map<int, int> lru;
    unordered_map<int, int> exist;
    int capacity = 0;

public:
    explicit LRUCache(int capacity): capacity(capacity) {
    }

    int get(int key) {
        if(lru.count(key)) {
            times.push_front(key);
            exist[key]++;
            return lru[key];
        }
        return -1;
    }

    void put(int key, int value) {
        if(lru.count(key)) {
            lru[key] = value;
            times.push_front(key);
            exist[key]++;
        }
        else {
            int size = lru.size();
            if(size == capacity) {
                int old_key = times.back();
                while(exist[old_key] > 1) {
                    exist[old_key]--;
                    times.pop_back();
                    old_key = times.back();
                }
                times.pop_back();
                exist[old_key]--;
                lru.erase(old_key);
            }
            lru[key] = value;
            times.push_front(key);
            exist[key]++;
        }
    }
};

#endif //C_TEST_LRUCACHE_H
