add_subdirectory(SerialComm)
add_subdirectory(JsonParser)

target_sources(${PROJECT_NAME} 
    PRIVATE    
    
    ${CMAKE_CURRENT_LIST_DIR}/mainLib.h
    ${CMAKE_CURRENT_LIST_DIR}/mainLib.cpp
)

