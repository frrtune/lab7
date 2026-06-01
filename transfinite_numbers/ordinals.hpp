#pragma once

#include "../lab5/exceptions/exceptions.hpp"

class Ordinal {
    private: 
        enum class OrdinalType {
            Zero,
            Finite,
            Omega,
            OmegaPlusN
        };
        OrdinalType type_;
        size_t value_;
    public:
        Ordinal() : type_(OrdinalType::Zero), value_(0) {}
        Ordinal(size_t value) : type_(OrdinalType::Finite), value_(value) {}    
        static Ordinal omega() {
            Ordinal o;
            o.type_ = OrdinalType::Omega;
            o.value_ = 0;
            return o;
        }
        static Ordinal omega_plus(size_t n) {
            Ordinal o;
            o.type_ = OrdinalType::OmegaPlusN;
            o.value_ = n;
            return o;
        }
        bool IsOmega() const {
            return type_ == OrdinalType::Omega;
        }
        bool IsOmegaPlusN() const {
            return type_ == OrdinalType::OmegaPlusN;
        }
        size_t GetOmegaPlusN() const {
            if (!IsOmegaPlusN()) throw OrdinalError("not OmegaPlusN");
            return value_;
        }
        bool IsZero() const { 
            return type_ == OrdinalType::Zero; 
        }
        bool IsFinite() const {
            return type_ == OrdinalType::Finite; 
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
            if (IsOmega()) {
                if (other.IsOmega()) return false;
                if (other.IsOmegaPlusN()) return true;
                return false;
            }
            if (IsOmegaPlusN()) {
                if (other.IsOmega()) return false;
                if (other.IsOmegaPlusN()) return value_ < other.value_;
                return false;
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
            if (IsOmega() && other.IsFinite()) {
                return omega_plus(other.GetValue());
            }
            if (IsOmegaPlusN() && other.IsFinite()) {
                return omega_plus(value_ + other.GetValue());
            }
            if (IsFinite() && (other.IsOmega() || other.IsOmegaPlusN())) {
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
            if (IsOmega()) return omega_plus(value);
            if (IsOmegaPlusN()) return omega_plus(value_ + value);
            return Ordinal(GetValue() + value);
        }
        Ordinal operator*(const Ordinal& other) const {
            if (IsZero() || other.IsZero()) {
                return Ordinal(0);
            }
            if ((IsOmega() || IsOmegaPlusN()) && other.IsFinite()) {
                if (other.value_ == 0) return Ordinal(0);
                return *this;
            }
            if (IsFinite() && (other.IsOmega() || other.IsOmegaPlusN())) {
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