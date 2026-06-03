#pragma once

#include "generator.hpp"

template<typename T>
class InsertAtGenerator : public Generator<T> {
    private:
        std::shared_ptr<Generator<T>> generator_;
        T item_;
        bool done_; 
};