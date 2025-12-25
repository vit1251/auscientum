
#include <string>
#include <iostream>
#include <fstream>

#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/id3v2tag.h>
#include <taglib/id3v2frame.h>
#include <taglib/attachedpictureframe.h>
#include <taglib/mpegfile.h>

#include "Book.hpp"
#include "Chapter.hpp"


void LoadMeta(Book *book, Chapter *chapter) {

    TagLib::FileRef file(chapter->m_path.c_str());
    if (file.isNull()) {
        std::cerr << "Error: file is null" << std::endl;
        return;
    }
    TagLib::Tag *tag = file.tag();
    if (tag == nullptr) {
        std::cerr << "Error: tag is null" << std::endl;
        return;
    }

    std::string artist = tag->artist().to8Bit(true);
    std::cout << "Исполнитель: " << artist << std::endl;
    book->SetAuthor(artist);

    std::string title = tag->title().to8Bit(true);
    std::cout << "Название: " << title << std::endl;
    chapter->SetName(title);

    std::string album = tag->album().to8Bit(true);
    std::cout << "Альбом: " << album << std::endl;
    book->SetName(album);

    unsigned track = tag->track();
    std::cout << "Номер трека: " << track << std::endl;
    chapter->SetNumber(track);

    unsigned year = tag->year();
    std::cout << "Год: " << year << std::endl;
    book->SetYear(year);

}


bool extractAlbumCover(const std::string& audioFile, const std::string& outputImage) {
    TagLib::MPEG::File file(audioFile.c_str());
    
    if(!file.isValid()) {
        std::cerr << "Неверный файл" << std::endl;
        return false;
    }
    
    if(!file.ID3v2Tag()) {
        std::cerr << "Нет ID3v2 тегов" << std::endl;
        return false;
    }
    
    TagLib::ID3v2::Tag* tag = file.ID3v2Tag();
    TagLib::ID3v2::FrameList frames = tag->frameList("APIC");
    
    if(frames.isEmpty()) {
        std::cerr << "Нет обложек" << std::endl;
        return false;
    }
    
    TagLib::ID3v2::AttachedPictureFrame* picture = 
        static_cast<TagLib::ID3v2::AttachedPictureFrame*>(frames.front());
    
    if(picture) {
        // Сохраняем обложку
        std::ofstream out(outputImage, std::ios::binary);
        out.write(picture->picture().data(), picture->picture().size());
        out.close();
        std::cout << "Обложка сохранена: " << outputImage << std::endl;
        return true;
    }
    
    return false;
}
