#ifndef CHAPTERVIEW_HPP__
#define CHAPTERVIEW_HPP__

class Chapter;

class ChapterView : public wxPanel {
    protected:
        Chapter* m_chapter;                               // Ссылка на главу
        wxTimer* m_timer;                                 // Таймер для обновления позиции
        bool m_playing;                                   // Проигрываем сейчас
    public:
        ChapterView(Chapter* chapter, wxWindow* parent, wxWindowID id);
        ~ChapterView();
    public:
        void InitializeComponents();
        void SetupLayout();
        void BindEvents();
    public:
        void OnMouseClick(wxMouseEvent& event);
        void OnPaint(wxPaintEvent& event);
        void OnTimer(wxTimerEvent& event);
    public:
        unsigned GetPos();
};

#endif // CHAPTERVIEW_HPP__
