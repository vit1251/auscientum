#ifndef BOOKLIST_HPP__
#define BOOKLIST_HPP__

class BookList : public wxPanel {
    protected:
    public:
        BookList(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style);
        ~BookList();
    public:
        void InitializeComponents();
        void SetupLayout();
        void BindEvents();

};

#endif // BOOKLIST_HPP__
