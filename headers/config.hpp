#pragma once

#include "control_json_file.hpp"

class Config
{
public:
    static std::string remouteServerPort;
    static std::string remouteServerURI;
    static std::string remouteServerName;
    static std::string serverPort;
    static std::string serverURI;
    static std::string serverName;
    static std::string pathToTmpFolder;
    static std::string pathToBackUpFolder;

    static void LoadConfiguration(std::string);

private:
    Config() {}
};
