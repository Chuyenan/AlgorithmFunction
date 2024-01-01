//
// Created by 14911 on 2023/10/9.
//
/**
 * Least Recently Used
 */
#ifndef HELPER_LRUCACHE_H
#define HELPER_LRUCACHE_H
#include <bits/stdc++.h>
using namespace std;

struct ListNode1 {
    int val_;
    int key_;
    ListNode1* next_;
    ListNode1* prev_;
    ListNode1(): val_(-1), key_(-1), next_(nullptr), prev_(nullptr){}
    ListNode1(int key, int val): val_(val), key_(key), next_(nullptr), prev_(nullptr){}
};

class LRUCache {
private:
    ListNode1* head_;
    ListNode1* tail_;
    unordered_map<int, ListNode1*> cache_;
    int sz_;

    static void removeNode(ListNode1* node) {
        node->prev_->next_ = node->next_;
        node->next_->prev_ = node->prev_;
    }
    void moveToHead(ListNode1* node) {
        removeNode(node);
        addToHead(node);
    }

    void addToHead(ListNode1* node) {
        head_->next_->prev_ = node;
        node->next_ = head_->next_;
        node->prev_ = head_;
        head_->next_ = node;
    }

    int removeTail() {
        auto target = tail_->prev_;
        auto key = target->key_;
        removeNode(target);
        return key;
    }

public:

    explicit LRUCache(int sz): sz_(sz) {
        head_ = new ListNode1();
        tail_ = new ListNode1();
        head_->next_ = tail_;
        tail_->prev_ = head_;
    }

    void put(int key, int val) {
        if (cache_.find(key) != cache_.end()) {
            cache_[key]->val_ = val;
            moveToHead(cache_[key]);
            return;
        }
        auto node = new ListNode1(key, val);
        addToHead(node);
        cache_[key] = node;
        if (cache_.size() > sz_) {
            auto k = removeTail();
            cache_.erase(k);
        }
    }

    int get(int key) {
        if (cache_.find(key) != cache_.end()) {
            moveToHead(cache_[key]);
            return cache_[key]->val_;
        }
        return -1;
    }
};

#endif //HELPER_LRUCACHE_H
