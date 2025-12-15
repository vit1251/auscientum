#ifndef BOOKVIEW_HPP__
#define BOOKVIEW_HPP__

class BookView : public wxPanel {
    protected:
    public:
        BookView(wxWindow* parent, wxWindowID id);
        BookView(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style);
        ~BookView();
    public:
        void InitializeComponents();
        void SetupLayout();
        void BindEvents();
    public:
        void OnPaint(wxPaintEvent& event);

};

#endif // BOOKVIEW_HPP__
