#include "lazy_sequence/lazy_sequence.hpp"
#include "generator/ordinal_generator.hpp"
#include "generator/insert_generator.hpp"
#include "generator/concat_generator.hpp"
#include "generator/natural_numbers_generator.hpp"
#include <iostream>
#include <memory>

std::string ordinal_to_string(const Ordinal& o) {
    if (o.IsZero()) return "0";
    if (o.IsFinite()) return std::to_string(o.GetValue());
    if (o.IsOmega()) return "w";
    if (o.IsOmegaPlusN()) return "w+" + std::to_string(o.GetOmegaPlusN());
    return "";
}