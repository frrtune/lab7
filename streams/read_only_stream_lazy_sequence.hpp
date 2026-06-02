#pragma once

#include "../lazy_sequence/lazy_sequence.hpp"
#include "../streams/read_only_stream.hpp"

template<typename T>
class ReadOnlyStreamLazySequence : public ReadOnlyStream<T> {
    private:
        LazySequence<T>* sequence_;
        size_t current_;
    public:
        ReadOnlyStreamLazySequence(LazySequence<T>* sequence) : sequence_(sequence), current_(0) {}
        bool is_end() override {
            try {
                sequence_->Get(current_);
                return false;
            } catch (const RangeError&) return true;
        }
        Optional<T> try_read() override {};
        T read() override {};
        void close() override {};
};