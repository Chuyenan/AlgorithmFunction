//
// Created by 14911 on 2023/4/16.
//

#ifndef C__TEST_LRU_AUTOPTR_H
#define C__TEST_LRU_AUTOPTR_H

#include "bits/stdc++.h"

struct DLinkedNode {
    int key, val;
    std::weak_ptr<DLinkedNode> prev;
    std::weak_ptr<DLinkedNode> next;
    DLinkedNode(): key(0), val(0) {}
    DLinkedNode(int key, int val): key(key), val(val) {}
};

class LRUCache {
    std::unordered_map<int, std::shared_ptr<DLinkedNode>> cache;
    std::shared_ptr<DLinkedNode> head;
    std::shared_ptr<DLinkedNode> tail;
    int capacity;
    int size = 0;
    static void removeNode(const std::shared_ptr<DLinkedNode>& node) {
        node->prev.lock()->next = node->next;
        node->next.lock()->prev = node->prev;
    }
    void addToHead(const std::shared_ptr<DLinkedNode>& node) {
        node->prev = head;
        node->next = head->next;
        head->next.lock()->prev = node;
        head->next = node;
    }
    void moveToHead(const std::shared_ptr<DLinkedNode>& node) {
        removeNode(node);
        addToHead(node);
    }
    std::shared_ptr<DLinkedNode> removeFromTail() {
        auto tail_node = tail->prev.lock();
        removeNode(tail_node);
        return tail_node;
    }
public:
    explicit LRUCache(int capacity): capacity(capacity), size(0) {
        head = std::make_shared<DLinkedNode>(DLinkedNode());
        tail = std::make_shared<DLinkedNode>(DLinkedNode());
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if(cache.count(key)) {
            auto node = cache[key];
            moveToHead(node);
            return node->val;
        }else {
            return -1;
        }
    }

    void put(int key, int value) {
        if(!cache.count(key)) {
            std::shared_ptr<DLinkedNode> node = std::make_shared<DLinkedNode>(DLinkedNode(key, value));
            cache[key] = node;
            addToHead(node);
            ++size;
            if(size > capacity) {
                std::shared_ptr<DLinkedNode> removed = removeFromTail();
                cache.erase(removed->key);
                --size;
            }
        }else {
            auto node = cache[key];
            node->val = value;
            moveToHead(node);
        }
    }
};



#endif //C__TEST_LRU_AUTOPTR_H
