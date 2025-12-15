


class MainFrame : public wxFrame {
    private:
        wxPanel* m_main;                    // Основное окно приложения
        wxPanel* m_view;                    // Основное виджет приложения
        Player* m_player;                   // Компонент проигрываетля
        wxMenuBar *m_menuBar;
        wxMenu *m_menuFile;
        unsigned m_progress;
    private:
        void InitializeComponents();
        void SetupLayout();
        void BindEvents();
        // Работа с меню
        void OnOpen(wxCommandEvent& event);
        void OnExit(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnUnpackProgress(wxThreadEvent& event);
	void OnUnpackComplete(wxThreadEvent& event);
    public:
        MainFrame();
};
