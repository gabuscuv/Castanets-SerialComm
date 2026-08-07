#include "lib.h"
#include <iostream>
#include "mainLib.h"

int getExample()
{
    return 42;
};

int castasnet_exit()
{
    return 0;
}

int castasnet_init(InputCallBack functionCallback)
{
    std::cout << "Starting Init castasnet." << std::endl;
    K2_Castasnet::getInstance()->setNewParsedCallback(functionCallback);
    K2_Castasnet::getInstance()->init();

    return 0;
};