

#include <mvcgame/platform/vita/FilesystemBridge.hpp>

#define DIR_SEP '/'

#ifdef MVCGAME_DEBUG_FILESYSTEM
#include <iostream>
#endif

namespace mvcgame {

    FilesystemBridge::FilesystemBridge()
    {

    }

    std::string FilesystemBridge::fixPath(const std::string& path)
    {
        return "";
    }

    bool FilesystemBridge::readResource(const std::string& path, std::ifstream& in)
    {
        return true;
    }

    FilesystemBridge::Paths FilesystemBridge::findResource(const std::string& name, const std::string& path)
    {
        Paths results;
        return results;
    }
}