
#include "stdwx.h"

#include "AppState.hpp"
#include "App.hpp"
#include "PlayerPanel.hpp"
#include "MainFrame.hpp"
#include "UnpackThread.hpp"
#include "BookView.hpp"
#include "ChapterList.hpp"


MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "Auscientum") {
    InitializeComponents();
    SetupLayout();
    BindEvents();
}

void MainFrame::OnOpen(wxCommandEvent& event) {
    AudokApp& audokApp = wxGetApp();
    AppState& appState = audokApp.m_state;

    // Шаг 1. Уже читаем
    if (appState.m_reading) {
        wxLogError(wxT("Идет процесс распаковки аудиокниги."));
        return;
    }


    wxFileDialog* openFileDialog = new wxFileDialog(this,
        wxT("Открытие аудиокниги"),
        wxT(""),
        wxT(""),
        wxT("Архив аудиокниги с Litres (*.zip)|*.zip"),
        wxFD_OPEN | wxFD_FILE_MUST_EXIST
    );
    if (openFileDialog->ShowModal() == wxID_OK){
        wxString fileName = openFileDialog->GetPath();
        wxLogDebug(wxT("Запрос на открытие аудиокниги %s"), fileName);

        //
        appState.m_reading = true;

        //
        std::string fileName2 = fileName.utf8_string();
        UnpackThread* unpackThread = new UnpackThread(this, fileName2);
        if ( unpackThread->Create() != wxTHREAD_NO_ERROR ) {
            wxLogError(wxT("Не удалось создать поток для распаковки аудиокниги!"));
        }
        if ( unpackThread->Run() != wxTHREAD_NO_ERROR ) {
            wxLogError(wxT("Не удалось запустить поток для распаковки аудиокниги!"));
            return;
        }
    }
}

void MainFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void MainFrame::OnClose(wxCloseEvent& event) {
    // Шаг 1. Сохраняем позицию прослушивания
    wxLogDebug(wxT("Происходит выполнение функции OnClose()."));
    // Шаг 2. Отдаем закрытие системному обработчику
    event.Skip();
}

void MainFrame::InitializeComponents() {

    //
    m_progress = 0;

    // Шаг 0. Главное меню
    m_menuBar = new wxMenuBar();
    m_menuFile = new wxMenu();
    wxMenuItem *mFileOpen = new wxMenuItem(m_menuFile, wxID_OPEN, wxT("&Open.."));
    wxMenuItem *mFileExit = new wxMenuItem(m_menuFile, wxID_EXIT, wxT("&Quit"));
    m_menuFile->Append(mFileOpen);
    m_menuFile->Append(mFileExit);
    m_menuBar->Append(m_menuFile, wxT("&File"));
    SetMenuBar(m_menuBar);

    // Шаг 1. Основная панель приложения
    m_main = new wxPanel(this, wxID_ANY);
    // Шаг 2. Основной виджет приложения
    m_view = new ChapterList(m_main, wxID_ANY);
    // Шаг 3. Проигрыватель
    m_player = new PlayerPanel(m_main);
    m_player->SetDuration(3 * 3600 + 2 * 60 + 34);
    m_player->SetPos(30);
}

void MainFrame::SetupLayout() {
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_view, 1, wxALL | wxEXPAND);
    sizer->Add(m_player, 0, wxALL | wxEXPAND);
    m_main->SetSizer(sizer);
}

void MainFrame::OnUnpackProgress(wxThreadEvent& event) {
    wxLogDebug(wxT("Обновляем интерфейс."));
    m_progress += 1;
}

void MainFrame::OnUnpackComplete(wxThreadEvent& event) {
    AudokApp& audokApp = wxGetApp();
    AppState& appState = audokApp.m_state;

    wxLogDebug(wxT("Можно разблокировать интерфейс."));
    appState.m_reading = false;

    // Отправим себе новое сообщение
    wxCommandEvent updateEvent(BOOK_UPDATE_EVENT);
    this->GetEventHandler()->QueueEvent(updateEvent.Clone());
}

void MainFrame::OnBookUpdate(wxCommandEvent& event) {
    // Шаг 1. Рассылаем событие дочерним компонентам о изменении книги
    wxCommandEvent updateEvent(BOOK_UPDATE_EVENT);
    m_view->GetEventHandler()->QueueEvent(updateEvent.Clone());
}

void MainFrame::BindEvents() {
    // Системные события
    Bind(wxEVT_MENU, &MainFrame::OnOpen, this, wxID_OPEN);
    Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);
    Bind(wxEVT_THREAD, &MainFrame::OnUnpackComplete, this, EVENT_UNPACK_COMPLETE);
    Bind(wxEVT_THREAD, &MainFrame::OnUnpackProgress, this, EVENT_UNPACK_UPDATE);
    // Пользовательские события
    Bind(BOOK_UPDATE_EVENT, &MainFrame::OnBookUpdate, this);
}

