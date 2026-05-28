#pragma once

#include "../optional/optional.hpp"
#include <fstream>
#include <string>

template<typename T>
class ReadOnlyStream {
    private:
        std::ifstream file_;
    public:
        ReadOnlyStream(std::string filename) {
            file_.open(filename);
            if (!file_.is_open()) throw StreamOpenError(filename);
        }
        ~ReadOnlyStream() {
            if (file_.is_open()) file_.close();
        }
        bool is_end() {
            return (file_.eof() || file_.fail());
        }
        Optional<T> try_read() {
            if (is_end()) return Optional<T>();
            return Optional<T>(read());
        }
        T read() {
            T value;
            file_ >> value;
            if (file_.fail()) {
                throw EndOfStreamError();
            }
            return value;
        }
        void close() {
            file_.close();
        }
};