#ifndef CHAPTERLIST_HPP__
#define CHAPTERLIST_HPP__

class ChapterList : public wxPanel {
    protected:
    public:
        ChapterList(wxWindow* parent, wxWindowID id);
        ChapterList(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style);
        ~ChapterList();
    public:
        void InitializeComponents();
        void SetupLayout();
        void BindEvents();

};

#endif // CHAPTERLIST_HPP__
