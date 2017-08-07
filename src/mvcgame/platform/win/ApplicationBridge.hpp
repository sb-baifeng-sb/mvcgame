#ifndef mvcgame_win_ApplicationBridge_hpp
#define mvcgame_win_ApplicationBridge_hpp

#include <mvcgame/platform/IApplicationBridge.hpp>
#include <mvcgame/platform/gl/RenderBridge.hpp>
#include <mvcgame/platform/win/FilesystemBridge.hpp>

namespace mvcgame {

    class ApplicationBridge : public IApplicationBridge
    {
    private:
        Application* _app;
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

	public:
		static void glReshape(int w, int h);
		static void glInputProc(unsigned char key, int x, int y);
		static void glMouseProc(int button, int state, int x, int y);
		static void glmouseMoveProc(int x, int w);
		static void glDisplay();
	private:
		static ApplicationBridge* _instance;
		static ApplicationBridge& getInstance();
    };
}

#endif