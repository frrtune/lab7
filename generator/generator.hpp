#pragma once

#include "../lab5/sequence/sequence.hpp"
#include "../optional/optional.hpp"

template <typename T>
class Generator {
    public:
        virtual ~Generator() = default;
        virtual T GetNext() = 0;
        virtual bool HasNext() const = 0;
        virtual Optional<T> TryGetNext() = 0;
        /*virtual std::shared_ptr<Generator<T>> Append(T& item) const = 0; 
        virtual std::shared_ptr<Generator<T>> Append(Sequence<T>& items) const = 0; 
        virtual std::shared_ptr<Generator<T>> Insert(T& item) const = 0; 
        virtual std::shared_ptr<Generator<T>> Insert(Sequence<T>& items) const = 0; 
        virtual std::shared_ptr<Generator<T>> Remove(T& item) const = 0; 
        virtual std::shared_ptr<Generator<T>> Remove(Sequence<T>& items) const = 0;*/
};