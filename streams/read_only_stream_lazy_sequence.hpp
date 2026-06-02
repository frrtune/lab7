#pragma once

#include "../streams/read_only_stream.hpp"

template<typename T>
class ReadOnlyStreamLazySequence : public ReadOnlyStream<T> {
    private:
        LazySequence<T>* sequence_;
    public:
        ~ReadOnlyStreamLazySequence() = default;
        bool is_end() override {}
        Optional<T> try_read() override {};
        T read() override {};
        void close() override {};
};