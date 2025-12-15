
#include "stdwx.h"

#include "AppState.hpp"
#include "App.hpp"
#include "BookList.hpp"


BookList::BookList(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style) : wxPanel(parent, id, pos, size, style) {
    InitializeComponents();
    SetupLayout();
    BindEvents();
}

BookList::~BookList() {
}

void BookList::InitializeComponents() {
}

void BookList::SetupLayout() {
}

void BookList::BindEvents() {
}
