#include "shared/dataStruct.h"
class JsonParserReceiver
{
public:
    void onData(InputFrame frame)
    {
        received = true;
        frameReceived = frame;
    }

    bool received = false;
    InputFrame frameReceived{};
};