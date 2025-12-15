#ifndef CHAPTERVIEW_HPP__
#define CHAPTERVIEW_HPP__

class ChapterView : public wxPanel {
    protected:
    public:
        ChapterView(wxWindow* parent, wxWindowID id);
        ChapterView(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style);
        ~ChapterView();
    public:
        void InitializeComponents();
        void SetupLayout();
        void BindEvents();
    public:
        void OnPaint(wxPaintEvent& event);

};

#endif // CHAPTERVIEW_HPP__
