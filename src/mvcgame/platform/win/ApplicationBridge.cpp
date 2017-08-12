
#include <mvcgame/platform/win/ApplicationBridge.hpp>
#include <mvcgame/base/Application.hpp>
#include <mvcgame/base/Geometry.hpp>
#include <cassert>
#include <glut.h>

namespace mvcgame {

	ApplicationBridge* ApplicationBridge::_instance = NULL;

	ApplicationBridge& ApplicationBridge::getInstance()
	{
		return *_instance;
	}

	ApplicationBridge::ApplicationBridge(int argc, char** argv) :_app(nullptr), _argc(argc), _argv(argv)
	{
		_instance = this;
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
		::exit(0);
	}

	void ApplicationBridge::setApplication(Application& app)
	{
		_app = &app;
	}

	void ApplicationBridge::showError(const std::string& error)
	{
	}

	void OnTimer(int value)
	{
		glutPostRedisplay();
		glutTimerFunc(16, OnTimer, 1);
	}

	static int const SCREEN_WIDTH = 960;
	static int const SCREEN_HEIGHT = 544;

	void ApplicationBridge::run()
	{
		assert(_app);
		assert(_argv);
		glutInit(&_argc, _argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		glutInitWindowPosition(200, 100);
		glutCreateWindow("Lite2D");

		glutTimerFunc(16, OnTimer, 1);
		glutDisplayFunc([]() {
			ApplicationBridge::glDisplay();
		});
		glutReshapeFunc([](int w, int h) {
			ApplicationBridge::glReshape(w, h);
		});
		glutKeyboardFunc([](unsigned char key, int x, int y) {
			ApplicationBridge::glInputProc(key, x, y);
		});
		glutMouseFunc([](int button, int state, int x, int y) {
			ApplicationBridge::glMouseProc(button, state, x, y);
		});
		glutMotionFunc([](int x, int y) {
			ApplicationBridge::glmouseMoveProc(x, y);
		});
		glutMainLoop();
	}

	void ApplicationBridge::glReshape(int w, int h)
	{
		glViewport(0, 0, (GLsizei)w, (GLsizei)h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void ApplicationBridge::glInputProc(unsigned char key, int x, int y)
	{
		switch (key) {
		case 27:
			getInstance().exit();
			break;
		default:
			break;
		}
	}

	static bool mouseDown = false;

	void ApplicationBridge::glMouseProc(int button, int state, int x, int y)
	{
		if (GLUT_LEFT_BUTTON == button) {
			std::vector<Point> ptVec;
			ptVec.push_back(Point(x, SCREEN_HEIGHT - y));
			switch (state) {
			case GLUT_DOWN:
				mouseDown = true;
				getInstance()._app->getRoot().emitTouchStart(ptVec);
				break;
			case GLUT_UP:
				mouseDown = false;
				getInstance()._app->getRoot().emitTouchEnd(ptVec);
				break;
			default:
				break;
			}
			//printf("鼠标%s: x:%d, y:%d\n", state == GLUT_DOWN ? "按下" : "弹起", x, y);
		}
	}

	void ApplicationBridge::glmouseMoveProc(int x, int y)
	{
		if (!mouseDown) {
			return;
		}
		std::vector<Point> ptVec;
		ptVec.push_back(Point(x, SCREEN_HEIGHT - y));
		getInstance()._app->getRoot().emitTouchUpdate(ptVec);
		//printf("鼠标移动: x:%d, y:%d\n", x, y);
	}

	void ApplicationBridge::glDisplay()
	{
		getInstance()._app->update();
	}
}
