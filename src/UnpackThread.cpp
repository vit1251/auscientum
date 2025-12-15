
#include "stdwx.h"

#include "AppState.hpp"
#include "App.hpp"
#include "UnpackThread.hpp"
#include "Book.hpp"
#include "ZipStore.hpp"
#include "Hash.hpp"


UnpackThread::UnpackThread(wxFrame *parent, std::string fileName) : m_parent(parent), m_fileName(fileName) {
}

void* UnpackThread::Entry() {

    // Шаг 0. Отладочная информация
    wxLogDebug(wxT("Вычисляем метаинформацию о книге %s"), m_fileName);

    // Шаг 1. Восстанавливаем информацию о книге
    Book* book = restoreBook(m_fileName);
    if (book->m_error != "") {
        wxLogDebug(wxT("Ошибка %s"), book->m_error);
    }

    // Шаг 2. Вычисляем уникальный идентификатор книги
    std::vector<std::string> hashs;
    for (auto chapter: book->m_chapters) {
        wxLogDebug(wxT("Глава: %s hash = %s"), chapter->m_path, chapter->m_hash);
        hashs.push_back(chapter->m_hash);
    }
    std::sort(hashs.begin(), hashs.end());
    Hash bookDigest;
    for (auto hash: hashs) {
        wxLogDebug(wxT("В алфавитном порядке %s"), hash);
        bookDigest.Update(hash);
    }
    std::string bookHash = bookDigest.Digest();
    wxLogDebug(wxT("Книге присвоен идентификатор %s"), bookHash);
    book->SetHash(bookHash);

    // Шаг 3. Завершение
    wxLogDebug(wxT("Вычисление завершено."));

    // Шаг 4. Окончание работы
    SendMessage(EVENT_UNPACK_COMPLETE);

    return nullptr;
}

void UnpackThread::SendMessage(int messageType) {

    // Шаг 0. Диагностическое сообщение
    wxLogDebug(wxT("Отправляем сообщение в родительский поток."));

    // Шаг 1. Формируем отправляемое сообщение
    wxThreadEvent* event = new wxThreadEvent(wxEVT_THREAD, messageType);
    event->SetInt(50);

    // Шаг 2. Отправляем сообщение
    wxQueueEvent(m_parent, event);

}
