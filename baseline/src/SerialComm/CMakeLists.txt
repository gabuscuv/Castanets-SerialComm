target_link_libraries( ${PROJECT_NAME}
    PRIVATE
    asio
)

if(${CMAKE_SYSTEM_NAME} STREQUAL Linux)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(UDEV REQUIRED IMPORTED_TARGET libudev)

    target_link_libraries(${PROJECT_NAME}
        PRIVATE
            PkgConfig::UDEV
    )
endif()

target_sources(${PROJECT_NAME} 
    PRIVATE

    ${CMAKE_CURRENT_LIST_DIR}/serialComm.cpp
    ${CMAKE_CURRENT_LIST_DIR}/serialComm.hpp
    ${CMAKE_CURRENT_LIST_DIR}/serialCommImpl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/serialCommImpl.h
    
    ${CMAKE_CURRENT_LIST_DIR}/serialDetector.h
    ${CMAKE_CURRENT_LIST_DIR}/serialDetector.cpp
)