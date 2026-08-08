add_subdirectory(SerialComm)

target_sources(${PROJECT_NAME} 
    PRIVATE    
    
    dataStruct_json.h
    mainLib.h
    mainLib.cpp
    jsonParse.h
    jsonParse.cpp
)

