#ifndef PLAYER_PANEL_HPP__
#define PLAYER_PANEL_HPP__

wxDECLARE_EVENT(PLAYER_CHANGE_POSITION, wxCommandEvent);

class PlayerPanel : public wxPanel {
    private:
        unsigned m_position;                              // Позиция проигрывателя аудиозаписи
        unsigned m_duration;                              // Длительность аудиозаписи
        wxTimer* m_timer;                                 // Таймер для обновления позиции
        wxPanel* m_progress;                              // Панель положения проигрывателя
        wxBitmapButton* m_play;                           // Кнопка проигрывания
        wxBitmapButton* m_pause;                          // Кнопка перемотки вперед
        wxStaticText* m_info;                             // Информационное табло
    private:
        void InitializeComponents();
        void SetupLayout();
        void BindEvents();
    protected:
        void ProgressOnTimer(wxTimerEvent& event);
        void ProgressOnPaint(wxPaintEvent& event);
        void ProgressOnMouseClick(wxMouseEvent& event);
        void OnPlay(wxCommandEvent& event);
        void OnPause(wxCommandEvent& event);
    public:
        PlayerPanel(wxWindow* parent);
        ~PlayerPanel();
        void SetPos(unsigned sec);
        void SetDuration(unsigned sec);
};

#endif // PLAYER_PANEL_HPP__
