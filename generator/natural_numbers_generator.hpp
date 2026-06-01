#pragma once

#include "generator.hpp"

template<typename T>
class NaturalNumbersGenerator : public Generator<T> {
    private:
        long long current_;
        long long limit_;
    public:
        NaturalNumbersGenerator(long long limit) : current_(0), limit_(limit) {}
};