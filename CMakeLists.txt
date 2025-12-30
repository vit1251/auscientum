cmake_minimum_required(VERSION 3.20)

project(auscientum C CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(PkgConfig REQUIRED)

find_package(SFML 2.5 COMPONENTS audio graphics window system REQUIRED)
find_package(libzip REQUIRED)
#find_package(TagLib REQUIRED)
pkg_check_modules(TAGLIB REQUIRED IMPORTED_TARGET taglib)
pkg_check_modules(OPENSSL REQUIRED IMPORTED_TARGET openssl)
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
        "src/PlayerPanel.cpp"
        "src/UnpackThread.cpp"
        "src/archive/ZipStore.cpp"
        "src/meta/Book.cpp"
        "src/meta/Chapter.cpp"
        "src/compat/Hash.cpp"
        "src/compat/StopWatch.cpp"
        "src/compat/xdg.cpp"
        "src/compat/fsx.cpp"
        "src/compat/str.cpp"
        "src/compat/ZipArchive.cpp"
        "src/Config.cpp"
        "src/audio/AudioPlayer.cpp"
        "src/audio/Tag.cpp"
        "src/audio/Duration.cpp"
        "src/repo/BookmarkRepo.cpp"
    )

list(APPEND SOURCES ${CXX_SOURCES})

add_executable(auscientum ${SOURCES})

target_include_directories(auscientum PRIVATE "res")
target_include_directories(auscientum PRIVATE "include")
target_include_directories(auscientum PRIVATE "src")
target_include_directories(auscientum PRIVATE "src/repo")
target_include_directories(auscientum PRIVATE "src/archive")
target_include_directories(auscientum PRIVATE "src/meta")
target_include_directories(auscientum PRIVATE "src/compat")
target_include_directories(auscientum PRIVATE "src/audio")
target_include_directories(auscientum PRIVATE ${SFML_INCLUDE_DIRS})
target_include_directories(auscientum PRIVATE ${TAGLIB_INCLUDE_DIRS})

target_compile_options(auscientum PRIVATE ${SFML_CXX_FLAGS})

target_link_libraries(auscientum PRIVATE sfml-audio sfml-window sfml-system sfml-graphics)
target_link_libraries(auscientum PRIVATE libzip::zip)
target_link_libraries(auscientum PRIVATE wxWidgets::wxWidgets)
target_link_libraries(auscientum PRIVATE SQLite::SQLite3)

target_link_libraries(auscientum PRIVATE PkgConfig::TAGLIB)
target_link_libraries(auscientum PRIVATE PkgConfig::OPENSSL)


##########
### Test

# Test 1 - Check Hash (SHA256)

add_executable(test_hash 
        "tests/test_hash.cpp"
        "src/compat/Hash.cpp"
    )
target_include_directories(test_hash PRIVATE "src/compat")
target_link_libraries(test_hash PRIVATE PkgConfig::OPENSSL)
add_test(NAME "Hash Test" COMMAND test_hash)

# Test 2 - Check
