#pragma once

#include <boost/filesystem.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/lexical_cast.hpp>

namespace pt = boost::property_tree;
namespace fs = boost::filesystem;

struct path_leaf_string
{
    std::string operator()(const boost::filesystem::directory_entry &entry) const
    {
        return entry.path().leaf().string();
    }
};

typedef std::vector<std::string> stringvec;

class ControlJsonFile
{
public:
    static void SaveFile(std::string, pt::ptree);
    static pt::ptree LoadFile(std::string);
    static std::string GetFilePath(std::string);
    static bool RemoveFile(std::string);

private:
    ControlJsonFile() {}

    static void ReadDirectory(const std::string &, stringvec &);
};