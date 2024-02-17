#include "server/include/FileRouter.hpp"

namespace server
{

FileRouter& FileRouter::getInstance()
{
    static FileRouter instance;
    return instance;
}

std::string FileRouter::getFileContentFromPath(const std::string& path)
{
    std::ifstream file = getFileFromPath(path);
    return getFileContent(file);
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
    file.open(path);
    return file;
}

} // namespace server
