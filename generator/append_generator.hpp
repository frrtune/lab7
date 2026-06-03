#pragma once

#include "generator.hpp"

template<typename T>
class AppendGenerator : public Generator<T> {
    private:
        std::shared_ptr<Generator<T>> generator_;
        T item_;
        bool done_; 
    public:
        AppendGenerator(std::shared_ptr<Generator<T>> generator, T item) : 
        generator_(generator), item_(item), done_(false) {}
        T GetNext() override {
            try {
                return generator_->GetNext();
            } catch (const EmptyBufferError&) {
                if (!done_) {
                    done_ = true;
                    return item_;
                }
                throw;
            }
        }
        bool HasNext() const override {
            return !done_;
        }
        Optional<T> TryGetNext() override {
            if (!HasNext()) {
                return Optional<T>();
            }
            return Optional<T>(GetNext());
        }
};