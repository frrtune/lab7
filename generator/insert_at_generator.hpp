#pragma once

#include "generator.hpp"

template<typename T>
class InsertAtGenerator : public Generator<T> {
    private:
        std::shared_ptr<Generator<T>> generator_;
        T item_;
        bool done_;
        size_t index_;
        size_t current_;
    public:
        InsertAtGenerator(std::shared_ptr<Generator<T>> generator, T item, size_t index) : 
        generator_(generator), item_(item), done_(false), index_(index), current_(0) {}
        T GetNext() override {
            if (current_ < index_ && generator_->HasNext()) {
                current_++;
                return generator_->GetNext();
            }
            if (!done_) {
                done_ = true;
                return item_;
            }
            if (generator_->HasNext()) return generator_->GetNext();
            throw EmptyBufferError();
        }
        bool HasNext() const override {
            if (current_ < index_ && generator_->HasNext()) return true;
            if (!done_) return true;
            return generator_->HasNext();
        }
        Optional<T> TryGetNext() override {
            if (!HasNext()) {
                return Optional<T>();
            }
            return Optional<T>(GetNext());
        }
};