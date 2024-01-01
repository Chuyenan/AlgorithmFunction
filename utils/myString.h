//
// Created by 14911 on 2023/9/18.
//

#ifndef C_TEST_MYSTRING_H
#define C_TEST_MYSTRING_H

#include "bits/stdc++.h"
using namespace std;

class myString {
private:
    size_t size_;
    char* str_{};
public:
    myString(): size_(0) { str_ = nullptr; };
    explicit myString(const char* str): myString() {
        if (str) {
            delete[] this->str_;
            this->size_ = strlen(str);
            str_ = new char[size_ + 1];
            for (int i = 0; i < size_; ++i) {
                *(str_ + i) = *(str + i);
            }
            str_[size_] = '\0';
        }
    }
    ~myString() {
        delete[] this->str_;
    }
    myString(const myString& mystr): myString(mystr.c_str()) {}
    myString& operator= (const myString& rv) {
        if (this == &rv) return *this;
        this->size_ = rv.size();
        auto tmp = rv.c_str();
        delete[] this->str_;
        this->str_ = new char[size_ + 1];
        for (int i = 0; i < size_; i++) {
            *(str_ + i) = *(tmp + i);
        }
        this->str_[size_] = '\0';
        return *this;
    }
    char& operator[](size_t pos) const {
        return *(this->str_ + pos);
    }
    [[nodiscard]] const char* c_str() const{
        return str_;
    }
    [[nodiscard]] size_t size() const{
        return size_;
    }
    void print() const {
        cout << this->size() << " " << this->c_str() << endl;
    }
};

#endif //C_TEST_MYSTRING_H
