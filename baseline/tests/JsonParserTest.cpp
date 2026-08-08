#include <gtest/gtest.h>

#include "jsonParse.h"
#include "helpers/JsonParser/JsonParserReceiver.hpp"
#include <string>
#include <vector>

class JsonParserTest : public ::testing::Test
{
protected:
    static constexpr const char* validJson = R"json(
    {
        "version": 1,
        "type": "controller",
        "hubTime": 123456789,

        "leftController": {
            "clicks": [
                {
                    "time": 100,
                    "button": "A"
                },
                {
                    "time": 200,
                    "button": "B"
                }
            ],
            "imu": {
                "time": 300,
                "x": 1.5,
                "y": -2.5,
                "z": 3.5
            }
        },

        "rightController": {
            "clicks": [
                {
                    "time": 400,
                    "button": "X"
                }
            ],
            "imu": {
                "time": 500,
                "x": -1.0,
                "y": 2.0,
                "z": -3.0
            }
        },

        "feetController": [
            {
                "time": 600,
                "value": 0.25
            },
            {
                "time": 700,
                "value": 0.75
            }
        ]
    }
    )json";
};

TEST_F(JsonParserTest, ParsesCompleteInputFrame)
{
    const InputFrame frame =
        JsonParser::parseJson(validJson);

    EXPECT_EQ(frame.version, 1);
    EXPECT_EQ(frame.type, "controller");
    EXPECT_EQ(frame.hubTime, 123456789);

    // Left controller

    ASSERT_EQ(frame.leftController.clicks.size(), 2);

    EXPECT_EQ(
        frame.leftController.clicks[0].time,
        100);

    EXPECT_EQ(
        frame.leftController.clicks[0].button,
        "A");

    EXPECT_EQ(
        frame.leftController.clicks[1].time,
        200);

    EXPECT_EQ(
        frame.leftController.clicks[1].button,
        "B");

    EXPECT_EQ(
        frame.leftController.imu.time,
        300);

    EXPECT_FLOAT_EQ(
        frame.leftController.imu.x,
        1.5f);

    EXPECT_FLOAT_EQ(
        frame.leftController.imu.y,
        -2.5f);

    EXPECT_FLOAT_EQ(
        frame.leftController.imu.z,
        3.5f);

    // Right controller

    ASSERT_EQ(frame.rightController.clicks.size(), 1);

    EXPECT_EQ(
        frame.rightController.clicks[0].time,
        400);

    EXPECT_EQ(
        frame.rightController.clicks[0].button,
        "X");

    EXPECT_EQ(
        frame.rightController.imu.time,
        500);

    EXPECT_FLOAT_EQ(
        frame.rightController.imu.x,
        -1.0f);

    EXPECT_FLOAT_EQ(
        frame.rightController.imu.y,
        2.0f);

    EXPECT_FLOAT_EQ(
        frame.rightController.imu.z,
        -3.0f);

    // Feet

    ASSERT_EQ(frame.feetController.size(), 2);

    EXPECT_EQ(
        frame.feetController[0].time,
        600);

    EXPECT_FLOAT_EQ(
        frame.feetController[0].value,
        0.25f);

    EXPECT_EQ(
        frame.feetController[1].time,
        700);

    EXPECT_FLOAT_EQ(
        frame.feetController[1].value,
        0.75f);
}

TEST_F(JsonParserTest, OnNewDataEmitsParsedFrame)
{
    JsonParser parser;
    JsonParserReceiver receiver;

    parser.newDataAvaliable
        .connect<&JsonParserReceiver::onData>(&receiver);

    parser.onNewData(validJson);

    ASSERT_TRUE(receiver.received);

    const auto& frame = receiver.frameReceived;

    EXPECT_EQ(frame.version, 1);
    EXPECT_EQ(frame.type, "controller");
    EXPECT_EQ(frame.hubTime, 123456789);

    ASSERT_EQ(frame.leftController.clicks.size(), 2);

    EXPECT_EQ(
        frame.leftController.clicks[0].button,
        "A");

    EXPECT_FLOAT_EQ(
        frame.leftController.imu.x,
        1.5f);
}