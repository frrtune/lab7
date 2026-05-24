#pragma once

#include "generator.hpp"
#include "../transfinite_numbers/ordinals.hpp"

class OrdinalGenerator : public Generator<Ordinal> {
    private:
        size_t mode_;
        size_t counter_;
    public:
        OrdinalGenerator() : mode_(0), counter_(0) {}
}