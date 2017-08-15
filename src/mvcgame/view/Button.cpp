
#include <mvcgame/view/Button.hpp>
#include <mvcgame/base/Geometry.hpp>
#include <mvcgame/base/Color.hpp>
#include <mvcgame/platform/IRenderBridge.hpp>
#include <assert.h>

namespace mvcgame {

	Button::Button() :_enable(true), _pressed(false), _normal(nullptr), _light(nullptr), _disable(nullptr) {

    }

	Button::Button(BtnTexture normal, BtnTexture light, BtnTexture disable) : Button() {
		setTexture(normal, light, disable);
	}

	void Button::setEnable(bool b) {
		_enable = b;
	}

	void Button::setPressed(bool b) {
		_pressed = b;
	}

	bool Button::isEnable() const {
		return _enable;
	}

	bool Button::isPressed() const {
		return _pressed;
	}

	void Button::setTexture(BtnTexture normal, BtnTexture light, BtnTexture disable) {
		assert(normal && light && disable);
		assert(normal->getWidth() == normal->getWidth() && normal->getWidth() == disable->getWidth());
		assert(normal->getHeight() == normal->getHeight() && normal->getHeight() == disable->getHeight());
		_normal = normal;
		_light = light;
		_disable = disable;
		getFrame().size = Size(normal->getWidth(), normal->getHeight());
	}

	void Button::drawView() {
		if (!_enable) {
			getBridge().drawTexture(_disable, Rect(Point(0, 0), getFrame().size), Color(255, 255, 255, 255));
			return;
		}
		if (_pressed) {
			getBridge().drawTexture(_light, Rect(Point(0, 0), getFrame().size), Color(255, 255, 255, 255));
		} else {
			getBridge().drawTexture(_normal, Rect(Point(0,0), getFrame().size), Color(255, 255, 255, 255));
		}
	}

	void Button::setClickedFunc(ClickedFunc func) {
		_click = func;
	}

}