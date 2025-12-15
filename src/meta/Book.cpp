
#include "Book.hpp"

Book::Book() {
    m_curChapter = nullptr;
}

Book::Book(Book&& other) noexcept {
    m_path = std::move(other.m_path);
}

void Book::SetPath(std::string path) {
    m_path = path;
}

void Book::SetName(std::string name) {
    m_name = name;
}

void Book::SetHash(std::string hash) {
    m_hash = hash;
}

void Book::SetAuthor(std::string author) {
    // TODO - ...
}

void Book::SetYear(unsigned year) {
    // TODO - ...
}

void Book::SetError(std::string error) {
    m_error = error;
}

void Book::SetArchive(std::string archive) {
    m_archive = archive;
}

void Book::addChapter(Chapter *chapter) {
    m_chapters.push_back(chapter);
}
