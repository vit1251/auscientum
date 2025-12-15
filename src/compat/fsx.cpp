
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <string>

#include "fsx.hpp"

namespace fsx {

    bool ensure_directory(const std::string& path) {
        if (is_directory(path)) {
            return true;
        }
        return mkdir(path.c_str(), 0755) == 0;
    }

    bool is_directory(const std::string& path) {
        struct stat st;
        if (stat(path.c_str(), &st) == 0) {
            return S_ISDIR(st.st_mode);
        }
        return false;
    }

    bool is_regular_file(const std::string& path) {
        struct stat st;
        if (stat(path.c_str(), &st) == 0) {
            return S_ISREG(st.st_mode);
        }
        return false;
    }

}