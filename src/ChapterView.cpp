
#include <memory>
#include <iostream>

#include "stdwx.h"

#include "str.hpp"

#include "AppState.hpp"
#include "App.hpp"
#include "ChapterView.hpp"
#include "Bookmark.hpp"
#include "Chapter.hpp"

#include "btn-play.xpm"


ChapterView::ChapterView(Chapter* chapter, wxWindow* parent, wxWindowID id) : wxPanel(parent, id), m_chapter(chapter)
{
    InitializeComponents();
    SetupLayout();
    BindEvents();
}

ChapterView::~ChapterView() {
    delete m_timer;
}

void ChapterView::InitializeComponents() {
    m_timer = new wxTimer(this, wxID_ANY);
    
}

void ChapterView::SetupLayout() {
    SetMinSize(wxSize(-1, 100));
}



void ChapterView::BindEvents() {
    Bind(wxEVT_TIMER, &ChapterView::OnTimer, this);
    Bind(wxEVT_LEFT_DOWN, &ChapterView::OnMouseClick, this);
    Bind(wxEVT_PAINT, &ChapterView::OnPaint, this);
//    Bind(wxEVT_TIMER, &ChapterView::OnTimer, this, ID_TIMER);
}

static unsigned GetPos() {
    AudokApp& audokApp = wxGetApp();
    AppState& appState = audokApp.m_state;

    double curPos = appState.m_music.getPlayingOffset().asSeconds();
    double curDur = appState.m_music.getDuration().asSeconds();
    if (curDur == 0.0) {
        return 0;
    }

    unsigned percent = unsigned(curPos * 100 / curDur);

    std::cout << "Позиция проигрывания " << percent << std::endl;

    return percent;
}

void ChapterView::OnTimer(wxTimerEvent& event) {
    AudokApp& audokApp = wxGetApp();
    AppState& appState = audokApp.m_state;

    m_chapter->m_pos = appState.m_music.getPlayingOffset().asSeconds();

    Refresh();
}

void ChapterView::OnMouseClick(wxMouseEvent& event) {
    AudokApp& audokApp = wxGetApp();
    AppState& appState = audokApp.m_state;
    wxPoint pos = event.GetPosition();
    std::string chapterPath = m_chapter->m_path;
    int x = pos.x;
    int y = pos.y;

    wxString wxMsg = wxString::Format("Вы уверены, что хотите перейти к главе '%s'?",  m_chapter->m_name);
    int answer = wxMessageBox(
        wxMsg,                                           // Текст вопроса
        "Переход к новой главее",                        // Заголовок окна
        wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION        // Кнопки и иконка
    );
    if (answer == wxYES) {
        // Пользователь нажал "Да"
    } else {
        // Пользователь нажал "Нет" (или закрыл окно)
        return;
    }

    auto bookmark = std::make_unique<Bookmark>();

    // Останавливаем если уже проигрываем
    if (appState.m_music.getStatus() == sf::Music::Playing) {
        bookmark->SaveChapter(appState.m_book, m_chapter);
        appState.m_music.stop();
        m_timer->Stop();
        return;
    }

    // Загружаем аудиокнигу
    if (!appState.m_music.openFromFile(chapterPath)) {
        std::cerr << "Failed to open music file" << std::endl;
        return;
    }

    // Запускаем проигрывание аудиокниги
    std::cout << "Продолжаем проигрывание аудиокниги с позиции " << m_chapter->m_pos << " сек. " << std::endl;
    appState.m_music.play();
    appState.m_music.setPlayingOffset(sf::seconds(m_chapter->m_pos));

    // Запускаем таймер для обновления позиции
    m_timer->Start(500);

}

void ChapterView::OnPaint(wxPaintEvent& event) {
    AudokApp& audokApp = wxGetApp();
    AppState& appState = audokApp.m_state;

    wxSize size = GetClientSize();
    wxPaintDC dc(this);

    dc.SetBackgroundMode(wxSOLID);
    dc.SetTextForeground(*wxBLACK);

    // Draw the chapter title
    uint16_t chapterNumber = m_chapter->m_number;
    const char* chapterName = m_chapter->m_name.c_str();
    wxString title = wxString::Format("%02d. %s", chapterNumber, chapterName);
    dc.DrawText(title, 10, 10);

    // Шаг 2. Рисуем позицию прогирывания
    double curPos = appState.m_music.getPlayingOffset().asSeconds();
    double curDur = appState.m_music.getDuration().asSeconds();
    std::string szPos = str::makeDuration(curPos);
    std::string szDur = str::makeDuration(curDur);

    wxString wxPos = wxString::Format("%s", szPos.c_str());
    wxString wxDur = wxString::Format("%s", szDur.c_str());

    dc.DrawText(wxPos, 10, 50);
    unsigned posX = size.GetWidth() - 20 - 50;
    dc.DrawText(wxDur, posX, 50);

    // Draw the play button
    wxBitmap playBitmap(btn_play);
    dc.DrawBitmap(playBitmap, 10, 50, true);

    // Draw the progress bar
    int progressBarWidth = size.GetWidth() - 20;
    int progressBarHeight = 20;
    int progressValue = m_chapter->m_pos;

    dc.SetPen(*wxBLACK_PEN);
    dc.SetBrush(wxBrush(wxColour(192, 192, 192)));
    dc.DrawRectangle(10, 70, progressBarWidth, progressBarHeight);

    dc.SetBrush(wxBrush(wxColour(255, 0, 0)));
    dc.DrawRectangle(10, 70, (progressValue * progressBarWidth) / 100, progressBarHeight);
}

