#pragma once

#include "../lab5/exceptions/exceptions.hpp"

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
        bool operator==(const Ordinal& other) const {
            if (type_ != other.type_) return false;
            if (type_ == OrdinalType::Finite) return value_ == other.value_;
            return true;
        }
        bool operator!=(const Ordinal& other) const {
            return !(*this == other);
        }
        bool operator<(const Ordinal& other) const {
            if (type_ == OrdinalType::Zero) return !other.IsZero();
            if (type_ == OrdinalType::Finite) {
                if (other.type_ == OrdinalType::Zero) return false;
                if (other.type_ == OrdinalType::Finite) return value_ < other.value_;
                return true;
            }
            return false;
        }
        bool operator>(const Ordinal& other) const {
            return other < *this;
        }
        bool operator<=(const Ordinal& other) const {
            return !(*this > other);
        }
        bool operator>=(const Ordinal& other) const {
            return !(*this < other);
        }
        Ordinal operator+(const Ordinal& other) const {
            if (IsTransfinite() && other.IsFinite()) {
                return *this;
            }
            if (IsFinite() && other.IsTransfinite()) {
                return other;
            }
            if (IsZero()) return other;
            if (other.IsZero()) return *this;
            if (IsFinite() && other.IsFinite()) {
                size_t new_value = value_ + other.value_;
                return Ordinal(new_value);
            }
            return *this;
        }
        Ordinal operator+(size_t value) const {
            if (IsTransfinite()) {
                return *this;
            }
            return Ordinal(GetValue() + value);
        }
        Ordinal operator*(const Ordinal& other) const {
            if (IsZero() || other.IsZero()) {
                return Ordinal(0);
            }
            if (IsTransfinite() && other.IsFinite()) {
                if (other.value_ == 0) return Ordinal(0);
                return *this;
            }
            if (IsFinite() && other.IsTransfinite()) {
                if (value_ == 0) return Ordinal(0);
                return other;
            }
            if (IsFinite() && other.IsFinite()) {
                size_t new_value = value_ * other.value_;
                return Ordinal(new_value);
            }
            return *this;
        }
};