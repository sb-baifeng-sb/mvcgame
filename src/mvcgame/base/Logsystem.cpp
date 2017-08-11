
#include <mvcgame/base/Logsystem.hpp>

namespace mvcgame {

    Logsystem::Logsystem(std::unique_ptr<ILogsystemBridge> bridge) :
    _bridge(std::move(bridge)) {

    }
    
}