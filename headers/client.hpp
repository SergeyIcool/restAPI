#pragma once

#include <cpprest/http_client.h>
#include <cpprest/json.h>

using namespace utility;           // Common utilities like string conversions
using namespace web;               // Common features like URIs.
using namespace web::http;         // Common HTTP functionality
using namespace web::http::client; // HTTP client features

#include "plog/Log.h"

#include "data_types.hpp"
#include "config.hpp"

class Client
{
private:
    http_client *_client;

public:
    Client(utility::string_t url);
    ~Client();

    bool sendMessage(const OutgoingMessage &);
};