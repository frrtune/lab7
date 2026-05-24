#pragma once

#include "generator.hpp"
#include "../transfinite_numbers/ordinals.hpp"

class OrdinalGenerator : public Generator<Ordinal> {
    private:
        size_t mode_;
        size_t counter_;
        static constexpr size_t LIMIT = 10;
    public:
        OrdinalGenerator() : mode_(0), counter_(0) {}
        Ordinal GetNext() override {
            if (mode_ == 0) {
                if (counter_ < LIMIT) {
                    return Ordinal(counter_++);
                }
                mode_ = 1;
                return Ordinal::omega();
            }
            if (mode_ == 1) {
                mode_ = 2;
                counter_ = 1;
                return Ordinal::omega();
            }
            Ordinal result = Ordinal::omega() + counter_;
            counter_++;
            return result;
        }
        bool HasNext() const override {
            return true;
        }
        Optional<Ordinal> TryGetNext() override {
            if (!HasNext()) {
                return Optional<Ordinal>();
            }
            return Optional<Ordinal>(GetNext());
        }
};