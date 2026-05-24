#pragma once

#include "../exceptions/exceptions.hpp"
#include "../lab5/sequence/sequence.hpp"
#include "../lab5/array_sequence/array_sequence.hpp"
#include "../generator/generator.hpp"
#include "../optional/optional.hpp"

template<typename T, template <typename> class Container = ArraySequence>
class LazySequence {
    private:
        std::unique_ptr<Generator<T>> generator_;
        Container<T> cache_;
    public:
        LazySequence() : generator_(nullptr) {}
        LazySequence (const T* items, size_t count) : generator_(nullptr) {
            for (size_t i = 0; i < count; i++) {
                cache_.Append(items[i]);
            }
        } 
        LazySequence (Container<T>& sequence) : generator_(nullptr) {
            for (size_t i = 0; i < sequence.Getlength(); i++) {
                cache_.Append(sequence.Get(i));
            }
        }
        LazySequence (const LazySequence<T>& other) : generator_(other.generator_), cache_(other.cache_) {};
        /* реализовать генератор для функций
        LazySequence (T(*function)(Sequence<T>*), Sequence<T> base)  {

        }
        LazySequence (std::function<T(Sequence<T>&), Sequence<T>& base) {

        }*/
       T GetFirst() {
            if (cache_.GetLength() == 0) throw EmptyBufferError("cache is empty");
            return cache_.Get(0);
       }
       T GetLast() {
            if (cache_.GetLength() == 0) throw EmptyBufferError("cache is empty");
            return cache_.Get(cache_.GetLength() - 1);
       }
       T Get(size_t index) {
            if (cache_.GetLength() == 0) throw EmptyBufferError("cache is empty");
            if (index >= cache_.GetLength()) {
                throw RangeError(index, cache_.GetLength());
            } 
            return cache_.Get(index);
       }
       LazySequence <T>* GetSubsequence(size_t start_index, size_t end_index) {
            if (start_index >= cache_.GetLength()) {
                    throw RangeError(start_index, cache_.GetLength());   
            }
            if (end_index >= cache_.GetLength()) {
                throw RangeError(end_index, cache_.GetLength());
            }
            if (start_index > end_index) {
                throw InvalidArgumentError("start index must be less than end index");
            }
            LazySequence<T>* subsequence = new LazySequence<T>();
            for (size_t i = start_index; i <= end_index; i++) {
                subsequence->cache_.Append(cache_.Get(i));
            }
            return subsequence;
       }
};