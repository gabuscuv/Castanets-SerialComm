#pragma once

#include <thread>

struct InputFrame;
class SerialComm;
class JsonParser;
typedef void (*InputCallBack)(InputFrame);

class CastasnetInternal {

public:
    static CastasnetInternal* getInstance();
    void init();
    void setNewParsedCallback(InputCallBack dataParsed);
    void exit();
private:
    
    static std::unique_ptr<CastasnetInternal> instance;
    const static int sleep_timeout = 1; // seconds
    bool isRunning = false;
    static std::thread threadId;
    std::unique_ptr<JsonParser> jsonParser;
    std::unique_ptr<SerialComm> serialComm;
    InputCallBack inputCallback;

    void emitGameEngineCallback(InputFrame dataParsed);

};