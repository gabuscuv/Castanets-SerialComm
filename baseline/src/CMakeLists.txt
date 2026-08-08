add_subdirectory(SerialComm)
add_subdirectory(JsonParser)

target_sources(${PROJECT_NAME} 
    PRIVATE    
    
    mainLib.h
    mainLib.cpp
)

