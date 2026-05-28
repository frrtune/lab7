add_library(generator INTERFACE)
target_include_directories(generator INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(generator INTERFACE 
    exceptions
    optional
)