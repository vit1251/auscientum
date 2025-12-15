
#include "Chapter.hpp"

Chapter::Chapter() {
}

void Chapter::SetHash(std::string hash) {
    m_hash = hash;
}

void Chapter::SetPath(std::string path) {
    m_path = path;
}

void Chapter::SetName(std::string name) {
    m_name = name;
}