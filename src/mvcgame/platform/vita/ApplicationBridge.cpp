
#include <mvcgame/platform/vita/ApplicationBridge.hpp>
#include <mvcgame/base/Application.hpp>
#include <mvcgame/base/Geometry.hpp>
#include <mvcgame/controller/RootViewController.hpp>
#include <cassert>
#include <cstring>
#include <string>
#include <iostream>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/touch.h>
#include <vita2d.h>

#define lerp(value, from_max, to_max) ((((value * 10) * (to_max * 10)) / (from_max * 10)) / 10)
#define RGBA8(r,g,b,a) ((((a)&0xFF)<<24) | (((b)&0xFF)<<16) | (((g)&0xFF)<<8) | (((r)&0xFF)<<0))
#define BLACK   RGBA8(  0,   0,   0, 255)
#define WHITE   RGBA8(255, 255, 255, 255)
#define GREEN   RGBA8(  0, 255,   0, 255)
#define RED     RGBA8(255,   0,   0, 255)
#define BLUE    RGBA8(  0,   0, 255, 255)
#define PURPLE  RGBA8(255,   0, 255, 255)
#define APP_CTRL_SIZE_MAX (13)

namespace mvcgame {

    static int const SCREEN_WIDTH = 960;
    static int const SCREEN_HEIGHT = 544;

    ApplicationBridge* ApplicationBridge::_instance = NULL;

    ApplicationBridge& ApplicationBridge::getInstance()
    {
        return *_instance;
    }

    ApplicationBridge::ApplicationBridge(int argc, char** argv) :
    _app(nullptr), _finished(false), _argc(argc), _argv(argv)
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

    typedef enum {
        APP_CTRL_SELECT     = 0x000001, //!< Select button.
        APP_CTRL_START      = 0x000008, //!< Start button.
        APP_CTRL_UP         = 0x000010, //!< Up D-Pad button.
        APP_CTRL_RIGHT      = 0x000020, //!< Right D-Pad button.
        APP_CTRL_DOWN       = 0x000040, //!< Down D-Pad button.
        APP_CTRL_LEFT       = 0x000080, //!< Left D-Pad button.
        APP_CTRL_LTRIGGER   = 0x000100, //!< Left trigger.
        APP_CTRL_RTRIGGER   = 0x000200, //!< Right trigger.
        APP_CTRL_TRIANGLE   = 0x001000, //!< Triangle button.
        APP_CTRL_CIRCLE     = 0x002000, //!< Circle button.
        APP_CTRL_CROSS      = 0x004000, //!< Cross button.
        APP_CTRL_SQUARE     = 0x008000, //!< Square button.
        APP_CTRL_ANY        = 0x010000  //!< Any input intercepted.
    } APP_CTRL_TYPE;

    static APP_CTRL_TYPE keyState[] = {
        APP_CTRL_SELECT,
        APP_CTRL_START,
        APP_CTRL_UP,
        APP_CTRL_RIGHT,
        APP_CTRL_DOWN,
        APP_CTRL_LEFT,
        APP_CTRL_LTRIGGER,
        APP_CTRL_RTRIGGER,
        APP_CTRL_TRIANGLE,
        APP_CTRL_CIRCLE,
        APP_CTRL_CROSS,
        APP_CTRL_SQUARE,
        APP_CTRL_ANY
    };

