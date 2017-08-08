
#include <mvcgame/platform/3ds/ApplicationBridge.hpp>
#include <mvcgame/base/Application.hpp>
#include <mvcgame/base/Geometry.hpp>
#include <mvcgame/controller/RootViewController.hpp>
#include <cassert>

namespace mvcgame {

    ApplicationBridge::ApplicationBridge(int argc, char** argv) :
    _app(nullptr), _finished(false), _argc(argc), _argv(argv)
    {
    }

    IRenderBridge& ApplicationBridge::getRender()
    {
        return _renderBridge;
    }

    IFilesystemBridge& ApplicationBridge::getFilesystem()
    {
        return _fsBridge;
    }

    void ApplicationBridge::exit()
    {
        _finished = true;
    }

    void ApplicationBridge::setApplication(Application& app)
    {
        _app = &app;
    }

    void ApplicationBridge::showError(const std::string& error)
    {
        printf("mvcgame error: %s\n", error.c_str());
    }

    void ApplicationBridge::run()
    {
        assert(_app);
        assert(_argv);
    }
}