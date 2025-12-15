
#include "stdwx.h"

#include "AppState.hpp"
#include "Player.hpp"
#include "MainFrame.hpp"
#include "App.hpp"
#include "Hash.hpp"


bool AudokApp::OnInit() {
    MainFrame* frame = new MainFrame();
    frame->Show(true);
    return true;
}

IMPLEMENT_APP(AudokApp)
