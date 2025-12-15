#ifndef PLAYER_HPP__
#define PLAYER_HPP__

wxDECLARE_EVENT(PLAYER_CHANGE_POSITION, wxCommandEvent);

class Player : public wxPanel {
    private:
        unsigned m_position;                              // Позиция проигрывателя аудиозаписи
        unsigned m_duration;                              // Длительность аудиозаписи
        wxTimer* m_timer;                                 // Таймер для обновления позиции
        wxPanel* m_progress;                              // Панель положения проигрывателя
        wxButton* m_play;                                 // Кнопка проигрывания
        wxButton* m_rewind_back;                          // Кнопка перемотки назад
        wxButton* m_rewind_forward;                       // Кнопка перемотки вперед
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
        void OnRewindBack(wxCommandEvent& event);
        void OnRewindForward(wxCommandEvent& event);
    public:
        Player(wxWindow* parent);
        ~Player();
        void SetPos(unsigned sec);
        void SetDuration(unsigned sec);
};

#endif // PLAYER_HPP__
