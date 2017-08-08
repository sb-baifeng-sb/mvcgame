
#include <mvcgame/platform/vita/ApplicationBridge.hpp>
#include <mvcgame/base/Application.hpp>
#include <mvcgame/base/Geometry.hpp>
#include <mvcgame/controller/RootViewController.hpp>
#include <cassert>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/touch.h>
#include <vita2d.h>

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

    typedef struct InputContent {
    bool touch_pressed;
    SceCtrlData oldPad, newPad;
    SceTouchData oldTouch, newTouch;

    float axislx() const {
        return newPad.lx-127.5f;
    }
    float axisly() const {
        return newPad.ly-127.5f;
    }
    float axisrx() const {
        return newPad.rx-127.5f;
    }
    float axisry() const {
        return newPad.ry-127.5f;
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
            return touchx()!=otouchx() || touchy()!=otouchy();
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
    void InputProc() {
        oldPad = newPad;
        oldTouch = newTouch;
        sceCtrlPeekBufferPositive(0, &newPad, 1);
        sceTouchPeek(SCE_TOUCH_PORT_FRONT, &newTouch, 1);

        lite2d::AppContent& content = lite2d::AppContent::instance();
        TouchHolder& touch = content.getTouchHolder();
        KeyCtrlHolder& keyCtrl = content.getKeyCtrlHolder();

        int key = 0;

        for (int i = 0; i < APP_CTRL_SIZE_MAX; ++i) {
            if (isButtonPressed(keyCtrl.getKeyState(i))) {
                key = key | keyCtrl.getKeyState(i);
            }
        }
        if (key > 0) {
            keyCtrl.keyDown(key);
        }

        key = 0;

        for (int i = 0; i < APP_CTRL_SIZE_MAX; ++i) {
            if (isButtonUp(keyCtrl.getKeyState(i))) {
                key = key | keyCtrl.getKeyState(i);
            }
        }
        if (key > 0) {
            keyCtrl.keyUp(key);
        }


        if (istouch()) {
            if (!touch_pressed) {
                // first touch
                touch.touchBegin(touchx(), touchy());
            }else {
                if (istouch_moved()) {
                    // move
                    touch.touchMoved(touchx(), touchy());
                }
            }
            touch_pressed = true;
        }else {
            // end touch
            if (touch_pressed) {
                if (isotouch()) {
                    touch.touchEnded(otouchx(), otouchy());
                }else {
                    touch.touchEnded(0, 0);
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

        // 初始化控制
        sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG_WIDE);
        sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);
        sceTouchSetSamplingState(SCE_TOUCH_PORT_BACK, SCE_TOUCH_SAMPLING_STATE_START);

        while(!_finished) {
            input.InputProc();
            _app.update();
        }

        // 结束
        vita2d_fini();
        sceKernelExitProcess(0);
    }
}