#pragma once

#include "../streams/read_only_stream.hpp"
#include "../optional/optional.hpp"
#include "../lab5/dynamic_array/dynamic_array.hpp"

template<typename T>
class Statistics {
    private:
        size_t count_;
        T sum_;
        T min_;
        T max_;
        DynamicArray<T> values_;
        size_t partition(DynamicArray<T>& arr, size_t low, size_t high) {
            T pivot = arr.Get(high);
            size_t i = low;
            for (size_t j = low; j < high; j++) {
                if (arr.Get(j) < pivot) {
                    T temporary = arr.Get(i);
                    arr.Set(i, arr.Get(j));
                    arr.Set(j, temporary);
                    i++;
                }
            }
            T temporary = arr.Get(i);
            arr.Set(i, arr.Get(high));
            arr.Set(high, temporary);
            return i;
        }
        void quick_sort(DynamicArray<T>& arr, size_t low, size_t high) {
            if (low >= high) return;
            size_t i = partition(arr, low, high);
            if (i > low) quick_sort(arr, low, i - 1);
            if (i + 1 < high) quick_sort(arr, i + 1, high);
        }
    public:
        Statistics() : count_(0), sum_(0), min_(0), max_(0) {}
        void add(const T& value) {
            if (count_ == 0) {
                min_ = value;
                max_ = value;
            } else {
                if (value < min_) min_ = value;
                if (value > max_) max_ = value;
            }
            sum_ += value;
            values_.PushBack(value);
            count_++;
        }
};