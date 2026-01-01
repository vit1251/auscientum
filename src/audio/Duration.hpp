#ifndef DURATION_HPP__
#define DURATION_HPP__

#include <string>
#include <variant>

class Book;
class Chapter;

enum class DurationError {
    Ok      = 0,       // Успещное завершение
    IOError = 1        // Ошибка чтения
};

DurationError LoadDuration(Book *book, Chapter *chapter);

#endif
