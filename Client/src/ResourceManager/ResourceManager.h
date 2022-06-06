#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "unordered_map"
#include <vector>
#include <string>
#include <dirent.h>
#include <iostream>
#include <algorithm>
#include <functional>

template <typename T>
class ResourceManager
{
public:
    ResourceManager(std::string resourceType, std::vector<std::string> supportedExtensions, std::function<T *(std::string)> loadFunction) : resourceType(resourceType), supportedExtensions(supportedExtensions), createResource(loadFunction) {}
    ResourceManager(std::string resourceType, std::vector<std::string> supportedExtensions, const char *path, std::function<T *(std::string)> loadFunction) : resourceType(resourceType), supportedExtensions(supportedExtensions), createResource(loadFunction) { load(path); }

    virtual ~ResourceManager() { clear(); };

    void load(const char *pathName)
    {
        std::cout << "Loading " << resourceType << " from " << pathName << "..." << std::endl;

        // Using dirent, check if pathName is a directory
        DIR *dir = opendir(pathName);

        // If it is a directory, load all files in it with extension .png or .jpg
        if (dir != nullptr)
        {
            // Get all files in directory
            struct dirent *ent;
            while ((ent = readdir(dir)) != nullptr)
            {
                // Get file extension
                std::string fileName = ent->d_name;
                std::string ext = fileName.substr(fileName.find_last_of(".") + 1);
                std::string fileNameWithoutExt = fileName.substr(0, fileName.find_last_of("."));

                // If file extension is .png or .jpg, load texture
                if (isSupported(ext))
                {
                    std::string filePath = pathName;
                    filePath.append("/");
                    filePath.append(fileName);

                    T *resource = createResource(filePath);

                    std::cout << "Loaded " << resourceType << " " << fileNameWithoutExt << std::endl;
                    resourceMap.insert(std::pair<std::string, T *>(fileNameWithoutExt, resource));
                }
            }

            std::cout << resourceType << "s loaded!" << std::endl;
        }
        else // If pathName is not a directory, we throw an error message
            std::cout << "Path " << pathName << " is not a directory!" << std::endl;
    };

    T *get(std::string name) const
    {
        auto it = resourceMap.find(name);

        if (it != resourceMap.end())
            return it->second;
        else
            return nullptr;
    };

    virtual void clear()
    {
        for (auto &resource : resourceMap)
            delete resource.second;

        resourceMap.clear();
    };

private:
    bool isSupported(std::string extension) const
    {
        return std::find(supportedExtensions.begin(), supportedExtensions.end(), extension) != supportedExtensions.end();
    };

private:
    std::unordered_map<std::string, T *> resourceMap;
    std::string resourceType;
    std::vector<std::string> supportedExtensions;
    std::function<T *(std::string)> createResource;
};

#endif