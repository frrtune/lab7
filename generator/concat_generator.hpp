#pragma once

#include "generator.hpp"

template<typename T>
class ConcatGenerator : public Generator<T> {
    private:
        std::shared_ptr<Generator<T>> first_;
        std::shared_ptr<Generator<T>> second_;
        bool first_done_; 
    public:
        ConcatGenerator(std::shared_ptr<Generator<T>> first, std::shared_ptr<Generator<T>> second) :
        first_(first), second_(second), first_done_(false) {}
         T GetNext() override {
            if (!first_done_ && first_->HasNext()) {
                return first_->GetNext();
            }
            first_done_ = true;
            return second_->GetNext();
        }
        bool HasNext() const override {
            if (!first_done_ && first_->HasNext()) {
                return true;
            }
            return second_->HasNext();
        }
        Optional<T> TryGetNext() override {
            if (!HasNext()) {
                return Optional<T>();
            }
            return Optional<T>(GetNext());
        }
};