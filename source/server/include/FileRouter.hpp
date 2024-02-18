#pragma once

#include <string>
#include <fstream>
#include <memory>

#include "structures/include/LruCache.hpp"

namespace server
{
    class FileRouter
    {
    public:
        FileRouter();
        static FileRouter& getInstance();

        std::string getFileContentFromPath(const std::string& path);
        std::string getFileContent(std::ifstream& file);
        std::ifstream getFileFromPath(const std::string& path);

    private:
        SK::LruCache<std::string, std::string> m_FileCache;
    };
}
