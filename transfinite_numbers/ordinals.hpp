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
        static Ordinal omega() {
            Ordinal o;
            o.type_ = OrdinalType::Transfinite;
            o.value_ = 0;
            return o;
        }
        bool IsZero() const { 
            return type_ == OrdinalType::Zero; 
        }
        bool IsFinite() const {
            return type_ == OrdinalType::Finite; 
        }
        bool IsTransfinite() const {
            return type_ == OrdinalType::Transfinite; 
        }
        size_t GetValue() const {
            if (!IsFinite()) {
                throw OrdinalError("ordinal is not finite");
            }
            return value_;
        }
};