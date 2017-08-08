#ifndef mvcgame_linux_ApplicationBridge_hpp
#define mvcgame_linux_ApplicationBridge_hpp

#include <mvcgame/platform/IApplicationBridge.hpp>
#include <mvcgame/platform/3ds/RenderBridge.hpp>
#include <mvcgame/platform/3ds/FilesystemBridge.hpp>

namespace mvcgame {

    class ApplicationBridge : public IApplicationBridge
    {
    private:
        Application* _app;
        bool _finished;
        RenderBridge _renderBridge;
        FilesystemBridge _fsBridge;

        // os args
        int _argc;
        char** _argv;

    public:
        ApplicationBridge(int argc, char** argv);
        void run();
        void exit();
        void setApplication(Application& app);
        void showError(const std::string& error);
        IRenderBridge& getRender();
        IFilesystemBridge& getFilesystem();
    };
}

#endif