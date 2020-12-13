#pragma once

#include <iostream>

#include "cpprest/http_listener.h"
#include "cpprest/uri.h"
#include "cpprest/asyncrt_utils.h"
#include "cpprest/containerstream.h"
#include "cpprest/producerconsumerstream.h"

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

#include "data_types.hpp"

#include "plog/Log.h"

class Server
{

public:
    Server(utility::string_t, std::function<void(IncomingMessage)>);
    virtual ~Server(void);

    bool openServer(void);
    void closeServer(void);

    std::string getUri(void);

private:
    pplx::task<void> open() { return m_listener.open(); }
    pplx::task<void> close() { return m_listener.close(); }

    void serverPost(http_request message);
    void serverError(http_request message);
    http_listener m_listener;
    std::function<void(IncomingMessage)> responseFunction;
    http::uri _serversUri;
};
