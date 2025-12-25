
#include "stdwx.h"

#include "AppState.hpp"
#include "App.hpp"
#include "BookView.hpp"

BookView::BookView(wxWindow* parent, wxWindowID id) : wxPanel(parent, id)
{
    InitializeComponents();
    SetupLayout();
    BindEvents();
}

BookView::BookView(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style) : wxPanel(parent, id, pos, size, style)
{
    InitializeComponents();
    SetupLayout();
    BindEvents();
}

BookView::~BookView() {
}

void BookView::InitializeComponents() {
}

void BookView::SetupLayout() {
}

void BookView::BindEvents() {
    Bind(wxEVT_PAINT, &BookView::OnPaint, this);
//    Bind(wxEVT_TIMER, &BookView::OnTimer, this, ID_TIMER);
}

void BookView::OnPaint(wxPaintEvent& event)
{
    wxSize size = GetClientSize();
    wxPaintDC dc(this);

    AudokApp& audokApp = wxGetApp();
    AppState& appState = audokApp.m_state;

    dc.SetBackgroundMode(wxSOLID);
    dc.SetTextForeground(*wxBLACK);

    // Draw the chapter title
    wxString title = "Chapter Title";
    dc.DrawText(title, 10, 10);

    // Draw the play button
//    wxBitmap playBitmap("play_button.png");
//    dc.DrawBitmap(playBitmap, 10, 50);

    // Draw the progress bar
    int progressBarWidth = size.GetWidth() - 20;
    int progressBarHeight = 20;
    int progressValue = 50; // Example value

    dc.SetPen(*wxBLACK_PEN);
    dc.SetBrush(wxBrush(wxColour(192, 192, 192)));
    dc.DrawRectangle(10, 70, progressBarWidth, progressBarHeight);

    dc.SetBrush(wxBrush(wxColour(255, 0, 0)));
    dc.DrawRectangle(10, 70, (progressValue * progressBarWidth) / 100, progressBarHeight);
}

