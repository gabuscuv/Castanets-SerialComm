add_library(asio INTERFACE)

target_include_directories(asio
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/asio-src/include
)

target_compile_definitions(asio
    INTERFACE
        ASIO_STANDALONE
)

if (WIN32)
    target_link_libraries(asio INTERFACE ws2_32)
endif()