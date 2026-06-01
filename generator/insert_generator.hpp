#pragma once

#include "generator.hpp"

template<typename T>
class InsertGenerator : public Generator<T> {
    private:
        std::shared_ptr<Generator<T>> first_;
        std::shared_ptr<Generator<T>> second_;
        size_t insert_index_;
        size_t current_index_;
    public:
        InsertGenerator(std::shared_ptr<Generator<T>> first, std::shared_ptr<Generator<T>> second, size_t insert_index) :
        first_(first), second_(second), insert_index_(insert_index), current_index_(0) {}
        T GetNext() override {
            if (current_index_ < insert_index_) {
                current_index_++;
                return first_->GetNext();
            }
            return second_->GetNext();
        }
        bool HasNext() const override {
            if (current_index_ < insert_index_) {
                return first_->HasNext();
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