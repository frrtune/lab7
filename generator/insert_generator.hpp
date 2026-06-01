#pragma once

#include "generator.hpp"

template<typename T>
class InsertGenerator : public Generator<T> {
    private:
        std::shared_ptr<Generator<T>> first_;
        std::shared_ptr<Generator<T>> second_;
        size_t insert_index_;
        size_t current_index_;
    public:
        InsertGenerator(std::shared_ptr<Generator<T>> first, std::shared_ptr<Generator<T>> second, size_t insert_index) :
        first_(first), second_(second), insert_index_(insert_index), current_index_(0) {}
};