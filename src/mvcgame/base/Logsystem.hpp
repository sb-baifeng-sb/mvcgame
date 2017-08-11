

#ifndef mvcgame_Logsystem_hpp
#define mvcgame_Logsystem_hpp

#include <mvcgame/platform/ILogsystemBridge.hpp>
#include <memory>

namespace mvcgame {

	class Logsystem
	{
    private:
        std::unique_ptr<ILogsystemBridge> _bridge;
	public:
        Logsystem(std::unique_ptr<ILogsystemBridge> bridge);
    public:
    	
	};
}

#endif