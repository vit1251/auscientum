
#include "stdwx.h"

#include "AppState.hpp"
#include "MainFrame.hpp"
#include "App.hpp"
#include "Hash.hpp"


bool AudokApp::OnInit() {
    MainFrame* frame = new MainFrame();
    frame->Show(true);
    return true;
}

IMPLEMENT_APP(AudokApp)

wxDEFINE_EVENT(BOOK_UPDATE_EVENT, wxCommandEvent);
