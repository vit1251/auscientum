cmake_minimum_required(VERSION 3.20)

project(auscientum C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 2.5 COMPONENTS audio graphics window system REQUIRED)
find_package(libzip REQUIRED)
find_package(TagLib REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(wxWidgets REQUIRED COMPONENTS base core)
find_package(SQLite3 REQUIRED)

file(GLOB CXX_SOURCES "src/App.cpp"
        "src/BookView.cpp"
        "src/BookList.cpp"
        "src/Bookmark.cpp"
        "src/ChapterView.cpp"
        "src/ChapterList.cpp"
        "src/AppState.cpp"
        "src/MainFrame.cpp"
        "src/Player.cpp"
        "src/PlayerPanel.cpp"
        "src/UnpackThread.cpp"
        "src/common/Hash.cpp"
        "src/archive/ZipStore.cpp"
        "src/meta/Book.cpp"
        "src/meta/Chapter.cpp"
        "src/compat/xdg.cpp"
        "src/compat/fsx.cpp"
        "src/compat/str.cpp"
        "src/compat/ZipArchive.cpp"
        "src/Config.cpp"
        "src/info/Tag.cpp"
    )

list(APPEND SOURCES ${CXX_SOURCES})

add_executable(auscientum ${SOURCES})

target_include_directories(auscientum PRIVATE "res")
target_include_directories(auscientum PRIVATE "include")
target_include_directories(auscientum PRIVATE "src")
target_include_directories(auscientum PRIVATE "src/archive")
target_include_directories(auscientum PRIVATE "src/meta")
target_include_directories(auscientum PRIVATE "src/common")
target_include_directories(auscientum PRIVATE "src/compat")
target_include_directories(auscientum PRIVATE "src/info")
target_include_directories(auscientum PRIVATE ${SFML_INCLUDE_DIRS})
target_include_directories(auscientum PRIVATE ${TAGLIB_INCLUDE_DIRS})

target_compile_options(auscientum PRIVATE ${SFML_CXX_FLAGS})

target_link_libraries(auscientum PRIVATE sfml-audio sfml-window sfml-system sfml-graphics)
target_link_libraries(auscientum PRIVATE libzip::zip)
target_link_libraries(auscientum PRIVATE TagLib::tag)
target_link_libraries(auscientum PRIVATE OpenSSL::SSL)
target_link_libraries(auscientum PRIVATE wxWidgets::wxWidgets)
target_link_libraries(auscientum PRIVATE SQLite::SQLite3)
