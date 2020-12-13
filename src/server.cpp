#include "server.hpp"

Server::Server(utility::string_t url, std::function<void(IncomingMessage)> f)
    : m_listener(url), responseFunction(f)
{
    try
    {
        this->_serversUri = http::uri();

        m_listener.support(methods::POST, std::bind(&Server::serverPost, this,
                                                    std::placeholders::_1));

        // m_listener.support(methods::CONNECT, std::bind(&Server::serverError, this,
        //                                                std::placeholders::_1));
    }
    catch (...)
    {
        throw;
    }
}

Server::~Server()
{
    this->close().wait();
}

bool Server::openServer(void)
{
    try
    {
        this->open().wait();
        this->_serversUri = this->m_listener.uri();
        return true;
    }
    catch (...)
    {
        throw;
    }
}

void Server::closeServer(void)
{
    try
    {
        this->close().wait();
    }
    catch (...)
    {
        throw;
    }
}

void Server::serverPost(http_request message)
{
    try
    {
        PLOGD << "server_post msg = " << message.to_string();

        json::value jsonRequest = message.extract_json().get();

        IncomingMessage msg;
        msg.EnablePeopleRecognition = jsonRequest.at(U("recognition")).as_bool();
        msg.EnableMotionDetection = jsonRequest.at(U("motion")).as_bool();

        this->responseFunction(msg);

        message.reply(status_codes::OK);
    }
    catch (const std::exception &e)
    {
        PLOGE << e.what();
    }

    message.reply(status_codes::BadRequest);
}

void Server::serverError(http_request message)
{
    LOGE << "error";
}

std::string Server::getUri(void)
{
    return this->_serversUri.to_string();
}
