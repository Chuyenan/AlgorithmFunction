//
// Created by 14911 on 2023/4/9.
//

#ifndef C__TEST_MAXHEAP_H
#define C__TEST_MAXHEAP_H

#include <iostream>
#include "cstring"

template <typename T>
class MaxHeap {
private:
    int _size;
    int _pos;
    T* heap;
public:
    MaxHeap(): _size(0), _pos(-1), heap(nullptr) {};
//    ~MaxHeap() { delete [] heap; };
    void insert(const T& val) {
        _pos++;
        if(_pos >= _size) {
            int new_size = _size + 10;
            std::cout<<"out of range! enlarge heap size to:" << new_size <<std::endl;
            T* tem = new T[new_size];
            for(int i=0;i<_pos;i++){
                *(tem + i) = *(heap + i);
            }
            delete [] heap;
            heap = tem;
            _size = new_size;
        }
        heap[_pos] = val;
        int child = _pos, parent = (child - 1) / 2;
        while(parent > 0) {
            if(heap[child] > heap[parent]) {
                std::swap(heap[child], heap[parent]);
                child = parent;
                parent = child <= 1 ? -1 : (child - 1) / 2;
            }else break;
        }
    }
    const T& top() const {
        if(_pos >= 0)
            return heap[0];
        throw "empty!";
    }
    const T& bottom() const {
        return heap[_pos];
    }
    bool empty() {
        return _pos < 0;
    }
    bool pop() {
        if(_pos < 0) {
            std::cout<< "empty heap!"<<std::endl;
            return false;
        }
        std::swap(heap[0], heap[_pos]);
        _pos--;
        int parent = 0, child = 2 * parent + 1;
        while(child <= _pos) {
            if(child + 1 < _pos && heap[child + 1] > heap[child])
                child += 1;
            if(heap[parent] < heap[child]) {
                std::swap(heap[parent], heap[child]);
                parent = child;
                child = parent * 2 + 1;
            }else break;
        }
        return true;
    }
    [[nodiscard]] const int& size() const{
        return _pos;
    }
    [[nodiscard]] const int& capacity() const {
        return _size;
    }
    T& operator[](int index) const {
        return heap[index];
    }
    void print() const {
        std::cout<<"capacity: "<<capacity()<<" , size: "<<size()<<std::endl;
        std::cout<<"cur heap item: ";
        for (int i = 0; i <= _pos; ++i) {
            std::cout<<heap[i]<<" ";
        }
        std::cout<<std::endl;
    }
};


#endif //C__TEST_MAXHEAP_H
