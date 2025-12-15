#ifndef BOOK_HPP
#define BOOK_HPP

#include <stdint.h>
#include <string>
#include <list>

#include "Chapter.hpp"

class Book {
    public:
        Book();
        Book(Book&& other) noexcept;
    
        void SetError(std::string error);
        void SetArchive(std::string fileName);
        void SetPath(std::string path);
        void SetName(std::string name);
        void SetHash(std::string hash);
        void SetAuthor(std::string author);
        void SetYear(unsigned year);
    
        void addChapter(Chapter *chapter);

    public:
        std::string m_year;
        std::string m_author;
        std::string m_genre;
        std::string m_archive;
        std::string m_error;

    public:
        std::string m_hash;
        std::string m_name;
        std::string m_path;
        std::list<Chapter *> m_chapters;
        Chapter *m_curChapter;

};

#endif // BOOK_HPP
