#include "mainLib.h"
#include "SerialComm/serialComm.hpp"
#include "SerialComm/serialCommImpl.h"
#include "jsonParse.h"
#include "spdlog/spdlog.h"

std::unique_ptr<CastasnetInternal> CastasnetInternal::instance = nullptr;

void CastasnetInternal::init() {
    spdlog::info("Initializing Castanet Internals");
    jsonParser = std::make_unique<JsonParser>();
    serialComm = std::make_unique<SerialComm>();

    jsonParser->newDataAvaliable
        .connect<&CastasnetInternal::emitGameEngineCallback>(this);

    serialComm->getNewDataAvaliable()
        ->connect<&JsonParser::onNewData>(jsonParser.get());

    serialComm->start();

    isRunning = true;
}

void CastasnetInternal::exit()
{
    if (!isRunning)
    {
        spdlog::warn("Called Exit when it's not running");
        return;
    }

    spdlog::info("Exiting Castanet Internals");

    serialComm->stop();

    serialComm.reset();
    jsonParser.reset();

    isRunning = false;
}

void CastasnetInternal::setNewParsedCallback(InputCallBack dataParsed)
{
    inputCallback = dataParsed;
}

void CastasnetInternal::emitGameEngineCallback(InputFrame dataParsed)
{
    inputCallback(dataParsed);
}

CastasnetInternal *CastasnetInternal::getInstance()
{
    if (instance == nullptr)
    {
        instance = std::make_unique<CastasnetInternal>();
    };
    
    return instance.get();
}