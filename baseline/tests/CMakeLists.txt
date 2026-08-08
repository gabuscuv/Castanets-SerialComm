find_package(GTest REQUIRED)

set(TARGET CASTANETS_SERIALCOMM_TESTS)

add_executable(${TARGET}
    SerialCommTest.cpp
    JsonParserTest.cpp
)

add_subdirectory(helpers)

target_include_directories(CASTANETS_SERIALCOMM_TESTS
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/extern/nano-signal-slot/nano-signal-slot-src
        ${PROJECT_SOURCE_DIR}/extern/json/include
)

target_link_libraries(CASTANETS_SERIALCOMM_TESTS
    PRIVATE
        CASTANETS_SERIALCOMM
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(CASTANETS_SERIALCOMM_TESTS)