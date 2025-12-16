
#include "stdwx.h"

#include "AppState.hpp"
#include "App.hpp"
#include "UnpackThread.hpp"
#include "Book.hpp"
#include "ZipStore.hpp"
#include "Hash.hpp"
#include "Bookmark.hpp"


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

    // Шаг 2. Обновим метаиниформацию в индексе
    Bookmark* bookmark = new Bookmark();
    for (auto chapter: book->m_chapters) {
        bookmark->UpdateChapter(book, chapter);
    }

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
