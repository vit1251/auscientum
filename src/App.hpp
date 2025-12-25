#ifndef APP_HPP__
#define APP_HPP__

class AudokApp : public wxApp {
    public:
        AppState m_state;
    public:
        virtual bool OnInit();
};

DECLARE_APP(AudokApp)

wxDECLARE_EVENT(BOOK_UPDATE_EVENT, wxCommandEvent);

#endif // APP_HPP__
