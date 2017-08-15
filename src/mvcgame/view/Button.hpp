

#ifndef mvcgame_Button_hpp
#define mvcgame_Button_hpp

#include <mvcgame/view/View.hpp>
#include <mvcgame/texture/Texture.hpp>

namespace mvcgame {

    class Button : public View
    {
	public:
		typedef std::function<void(Button*)> ClickedFunc;
		typedef std::shared_ptr<const Texture> BtnTexture;
    public:
		Button();
		Button(BtnTexture normal, BtnTexture light, BtnTexture disable);
	public:
		void setClickedFunc(ClickedFunc func);
		void setTexture(BtnTexture normal, BtnTexture light, BtnTexture disable);
		void setEnable(bool b);
	public:
		bool isEnable() const;
		bool isPressed() const;
	private:
		void setPressed(bool b);
		void drawView();
	private:
		bool _enable;
		bool _pressed;
		BtnTexture _normal;
		BtnTexture _light;
		BtnTexture _disable;
		ClickedFunc _click;
    };

}

#endif