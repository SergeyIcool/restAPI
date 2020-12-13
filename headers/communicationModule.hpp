#pragma once

#include "plog/Log.h"

#include "client.hpp"
#include "server.hpp"

#include "control_json_file.hpp"

#include <opencv2/imgcodecs.hpp>

class CommunicationModule
{
private:
    Client *_client;
    Server *_server;

public:
    CommunicationModule(std::function<void(IncomingMessage)>);
    virtual ~CommunicationModule(void);

    bool sendMessage(OutgoingMessage &);
    bool start(void);
    void stop(void);

private:
    std::function<void(IncomingMessage)> responseFunction;
    std::string pathToFolder;

    void saveMessage(const OutgoingMessage &);
};
