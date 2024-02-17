#pragma once

#include <string>
#include <unordered_map>
#include <fstream>

namespace server
{
    class FileRouter
    {
    public:
        static FileRouter& getInstance();

        std::string getFileContentFromPath(const std::string& path);
        std::string getFileContent(std::ifstream& file);
        std::ifstream getFileFromPath(const std::string& path);

    private:
        // TODO : LRU file cache
    };
}