	typedef struct InputContent {
		bool touch_pressed;
		SceCtrlData oldPad, newPad;
		SceTouchData oldTouch, newTouch;

		float axislx() const {
			return newPad.lx - 127.5f;
		}
		float axisly() const {
			return newPad.ly - 127.5f;
		}
		float axisrx() const {
			return newPad.rx - 127.5f;
		}
		float axisry() const {
			return newPad.ry - 127.5f;
		}
		int touchx() const {
			if (istouch()) {
				return lerp(newTouch.report[0].x, 1919, 960);
			}
			return 0;
		}
		int touchy() const {
			if (istouch()) {
				return lerp(newTouch.report[0].y, 1087, 544);
			}
			return 0;
		}
		bool istouch() const {
			return newTouch.reportNum > 0;
		}
		int otouchx() const {
			if (isotouch()) {
				return lerp(oldTouch.report[0].x, 1919, 960);
			}
			return 0;
		}
		int otouchy() const {
			if (isotouch()) {
				return lerp(oldTouch.report[0].y, 1087, 544);
			}
			return 0;
		}
		bool isotouch() const {
			return oldTouch.reportNum > 0;
		}
		bool istouch_moved() const {
			if (isotouch() && istouch()) {
				return touchx() != otouchx() || touchy() != otouchy();
			}
			return false;
		}
		bool isButtonPressed(unsigned int button) {
			if (!(oldPad.buttons & button)) {
				if (newPad.buttons & button) {
					return true;
				}
			}
			return false;
		}
		bool isButtonUp(unsigned int button) {
			if (oldPad.buttons & button) {
				if (!(newPad.buttons & button)) {
					return true;
				}
			}
			return false;
		}
        APP_CTRL_TYPE getKeyState(int index) {
            return keyState[index];
        }
		void InputProc() {
			oldPad = newPad;
			oldTouch = newTouch;
			sceCtrlPeekBufferPositive(0, &newPad, 1);
			sceTouchPeek(SCE_TOUCH_PORT_FRONT, &newTouch, 1);

			int key = 0;

			for (int i = 0; i < APP_CTRL_SIZE_MAX; ++i) {
				if (isButtonPressed(getKeyState(i))) {
					key = key | getKeyState(i);
				}
			}
			if (key > 0) {
				ApplicationBridge::keyDownProc(key);
			}

			key = 0;

			for (int i = 0; i < APP_CTRL_SIZE_MAX; ++i) {
				if (isButtonUp(getKeyState(i))) {
					key = key | getKeyState(i);
				}
			}
			if (key > 0) {
				ApplicationBridge::keyUpProc(key);
			}


			if (istouch()) {
				if (!touch_pressed) {
					// first touch
                    ApplicationBridge::touchDownProc(touchx(), touchy());
				}
				else {
					if (istouch_moved()) {
						// move
                        ApplicationBridge::touchMoveProc(touchx(), touchy());
					}
				}
				touch_pressed = true;

			} else {
				// end touch
				if (touch_pressed) {
					if (isotouch()) {
                        ApplicationBridge::touchUpProc(otouchx(), otouchy());
					}
					else {
                        ApplicationBridge::touchUpProc(0, 0);
					}
				}
				touch_pressed = false;
			}
		}
	} InputContent;

	InputContent input;

    void ApplicationBridge::run()
    {
        assert(_app);
        assert(_argv);

        // 初始化图形
        vita2d_init();
        vita2d_set_clear_color(BLACK);
        memset(&input, 0, sizeof(input));

        // 初始化控制
        sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG_WIDE);
        sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);
        sceTouchSetSamplingState(SCE_TOUCH_PORT_BACK, SCE_TOUCH_SAMPLING_STATE_START);

        // 帧率
        float dt = 0.0f;
		SceUInt64 cur_micros = 0, delta_micros = 0, last_micros = 0;
		last_micros = sceKernelGetProcessTimeWide();
		auto pgf = vita2d_load_default_pgf();

		// 测试代码
		std::ifstream file("app0:resources/hello.txt");
        std::string hello((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        while(!_finished) {
            input.InputProc();
            //_app->update();

            cur_micros = sceKernelGetProcessTimeWide();

            // display begin
			vita2d_start_drawing();
			vita2d_clear_screen();

			vita2d_pgf_draw_textf(pgf, 2, 22, WHITE, 1.0f, "FPS %.2f", (1.0f / dt));
			vita2d_pgf_draw_textf(pgf, 2, 22+20, WHITE, 1.0f, hello.c_str());

			// display end
            vita2d_end_drawing();
			vita2d_swap_buffers();

			delta_micros = cur_micros - last_micros;
			last_micros = cur_micros;
			dt = (float)delta_micros / 1000000.0f;
        }

        // 结束
        vita2d_fini();
        vita2d_free_pgf(pgf);
        sceKernelExitProcess(0);
    }

    void ApplicationBridge::keyDownProc(int key) {
    	
    }

    void ApplicationBridge::keyUpProc(int key) {

    }

    void ApplicationBridge::touchDownProc(int x, int y) {
        std::vector<Point> ptVec;
        ptVec.push_back(Point(x, SCREEN_HEIGHT - y));
        getInstance()._app->getRoot().emitTouchStart(ptVec);
    }

    void ApplicationBridge::touchMoveProc(int x, int y) {
        std::vector<Point> ptVec;
        ptVec.push_back(Point(x, SCREEN_HEIGHT - y));
        getInstance()._app->getRoot().emitTouchUpdate(ptVec);
    }

    void ApplicationBridge::touchUpProc(int x, int y) {
        std::vector<Point> ptVec;
        ptVec.push_back(Point(x, SCREEN_HEIGHT - y));
        getInstance()._app->getRoot().emitTouchEnd(ptVec);
    }

}