#ifndef UNPACKTHREAD_HPP__
#define UNPACKTHREAD_HPP__

const int EVENT_UNPACK_UPDATE   = wxID_HIGHEST + 101;   // Обновление интерфейса
const int EVENT_UNPACK_COMPLETE = wxID_HIGHEST + 102;   // Окончание блокировки

class UnpackThread : public wxThread {
    private:
        wxFrame *m_parent;                            // Родительское окно
        std::string m_fileName;                       // Имя файла с аудиокнигой
        void SendMessage(int messageType);            // Функция о завершении чтения файла
    public:
        UnpackThread(wxFrame *parent, std::string fileName);  // Конструктор
        virtual void *Entry();                                // Рутина распаковки 
};

#endif // UNPACKTHREAD_HPP__
