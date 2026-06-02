#pragma once

#include "../streams/read_only_stream.hpp"
#include <fstream>
#include <string>

template<typename T>
class ReadOnlyStreamFile : public ReadOnlyStream<T> {
    private:
        std::ifstream file_;
    public:
        ReadOnlyStreamFile(std::string filename) {
            file_.open(filename);
            if (!file_.is_open()) throw StreamOpenError(filename);
        }
        ~ReadOnlyStreamFile() override {
            if (file_.is_open()) file_.close();
        }
        bool is_end() override {
            return (file_.eof() || file_.fail());
        }
        Optional<T> try_read() override {
            if (is_end()) return Optional<T>();
            return Optional<T>(read());
        }
        T read() override {
            T value;
            file_ >> value;
            if (file_.fail()) {
                throw EndOfStreamError();
            }
            return value;
        }
        void close() override {
            file_.close();
        }
};