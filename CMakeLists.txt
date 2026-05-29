cmake_minimum_required(VERSION 3.15)
project(LAB7 VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(optional)
add_subdirectory(transfinite_numbers)
add_subdirectory(generator)
add_subdirectory(lazy_sequence)
add_subdirectory(streams)
add_subdirectory(statistics)
add_subdirectory(lab5)

find_path(PDCURSES_INCLUDE_DIR
    NAMES curses.h
    PATHS
        ${CMAKE_CURRENT_SOURCE_DIR}/lab5/pdcurses
        C:/msys64/mingw64/include/pdcurses
        C:/msys64/mingw64/include
)

find_library(PDCURSES_LIBRARY
    NAMES pdcurses libpdcurses
    PATHS
        ${CMAKE_CURRENT_SOURCE_DIR}/lab5/pdcurses
        C:/msys64/mingw64/lib
)

add_subdirectory(ui)

add_executable(lab7_main 
    main.cpp
)

target_link_libraries(lab7_main
    ui
    ${PDCURSES_LIBRARY}
)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_subdirectory(tests)