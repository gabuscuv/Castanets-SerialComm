#pragma once
#include "jsonParse.h"
#include <thread>

struct InputFrame;
class SerialComm;
typedef void (*InputCallBack)(InputFrame);

class K2_Castasnet {

public:
    static K2_Castasnet* getInstance();
    void init();
    void setNewParsedCallback(InputCallBack dataParsed);
private:
  
    static K2_Castasnet* instance;
    const static int sleep_timeout = 1; // seconds
    bool is_running = false;
    static std::thread threadId;
    JsonParser * jsonParser;
    SerialComm * serialComm;

    void emitGameEngineCallback(InputFrame dataParsed);

};