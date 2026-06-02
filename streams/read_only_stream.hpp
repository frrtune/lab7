#pragma once

#include "../optional/optional.hpp"

template<typename T>
class ReadOnlyStream {
    public:
        virtual ~ReadOnlyStream() = default;
        virtual bool is_end() = 0;
        virtual Optional<T> try_read() = 0;
        virtual T read() = 0;
        virtual void close() = 0;
};