#include "control_json_file.hpp"

void ControlJsonFile::SaveFile(std::string path, boost::property_tree::ptree root)
{
    try
    {
        pt::write_json(path, root);
    }
    catch (...)
    {
        throw;
    }
}

pt::ptree ControlJsonFile::LoadFile(std::string path)
{
    try
    {
        if (!fs::is_regular_file(path))
        {
            throw std::invalid_argument("File or directory not exist");
        }

        pt::ptree root;

        pt::read_json(path, root);

        return root;
    }
    catch (...)
    {
        throw;
    }
}

void ControlJsonFile::ReadDirectory(const std::string &name, stringvec &v)
{
    try
    {
        boost::filesystem::path p(name);
        boost::filesystem::directory_iterator start(p);
        boost::filesystem::directory_iterator end;
        std::transform(start, end, std::back_inserter(v), path_leaf_string());
    }
    catch (...)
    {
        throw;
    }
}

std::string ControlJsonFile::GetFilePath(std::string path)
{
    try
    {
        stringvec v;
        ReadDirectory(path, v);

        if (v.size() > 0)
        {
            return v[0];
        }

        return "";
    }
    catch (...)
    {
        throw;
    }
}

bool ControlJsonFile::RemoveFile(std::string path)
{
    try
    {
        return boost::filesystem::remove(path);
    }
    catch (...)
    {
        throw;
    }
}