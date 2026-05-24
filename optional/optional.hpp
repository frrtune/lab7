#pragma once

#include "../exceptions/exceptions.hpp"

template <typename T>
class Optional {
    private:
        T* value_;
    public:
        Optional() : value_(nullptr) {}
        Optional(const T& value) : value_(new T(value)) {}
        Optional(const Optional& other) : value_(nullptr) {
            if (other.value_) {
                value_ = new T(*other.value_);
            }
        }
        ~Optional() {
            delete value_;
        }
}