#pragma once

#include "generator.hpp"

template<typename T>
class PrependGenerator : public Generator<T> {
    private:
        std::shared_ptr<Generator<T>> generator_;
        T item_;
        bool done_;
    public:
        PrependGenerator(std::shared_ptr<Generator<T>> generator, T item) : 
        generator_(generator), item_(item), done_(false) {}
        T GetNext() override {
            if (!done_) {
                done_ = true;
                return item_;
            }
            if (generator_->HasNext()) {
                return generator_->GetNext();
            }
            throw EmptyBufferError("no more elements");
        }
        bool HasNext() const override {
            return !done_ || generator_->HasNext();
        }
        Optional<T> TryGetNext() override {
            if (!HasNext()) {
                return Optional<T>();
            }
            return Optional<T>(GetNext());
        }
};