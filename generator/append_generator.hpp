#pragma once

#include "generator.hpp"

template<typename T>
class AppendGenerator : public Generator<T> {
    private:
        std::shared_ptr<Generator<T>> generator_;
        T item_;
        bool done_; 
    public:
        AppendGenerator(std::shared_ptr<Generator<T>> generator, I item) : generator_(generator), done_(false) {}
};