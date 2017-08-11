

#ifndef mvcgame_ILogsystemBridge_hpp
#define mvcgame_ILogsystemBridge_hpp

#include <string>

namespace mvcgame {

    class ILogsystemBridge
    {
    public:
        virtual ~ILogsystemBridge(){};
        virtual void debug(std::string const& s) = 0;
        virtual void error(std::string const& s) = 0;
        virtual void fatal(std::string const& s) = 0;
        virtual void info(std::string const& s) = 0;
        virtual void warn(std::string const& s) = 0;
    };

}

#endif