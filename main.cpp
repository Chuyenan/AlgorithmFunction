#include <bits/stdc++.h>

using namespace std;

#include "helper/QuickSort.h"
#include "helper/MergeSort.h"
#include "helper/HeapSort.h"

//��������ģʽ
template<class T>
class SingLeton {
public:
    // ���ö��� data
    static T *getsingleton() {
        return &data;
    }

private:
    //���໹û��ʵ��������ǰ����һ��������
    static T data;
};

void string_sizeof(char szStr1[10]) {
    char szStr2[10] = "12345";
    printf("%u, ", sizeof(szStr1));
    printf("%u\r\n ", sizeof(szStr2));
}

#define pui_t2 unsigned int *

class A {
private:
    int a;
public:

};

int main() {
    vector<int> nums;
    default_random_engine e;
    e.seed(time(0));
    uniform_int_distribution uid(2, 20);
    for (int i = 0; i < 10; ++i) {
        nums.push_back(uid(e));
    }
    auto nums2 = nums;
    auto nums3 = nums;
    // ����
    cout << "���Ž����" << endl;
    QuickSort::print(nums);
    QuickSort::qSort(nums);
    QuickSort::print(nums);
    // ����
    cout << "���Ž����" << endl;
    MergeSort::print(nums2);
    MergeSort::mSort(nums2);
    MergeSort::print(nums2);
    // ����
    cout << "���Ž����" << endl;
    HeapSort::print(nums3);
    HeapSort::hSort(nums3);
    atomic<int> a;
}