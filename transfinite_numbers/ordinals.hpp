#pragma once

#include "../exceptions/exceptions.hpp"

class Ordinal {
    private: 
        enum class OrdinalType {
            Zero,
            Finite,
            Transfinite
        };
        OrdinalType type_;
        size_t value_;
    public:
        Ordinal() : type_(OrdinalType::Zero), value_(0) {}
        Ordinal(size_t value) : type_(OrdinalType::Finite), value_(value) {}      
};