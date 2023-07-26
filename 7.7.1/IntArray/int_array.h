//
// Created by arseniy on 26.07.23.
//
#pragma once

class IntArray {
public:
    IntArray(int max_size);
    IntArray(const IntArray &other);
    int& operator[](int index);
    IntArray& operator=(const IntArray &other);
    friend std::ostream &operator<<(std::ostream &output, const IntArray &arr );
    void push_back(int new_element);
    void push_front(int new_element);
    void resize(int new_max_size);
    int find(int element) const;
    void remove(int index);
    ~IntArray();

private:
    int _max_size, _current_size;
    int *_array;
};
