cmake_minimum_required(VERSION 3.24)
project(C__Test)

set(CMAKE_CXX_STANDARD 17)

add_executable(C__Test main.cpp utils/readlist.cpp test1.cpp utils/MaxHeap.cpp utils/MaxHeap.h utils/QuickSort.cpp utils/quickSort.h utils/MergeSort.cpp utils/MergeSort.h utils/UnionFind.cpp utils/UnionFind.h utils/Kruskal.cpp utils/Kruskal.h utils/Prim.cpp utils/Prim.h utils/LRUCache.cpp utils/LRUCache.h utils/LRU_autoptr.cpp utils/LRU_autoptr.h utils/SegmentTree.h utils/myString.h
        helper/QuickSort.h
        helper/MergeSort.h
        helper/HeapSort.h
        helper/UnionFind.h
        helper/LRUCache.h
)
