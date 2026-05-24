#pragma once

#include "../exceptions/exceptions.hpp"

class Cardinal {
    private:
        bool is_infinite_;
        size_t value_;
    public:
        Cardinal() : is_infinite_(0), value_(0) {}
        Cardinal(size_t value) : is_infinite_(0), value_(value) {}
        static Cardinal infinity() {
            Cardinal c;
            c.is_infinite_ = true;
            c.value_ = 0;
            return c;
        }
        bool IsInfinite() const { 
            return is_infinite_;
        }
        size_t GetValue() const {
            if (is_infinite_) {
                throw CardinalError("cardinal is infinite");
            }
            return value_;
        }
        bool operator==(const Cardinal& other) const {
            if (is_infinite_ && other.is_infinite_) return true;
            if (is_infinite_ || other.is_infinite_) return false;
            return value_ == other.value_;
        }
        bool operator!=(const Cardinal& other) const {
            return !(*this == other);
        }
        bool operator<(const Cardinal& other) const {
            if (is_infinite_) return false;
            if (other.is_infinite_) return true;
            return value_ < other.value_;
        }
        bool operator>(const Cardinal& other) const {
            return other < *this;
        }
        bool operator<=(const Cardinal& other) const {
            return !(*this > other);
        }
        bool operator>=(const Cardinal& other) const {
            return !(*this < other);
        }
        Cardinal operator+(const Cardinal& other) const {
            if (is_infinite_ || other.is_infinite_) {
                return infinity();
            }
            size_t new_value = value_ + other.value_;
            return Cardinal(new_value);
        }
        Cardinal operator*(const Cardinal& other) const {
            if (is_infinite_ && other.is_infinite_) return infinity();
            if (is_infinite_) {
                if (other.value_ == 0) return Cardinal(0);
                return infinity();
            }
            if (other.is_infinite_) {
                if (value_ == 0) return Cardinal(0);
                return infinity();
            }
            size_t new_value = value_ * other.value_;
            return Cardinal(new_value);
        }
};