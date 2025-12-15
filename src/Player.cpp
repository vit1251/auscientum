
#include "stdwx.h"
#include "Player.hpp"

wxDEFINE_EVENT(PLAYER_CHANGE_POSITION, wxCommandEvent);

wxString makeDuration(unsigned total_seconds) {
    std::div_t hm = std::div(total_seconds, 3600);
    unsigned hours = hm.quot;
    unsigned rem_seconds = hm.rem;
    std::div_t ms = std::div(rem_seconds, 60);
    unsigned minutes = ms.quot;
    unsigned seconds = ms.rem;
    return wxString::Format("%02u:%02u:%02u", hours, minutes, seconds);
}

Player::Player(wxWindow* parent) : wxPanel(parent, wxID_ANY) {
    SetBackgroundColour(wxColour(0, 230, 0));
    InitializeComponents();
    SetupLayout();
    BindEvents();
}

Player::~Player() {
    if (m_timer->IsRunning()) {
        m_timer->Stop();
    }
}

void Player::InitializeComponents() {
    // Панель прогресса с таймингами
    m_progress = new wxPanel(this);
    m_progress->SetMinSize(wxSize(-1, 12));
    // Панель кнопок с заголовком страницы
    m_play = new wxButton(this, wxID_ANY, "P");
    m_rewind_back = new wxButton(this, wxID_ANY, "<");
    m_rewind_forward = new wxButton(this, wxID_ANY, ">");
    m_info = new wxStaticText(this, wxID_ANY, "Глава 1. Введение");
    // Служебные компоненты
    m_timer = new wxTimer(this, wxID_ANY);
    m_timer->Start(500);
}

void Player::SetupLayout() {
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* controlSizer = new wxBoxSizer(wxHORIZONTAL);
    controlSizer->SetMinSize(wxSize(-1, 24));
    // Шаг 2. Формируем разметку управления
    controlSizer->Add(m_play, 0, wxALL);
    controlSizer->Add(m_rewind_back, 0, wxALL);
    controlSizer->Add(m_rewind_forward, 0, wxALL);
    controlSizer->Add(m_info, 1, wxALL | wxALIGN_CENTER_VERTICAL);
    // Шаг 3. Формируем основную разметку
    mainSizer->Add(m_progress, 0, wxALL | wxEXPAND);
    mainSizer->Add(controlSizer, 0, wxALL);
    SetSizer(mainSizer);
}

void Player::ProgressOnTimer(wxTimerEvent& event) {
    Refresh();
}

void Player::ProgressOnPaint(wxPaintEvent& event) {
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
    wxString curPosition = makeDuration(m_position);
    wxString curDuration = makeDuration(m_duration);
//    wxLogDebug("Позиция: %s", curPosition);
//    wxLogDebug("Длительность: %s", curDuration);

}

void Player::ProgressOnMouseClick(wxMouseEvent& event) {
    wxPoint pos = event.GetPosition();
    wxSize size = GetClientSize();
    // Шаг 1. Пересчитаем позицию воспроизведения
    

    // Шаг 2. Отправим событие подписчикам
    wxCommandEvent customEvent(PLAYER_CHANGE_POSITION, GetId());
    customEvent.SetInt(m_position);
    customEvent.SetEventObject(this);
    ProcessWindowEvent(customEvent);
}

void Player::OnPlay(wxCommandEvent& event) {
    wxMessageBox("Hello, World!", "Info", wxOK | wxICON_INFORMATION);
}

void Player::OnRewindBack(wxCommandEvent& event) {
    unsigned new_position = m_position > 10 ? m_position - 10 : 0;
    m_position = new_position;
}

void Player::OnRewindForward(wxCommandEvent& event) {
    unsigned new_position = m_position + 10 < m_duration ? m_position + 10 : m_duration;
    m_position = new_position;
}

void Player::BindEvents() {
    // Шаг 1. Привязка таймера
    Bind(wxEVT_TIMER, &Player::ProgressOnTimer, this);
    // Шаг 2. Привязка кнопок
    m_play->Bind(wxEVT_BUTTON, &Player::OnPlay, this);
    m_rewind_back->Bind(wxEVT_BUTTON, &Player::OnRewindBack, this);
    m_rewind_forward->Bind(wxEVT_BUTTON, &Player::OnRewindForward, this);
    // Шаг 3. Отрисовка прогресса
    m_progress->Bind(wxEVT_PAINT, &Player::ProgressOnPaint, this);
}

void Player::SetPos(unsigned position) {
    m_position = position;
}

void Player::SetDuration(unsigned duration) {
    m_duration = duration;
}
