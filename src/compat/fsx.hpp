#ifndef FSX_HPP__
#define FSX_HPP__

namespace fsx {

    bool ensure_directory(const std::string& path);
    bool is_directory(const std::string& path);
    bool is_regular_file(const std::string& path);

}

#endif // FSX_HPP__
