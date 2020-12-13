#include "communicationModule.hpp"

/**
 * @brief Launch server and client
 * 
 * @param f response function (Event)
 */
CommunicationModule::CommunicationModule(std::function<void(IncomingMessage)> f) : responseFunction(f)
{
    try
    {
        this->pathToFolder = Config::pathToTmpFolder;
        utility::string_t serverAddress = Config::serverURI;
        serverAddress.append(Config::serverPort);
        serverAddress.append(Config::serverName);

        uri_builder serverURI(serverAddress);

        auto serverAddr = serverURI.to_uri().to_string();
        this->_server = new Server(serverAddr, responseFunction);

        utility::string_t remouteServerAddress = Config::remouteServerURI;

        remouteServerAddress.append(Config::remouteServerPort);
        remouteServerAddress.append(Config::remouteServerName);
        uri_builder remouteServerURI(remouteServerAddress);

        auto remouteServerAddr = remouteServerURI.to_uri().to_string();
        this->_client = new Client(remouteServerAddr);
    }
    catch (const std::exception &e)
    {
        LOGE << e.what();
    }
}

CommunicationModule::~CommunicationModule()
{
    this->stop();

    if (this->_server != NULL)
    {
        delete this->_server;
        this->_server = NULL;
    }

    if (this->_client != NULL)
    {
        delete this->_client;
        this->_client = NULL;
    }
}

/**
 * @brief Start server
 * 
 * @return true 
 * @return false 
 */
bool CommunicationModule::start(void)
{
    try
    {
        LOGI << "start";
        if (this->_server == NULL)
        {
            LOGE << "Server is NULL";
            return false;
        }

        if (this->_server->openServer())
        {
            LOGE << "Server is opened uri = " + this->_server->getUri();
            return true;
        }
        else
        {
            LOGE << "Error openServer()";
            return false;
        }
    }
    catch (const std::exception &e)
    {
        LOGE << e.what();
        return false;
    }
}

/**
 * @brief Stop server
 * 
 */
void CommunicationModule::stop(void)
{
    try
    {
        LOGI << "stop";
        if (this->_server != NULL)
        {
            this->_server->closeServer();
        }
    }
    catch (const std::exception &e)
    {
        LOGE << e.what();
    }
}

/**
 * @brief Send Message
 * 
 * @param msg 
 * @return true 
 * @return false 
 */
bool CommunicationModule::sendMessage(OutgoingMessage &msg)
{
    bool sendingSuccessful = false;

    try
    {
        PLOGI << "sendMessage";
        if (msg.img.empty())
        {
            LOGE << "Image is empty";
            return false;
        }

        std::string path = this->pathToFolder + msg.timestamp + ".png";

        if (!cv::imwrite(path, msg.img))
        {
            LOGE << "Error write image";
            return false;
        }

        msg.pathToFile = path;

        try
        {
            if (this->_client == NULL)
            {
                LOGE << "Client is NULL";
            }
            else
            {
                sendingSuccessful = this->_client->sendMessage(msg);
            }
        }
        catch (...)
        {
            sendingSuccessful = false;
        }

        if (sendingSuccessful)
        {
            LOGI << "Message sending successful";
        }
        else
        {
            LOGE << "Error sending message";
            this->saveMessage(msg);
            sendingSuccessful = true;
        }
    }
    catch (std::exception &e)
    {
        LOGE << e.what();
    }

    return sendingSuccessful;
}

/**
 * @brief Save message. If the message cannot be sent, you need to save it for sending later
 * 
 * @param msg 
 */
void CommunicationModule::saveMessage(const OutgoingMessage &msg)
{
    try
    {
        LOGI << "saveMessage";
        pt::ptree root;
        root.put("timestamp", msg.timestamp);
        root.put("typeOfEvent", std::to_string(msg.systemCondition));

        pt::ptree zone_node;
        for (points::const_iterator it = msg.zone.begin(); it != msg.zone.end(); ++it)
        {
            pt::ptree node;
            node.put("", (*it));
            zone_node.push_back(std::make_pair("", node));
        }

        root.add_child("zone", zone_node);
        root.put("file", msg.pathToFile);

        pt::write_json(Config::pathToBackUpFolder + msg.timestamp + ".json", root);
    }
    catch (...)
    {
        throw;
    }
}