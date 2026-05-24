#pragma once

#include "../exceptions/exceptions.hpp"
#include "../lab5/sequence/sequence.hpp"
#include "../lab5/array_sequence/array_sequence.hpp"
#include "../generator/generator.hpp"
#include "../optional/optional.hpp"

template<typename T, template <typename> class Container = ArraySequence>
class LazySequence {
    private:
        std::shared_ptr<Generator<T>> generator_;
        std::shared_ptr<Container<T>> cache_;
    public:
        LazySequence() : generator_(nullptr), cache_(new Container<T>()) {}
        LazySequence (const T* items, size_t count) : generator_(nullptr), cache_(new Container<T>()) {
            for (size_t i = 0; i < count; i++) {
                cache_->Append(items[i]);
            }
        } 
        LazySequence (Container<T>& sequence) : generator_(nullptr), cache_(new Container<T>()) {
            for (size_t i = 0; i < sequence.GetLength(); i++) {
                cache_->Append(sequence.Get(i));
            }
        }
        LazySequence (const LazySequence<T>& other) : generator_(other.generator_), cache_(new Container<T>(*other.cache_)) {};
        /* реализовать генератор для функций
        LazySequence (T(*function)(Sequence<T>*), Sequence<T> base)  {

        }
        LazySequence (std::function<T(Sequence<T>&), Sequence<T>& base) {

        }*/
       T GetFirst() {
            if (cache_->GetLength() == 0) throw EmptyBufferError("cache is empty");
            return cache_->Get(0);
       }
       T GetLast() {
            if (cache_->GetLength() == 0) throw EmptyBufferError("cache is empty");
            return cache_->Get(cache_->GetLength() - 1);
       }
       T Get(size_t index) { // материализовывать (?)
            if (cache_->GetLength() == 0) throw EmptyBufferError("cache is empty");
            if (index >= cache_->GetLength()) {
                throw RangeError(index, cache_->GetLength());
            } 
            return cache_->Get(index);
       }
       LazySequence <T>* GetSubsequence(size_t start_index, size_t end_index) {
            if (start_index >= cache_->GetLength()) {
                    throw RangeError(start_index, cache_->GetLength());   
            }
            if (end_index >= cache_->GetLength()) {
                throw RangeError(end_index, cache_->GetLength());
            }
            if (start_index > end_index) {
                throw InvalidArgumentError("start index must be less than end index");
            }
            LazySequence<T>* subsequence = new LazySequence<T>();
            for (size_t i = start_index; i <= end_index; i++) {
                subsequence->cache_->Append(cache_->Get(i));
            }
            return subsequence;
       }
       // реализовать cardinal 
       //Cardinal GetLength() const {}
       size_t GetMaterializedCount() const {
            return cache_->GetLength();
       }
       /*Sequence<T>* Append(T item) {
            LazySequence<T>* new_sequence = new LazySequence<T>(*this);
            new_sequence->cache_ = cache_->Append(item);
            return new_sequence;
       }
       Sequence<T>* Prepend(T item) {
            LazySequence<T>* new_sequence = new LazySequence<T>();
            new_sequence->cache_ = cache_->Prepend(item);
            for (size_t i = 1; i < cache_->GetLength(); i++) {
                cache_->Append(cache_[i]);
            }
            return new_sequence;
       }*/
};