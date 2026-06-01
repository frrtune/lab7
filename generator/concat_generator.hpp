#pragma once

#include "generator.hpp"

template<typename T>
class ConcatGenerator : public Generator<T> {
    private:
        std::shared_ptr<Generator<T>> first_;
        std::shared_ptr<Generator<T>> second_;
        bool first_done_; 
    public:
        InsertGenerator(std::shared_ptr<Generator<T>> first, std::shared_ptr<Generator<T>> second) :
        first_(first), second_(second), first_done_(false) {}
};