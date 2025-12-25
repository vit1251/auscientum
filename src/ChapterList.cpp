
#include "stdwx.h"

#include "AppState.hpp"
#include "App.hpp"
#include "ChapterList.hpp"
#include "ChapterView.hpp"
#include "Book.hpp"

ChapterList::ChapterList(wxWindow* parent, wxWindowID id) : wxScrolledWindow(parent, id) {
    InitializeComponents();
    SetupLayout();
    BindEvents();
}

ChapterList::~ChapterList() {
}


void ChapterList::InitializeComponents() {
    // Шаг 1. Растановкой компонента будет заниматься основной сайзер
    m_sizer = new wxBoxSizer(wxVERTICAL);
}

void ChapterList::SetupLayout() {
    SetSizer(m_sizer);
    SetScrollRate(0, 10);
}

void ChapterList::BindEvents() {
    Bind(BOOK_UPDATE_EVENT, &ChapterList::OnBookUpdate, this);
}

void ChapterList::OnBookUpdate(wxCommandEvent& event) {
    AudokApp& audokApp = wxGetApp();
    AppState& appState = audokApp.m_state;

    // Шаг 1. Отключаем отрисовку
    Freeze();

    // Шаг 2. Замена дочерних компонентов
    m_sizer->Clear(true);

    //
    Book* book = appState.m_book;
    for (auto chapter: book->m_chapters) {
        auto chapterView = new ChapterView(chapter, this, wxID_ANY);
        m_sizer->Add(chapterView, 0, wxEXPAND | wxALL);
    }

    // Шаг 3. Включаем отрисовку
    FitInside();
//    this->Layout();
    Thaw();
}

