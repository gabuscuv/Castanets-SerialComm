#include "lib.h"
#include <iostream>
#include "mainLib.h"
#include "spdlog/spdlog.h"

int getExample()
{
    return 42;
};

int castasnet_exit()
{
    CastasnetInternal::getInstance()->exit();
    return 0;
}

int castasnet_init(InputCallBack functionCallback) {
    spdlog::info("Starting Init castasnet Entry Point.");
    CastasnetInternal::getInstance()->setNewParsedCallback(functionCallback);
    CastasnetInternal::getInstance()->init();

    return 0;
};