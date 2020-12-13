#include "config.hpp"

std::string Config::remouteServerPort = "";
std::string Config::remouteServerURI = "";
std::string Config::remouteServerName = "";
std::string Config::serverPort = "";
std::string Config::serverURI = "";
std::string Config::serverName = "";
std::string Config::pathToTmpFolder = "";
std::string Config::pathToBackUpFolder = "";

void Config::LoadConfiguration(std::string path)
{
    try
    {
        pt::ptree root = ControlJsonFile::LoadFile(path);

        Config::pathToTmpFolder = root.get<std::string>("PathToTmpFolder");
        Config::pathToBackUpFolder = root.get<std::string>("PathToBackUpFolder");
        Config::remouteServerPort = root.get<std::string>("RemouteServerPort");
        Config::remouteServerURI = root.get<std::string>("RemouteServerURI");
        Config::remouteServerName = root.get<std::string>("RemouteServerName");
        Config::serverPort = root.get<std::string>("ServerPort");
        Config::serverURI = root.get<std::string>("ServerURI");
        Config::serverName = root.get<std::string>("ServerName");
    }
    catch (...)
    {
        throw;
    }
}
