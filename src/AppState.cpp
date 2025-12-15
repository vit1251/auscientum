
#include "stdwx.h"

#include "AppState.hpp"
#include "Book.hpp"
#include "Bookmark.hpp"
#include "Config.hpp"


AppState::AppState() {
    m_reading = false;
    m_book = nullptr;
    m_dbPath = GetDbPath();
    m_bookmark = new Bookmark();
}

