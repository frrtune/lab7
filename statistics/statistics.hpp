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
};