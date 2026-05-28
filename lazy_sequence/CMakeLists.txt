add_library(lazy_sequence INTERFACE)
target_include_directories(lazy_sequence INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../lab5
)
target_link_libraries(lazy_sequence INTERFACE 
    optional
    generator
    cardinals
)