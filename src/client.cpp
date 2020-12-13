#include "client.hpp"

Client::Client(utility::string_t url)
{
    try
    {
        this->_client = new http_client(U(url));
    }
    catch (...)
    {
        throw;
    }
}

Client::~Client(void)
{
    if (this->_client != NULL)
    {
        delete this->_client;
        this->_client = NULL;
    }
}

/**
 * @brief Send Message
 * 
 * @param msg 
 * @return true 
 * @return false 
 */
bool Client::sendMessage(const OutgoingMessage &msg)
{
    try
    {
        LOGI << "sendMessage";

        if (this->_client == NULL)
        {
            throw std::invalid_argument("Client is NULL");
        }
        json::value putvalue;

        utility::string_t str = utility::conversions::to_string_t(msg.timestamp);
        putvalue[U("timestamp")] = json::value::string(str);
        str = utility::conversions::to_string_t(std::to_string(msg.systemCondition));
        putvalue[U("systemCondition")] = json::value::string(str);

        str = "[";
        for (size_t i = 0; i < msg.zone.size(); i++)
        {
            str += std::to_string(msg.zone[i]);

            if (i + 1 < msg.zone.size())
            {
                str += ",";
            }
        }
        str += "]";

        putvalue[U("zone")] = json::value::string(str);
        str = utility::conversions::to_string_t(msg.pathToFile);
        putvalue[U("file")] = json::value::string(str);

        http_response response = this->_client->request(methods::POST, U("/"), putvalue).get();

        auto code = response.status_code();

        LOGI << "request status = " << code << " request = " << putvalue.serialize();

        return code == status_codes::OK;
    }
    catch (...)
    {
        throw;
    }
}
