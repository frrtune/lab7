#pragma once

#include "../optional/optional.hpp"
#include <fstream>

template<typename T>
class ReadOnlyStream {
    private:
        std::ifstream file_;
    public:
        ReadOnlyStream(std::string filename) {
            file_.open(filename);
            if (!file_.is_open) throw StreamOpenError(filename);
        }
        ~ReadOnlyStream() {
            if (file_.is_open) file_.close();
        }
}