
#include "Chapter.hpp"

Chapter::Chapter() {
    m_number = 0;
    m_pos = 0;
}

void Chapter::SetHash(std::string hash) {
    m_hash = hash;
}

void Chapter::SetPath(std::string path) {
    m_path = path;
}

void Chapter::SetZipPath(std::string zipPath) {
    m_zip_path = zipPath;
}


void Chapter::SetName(std::string name) {
    m_name = name;
}

void Chapter::SetNumber(unsigned number) {
    m_number = number;
}
