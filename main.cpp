/**
 * @file main.cpp
 * @author I_cool
 * @brief There is simple comunication module build on https://github.com/microsoft/cpprestsdk.
 * @version 0.1
 * @date 2020-12-12
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "communicationModule.hpp"
#include "config.hpp"

#include <iostream>
#include <algorithm>

#include "plog/Initializers/RollingFileInitializer.h"
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Appenders/ColorConsoleAppender.h>

using namespace std;

std::string getDateTime();
void serversResponse(IncomingMessage msg);

int main(int argc, char *argv[])
{
    static plog::RollingFileAppender<plog::TxtFormatter> fileAppender("log.txt", 8000, 3);
    static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
    plog::init(plog::debug, &consoleAppender).addAppender(&fileAppender);

    Config::LoadConfiguration("config.json");

    CommunicationModule communication(std::bind(serversResponse, std::placeholders::_1));

    LOGE_IF(communication.start()) << "Failed start";

    OutgoingMessage msg;
    msg.timestamp = getDateTime();
    msg.img = cv::imread("Lenna.png");
    msg.systemCondition = SystemCondition::Info;

    for (size_t i = 0; i < 10; i++)
    {
        msg.zone.push_back(i);
    }

    while (true)
    {
        LOGE_IF(!communication.sendMessage(msg)) << "error send message";
        sleep(10);
    }

    std::string line;
    std::getline(std::cin, line);

    return 0;
}

/**
 * @brief Get the Date Time
 * 
 * @return std::string
 */
std::string getDateTime()
{
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch());
    return std::to_string(ms.count());
}

/**
 * @brief Event - server response
 * 
 * @param msg IncomingMessage
 */
void serversResponse(IncomingMessage msg)
{
    LOGI << "recognition = " << msg.EnablePeopleRecognition << std::endl;
    LOGI << "motion = " << msg.EnableMotionDetection << std::endl;
}