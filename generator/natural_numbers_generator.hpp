#pragma once

#include "generator.hpp"

class NaturalNumbersGenerator : public Generator<long long> {
    private:
        long long current_;
        long long limit_;
    public:
        NaturalNumbersGenerator(long long limit) : current_(1), limit_(limit) {}
        long long GetNext() override {
            if (current_ >= limit_) throw InvalidArgumentError("limit has been reached");
            return current_++;
        }
        bool HasNext() const override {
            return current_ < limit_;
        }
        Optional<long long> TryGetNext() override {
            if (!HasNext()) {
                return Optional<long long>();
            }
            return Optional<long long>(GetNext());
        }
};