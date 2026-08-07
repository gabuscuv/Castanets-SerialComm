#include "mainLib.h"
#include "serialComm.h"
#include "jsonParse.h"

K2_Castasnet* K2_Castasnet::instance = nullptr;

void K2_Castasnet::init() {
    jsonParser = new JsonParser;
    serialComm = new SerialComm;

    jsonParser->newDataAvaliable
        .connect<&K2_Castasnet::emitGameEngineCallback>(this);

    serialComm->newDataAvaliable
        .connect<&JsonParser::onNewData>(jsonParser);

    serialComm->init();
}

void K2_Castasnet::setNewParsedCallback(InputCallBack dataParsed) {
  
}

void K2_Castasnet::emitGameEngineCallback(InputFrame dataParsed)
{
    
}

K2_Castasnet *K2_Castasnet::getInstance() {
    if (instance == nullptr)
    {
        instance = new K2_Castasnet();
    }
    
    return instance;
}