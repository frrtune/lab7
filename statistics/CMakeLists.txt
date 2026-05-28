add_library(statistics INTERFACE)
target_include_directories(statistics INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../transfinite_numbers
    ${CMAKE_CURRENT_SOURCE_DIR}/../streams
    ${CMAKE_CURRENT_SOURCE_DIR}/../optional
    ${CMAKE_CURRENT_SOURCE_DIR}/../lab5
)
target_link_libraries(statistics INTERFACE 
    optional
    streams
)