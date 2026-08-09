target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/extern/json/include
)

target_link_libraries( ${PROJECT_NAME}
    PRIVATE
    nlohmann_json::nlohmann_json
)

target_sources(${PROJECT_NAME} 
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/dataStruct_json.h
    ${CMAKE_CURRENT_LIST_DIR}/jsonParser.h
    ${CMAKE_CURRENT_LIST_DIR}/jsonParser.cpp
)