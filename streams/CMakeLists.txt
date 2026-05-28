add_library(streams INTERFACE)
target_include_directories(streams INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../optional
)
target_link_libraries(streams INTERFACE 
    optional
)