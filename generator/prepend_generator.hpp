#pragma once

#include "generator.hpp"

template<typename T>
class PrependGenerator : public Generator<T> {
    private:
        std::shared_ptr<Generator<T>> generator_;
        T item_;
};