#pragma once

#include <memory>
#include "../lab5/exceptions/exceptions.hpp"
#include "../lab5/sequence/sequence.hpp"
#include "../lab5/array_sequence/array_sequence.hpp"
#include "../generator/generator.hpp"
#include "../optional/optional.hpp"
#include "../transfinite_numbers/cardinals.hpp"

template<typename T, template <typename> class Container = ArraySequence>
class LazySequence {
    private:
        std::shared_ptr<Generator<T>> generator_;
        std::shared_ptr<Container<T>> cache_;
    public:
        LazySequence() : generator_(nullptr), cache_(new Container<T>()) {}
        LazySequence (const T* items, size_t count) : generator_(nullptr), cache_(new Container<T>()) {
            for (size_t i = 0; i < count; i++) {
                cache_->PushBack(items[i]);
            }
        } 
        LazySequence (Container<T>& sequence) : generator_(nullptr), cache_(new Container<T>()) {
            for (size_t i = 0; i < sequence.GetLength(); i++) {
                cache_->PushBack(sequence.Get(i));
            }
        }
        LazySequence (const LazySequence<T>& other) : generator_(other.generator_), cache_(new Container<T>(*other.cache_)) {};
        LazySequence(Generator<T>* generator) : generator_(generator), cache_(new Container<T>()) {};
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
            if (cache_->GetLength() == 0) {
                if (generator_ && generator_->HasNext()) {
                    while (generator_->HasNext()) {
                        cache_->PushBack(generator_->GetNext());
                    }
                }
                if (cache_->GetLength() == 0) throw EmptyBufferError("cache is empty");
            }
            return cache_->Get(cache_->GetLength() - 1);
       }
       T Get(size_t index) {
            while (cache_->GetLength() <= index && generator_ && generator_->HasNext()) {
                cache_->PushBack(generator_->GetNext());
            }
            if (index >= cache_->GetLength()) throw RangeError(index, cache_->GetLength());
            return cache_->Get(index);
       }
       LazySequence<T>* GetSubsequence(size_t start_index, size_t end_index) {
            if (start_index >= cache_->GetLength()) throw RangeError(start_index, cache_->GetLength());   
            if (end_index >= cache_->GetLength()) throw RangeError(end_index, cache_->GetLength());
            if (start_index > end_index) throw InvalidArgumentError("start index must be less than end index");
            LazySequence<T>* subsequence = new LazySequence<T>();
            for (size_t i = start_index; i <= end_index; i++) {
                subsequence->cache_->Append(cache_->Get(i));
            }
            return subsequence;
       }
       Cardinal GetLength() const {
            if (generator_ && !generator_->HasNext()) {
                return Cardinal(cache_->GetLength());
            }
            if (!generator_) {
                return Cardinal(cache_->GetLength());
            }
            return Cardinal::infinity();
       }
       size_t GetMaterializedCount() const {
            return cache_->GetLength();
       }
       LazySequence<T>* Append(T item) {
            LazySequence<T>* new_sequence = new LazySequence<T>(*this);
            new_sequence->cache_->Append(item);
            return new_sequence;
       }
       LazySequence<T>* Prepend(T item) {
            LazySequence<T>* new_sequence = new LazySequence<T>();
            new_sequence->cache_->PushBack(item);
            for (size_t i = 0; i < cache_->GetLength(); i++) {
                new_sequence->cache_->PushBack(cache_->Get(i));
            }
            return new_sequence;
       }
       LazySequence<T>* InsertAt(T item, size_t index) {
            if (index > cache_->GetLength()) throw RangeError(index, cache_->GetLength());   
            LazySequence<T>* new_sequence = new LazySequence<T>();
            for (size_t i = 0; i < index; i++) {
                new_sequence->cache_->Append(cache_->Get(i));
            }
            new_sequence->cache_->Append(item);
            for (size_t i = index; i < cache_->GetLength(); i++) {
                new_sequence->cache_->Append(cache_->Get(i));
            }
            return new_sequence;
       }
       LazySequence <T>* Concat(LazySequence<T>& other) {
            LazySequence<T>* new_sequence = new LazySequence<T>(*this);
            for (size_t i = 0; i < other.cache_->GetLength(); i++) {
                new_sequence->cache_->Append(other.cache_->Get(i));
            }
            return new_sequence;
       } 
};