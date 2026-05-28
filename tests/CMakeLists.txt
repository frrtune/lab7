add_executable(tests_lazy_sequence
    tests_lazy_sequence.cpp
)
target_link_libraries(tests_lazy_sequence
    gtest_main
    optional
    generator
    cardinals
    ordinals
    lazy_sequence
    statistics
)
target_include_directories(tests_lazy_sequence PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../lab5
)
include(GoogleTest)
gtest_discover_tests(tests_lazy_sequence)