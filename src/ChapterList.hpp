#ifndef CHAPTERLIST_HPP__
#define CHAPTERLIST_HPP__

class ChapterList : public wxScrolledWindow {
    protected:
        void OnBookUpdate(wxCommandEvent& event);                 // Обработчик события от загрузчика книги
    protected:
        wxBoxSizer* m_sizer;             // Основной сайзер компонента
    public:
        ChapterList(wxWindow* parent, wxWindowID id);
        ~ChapterList();
    public:
        void InitializeComponents();
        void SetupLayout();
        void BindEvents();
};

#endif // CHAPTERLIST_HPP__
