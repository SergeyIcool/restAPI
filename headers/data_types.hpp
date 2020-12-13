#pragma once

#include <iostream>
#include <opencv2/core/mat.hpp>

typedef std::vector<int> points;

/**
 * @brief System Condition
 * 
 */
enum SystemCondition
{
    None = -1,
    Info = 0,
    Warning = 1,
    Alarm = 2
};

/**
 * @brief Outgoing Message
 * 
 */
struct OutgoingMessage
{
public:
    std::string timestamp;
    SystemCondition systemCondition;
    points zone;
    cv::Mat img;
    std::string pathToFile;

    OutgoingMessage() : timestamp(), systemCondition(SystemCondition::None), zone(), img(), pathToFile() {}
};

/**
 * @brief Incoming Message
 * 
 */
struct IncomingMessage
{
public:
    bool EnablePeopleRecognition;
    bool EnableMotionDetection;
    IncomingMessage() : EnablePeopleRecognition(false), EnableMotionDetection(false) {}
};
