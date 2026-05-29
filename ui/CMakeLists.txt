add_library(ui STATIC
    ui.cpp
)

target_include_directories(ui PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${PDCURSES_INCLUDE_DIR}
)

target_link_libraries(ui
    optional
    generator
    cardinals
    ordinals
    lazy_sequence
    streams
    statistics
    ${PDCURSES_LIBRARY}
)