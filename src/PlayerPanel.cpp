
#include "stdwx.h"
#include "PlayerPanel.hpp"
#include "str.hpp"
#include "StopWatch.hpp"
#include "AppState.hpp"
#include "App.hpp"
#include "Book.hpp"
#include "Chapter.hpp"
#include "Bookmark.hpp"

#include "btn-play.xpm"
#include "btn-pause.xpm"

wxDEFINE_EVENT(PLAYER_CHANGE_BOOK, wxCommandEvent);
wxDEFINE_EVENT(PLAYER_CHANGE_CHAPTER, wxCommandEvent);
wxDEFINE_EVENT(PLAYER_CHANGE_POSITION, wxCommandEvent);


PlayerPanel::PlayerPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY) {
    m_book = nullptr;
    m_chapter = nullptr;
    //
    SetBackgroundColour(wxColour(0, 230, 0));
    //
    InitializeComponents();
    SetupLayout();
    BindEvents();
}

PlayerPanel::~PlayerPanel() {
    if (m_timer->IsRunning()) {
        m_timer->Stop();
    }
}

void PlayerPanel::InitializeComponents() {
    // Панель прогресса с таймингами
    m_progress = new wxPanel(this);
    m_progress->SetMinSize(wxSize(-1, 12));
    // Панель кнопок с заголовком страницы
    wxImage playImg(btn_play);
    playImg.Rescale(24, 24, wxIMAGE_QUALITY_HIGH);
    wxBitmap playBitmap(playImg);
    m_play = new wxBitmapButton(this, wxID_ANY, playBitmap, wxDefaultPosition, wxSize(32, 32), wxBORDER_NONE | wxBU_EXACTFIT);
    wxImage pauseImg(btn_pause);
    pauseImg.Rescale(24, 24, wxIMAGE_QUALITY_HIGH);
    wxBitmap pauseBitmap(pauseImg);
    m_pause = new wxBitmapButton(this, wxID_ANY, pauseBitmap, wxDefaultPosition, wxSize(32, 32), wxBORDER_NONE | wxBU_EXACTFIT);
    m_info = new wxStaticText(this, wxID_ANY, "");
    // Служебные компоненты
    m_timer = new wxTimer(this, wxID_ANY);
    m_timer->Start(500);
}

void PlayerPanel::SetupLayout() {
    //
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* controlSizer = new wxBoxSizer(wxHORIZONTAL);
    controlSizer->SetMinSize(wxSize(-1, 24));
    // Шаг 2. Формируем разметку управления
    controlSizer->Add(m_play, 0, wxALL);
    controlSizer->Add(m_pause, 0, wxALL);
    controlSizer->Add(m_info, 1, wxALL | wxALIGN_CENTER_VERTICAL);
    // Шаг 3. Формируем основную разметку
    mainSizer->Add(m_progress, 0, wxALL | wxEXPAND);
    mainSizer->Add(controlSizer, 0, wxALL);
    SetSizer(mainSizer);
}

static StopWatch watch;

void PlayerPanel::ProgressOnTimer(wxTimerEvent& event) {
    AudokApp& audokApp = wxGetApp();
    AppState& appState = audokApp.m_state;
    
    // ОБновляем текст
    if (m_chapter) {
        wxString myTitle = wxString::Format("%s - %u", m_chapter->m_name, 0);
        m_info->SetLabel(myTitle);
    }

    // Сохранить закладку каждый 100 сек.
    auto duration = watch.getOffset();
    if (duration > 100) {
        appState.m_bookmark->SaveChapter(m_book, m_chapter);
        watch.start();
    }

    // Обновить позицию проигрывания
    Refresh();
}

void PlayerPanel::ProgressOnPaint(wxPaintEvent& event) {
    wxPaintDC dc(m_progress);
    wxSize size = GetClientSize();
    wxColor playColor = wxColor(250, 250, 250);
    wxColor posColor = wxColour(250, 250, 0);

    // Шаг 1. Очищаем фон
    dc.Clear();
    dc.SetPen(*wxTRANSPARENT_PEN);

    // Прослушано (серый)
    dc.SetBrush(wxBrush(playColor));
    dc.DrawRectangle(0, 0, size.x - 20, size.y);

    // Текущая позиция
    dc.SetBrush(wxBrush(posColor));
    if (m_duration > 0) {
        dc.DrawRectangle(0, 0, size.x * m_position / m_duration, size.y);
    }

    // Сколько прослушано
    wxString curPosition = str::makeDuration(m_position);
    wxString curDuration = str::makeDuration(m_duration);
//    wxLogDebug("Позиция: %s", curPosition);
//    wxLogDebug("Длительность: %s", curDuration);

}

void PlayerPanel::ProgressOnMouseClick(wxMouseEvent& event) {
    wxPoint pos = event.GetPosition();
    wxSize size = GetClientSize();

    // Шаг 1. Пересчитаем позицию воспроизведения
    

    // Шаг 2. Отправим событие подписчикам
    wxCommandEvent customEvent(PLAYER_CHANGE_POSITION, GetId());
    customEvent.SetInt(m_position);
    customEvent.SetEventObject(this);
    ProcessWindowEvent(customEvent);
}

void PlayerPanel::OnPlay(wxCommandEvent& event) {
    AudokApp& audokApp = wxGetApp();
    AppState& appState = audokApp.m_state;

    std::cout << "Нажата кнопка PLAY" << std::endl;

    // Продолжаем проигрывание
    if (appState.m_music.getStatus() == AudioPlayer::State::Paused) {
        appState.m_music.play();
        return;
    }

    // Останавливаем если уже проигрываем
    if (appState.m_music.getStatus() == AudioPlayer::State::Playing) {
        appState.m_music.stop();
        m_timer->Stop();
        return;
    }

    // Загружаем аудиокнигу
    auto chapterPath = m_chapter->m_path;
    if (!appState.m_music.openFromFile(chapterPath)) {
        std::cerr << "Failed to open music file" << std::endl;
        return;
    }

    // Запускаем проигрывание аудиокниги
    std::cout << "Продолжаем проигрывание аудиокниги с позиции " << m_chapter->m_pos << " сек. " << std::endl;
    appState.m_music.play();
    appState.m_music.setPlayingOffset(m_chapter->m_pos);

    // Запускаем таймер для обновления позиции
    m_timer->Start(500);

}

void PlayerPanel::OnPause(wxCommandEvent& event) {
    AudokApp& audokApp = wxGetApp();
    AppState& appState = audokApp.m_state;

    std::cout << "Нажата кнопка PAUSE" << std::endl;

    if (appState.m_music.getStatus() == AudioPlayer::State::Playing) {
        appState.m_music.pause();
    }

}


void PlayerPanel::BindEvents() {
    // Шаг 1. Привязка таймера
    Bind(wxEVT_TIMER, &PlayerPanel::ProgressOnTimer, this);
    // Шаг 2. Привязка кнопок
    m_play->Bind(wxEVT_BUTTON, &PlayerPanel::OnPlay, this);
    m_pause->Bind(wxEVT_BUTTON, &PlayerPanel::OnPause, this);
    // Шаг 3. Отрисовка прогресса
    m_progress->Bind(wxEVT_PAINT, &PlayerPanel::ProgressOnPaint, this);
}

void PlayerPanel::SetPos(unsigned position) {
    m_position = position;
}

void PlayerPanel::SetDuration(unsigned duration) {
    m_duration = duration;
}
