#include "server/include/FileRouter.hpp"
#include "Config.hpp"

#include <sstream>
#include <iostream>

namespace server
{

FileRouter::FileRouter()
    : m_FileCache(config::SK_FILE_CACHE_CAPACITY)
{
}

FileRouter& FileRouter::getInstance()
{
    static FileRouter instance;
    return instance;
}

std::string FileRouter::getFileContentFromPath(const std::string& path)
{
    // Check if file is in cache:
    auto result = m_FileCache.get(path);
    if(result.has_value())
    {
        std::string str = result.value();
        return str;
    }

    std::ifstream file = getFileFromPath(path);
    std::string fileContent = getFileContent(file);
    m_FileCache.insert(path, fileContent);
    return fileContent;
}

std::string FileRouter::getFileContent(std::ifstream& file)
{
    std::string buffer;
    file.seekg(0, std::ios::end);
    buffer.resize(file.tellg());
    file.seekg(0);
    file.read(buffer.data(), buffer.size());
    return buffer;
}

std::ifstream FileRouter::getFileFromPath(const std::string& path)
{
    std::ifstream file;

    // TODO : Handle error for missing or invalid file

    file.open(path);
    return file;
}

} // namespace server
