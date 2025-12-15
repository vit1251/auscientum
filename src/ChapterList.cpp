
#include "stdwx.h"

#include "AppState.hpp"
#include "App.hpp"
#include "ChapterList.hpp"

ChapterList::ChapterList(wxWindow* parent, wxWindowID id) {
    InitializeComponents();
    SetupLayout();
    BindEvents();
}

ChapterList::ChapterList(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style) : wxPanel(parent, id, pos, size, style) {
    InitializeComponents();
    SetupLayout();
    BindEvents();
}

ChapterList::~ChapterList() {
}

void ChapterList::InitializeComponents() {

}

void ChapterList::SetupLayout() {
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
//    sizer->Add(m_view, 1, wxALL | wxEXPAND);
//    sizer->Add(m_player, 0, wxALL | wxEXPAND);
    SetSizer(sizer);
}

void ChapterList::BindEvents() {

}
