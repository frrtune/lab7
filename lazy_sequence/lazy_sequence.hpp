#pragma once

#include "../exceptions/exceptions.hpp"
#include "../lab5/sequence/sequence.hpp"
#include "../lab5/array_sequence/array_sequence.hpp"
#include "../generator/generator.hpp"
#include "../optional/optional.hpp"

template<template <typename> class Container = ArraySequence, typename T>
class LazySequence {
    private:
        std::unique_ptr<Generator<T>> generator_;
        Container<T> cache_;
    public:
        LazySequence() : generator_(nullptr) {}
        LazySequence (const T* items, size_t count) : generator_(nullptr) {
            for (size_t i = 0; i < count; i++) {
                cache_.Append(items[i])
            }
        } 
        LazySequence (Container<T>& sequence) : generator_(nullptr) {
            for (size_t i = 0; i < sequence.Getlength(); i++) {
                cache_.Append(data.Get(i))
            }
        }
        LazySequence (const LazySequence<T>& other) : generator_(nullptr) {

        }
};