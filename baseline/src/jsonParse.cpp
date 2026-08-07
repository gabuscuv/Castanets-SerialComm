#include "jsonParse.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;

InputFrame JsonParser::parseJson(const char* json)
{
    const auto data = json::parse(json);
  
    return data.get<InputFrame>();
};

void JsonParser::onNewData(const char* json)
{
    InputFrame frame = parseJson(json);

    newDataAvaliable.fire(frame);
}