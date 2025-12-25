
#include <zip.h>


class ZipArchive {
    protected:
        zip* m_archive;
    public:
        ZipArchive();
        ~ZipArchive();
    public:
        void Open(std::string path);
        void Extract(std::string zipFile, std::string outFile);
        void Close();
};
